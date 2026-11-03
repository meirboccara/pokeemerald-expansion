// KJH: wild packs in battle (docs/PACKS.md in the KJH repo, rules in src/kjh_pack_rules.c).
//
// 1 random wild Pokemon in 20 leads a pack: a few levels higher, perfect IVs, harder to catch, more Exp., and a
// gold healthbox with a crown. The wild Pokemon met first is the leader (party slot 0). In the levels-free game
// (LV-15) the odds are 1 in 40 with a Leader's own IVs, a helper can be a Leader too, and 1 wild Pokemon in 100 is
// an Alpha instead: it fights alone, with a red healthbox and an α.
//
// Before the turn's moves, the wild Pokemon met first may spend its turn calling for help: a leader often, any other
// wild Pokemon rarely. A helper of the same species joins the wild party (slots 1..4, so 5 at most). The first one
// turns the battle into a double battle: the screen fades out and is rebuilt in the double layout (the menus'
// reshow path), the helper comes into the right slot and the player's first healthy Pokemon that isn't fighting
// steps in next to theirs. Later helpers take a free wild slot, or wait for one: the engine's fainted-Pokemon
// replacement brings them in, like a trainer's next Pokemon. Expansion's own rules for balls in a double battle
// apply: no ball while two wild Pokemon are out, and it goes to the one left.
#include "global.h"
#include "battle.h"
#include "battle_controllers.h"
#include "battle_interface.h"
#include "battle_scripts.h"
#include "battle_setup.h"
#include "kjh_hidden_ability.h"
#include "kjh_levelless.h"
#include "kjh_mega.h"
#include "kjh_pack.h"
#include "kjh_team_level.h"
#include "ow_abilities.h"
#include "palette.h"
#include "party_menu.h"
#include "pokemon.h"
#include "random.h"
#include "reshow_battle_screen.h"
#include "safari_zone.h"
#include "sprite.h"
#include "util.h"
#include "window.h"
#include "constants/characters.h"
#include "constants/kjh_pack.h"
#include "constants/rgb.h"

#ifdef KJH_DEBUG_WARP
// Harness (kjh_tools/test/emu_expansion_eng6.py in the KJH repo): 1 at 0x0203FF30 makes every wild Pokemon that
// can lead a pack a leader that calls for help every turn (from the first), and someone always answers; 2 does the
// same, and in the levels-free game every helper is a Leader too (emu_expansion_lv15.py).
#define DEBUG_PACK (*(vu8 *)0x0203FF30)
// Harness (emu_expansion_lv15.py, LV-15): 1 at 0x0203FF50 makes every wild Pokemon that can be one an Alpha.
#define DEBUG_ALPHA (*(vu8 *)0x0203FF50)
#else
#define DEBUG_PACK 0
#define DEBUG_ALPHA 0
#endif
#define DEBUG_PACK_HELPER_LEADERS 2 // DEBUG_PACK's value that makes every helper a Leader too

#define PACK_FLAG_ACTIVE 1 // this wild battle can grow into a pack
#define PACK_FLAG_LEADER 2 // the wild Pokemon leads a pack
#define PACK_FLAG_DOUBLE 4 // a helper came: it is a double battle now
#define PACK_FLAG_ALPHA  8 // the wild Pokemon is an Alpha (LV-15): never a pack

#define ALPHA_TINT_COEFF 3 // how red an Alpha's sprite is (BlendPalette, 0-16)

// The battlers, once it is a double battle (fixed outside link battles)
#define PLAYER_LEFT  B_BATTLER_0
#define WILD_LEFT    B_BATTLER_1
#define PLAYER_RIGHT B_BATTLER_2
#define WILD_RIGHT   B_BATTLER_3
#define NO_WILD_SLOT MAX_BATTLERS_COUNT

// This battle's pack, past the leader roll
struct PackBattle
{
    u8 helpers;     // helpers that answered (wild party slots 1..KJH_PACK_MAX_HELPERS)
    u8 turnIdx;     // turn-order index while this turn's calls run
    u8 step;        // KJH_PACK_OP_TO_DOUBLE's step
    u8 partner;     // the player's party slot that steps in, or KJH_PACK_NO_PARTNER
    u16 callsTurn;  // the turn (gBattleTurnCounter) turnIdx and callsDone are for
    bool8 callsDone; // this turn's calls are done (RunTurnActionsFunctions comes back to the hook)
    u8 helperLeaders; // helpers that are Leaders too (LV-15)
};

