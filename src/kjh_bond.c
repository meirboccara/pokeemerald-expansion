// KJH (LV-5): Bond 1-20 (include/kjh_bond.h).
#include "global.h"
#include "battle.h"
#include "battle_setup.h"
#include "battle_util.h"
#include "difficulty.h"
#include "random.h"
#include "data.h"
#include "event_data.h"
#include "item.h"
#include "kjh_bond.h"
#include "kjh_real_clock.h"
#include "money.h"
#include "constants/vars.h"
#include "kjh_mega.h"
#include "kjh_levelless.h"
#include "kjh_progression.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "string_util.h"
#include "constants/characters.h"
#include "constants/battle.h"
#include "constants/hold_effects.h"
#include "constants/items.h"
#include "constants/pokemon.h"

#define BOND_STEPS (KJH_BOND_MAX - 1)                                 // 19 steps from Bond 1 to Bond 20
#define BOND_SPAN  (MAX_FRIENDSHIP - KJH_BOND_MIN_FRIENDSHIP)         // over 185 friendship points

u32 KJH_FriendshipToBond(u32 friendship)
{
    if (friendship <= KJH_BOND_MIN_FRIENDSHIP)
        return 1;
    if (friendship >= MAX_FRIENDSHIP)
        return KJH_BOND_MAX;
    return 1 + (friendship - KJH_BOND_MIN_FRIENDSHIP) * BOND_STEPS / BOND_SPAN;
}

u32 KJH_BondToFriendship(u32 bond)
{
    if (bond <= 1)
        return KJH_BOND_MIN_FRIENDSHIP;
    if (bond >= KJH_BOND_MAX)
        return MAX_FRIENDSHIP;
    return KJH_BOND_MIN_FRIENDSHIP + ((bond - 1) * BOND_SPAN + BOND_STEPS - 1) / BOND_STEPS;
}

u32 KJH_GetBond(struct Pokemon *mon)
{
    return KJH_FriendshipToBond(GetMonData(mon, MON_DATA_FRIENDSHIP));
}

u32 KJH_GetPeakBond(struct Pokemon *mon)
{
    return max(GetMonData(mon, MON_DATA_PEAK_BOND), KJH_GetBond(mon));
}

u32 KJH_BondFloorFriendship(u32 peakBond)
{
    return KJH_BondToFriendship((peakBond + 1) / 2);
}

static bool32 IsBondHolder(u32 species, bool32 isEgg)
{
    return species != SPECIES_NONE && species != SPECIES_EGG && !isEgg;
}

// LV-6: the stat bonus follows Bond. Not during a battle: the battle has its own copy of the stats, and the
// party's are recalculated when it ends (KJH_BondAfterBattle).
static void RecalculateStats(struct Pokemon *mon)
{
    if (!gMain.inBattle)
        CalculateMonStats(mon);
}

void KJH_GainBond(struct Pokemon *mon, u32 points)
{
    u32 friendship;

    if (!IsBondHolder(GetMonData(mon, MON_DATA_SPECIES), GetMonData(mon, MON_DATA_IS_EGG)))
        return;
    if (GetItemHoldEffect(GetMonData(mon, MON_DATA_HELD_ITEM)) == HOLD_EFFECT_FRIENDSHIP_UP)
        points = points * 3 / 2;
    friendship = min(GetMonData(mon, MON_DATA_FRIENDSHIP) + points, MAX_FRIENDSHIP);
    SetMonData(mon, MON_DATA_FRIENDSHIP, &friendship);
    RecalculateStats(mon);
}

// Down by points, but never under floor (a Pokemon already under it stays where it is)
static u32 LowerFriendship(u32 friendship, u32 points, u32 floor)
{
    if (friendship <= floor)
        return friendship;
    return friendship > floor + points ? friendship - points : floor;
}

void KJH_LoseBond(struct Pokemon *mon, u32 points)
{
    u32 friendship;

    if (!IsBondHolder(GetMonData(mon, MON_DATA_SPECIES), GetMonData(mon, MON_DATA_IS_EGG)))
        return;
    friendship = LowerFriendship(GetMonData(mon, MON_DATA_FRIENDSHIP), points, KJH_BOND_MIN_FRIENDSHIP);
    SetMonData(mon, MON_DATA_FRIENDSHIP, &friendship);
    RecalculateStats(mon);
}

