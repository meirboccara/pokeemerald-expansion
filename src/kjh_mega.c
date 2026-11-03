// KJH: Mega Evolution, levels-free (LV-19, include/kjh_mega.h).
#include "global.h"
#include "battle.h"
#include "battle_util.h"
#include "data.h"
#include "event_data.h"
#include "item.h"
#include "kjh_bond.h"
#include "kjh_mega.h"
#include "kjh_pack.h"
#include "kjh_power_cap.h"
#include "kjh_team_level.h"
#include "party_menu.h"
#include "tv.h"
#include "pokemon.h"
#include "script.h"
#include "string_util.h"
#include "constants/abilities.h"
#include "constants/vars.h"

// The held-back message is shown once per battle
static EWRAM_DATA bool8 sMegaHeldBackShown = FALSE;

u32 KJH_MegaHeldBackStat(u32 baseStat, u32 megaStat, u32 percent)
{
    if (percent >= 100 || megaStat <= baseStat)
        return megaStat;
    return baseStat + (megaStat - baseStat) * percent / 100;
}

static bool32 IsMegaMethod(enum FormChanges method)
{
    return method == FORM_CHANGE_BATTLE_MEGA_EVOLUTION_ITEM || method == FORM_CHANGE_BATTLE_MEGA_EVOLUTION_MOVE;
}

bool32 KJH_SpeciesHasMega(enum Species species)
{
    const struct FormChange *formChanges = GetSpeciesFormChanges(species);

    for (u32 i = 0; formChanges != NULL && formChanges[i].method != FORM_CHANGE_TERMINATOR; i++)
    {
        if (IsMegaMethod(formChanges[i].method))
            return TRUE;
    }
    return FALSE;
}

// Its stones in its form changes' order, up to max; returns how many (Charizard: X then Y)
static u32 GetMegaStones(enum Species species, enum Item *stones, u32 max)
{
    const struct FormChange *formChanges = GetSpeciesFormChanges(species);
    u32 count = 0;

    for (u32 i = 0; formChanges != NULL && formChanges[i].method != FORM_CHANGE_TERMINATOR && count < max; i++)
    {
        if (formChanges[i].method == FORM_CHANGE_BATTLE_MEGA_EVOLUTION_ITEM)
            stones[count++] = formChanges[i].param1;
    }
    return count;
}

enum Item KJH_MegaStoneForSpecies(enum Species species)
{
    enum Item stone = ITEM_NONE;

    GetMegaStones(species, &stone, 1);
    return stone;
}

u32 KJH_MegaAceSlot(const struct Trainer *trainer)
{
    for (u32 slot = trainer->partySize; slot > 0; slot--)
    {
        if (KJH_SpeciesHasMega(trainer->party[slot - 1].species))
            return slot - 1;
    }
    return trainer->partySize;
}

bool32 KJH_IsBraceletActiveHere(void)
{
    u32 map = (gSaveBlock1Ptr->location.mapGroup << 8) | gSaveBlock1Ptr->location.mapNum;

    if (!CheckBagHasItem(ITEM_MEGA_RING, 1))
        return FALSE;
    // In the levels-free game it works on Kanto's maps only: Johto's and Hoenn's bracelet is silent until their
    // quest (LV-23)
    return !KJH_IsLevelsFree() || KJH_RegionOf(gMapHeader.regionMapSectionId, map) == KJH_REGION_KANTO;
}

// The power cap's share for the region's badges (4: 80%, 5: 90%, 6+: 100%), with its switches (off in the test
// build and in link battles); never in the classic game
u32 KJH_MegaPercentHere(void)
{
    if (!KJH_IsLevelsFree())
        return 100;
    return KJH_PowerCapPercentNow();
}

bool32 KJH_HasMegaBond(struct Pokemon *mon)
{
    return !KJH_IsLevelsFree() || KJH_GetPeakBond(mon) >= KJH_MEGA_BOND;
}

// Its stone, held or in the bag
static bool32 HasMegaStone(enum Species species, enum Item heldItem)
{
    enum Item stones[2];
    u32 count = GetMegaStones(species, stones, ARRAY_COUNT(stones));

    if (count == 0)
        return TRUE; // Rayquaza needs none
    for (u32 i = 0; i < count; i++)
    {
        if (stones[i] == heldItem || CheckBagHasItem(stones[i], 1))
            return TRUE;
    }
    return FALSE;
}