// The wild Pokemon just made by CreateWildMon, until the battle starts
EWRAM_DATA static u8 sPackNextEncounter = 0;
// This battle's (PACK_FLAG_*)
EWRAM_DATA static u8 sPackBattleFlags = 0;
EWRAM_DATA static struct PackBattle sPack = {0};

u32 KJH_PackWildEncounterLevel(enum Species species, u32 level)
{
    sPackNextEncounter = 0;
    // The Safari Zone and the Pokemon Tower's ghosts make their wild Pokemon here too, but never have packs
    if (!KJH_PackSpeciesAllowed(species) || GetSafariZoneFlag()
     || CheckSilphScopeInPokemonTower(gSaveBlock1Ptr->location.mapGroup, gSaveBlock1Ptr->location.mapNum))
    {
        return level;
    }

    // LV-15: in the levels-free game, an Alpha fights alone. Outcome 0 is an Alpha, so a test that doesn't set the tag
    // never meets one.
    if (KJH_IsLevelsFree() && !DEBUG_PACK
     && (DEBUG_ALPHA || RandomWeighted(RNG_KJH_ALPHA, 1, KJH_ALPHA_ODDS - 1) == 0))
    {
        sPackNextEncounter = PACK_FLAG_ALPHA;
        return KJH_AlphaLevel(level);
    }

    sPackNextEncounter = PACK_FLAG_ACTIVE;
    // Outcome 0 leads, so a test that doesn't set RNG_KJH_PACK_LEADER (its default is the last outcome) never meets one
    u32 odds = KJH_IsLevelsFree() ? KJH_LEVELLESS_LEADER_ODDS : KJH_PACK_LEADER_ODDS;
    if (!DEBUG_PACK && RandomWeighted(RNG_KJH_PACK_LEADER, 1, odds - 1) != 0) return level;

    sPackNextEncounter |= PACK_FLAG_LEADER;
    return KJH_PackLeaderLevel(level);
}

static void SetAllIvs(struct Pokemon *mon, u32 iv)
{
    for (enum Stat stat = STAT_HP; stat < NUM_STATS; stat++)
    {
        SetMonData(mon, MON_DATA_HP_IV + stat, &iv);
    }
}

// ENG-6's leader has perfect IVs; LV-15's (levels-free game) its own, with the tier mark
static void MakeLeader(struct Pokemon *mon)
{
    u8 ivs[NUM_STATS];
    enum Stat perfect1, perfect2;
    enum KjhTierMark tierMark = KJH_TIER_LEADER;

    if (!KJH_IsLevelsFree())
    {
        SetAllIvs(mon, KJH_PACK_LEADER_IV);
        CalculateMonStats(mon);
        return;
    }

    for (enum Stat stat = STAT_HP; stat < NUM_STATS; stat++)
    {
        ivs[stat] = GetMonData(mon, MON_DATA_HP_IV + stat);
    }

    perfect1 = RandomUniform(RNG_KJH_LEADER_IVS, 0, NUM_STATS - 1);
    perfect2 = (perfect1 + 1 + RandomUniform(RNG_KJH_LEADER_IVS, 0, NUM_STATS - 2)) % NUM_STATS;
    KJH_LeaderIvs(ivs, perfect1, perfect2);
    for (enum Stat stat = STAT_HP; stat < NUM_STATS; stat++)
    {
        u32 iv = ivs[stat];

        SetMonData(mon, MON_DATA_HP_IV + stat, &iv);
    }

    SetMonData(mon, MON_DATA_TIER_MARK, &tierMark);
    CalculateMonStats(mon);
}

static void MakeAlpha(struct Pokemon *mon)
{
    enum KjhTierMark tierMark = KJH_TIER_ALPHA;

    SetAllIvs(mon, MAX_PER_STAT_IVS);
    SetMonData(mon, MON_DATA_TIER_MARK, &tierMark);
    CalculateMonStats(mon);
}

void KJH_PackFinishWildMon(struct Pokemon *mon)
{
    if (sPackNextEncounter & PACK_FLAG_ALPHA)
    {
        MakeAlpha(mon);
        KJH_GiveAlphaMegaStone(mon); // LV-22: a Mega-capable Alpha holds its stone, if the bracelet works here
    }
    else if (sPackNextEncounter & PACK_FLAG_LEADER)
    {
        MakeLeader(mon);
    }
}

void KJH_PackClearNextEncounter(void)
{
    sPackNextEncounter = 0;
}

void KJH_PackSetNextEncounter(bool32 leader)
{
    sPackNextEncounter = PACK_FLAG_ACTIVE | (leader ? PACK_FLAG_LEADER : 0);
}

void KJH_PackSetNextEncounterAlpha(void)
{
    sPackNextEncounter = PACK_FLAG_ALPHA;
}