void KJH_LoseBondFloored(struct Pokemon *mon, u32 points)
{
    u32 friendship;

    if (!IsBondHolder(GetMonData(mon, MON_DATA_SPECIES), GetMonData(mon, MON_DATA_IS_EGG)))
        return;
    friendship = LowerFriendship(GetMonData(mon, MON_DATA_FRIENDSHIP), points,
                                 KJH_BondFloorFriendship(KJH_GetPeakBond(mon)));
    SetMonData(mon, MON_DATA_FRIENDSHIP, &friendship);
    RecalculateStats(mon);
}

void KJH_BoxMonLoseBondFloored(struct BoxPokemon *boxMon, u32 points)
{
    u32 friendship, peak;

    if (!IsBondHolder(GetBoxMonData(boxMon, MON_DATA_SPECIES), GetBoxMonData(boxMon, MON_DATA_IS_EGG)))
        return;
    friendship = GetBoxMonData(boxMon, MON_DATA_FRIENDSHIP);
    peak = max(GetBoxMonData(boxMon, MON_DATA_PEAK_BOND), KJH_FriendshipToBond(friendship));
    friendship = LowerFriendship(friendship, points, KJH_BondFloorFriendship(peak));
    SetBoxMonData(boxMon, MON_DATA_FRIENDSHIP, &friendship);
}

void KJH_BondOnFoeDown(u32 sentInBits)
{
    for (u32 i = 0; i < PARTY_SIZE; i++)
    {
        if (sentInBits & (1u << i))
            KJH_GainBond(&gParties[B_TRAINER_PLAYER][i], KJH_BOND_GAIN_FOE);
    }
}

static bool32 IsBossBattle(void)
{
    u32 trainerNum = TRAINER_BATTLE_PARAM.opponentA;

    if (!(gBattleTypeFlags & BATTLE_TYPE_TRAINER) || trainerNum == TRAINER_NONE || IsSpecialTrainer(trainerNum))
        return FALSE;
    return KJH_IsBossTrainer(GetTrainerStructFromId(trainerNum), trainerNum);
}

static EWRAM_DATA bool8 sProtectedWhiteout = FALSE;

static bool32 IsProtectedTrainer(u32 trainer)
{
    u32 kind;
    if (trainer == TRAINER_NONE || IsSpecialTrainer(trainer))
        return FALSE;
    kind = KJH_BossKind(GetTrainerStructFromId(trainer)->trainerClass);
    return kind == KJH_BOSS_LEADER || kind == KJH_BOSS_ELITE_FOUR || kind == KJH_BOSS_CHAMPION;
}

bool32 KJH_BondBattleProtected(void)
{
    if (!(gBattleTypeFlags & BATTLE_TYPE_TRAINER))
        return FALSE;
    return IsProtectedTrainer(TRAINER_BATTLE_PARAM.opponentA)
        || ((gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS) && IsProtectedTrainer(TRAINER_BATTLE_PARAM.opponentB));
}

void KJH_BondAfterBattle(void)
{
    u32 points;

    // DoWhiteOut runs after leaving battle; do not rely on stale trainer flags in the field.
    sProtectedWhiteout = gBattleOutcome == B_OUTCOME_LOST && KJH_BondBattleProtected();

    if (gBattleOutcome == B_OUTCOME_CAUGHT)
        points = KJH_BOND_GAIN_WIN + KJH_BOND_GAIN_FOE; // the catch counts as a won battle and a foe
    else if (gBattleOutcome == B_OUTCOME_WON)
        points = IsBossBattle() ? KJH_BOND_GAIN_BOSS_WIN : KJH_BOND_GAIN_WIN;
    else
        return;
    for (u32 i = 0; i < PARTY_SIZE; i++)
    {
        if (gBattleStruct->partyState[B_TRAINER_PLAYER][i].sentOut)
            KJH_GainBond(&gParties[B_TRAINER_PLAYER][i], points);
    }
}

void KJH_BondRecalculatePartyStats(void)
{
    for (u32 i = 0; i < PARTY_SIZE; i++)
    {
        if (GetMonData(&gParties[B_TRAINER_PLAYER][i], MON_DATA_SPECIES) != SPECIES_NONE)
            CalculateMonStats(&gParties[B_TRAINER_PLAYER][i]);
    }
}