enum KjhMegaStatus KJH_MegaStatus(struct Pokemon *mon)
{
    enum Species species = GetMonData(mon, MON_DATA_SPECIES);

    if (!KJH_SpeciesHasMega(species))
        return KJH_MEGA_STATUS_NONE;
    if (!KJH_HasMegaBond(mon))
        return KJH_MEGA_STATUS_NEEDS_BOND;
    if (!HasMegaStone(species, GetMonData(mon, MON_DATA_HELD_ITEM)))
        return KJH_MEGA_STATUS_NO_STONE;
    if (!KJH_IsBraceletActiveHere())
        return KJH_MEGA_STATUS_BRACELET_SILENT;
    if (KJH_MegaPercentHere() < 100)
        return KJH_MEGA_STATUS_HELD_BACK;
    return KJH_MEGA_STATUS_READY;
}

u8 *KJH_AppendMegaLine(u8 *dest, struct Pokemon *mon)
{
    enum KjhMegaStatus status = KJH_MegaStatus(mon);

    if (status == KJH_MEGA_STATUS_NONE)
        return dest;
    dest = StringAppend(dest, COMPOUND_STRING("\nMega: "));
    switch (status)
    {
    case KJH_MEGA_STATUS_NEEDS_BOND:
        return StringAppend(dest, COMPOUND_STRING("needs Bond 18"));
    case KJH_MEGA_STATUS_NO_STONE:
        return StringAppend(dest, COMPOUND_STRING("no stone"));
    case KJH_MEGA_STATUS_BRACELET_SILENT:
        return StringAppend(dest, COMPOUND_STRING("bracelet silent here"));
    case KJH_MEGA_STATUS_HELD_BACK:
        dest = StringAppend(dest, COMPOUND_STRING("ready ("));
        dest = ConvertIntToDecimalStringN(dest, KJH_MegaPercentHere(), STR_CONV_MODE_LEFT_ALIGN, 3);
        return StringAppend(dest, COMPOUND_STRING("%)"));
    default:
        return StringAppend(dest, COMPOUND_STRING("ready"));
    }
}

// In a link battle the other console sees neither this player's bag nor their Bond rules: expansion's own rules
static bool32 IsLink(void)
{
    return gBattleTypeFlags & BATTLE_TYPE_LINK;
}

// CanMegaEvolve only asks this for the player's own Pokemon (not a multi battle's partner)
bool32 KJH_CanBattlerMegaEvolve(enum BattlerId battler)
{
    if (IsLink())
        return TESTING || CheckBagHasItem(ITEM_MEGA_RING, 1);
    if (!TESTING && !KJH_IsBraceletActiveHere())
        return FALSE;
    return KJH_HasMegaBond(GetBattlerMon(battler));
}

// The player's own Pokemon: not a multi battle's partner
static bool32 IsPlayersOwn(enum BattlerId battler)
{
    enum BattlerPosition position = GetBattlerPosition(battler);

    return position == B_POSITION_PLAYER_LEFT
        || (!(gBattleTypeFlags & BATTLE_TYPE_MULTI) && position == B_POSITION_PLAYER_RIGHT);
}

enum Item KJH_MegaStoneInPlay(enum BattlerId battler, enum FormChanges method, enum Item heldItem)
{
    enum Item stones[2];
    u32 count;

    if (method != FORM_CHANGE_BATTLE_MEGA_EVOLUTION_ITEM || IsLink() || !IsPlayersOwn(battler))
        return heldItem;
    count = GetMegaStones(gBattleMons[battler].species, stones, ARRAY_COUNT(stones));
    for (u32 i = 0; i < count; i++)
    {
        if (stones[i] == heldItem)
            return heldItem;
    }
    for (u32 i = 0; i < count; i++)
    {
        if (CheckBagHasItem(stones[i], 1))
            return stones[i];
    }
    return heldItem;
}

void KJH_HoldBackMegaEvolution(enum BattlerId battler, struct Pokemon *mon, const u16 *statsBefore,
                               enum Ability abilityBefore)
{
    u32 percent = KJH_MegaPercentHere();