bool32 KJH_PackIsNextEncounterAlpha(void)
{
    return (sPackNextEncounter & PACK_FLAG_ALPHA) != 0;
}

void KJH_PackMakeScriptedAlpha(struct Pokemon *mon)
{
    MakeAlpha(mon);
    sPackNextEncounter = PACK_FLAG_ALPHA;
}

void KJH_MakeAlwaysAlpha(struct Pokemon *mon, enum KjhJoinWay way)
{
    enum Species species = GetMonData(mon, MON_DATA_SPECIES);

    if (!KJH_IsLevelsFree() || GetMonData(mon, MON_DATA_IS_EGG)) return;

    if (KJH_IsLegendarySpecies(species) || (way == KJH_JOIN_GIVEN && KJH_IsStarterSpecies(species)))
    {
        MakeAlpha(mon);
    }
}

void KJH_PackBattleStart(void)
{
    // Only a battle with no battle type flags: a plain random wild battle or a plain scripted one (LV-20's Mt. Moon
    // guardian, made an Alpha by KJH_PackMakeScriptedAlpha), not a trainer, safari, ghost, roamer or legendary battle
    // nor one of expansion's double wild battles. A recorded one (the test runner's) plays the same.
    sPackBattleFlags = (gBattleTypeFlags & ~(BATTLE_TYPE_IS_MASTER | BATTLE_TYPE_RECORDED)) == 0 ? sPackNextEncounter : 0;
    sPackNextEncounter = 0;
    sPack = (struct PackBattle) {.partner = KJH_PACK_NO_PARTNER};

    // The healthboxes and the wild sprite were drawn before the battle knew it had a leader or an Alpha
    if (KJH_PackIsLeaderBattle() || KJH_PackIsAlphaBattle())
    {
        KJH_PackDecorateHealthbox(gHealthboxSpriteIds[WILD_LEFT], WILD_LEFT);
        KJH_PackTintAlpha(WILD_LEFT);
    }
}

bool32 KJH_PackIsLeaderBattle(void)
{
    return (sPackBattleFlags & PACK_FLAG_LEADER) != 0;
}

bool32 KJH_PackIsAlphaBattle(void)
{
    return (sPackBattleFlags & PACK_FLAG_ALPHA) != 0;
}

bool32 KJH_PackIsAlpha(enum BattlerId battler)
{
    return KJH_PackIsAlphaBattle() && GetBattlerSide(battler) == B_SIDE_OPPONENT && gBattlerPartyIndexes[battler] == 0;
}

// As expansion tints a Dynamax Pokemon: blend the battler's sprite palette, and keep it as the unfaded one
void KJH_PackTintAlpha(enum BattlerId battler)
{
    u32 paletteOffset = OBJ_PLTT_ID(battler);

    if (!KJH_PackIsAlpha(battler)) return;

    BlendPalette(paletteOffset, 16, ALPHA_TINT_COEFF, RGB(31, 2, 2));
    CpuCopy32(gPlttBufferFaded + paletteOffset, gPlttBufferUnfaded + paletteOffset, PLTT_SIZEOF(16));
}

enum KjhPackRole KJH_PackRole(enum BattlerId battler)
{
    if (!KJH_PackIsLeaderBattle() || GetBattlerSide(battler) != B_SIDE_OPPONENT) return KJH_PACK_ROLE_NONE;
    // The leader is the wild Pokemon met first; helpers fill the wild party slots after it
    return gBattlerPartyIndexes[battler] == 0 ? KJH_PACK_ROLE_LEADER : KJH_PACK_ROLE_LEADER_HELPER;
}

bool32 KJH_PackIsLeader(enum BattlerId battler)
{
    struct Pokemon *mon = GetBattlerMon(battler);

    if (KJH_PackRole(battler) == KJH_PACK_ROLE_LEADER) return TRUE;

    // LV-15: a helper that is a Leader too
    return KJH_PackIsLeaderBattle() && KJH_IsLevelsFree() && GetBattlerSide(battler) == B_SIDE_OPPONENT
        && GetMonData(mon, MON_DATA_TIER_MARK) == KJH_TIER_LEADER;
}

u32 KJH_PackBattlerCatchRate(u32 catchRate, enum BattlerId battler)
{
    if (KJH_PackIsAlpha(battler)) return max(catchRate / KJH_ALPHA_CATCH_DIVISOR, 1);

    return KJH_PackCatchRate(catchRate, KJH_PackIsLeader(battler));
}

bool32 KJH_PackIsHelperSendOut(enum BattlerId battler)
{
    return (sPackBattleFlags & PACK_FLAG_DOUBLE) && GetBattlerSide(battler) == B_SIDE_OPPONENT;
}