void KJH_BondOnWhiteOut(void)
{
    u32 count = 0;

    if (sProtectedWhiteout)
    {
        sProtectedWhiteout = FALSE;
        return;
    }

    for (u32 i = 0; i < PARTY_SIZE; i++)
    {
        if (IsBondHolder(GetMonData(&gParties[B_TRAINER_PLAYER][i], MON_DATA_SPECIES),
                         GetMonData(&gParties[B_TRAINER_PLAYER][i], MON_DATA_IS_EGG)))
            count++;
    }
    if (count < KJH_BOND_WHITEOUT_MIN_PARTY)
        return;
    for (u32 i = 0; i < PARTY_SIZE; i++)
        KJH_LoseBond(&gParties[B_TRAINER_PLAYER][i], KJH_BOND_LOSS_WHITEOUT);
}

void KJH_BondPcWeeks(u32 weeks)
{
    for (u32 week = 0; week < weeks; week++)
    {
        for (u32 box = 0; box < TOTAL_BOXES_COUNT; box++)
        {
            for (u32 slot = 0; slot < IN_BOX_COUNT; slot++)
                KJH_BoxMonLoseBondFloored(GetBoxedMonPtr(box, slot), KJH_BOND_LOSS_PC_WEEK);
        }
    }
}

void KJH_BondOnDaycarePickup(struct Pokemon *mon)
{
    KJH_LoseBondFloored(mon, KJH_BOND_LOSS_DAYCARE);
}

s32 KJH_BondFriendshipEvent(u32 event)
{
    switch (event)
    {
    case FRIENDSHIP_EVENT_WALKING:
        return KJH_BOND_GAIN_WALK;
    case FRIENDSHIP_EVENT_FAINT_SMALL:
    case FRIENDSHIP_EVENT_FAINT_LARGE:
        if (gMain.inBattle && KJH_BondBattleProtected())
            return 0;
        return -KJH_BOND_LOSS_FAINT;
    case FRIENDSHIP_EVENT_FAINT_FIELD_PSN:
        return -KJH_BOND_LOSS_FAINT;
    case FRIENDSHIP_EVENT_MASSAGE:
        return 3;  // Daisy's grooming, as in FireRed
    default:
        return 0;  // levels, the League bonus and TMs give no Bond: battles and steps do
    }
}

u32 KJH_BondCareRecovery(struct Pokemon *mon)
{
    if (!IsBondHolder(GetMonData(mon, MON_DATA_SPECIES), GetMonData(mon, MON_DATA_IS_EGG)))
        return 0;
    return min(KJH_GetPeakBond(mon) - KJH_GetBond(mon), KJH_BOND_CARE_MAX);
}

bool32 KJH_BondCareDayAvailable(u32 seconds)
{
    u32 last = VarGet(VAR_KJH_BOND_CARE_DAY_LO) | ((u32)VarGet(VAR_KJH_BOND_CARE_DAY_HI) << 16);
    return last == 0 || seconds / 86400 + 1 > last;
}

static u32 BondCareStatus(u32 slot, u32 *seconds)
{
    if (slot >= gPlayerPartyCount || KJH_BondCareRecovery(&gPlayerParty[slot]) == 0)
        return KJH_BOND_CARE_NO_LOSS;
    if (!KJH_RealClockNow(seconds))
        return KJH_BOND_CARE_NO_CLOCK;
    if (!KJH_BondCareDayAvailable(*seconds))
        return KJH_BOND_CARE_USED;
    return KJH_BOND_CARE_OK;
}

void KJH_PreviewBondCare(void)
{
    u32 seconds;
    gSpecialVar_Result = BondCareStatus(gSpecialVar_0x8004, &seconds);
    if (gSpecialVar_Result == KJH_BOND_CARE_OK)
    {
        struct Pokemon *mon = &gPlayerParty[gSpecialVar_0x8004];
        GetMonData(mon, MON_DATA_NICKNAME, gStringVar1);
        StringGet_Nickname(gStringVar1);
        ConvertIntToDecimalStringN(gStringVar2, KJH_BondCareRecovery(mon), STR_CONV_MODE_LEFT_ALIGN, 2);
    }
}