    if (percent >= 100)
        return;
    // HP doesn't change with a Mega; the other five are held back
    for (enum Stat stat = STAT_ATK; stat < NUM_STATS; stat++)
    {
        u32 value = KJH_MegaHeldBackStat(statsBefore[stat], GetMonData(mon, MON_DATA_MAX_HP + stat), percent);

        SetMonData(mon, MON_DATA_MAX_HP + stat, &value);
    }
    gBattleMons[battler].attack = GetMonData(mon, MON_DATA_ATK);
    gBattleMons[battler].defense = GetMonData(mon, MON_DATA_DEF);
    gBattleMons[battler].speed = GetMonData(mon, MON_DATA_SPEED);
    gBattleMons[battler].spAttack = GetMonData(mon, MON_DATA_SPATK);
    gBattleMons[battler].spDefense = GetMonData(mon, MON_DATA_SPDEF);
    gBattleMons[battler].ability = abilityBefore;
}

bool32 KJH_TryPrepareMegaHeldBack(void)
{
    u32 percent = KJH_MegaPercentHere();

    if (sMegaHeldBackShown || percent >= 100)
        return FALSE;
    sMegaHeldBackShown = TRUE;
    PREPARE_BYTE_NUMBER_BUFFER(gBattleTextBuff1, 3, percent);
    return TRUE;
}

// battle_script_commands.c's NATIVE_ARGS(const u8 *jumpInstr), which is local to it
struct __attribute__((packed)) KjhNativeJump
{
    u8 opcode;
    void (*func)(void);
    const u8 *jumpInstr;
    const u8 nextInstr[0];
};

static void JumpIf(bool32 jump)
{
    const struct KjhNativeJump *cmd = (const void *)gBattlescriptCurrInstr;

    gBattlescriptCurrInstr = jump ? cmd->jumpInstr : cmd->nextInstr;
}

void BS_KjhJumpIfMegaNotHeldBack(void)
{
    JumpIf(KJH_MegaPercentHere() >= 100);
}

void BS_KjhTryMegaHeldBackMessage(void)
{
    JumpIf(!KJH_TryPrepareMegaHeldBack());
}

void KJH_MegaStartBattle(void)
{
    sMegaHeldBackShown = FALSE;
}

void KJH_GiveBossAceMegaStone(struct Pokemon *mon, const struct TrainerMon *in, const struct Trainer *trainer)
{
    enum Item stone;

    if (!KJH_IsBraceletActiveHere() || in != &trainer->party[KJH_MegaAceSlot(trainer)])
        return;
    stone = KJH_MegaStoneForSpecies(in->species);
    if (stone != ITEM_NONE)
        SetMonData(mon, MON_DATA_HELD_ITEM, &stone);
}

void KJH_ScriptCountKantoBadges(struct ScriptContext *ctx)
{
    Script_RequestEffects(SCREFF_V1);
    gSpecialVar_Result = KJH_CountKantoBadges();
}

u32 KJH_MegaGuardianLevel(u32 teamLevel)
{
    if (teamLevel == 0)
        return KJH_MEGA_GUARDIAN_LEVEL;
    return KJH_AlphaLevel(teamLevel);
}

void KJH_ScriptSetupMegaGuardian(struct ScriptContext *ctx)
{
    struct Pokemon *mon = &gEnemyParty[0];

    Script_RequestEffects(SCREFF_V1);
    u32 level, exp;

    if (!KJH_IsLevelsFree())
        return; // the classic game has no Alphas (LV-15): a plain Clefable at the script's level
    // Its level, without a peak level (a caught guardian joins the team at the team's level, LV-2), and its moves
    // for that level
    level = KJH_MegaGuardianLevel(KJH_TeamLevel());
    exp = gExperienceTables[gSpeciesInfo[SPECIES_CLEFABLE].growthRate][level];
    SetMonData(mon, MON_DATA_EXP, &exp);
    CalculateMonStats(mon);
    GiveMonInitialMoveset(mon);
    KJH_PackMakeScriptedAlpha(mon);
}

// FireRed's VAR_STARTER_MON: 0 Bulbasaur, 1 Squirtle, 2 Charmander; each line's three stages
static const enum Species sStarterLines[][3] =
{
    {SPECIES_BULBASAUR, SPECIES_IVYSAUR, SPECIES_VENUSAUR},
    {SPECIES_SQUIRTLE, SPECIES_WARTORTLE, SPECIES_BLASTOISE},
    {SPECIES_CHARMANDER, SPECIES_CHARMELEON, SPECIES_CHARIZARD},
};