// ---------------------------------------------------------------- calling for help

u32 KJH_PackHelpers(void)
{
    return sPack.helpers;
}

// The wild slot a helper can come into now, or NO_WILD_SLOT when both are taken. In a single battle it is the right
// slot, which opens when the battle turns into a double battle.
static enum BattlerId FreeWildSlot(void)
{
    if (!IsDoubleBattle()) return WILD_RIGHT;
    if (!IsBattlerAlive(WILD_LEFT)) return WILD_LEFT;
    if (!IsBattlerAlive(WILD_RIGHT)) return WILD_RIGHT;
    return NO_WILD_SLOT;
}

// Only the wild Pokemon met first calls, while it can act
static bool32 CanCall(enum BattlerId battler)
{
    return !IsOnPlayerSide(battler)
        && gBattlerPartyIndexes[battler] == 0
        && IsBattlerAlive(battler)
        && !(gBattleMons[battler].status1 & (STATUS1_SLEEP | STATUS1_FREEZE))
        && !gBattleMons[battler].volatiles.multipleTurns
        && !gBattleMons[battler].volatiles.rechargeTimer;
}

// The player throws a ball, uses an item or switches this turn: no call, so a ball chosen against one wild Pokemon
// isn't thrown into a double battle, and the Pokemon coming in isn't also picked as the partner
static bool32 PlayerChoseItemOrSwitch(void)
{
    for (enum BattlerId battler = 0; battler < gBattlersCount; battler++)
    {
        if (IsOnPlayerSide(battler)
         && (gChosenActionByBattler[battler] == B_ACTION_USE_ITEM || gChosenActionByBattler[battler] == B_ACTION_SWITCH))
        {
            return TRUE;
        }
    }
    return FALSE;
}

// Outcome 0 calls (answers), so a test that doesn't set the tag (its default is the last outcome) never sees a call
static bool32 WantsToCall(enum BattlerId battler)
{
    u32 chance;

    if (DEBUG_PACK) return sPack.helpers < KJH_PACK_MAX_HELPERS;

    chance = KJH_PackCallChance(KJH_PackIsLeaderBattle(), sPack.helpers, FreeWildSlot() != NO_WILD_SLOT,
                                gBattleResults.battleTurnCounter == 0, gBattleMons[battler].hp, gBattleMons[battler].maxHP);
    return chance != 0 && RandomWeighted(RNG_KJH_PACK_CALL, chance, 100 - chance) == 0;
}

static bool32 CallAnswered(void)
{
    u32 chance = KJH_PackAnswerChance(KJH_PackIsLeaderBattle());

    return DEBUG_PACK || RandomWeighted(RNG_KJH_PACK_ANSWER, chance, 100 - chance) == 0;
}

bool32 KJH_TryPackCallsBeforeTurn(void)
{
    if (!(sPackBattleFlags & PACK_FLAG_ACTIVE)) return FALSE;

    if (sPack.callsTurn != gBattleTurnCounter)
    {
        sPack.callsTurn = gBattleTurnCounter;
        sPack.turnIdx = 0;
        sPack.callsDone = PlayerChoseItemOrSwitch();
    }
    if (sPack.callsDone) return FALSE;

    while (sPack.turnIdx < gBattlersCount)
    {
        u32 idx = sPack.turnIdx++;
        enum BattlerId battler = gBattlerByTurnOrder[idx];

        if (gActionsByTurnOrder[idx] != B_ACTION_USE_MOVE || !CanCall(battler) || !WantsToCall(battler)) continue;

        // The call is this Pokemon's turn. This turn's actions have started, so the current one is read again. The
        // script returns here (end3), then the turn goes on with the next action.
        gActionsByTurnOrder[idx] = B_ACTION_NOTHING_FAINTED;
        gCurrentActionFuncId = gActionsByTurnOrder[gCurrentTurnActionNumber];
        gChosenMoveByBattler[battler] = MOVE_NONE;
        gCurrentMove = MOVE_NONE;
        gBattlerAttacker = gBattleScripting.battler = battler;
        BattleScriptPushCursorAndCallback(BattleScript_KjhPackCall);
        return TRUE;
    }

    sPack.callsDone = TRUE;
    return FALSE;
}