void KJH_ApplyBondCare(void)
{
    u32 seconds, friendship, day;
    struct Pokemon *mon;
    gSpecialVar_Result = BondCareStatus(gSpecialVar_0x8004, &seconds);
    if (gSpecialVar_Result != KJH_BOND_CARE_OK)
        return;
    if (!IsEnoughMoney(&gSaveBlock1Ptr->money, KJH_BOND_CARE_PRICE))
    {
        gSpecialVar_Result = KJH_BOND_CARE_NO_MONEY;
        return;
    }
    mon = &gPlayerParty[gSpecialVar_0x8004];
    friendship = KJH_BondToFriendship(KJH_GetBond(mon) + KJH_BondCareRecovery(mon));
    // Direct restoration, not a gain: the Soothe Bell must not multiply paid care.
    SetMonData(mon, MON_DATA_FRIENDSHIP, &friendship);
    RecalculateStats(mon);
    RemoveMoney(&gSaveBlock1Ptr->money, KJH_BOND_CARE_PRICE);
    day = seconds / 86400 + 1;
    VarSet(VAR_KJH_BOND_CARE_DAY_LO, day & 0xFFFF);
    VarSet(VAR_KJH_BOND_CARE_DAY_HI, day >> 16);
}

void KJH_SetStarterBond(void)
{
    u32 friendship = KJH_BondToFriendship(KJH_STARTER_BOND);

    if (gPlayerPartyCount != 0)
        SetMonData(&gParties[B_TRAINER_PLAYER][gPlayerPartyCount - 1], MON_DATA_FRIENDSHIP, &friendship);
}

const struct KjhBondMilestone gKjhBondMilestones[KJH_BOND_MILESTONE_COUNT] =
{
    { 3, FALSE, COMPOUND_STRING("Emotions")},
    { 5, FALSE, COMPOUND_STRING("Stats +2%")},
    {10, FALSE, COMPOUND_STRING("Confusion")},
    {12, TRUE,  COMPOUND_STRING("Hidden Ab.")},
    {14, TRUE,  COMPOUND_STRING("Egg moves")},
    {15, FALSE, COMPOUND_STRING("Stats +5%")},
    {18, TRUE,  COMPOUND_STRING("Evolve, Mega")},
    {19, FALSE, COMPOUND_STRING("Status")},
    {20, TRUE,  COMPOUND_STRING("IV training")},
};

bool32 KJH_IsBondMilestoneUnlocked(u32 bond, u32 peakBond, u32 milestone)
{
    return (gKjhBondMilestones[milestone].keptAtPeak ? max(bond, peakBond) : bond) >= gKjhBondMilestones[milestone].bond;
}

u32 KJH_NextBondMilestone(u32 bond, u32 peakBond)
{
    u32 i;
    for (i = 0; i < KJH_BOND_MILESTONE_COUNT; i++)
    {
        if (!KJH_IsBondMilestoneUnlocked(bond, peakBond, i))
            break;
    }
    return i;
}

u32 KJH_BondPercentToMilestone(u32 friendship, u32 milestone)
{
    u32 from = KJH_BondToFriendship(KJH_FriendshipToBond(friendship));
    u32 to = KJH_BondToFriendship(gKjhBondMilestones[milestone].bond);

    if (friendship < from) // under 70: still at the start of Bond 1
        friendship = from;
    if (to <= from)
        return 99;
    return min((friendship - from) * 100 / (to - from), 99);
}

static u8 *AppendNumber(u8 *dest, u32 value)
{
    return ConvertIntToDecimalStringN(dest, value, STR_CONV_MODE_LEFT_ALIGN, 3);
}

static u8 *AppendNewline(u8 *dest)
{
    *dest++ = CHAR_NEWLINE;
    *dest = EOS;
    return dest;
}