// Its Mega form, by the stone held or in the bag (Charizard: the one the player picked)
static enum Species MegaFormOf(struct Pokemon *mon)
{
    enum Species species = GetMonData(mon, MON_DATA_SPECIES);
    enum Item held = GetMonData(mon, MON_DATA_HELD_ITEM);
    const struct FormChange *formChanges = GetSpeciesFormChanges(species);

    for (u32 i = 0; formChanges != NULL && formChanges[i].method != FORM_CHANGE_TERMINATOR; i++)
    {
        if (formChanges[i].method == FORM_CHANGE_BATTLE_MEGA_EVOLUTION_ITEM
         && (formChanges[i].param1 == held || CheckBagHasItem(formChanges[i].param1, 1)))
            return formChanges[i].targetSpecies;
    }
    return species;
}

void KJH_ScriptMegaStarterReady(struct ScriptContext *ctx)
{
    const enum Species *line = sStarterLines[min(VarGet(VAR_STARTER_MON), ARRAY_COUNT(sStarterLines) - 1)];
    struct Pokemon *starter = NULL;
    u32 stage = 0;

    Script_RequestEffects(SCREFF_V1);
    for (u32 i = 0; i < PARTY_SIZE; i++)
    {
        struct Pokemon *mon = &gPlayerParty[i];
        enum Species species = GetMonData(mon, MON_DATA_SPECIES);

        if (GetMonData(mon, MON_DATA_IS_EGG) || GetMonData(mon, MON_DATA_OT_ID) != GetPlayerIDAsU32())
            continue;
        for (u32 s = 0; s < ARRAY_COUNT(sStarterLines[0]); s++)
        {
            if (species == line[s] && (starter == NULL || s > stage))
            {
                starter = mon;
                stage = s;
            }
        }
    }

    if (starter == NULL)
    {
        StringCopy(gStringVar1, GetSpeciesName(line[2]));
        gSpecialVar_Result = KJH_MEGA_STARTER_MISSING;
        return;
    }
    GetMonNickname(starter, gStringVar1);
    if (stage < 2)
    {
        StringCopy(gStringVar2, GetSpeciesName(line[2]));
        gSpecialVar_Result = KJH_MEGA_STARTER_EVOLVE;
        return;
    }
    if (!KJH_HasMegaBond(starter))
    {
        gSpecialVar_Result = KJH_MEGA_STARTER_BOND;
        return;
    }
    gSpecialVar_0x8005 = line[2];
    gSpecialVar_0x8006 = MegaFormOf(starter);
    gSpecialVar_Result = KJH_MEGA_STARTER_READY;
}

// The never-sold list (docs/MEGA.md in the KJH repo): each is found in a place tied to its Pokemon (Kanto: Mewtwonite X and Y in
// Cerulean Cave); the others' places come with their regions
static const enum Item sNeverSoldStones[] =
{
    ITEM_DRAGONINITE,     // Dragon's Den (Johto)
    ITEM_MEWTWONITE_X,    // Cerulean Cave
    ITEM_MEWTWONITE_Y,    // Cerulean Cave
    ITEM_TYRANITARITE,    // Mt. Silver (Johto)
    ITEM_SALAMENCITE,     // Hoenn
    ITEM_METAGROSSITE,    // Mossdeep's space center (Hoenn)
    ITEM_LATIASITE,       // Hoenn
    ITEM_LATIOSITE,       // Hoenn
};

bool32 KJH_IsNeverSoldStone(enum Item item)
{
    for (u32 i = 0; i < ARRAY_COUNT(sNeverSoldStones); i++)
    {
        if (sNeverSoldStones[i] == item)
            return TRUE;
    }
    return FALSE;
}

// Expansion's stones cost 0, which the bag also reads as "can't be sold": a never-sold stone keeps it, so it can't be
// sold and lost for good
u32 KJH_ItemPrice(enum Item item, u32 price)
{
    if (GetItemHoldEffect(item) == HOLD_EFFECT_MEGA_STONE && !KJH_IsNeverSoldStone(item))
        return KJH_MEGA_STONE_PRICE;
    return price;
}