// LV-15: a helper that answers a Leader is a Leader too, now and then (outcome 0, so tests never see one by default)
static bool32 HelperIsLeader(void)
{
    return KJH_IsLevelsFree() && KJH_PackIsLeaderBattle() && sPack.helperLeaders < KJH_PACK_MAX_HELPER_LEADERS
        && (DEBUG_PACK == DEBUG_PACK_HELPER_LEADERS
            || RandomWeighted(RNG_KJH_PACK_HELPER_LEADER, KJH_PACK_HELPER_LEADER_CHANCE,
                              100 - KJH_PACK_HELPER_LEADER_CHANCE) == 0);
}

// A helper of the caller's species joins the wild party
static void AddHelper(void)
{
    struct Pokemon *party = gParties[B_TRAINER_OPPONENT_A];
    struct Pokemon *helper = &party[++sPack.helpers];
    enum Species species = GetMonData(&party[0], MON_DATA_SPECIES);
    bool32 leader = HelperIsLeader();
    u32 packLevel = GetMonData(&party[0], MON_DATA_LEVEL);
    u32 drop = RandomUniform(RNG_KJH_PACK_HELPER_LEVEL, 0, KJH_PACK_HELPER_MAX_LEVEL_DROP);
    // A Leader that answers is at the pack Leader's level
    u32 level = leader ? packLevel : KJH_PackHelperLevel(packLevel, KJH_PackIsLeaderBattle(), drop);
    u32 personality = GetMonPersonality(species, GetSynchronizedGender(WILDMON_ORIGIN, species),
                                        GetSynchronizedNature(WILDMON_ORIGIN, species), RANDOM_UNOWN_LETTER);

    CreateMonWithIVs(helper, species, level, personality, OTID_STRUCT_PLAYER_ID, USE_RANDOM_IVS);
    GiveMonInitialMoveset(helper);
    KJH_RollWildHiddenAbility(helper); // like any wild Pokemon
    if (leader)
    {
        sPack.helperLeaders++;
        MakeLeader(helper);
    }

    CalculateEnemyPartyCount();
    PREPARE_SPECIES_BUFFER(gBattleTextBuff1, species);
}

static void SetNewBattlerController(enum BattlerId battler, enum BattlerId sameAs)
{
    switch (gBattlerBattleController[sameAs])
    {
    case BATTLE_CONTROLLER_RECORDED_PLAYER:
        SetControllerToRecordedPlayer(battler);
        break;
    case BATTLE_CONTROLLER_RECORDED_OPPONENT:
        SetControllerToRecordedOpponent(battler);
        break;
    case BATTLE_CONTROLLER_OPPONENT:
        SetControllerToOpponent(battler);
        break;
    default:
        SetControllerToPlayer(battler);
        break;
    }
}

// The battle started single, so nothing was ever set for this battler. It stays off the field (notOnField: the
// rebuilt screen doesn't draw it) until it is sent out.
static void ClearNewBattler(enum BattlerId battler, enum BattlerId sameAs)
{
    memset(&gBattleMons[battler], 0, sizeof(gBattleMons[battler]));
    // An empty name: with no partner nothing fills this battler, and the end of the battle copies its name
    gBattleMons[battler].nickname[0] = EOS;
    for (u32 i = 0; i < NUM_BATTLE_STATS; i++)
    {
        gBattleMons[battler].statStages[i] = DEFAULT_STAT_STAGE;
    }
    memset(&gProtectStructs[battler], 0, sizeof(gProtectStructs[battler]));
    memset(&gSpecialStatuses[battler], 0, sizeof(gSpecialStatuses[battler]));
    memset(&gBattleSpritesDataPtr->battlerData[battler], 0, sizeof(gBattleSpritesDataPtr->battlerData[battler]));
    memset(&gBattleSpritesDataPtr->healthBoxesData[battler], 0, sizeof(gBattleSpritesDataPtr->healthBoxesData[battler]));
    gChosenMoveByBattler[battler] = MOVE_NONE;
    gChosenActionByBattler[battler] = B_ACTION_NOTHING_FAINTED;
    gBattleStruct->monToSwitchIntoId[battler] = PARTY_SIZE;
    gBattleStruct->battlerState[battler].notOnField = TRUE;
    SetNewBattlerController(battler, sameAs);
}