void KJH_FormatBondPage(struct Pokemon *mon, u8 *dest)
{
    u32 friendship = GetMonData(mon, MON_DATA_FRIENDSHIP);
    u32 bond = KJH_FriendshipToBond(friendship), peak = KJH_GetPeakBond(mon);
    u32 next = KJH_NextBondMilestone(bond, peak);
    u8 *end = dest;

    end = StringCopy(end, COMPOUND_STRING("BOND "));
    end = AppendNumber(end, bond);
    end = StringAppend(end, COMPOUND_STRING("/20   PEAK "));
    end = AppendNumber(end, peak);
    end = AppendNewline(end);
    for (u32 step = 1; step <= KJH_BOND_MAX; step++)
        *end++ = step <= bond ? CHAR_EQUALS : CHAR_HYPHEN;
    *end = EOS;
    end = AppendNewline(end);
    if (next < KJH_BOND_MILESTONE_COUNT)
    {
        end = StringAppend(end, COMPOUND_STRING("Next: "));
        end = AppendNumber(end, gKjhBondMilestones[next].bond);
        end = StringAppend(end, COMPOUND_STRING(" "));
        end = StringAppend(end, gKjhBondMilestones[next].name);
        end = StringAppend(end, COMPOUND_STRING("  "));
        end = AppendNumber(end, KJH_BondPercentToMilestone(friendship, next));
        end = StringAppend(end, COMPOUND_STRING("%"));
    }
    else
    {
        end = StringAppend(end, COMPOUND_STRING("Every step reached!"));
    }
    for (u32 i = 0; i < KJH_BOND_MILESTONE_COUNT; i++)
    {
        if (i % 2 == 0)
            end = AppendNewline(end);
        else
            end = StringAppend(end, COMPOUND_STRING("  "));
        end = StringAppend(end, KJH_IsBondMilestoneUnlocked(bond, peak, i) ? COMPOUND_STRING("+") : COMPOUND_STRING("·"));
        end = AppendNumber(end, gKjhBondMilestones[i].bond);
        end = StringAppend(end, COMPOUND_STRING(" "));
        end = StringAppend(end, gKjhBondMilestones[i].name);
    }
    KJH_AppendMegaLine(end, mon); // LV-19
}

// LV-6: the perks
bool32 KJH_BondPerksOn(void)
{
    return GetCurrentDifficultyLevel() != DIFFICULTY_HARD;
}

s32 KJH_BondStatBonus(s32 stat, u32 friendship)
{
    u32 bond = KJH_FriendshipToBond(friendship);

    if (!KJH_BondPerksOn() || stat <= 0)
        return 0;
    if (bond >= KJH_BOND_STATS_BIG)
        return max(stat * 5 / 100, 1);
    if (bond >= KJH_BOND_STATS_SMALL)
        return max(stat * 2 / 100, 1);
    return 0;
}

bool32 KJH_HasBondEmotions(struct Pokemon *mon)
{
    return KJH_GetBond(mon) >= KJH_BOND_EMOTIONS;
}

// Wild Pokemon have no Bond perks; the player's and trainers' do
static bool32 HasBattlePerks(u32 battler)
{
    if (!KJH_BondPerksOn() || !IsBattlerAlive(battler))
        return FALSE;
    return IsOnPlayerSide(battler) || (gBattleTypeFlags & BATTLE_TYPE_TRAINER);
}

enum KjhBondShake KJH_TryBondShake(u32 battler)
{
    u32 bond;

    if (!HasBattlePerks(battler))
        return KJH_BOND_SHAKE_NONE;
    bond = KJH_FriendshipToBond(gBattleMons[battler].friendship);
    if (bond >= KJH_BOND_SHAKE_STATUS && (gBattleMons[battler].status1 & STATUS1_ANY)
     && RandomPercentage(RNG_KJH_BOND_SHAKE, KJH_BOND_SHAKE_STATUS_CHANCE))
        return KJH_BOND_SHAKE_OFF_STATUS;
    if (bond >= KJH_BOND_SHAKE_CONFUSION && gBattleMons[battler].volatiles.confusionTimer
     && RandomPercentage(RNG_KJH_BOND_SHAKE, KJH_BOND_SHAKE_CONFUSION_CHANCE))
        return KJH_BOND_SHAKE_OFF_CONFUSION;
    if (bond >= KJH_BOND_SHAKE_CONFUSION && gBattleMons[battler].volatiles.infatuation
     && RandomPercentage(RNG_KJH_BOND_SHAKE, KJH_BOND_SHAKE_CONFUSION_CHANCE))
        return KJH_BOND_SHAKE_OFF_INFATUATION;
    return KJH_BOND_SHAKE_NONE;
}

// LV-4: no level shown
bool32 KJH_HideLevels(void)
{
    return IS_FRLG && FlagGet(FLAG_KJH_LEVELLESS);
}

u8 *KJH_BufferBondLabel(u8 *dest, u32 friendship)
{
    dest = StringCopy(dest, COMPOUND_STRING("BOND "));
    return ConvertIntToDecimalStringN(dest, KJH_FriendshipToBond(friendship), STR_CONV_MODE_LEFT_ALIGN, 2);
}