// The data side of turning a single wild battle into a double one. Battlers 2 (player right) and 3 (wild right)
// start absent; the call script then sends the helper and the partner in.
static void SetUpDoubleBattle(void)
{
    u32 fighting = gBattlerPartyIndexes[PLAYER_LEFT];
    bool8 usable[PARTY_SIZE];

    for (u32 i = 0; i < PARTY_SIZE; i++)
    {
        usable[i] = IsValidForBattle(&gParties[B_TRAINER_PLAYER][i]);
    }
    sPack.partner = KJH_PackPartnerSlot(usable, fighting);

    gBattleTypeFlags |= BATTLE_TYPE_DOUBLE;
    gBattlersCount = MAX_BATTLERS_COUNT;
    gBattlerPositions[PLAYER_RIGHT] = B_POSITION_PLAYER_RIGHT;
    gBattlerPositions[WILD_RIGHT] = B_POSITION_OPPONENT_RIGHT;
    ClearNewBattler(PLAYER_RIGHT, PLAYER_LEFT);
    ClearNewBattler(WILD_RIGHT, WILD_LEFT);
    // No partner: the right slot points at a fainted or empty party slot, so nothing is drawn there
    gBattlerPartyIndexes[PLAYER_RIGHT] = sPack.partner != KJH_PACK_NO_PARTNER ? sPack.partner : KJH_PackEmptySlot(usable, fighting);
    // The helper comes in from an empty party slot (helpers use slots 1..4)
    gBattlerPartyIndexes[WILD_RIGHT] = PARTY_SIZE - 1;
    gAbsentBattlerFlags |= (1u << PLAYER_RIGHT) | (1u << WILD_RIGHT);

    // This turn's order was made for two battlers: the new ones do nothing this turn
    gBattlerByTurnOrder[2] = PLAYER_RIGHT;
    gBattlerByTurnOrder[3] = WILD_RIGHT;
    gActionsByTurnOrder[2] = B_ACTION_NOTHING_FAINTED;
    gActionsByTurnOrder[3] = B_ACTION_NOTHING_FAINTED;

    // A double battle lists both fighters first in the party menu
    KJH_PackPutPartnerSecond(gBattleStruct->battlerPartyOrders[PLAYER_LEFT], gBattlerPartyIndexes[PLAYER_RIGHT]);
    memcpy(gBattleStruct->battlerPartyOrders[PLAYER_RIGHT], gBattleStruct->battlerPartyOrders[PLAYER_LEFT],
           sizeof(gBattleStruct->battlerPartyOrders[0]));
    BufferBattlePartyCurrentOrderBySide(WILD_LEFT, 0);
    BufferBattlePartyCurrentOrderBySide(WILD_RIGHT, 0);

    sPackBattleFlags |= PACK_FLAG_DOUBLE;
}

// Fade out, switch to a double battle, rebuild the screen in the double layout and wait for it to fade back in.
// While the screen is rebuilt the battle's main callback doesn't run, so this command waits on the same script
// line. Returns TRUE when done.
static bool32 TurnIntoDoubleBattle(void)
{
    switch (sPack.step)
    {
    case 0:
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
        sPack.step++;
        return FALSE;
    case 1:
        if (gPaletteFade.active) return FALSE;
        SetUpDoubleBattle();
        FreeAllWindowBuffers(); // the rebuild makes the battle windows again, as after the bag or party menu
        ReshowBattleScreenAfterMenu();
        sPack.step++;
        return FALSE;
    default:
        if (gMain.callback2 != BattleMainCB2 || gPaletteFade.active) return FALSE;
        sPack.step = 0;
        return TRUE;
    }
}

// The battler is sent out next: switchindataupdate expects it present (switchinanim would clear the flag later)
static void SetSendOutBattler(enum BattlerId battler, u32 partySlot)
{
    gBattleScripting.battler = gBattlerFainted = battler;
    gBattleStruct->monToSwitchIntoId[battler] = partySlot;
    gAbsentBattlerFlags &= ~(1u << battler);
}

// The kjhpack macro's bytes (asm/macros/battle_script.inc), laid out as battle_script_commands.c's NATIVE_ARGS
struct __attribute__((packed)) KjhPackArgs
{
    u8 opcode;
    void (*func)(void);
    u8 op;
    const u8 *jumpInstr;
    const u8 nextInstr[0];
};

// kjhpack op, jumpInstr: one step of BattleScript_KjhPackCall, op is KJH_PACK_OP_* (include/constants/kjh_pack.h)
void BS_KjhPack(void)
{
    const struct KjhPackArgs *cmd = (const void *)gBattlescriptCurrInstr;
    bool32 jump = FALSE;

    if (gBattleControllerExecFlags) return;

    switch (cmd->op)
    {
    case KJH_PACK_OP_ANSWER:
        jump = !CallAnswered();
        if (!jump)
        {
            AddHelper();
        }
        break;
    case KJH_PACK_OP_JUMP_IF_WAITING:
        jump = FreeWildSlot() == NO_WILD_SLOT;
        break;
    case KJH_PACK_OP_JUMP_IF_DOUBLE:
        jump = IsDoubleBattle();
        break;
    case KJH_PACK_OP_TO_DOUBLE:
        if (!TurnIntoDoubleBattle()) return;
        break;
    case KJH_PACK_OP_PREPARE_HELPER:
        SetSendOutBattler(FreeWildSlot(), sPack.helpers);
        break;
    case KJH_PACK_OP_PREPARE_PARTNER:
        jump = sPack.partner == KJH_PACK_NO_PARTNER;
        if (!jump)
        {
            SetSendOutBattler(PLAYER_RIGHT, sPack.partner);
        }
        break;
    }
    gBattlescriptCurrInstr = jump ? cmd->jumpInstr : cmd->nextInstr;
}

// ---------------------------------------------------------------- the leader's and the Alpha's healthboxes
// A Leader stands out from its helpers: its healthbox uses a copy of the healthbox palette where the text colors
// are gold (its name and level), and a small gold crown sits on the box. An Alpha's (LV-15) is red, with an α. Both
// go when another Pokemon takes its place.

#define TAG_PACK_LEADER 0x4B08 // the crown's tiles and the gold healthbox palette
#define TAG_ALPHA       0x4B09 // the α's tiles and the red healthbox palette
#define MARK_X (-22)           // from the healthbox's main (left) sprite: on its top edge, over the name
#define MARK_Y (-14)

// Healthbox palette entries the text is drawn with (sHealthBoxTextColor, src/battle_interface.c)
#define HEALTHBOX_TEXT   1
#define HEALTHBOX_SHADOW 3

// Drawn with the healthbox palette: the crown's outline is the text color (1), then the healthbox's yellow (9) and
// pink (10); the α is the text color only
static const u32 sCrown_Gfx[] = INCGFX_U32("graphics/battle_interface/kjh_pack_crown.png", ".4bpp");
static const u32 sAlphaMark_Gfx[] = INCGFX_U32("graphics/battle_interface/kjh_alpha_mark.png", ".4bpp");

static const struct SpriteSheet sSpriteSheet_Crown = {sCrown_Gfx, sizeof(sCrown_Gfx), TAG_PACK_LEADER};
static const struct SpriteSheet sSpriteSheet_AlphaMark = {sAlphaMark_Gfx, sizeof(sAlphaMark_Gfx), TAG_ALPHA};

static const struct OamData sOamData_Mark =
{
    .shape = SPRITE_SHAPE(8x8),
    .size = SPRITE_SIZE(8x8),
    .priority = 1,
};

static void SpriteCB_Mark(struct Sprite *sprite);

static const struct SpriteTemplate sSpriteTemplate_Crown =
{
    .tileTag = TAG_PACK_LEADER,
    .paletteTag = TAG_PACK_LEADER,
    .oam = &sOamData_Mark,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_Mark,
};

static const struct SpriteTemplate sSpriteTemplate_AlphaMark =
{
    .tileTag = TAG_ALPHA,
    .paletteTag = TAG_ALPHA,
    .oam = &sOamData_Mark,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_Mark,
};

#define tHealthbox data[0]
#define tBattler   data[1]
#define tPartyIdx  data[2]

// A healthbox palette with gold (or red) text, loaded the first time. 0xFF: no free palette (the box stays as it is).
static u32 MarkPaletteNum(u32 tag)
{
    u32 paletteNum = IndexOfSpritePaletteTag(tag);
    u32 healthboxPal = IndexOfSpritePaletteTag(TAG_HEALTHBOX_PAL);
    u16 colors[16];
    struct SpritePalette palette = {colors, tag};

    if (paletteNum != 0xFF || healthboxPal == 0xFF) return paletteNum;

    CpuCopy16(&gPlttBufferUnfaded[OBJ_PLTT_ID(healthboxPal)], colors, sizeof(colors));
    if (tag == TAG_ALPHA)
    {
        colors[HEALTHBOX_TEXT] = RGB(23, 2, 2);     // dark red
        colors[HEALTHBOX_SHADOW] = RGB(31, 18, 16); // light red
    }
    else
    {
        colors[HEALTHBOX_TEXT] = RGB(23, 15, 0);    // dark gold
        colors[HEALTHBOX_SHADOW] = RGB(31, 26, 12); // light gold
    }

    return LoadSpritePalette(&palette);
}

static void SetHealthboxPalette(u32 healthboxSpriteId, u32 paletteNum)
{
    gSprites[healthboxSpriteId].oam.paletteNum = paletteNum;
    gSprites[gSprites[healthboxSpriteId].oam.affineParam].oam.paletteNum = paletteNum; // the right half
}

static bool32 IsMark(struct Sprite *sprite, u32 tag)
{
    return sprite->inUse && sprite->callback == SpriteCB_Mark && sprite->template->tileTag == tag;
}

static bool32 IsMarkInUse(u32 tag)
{
    for (u32 i = 0; i < MAX_SPRITES; i++)
    {
        if (IsMark(&gSprites[i], tag)) return TRUE;
    }

    return FALSE;
}

// The healthbox goes back to the usual palette; the gold (or red) one is freed once no other box uses it
static void RemoveMarkPalette(u32 healthboxSpriteId, u32 tag)
{
    u32 markPal = IndexOfSpritePaletteTag(tag);

    if (markPal == 0xFF) return;

    if (gSprites[healthboxSpriteId].inUse && gSprites[healthboxSpriteId].oam.paletteNum == markPal)
    {
        SetHealthboxPalette(healthboxSpriteId, IndexOfSpritePaletteTag(TAG_HEALTHBOX_PAL));
    }

    for (u32 i = 0; i < MAX_SPRITES; i++)
    {
        // Another healthbox still uses it
        if (gSprites[i].inUse && gSprites[i].oam.paletteNum == markPal && gSprites[i].callback != SpriteCB_Mark) return;
    }

    if (!IsMarkInUse(tag))
    {
        FreeSpritePaletteByTag(tag);
    }
}

static void DestroyMark(struct Sprite *sprite)
{
    u32 tag = sprite->template->tileTag, healthboxSpriteId = sprite->tHealthbox;

    DestroySprite(sprite);
    RemoveMarkPalette(healthboxSpriteId, tag);
    if (!IsMarkInUse(tag))
    {
        FreeSpriteTilesByTag(tag);
    }
}

// Sits on its Pokemon's healthbox, and goes once another Pokemon is in its slot. Only battle globals that outlive the
// battle are read here: the last frames of a battle run after its resources are freed.
static void SpriteCB_Mark(struct Sprite *sprite)
{
    struct Sprite *healthbox = &gSprites[sprite->tHealthbox];

    if (!healthbox->inUse || gHealthboxSpriteIds[sprite->tBattler] != sprite->tHealthbox
     || gBattlerPartyIndexes[sprite->tBattler] != sprite->tPartyIdx)
    {
        DestroyMark(sprite);
        return;
    }

    sprite->x = healthbox->x + healthbox->x2 + MARK_X;
    sprite->y = healthbox->y + healthbox->y2 + MARK_Y;
    sprite->invisible = healthbox->invisible;
}

static void ShowMark(const struct SpriteTemplate *template, const struct SpriteSheet *sheet, u32 healthboxSpriteId,
                     enum BattlerId battler)
{
    u32 spriteId;

    for (u32 i = 0; i < MAX_SPRITES; i++)
    {
        if (IsMark(&gSprites[i], template->tileTag) && gSprites[i].tHealthbox == healthboxSpriteId) return;
    }

    if (GetSpriteTileStartByTag(template->tileTag) == 0xFFFF)
    {
        LoadSpriteSheet(sheet);
    }
    spriteId = CreateSprite(template, 0, 0, 0);
    if (spriteId == MAX_SPRITES) return;

    gSprites[spriteId].tHealthbox = healthboxSpriteId;
    gSprites[spriteId].tBattler = battler;
    gSprites[spriteId].tPartyIdx = gBattlerPartyIndexes[battler];
    gSprites[spriteId].callback(&gSprites[spriteId]); // in place from the first frame
}

#undef tHealthbox
#undef tBattler
#undef tPartyIdx

void KJH_PackDecorateHealthbox(u32 healthboxSpriteId, enum BattlerId battler)
{
    u32 paletteNum;

    if (KJH_PackIsAlpha(battler) && (paletteNum = MarkPaletteNum(TAG_ALPHA)) != 0xFF)
    {
        SetHealthboxPalette(healthboxSpriteId, paletteNum);
        ShowMark(&sSpriteTemplate_AlphaMark, &sSpriteSheet_AlphaMark, healthboxSpriteId, battler);
    }
    else if (KJH_PackIsLeader(battler) && (paletteNum = MarkPaletteNum(TAG_PACK_LEADER)) != 0xFF)
    {
        SetHealthboxPalette(healthboxSpriteId, paletteNum);
        ShowMark(&sSpriteTemplate_Crown, &sSpriteSheet_Crown, healthboxSpriteId, battler);
    }
    else
    {
        // A helper took a Leader's (or the Alpha's) slot before its mark noticed
        RemoveMarkPalette(healthboxSpriteId, TAG_PACK_LEADER);
        RemoveMarkPalette(healthboxSpriteId, TAG_ALPHA);
    }
}
