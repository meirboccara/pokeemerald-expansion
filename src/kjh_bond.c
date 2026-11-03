// KJH (LV-5): Bond 1-20 (include/kjh_bond.h).
#include "global.h"
#include "battle.h"
#include "battle_setup.h"
#include "data.h"
#include "event_data.h"
#include "item.h"
#include "kjh_bond.h"
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

void KJH_GainBond(struct Pokemon *mon, u32 points)
{
    u32 friendship;

    if (!IsBondHolder(GetMonData(mon, MON_DATA_SPECIES), GetMonData(mon, MON_DATA_IS_EGG)))
        return;
    if (GetItemHoldEffect(GetMonData(mon, MON_DATA_HELD_ITEM)) == HOLD_EFFECT_FRIENDSHIP_UP)
        points = points * 3 / 2;
    friendship = min(GetMonData(mon, MON_DATA_FRIENDSHIP) + points, MAX_FRIENDSHIP);
    SetMonData(mon, MON_DATA_FRIENDSHIP, &friendship);
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
}

void KJH_LoseBondFloored(struct Pokemon *mon, u32 points)
{
    u32 friendship;

    if (!IsBondHolder(GetMonData(mon, MON_DATA_SPECIES), GetMonData(mon, MON_DATA_IS_EGG)))
        return;
    friendship = LowerFriendship(GetMonData(mon, MON_DATA_FRIENDSHIP), points,
                                 KJH_BondFloorFriendship(KJH_GetPeakBond(mon)));
    SetMonData(mon, MON_DATA_FRIENDSHIP, &friendship);
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

void KJH_BondAfterBattle(void)
{
    u32 points;

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

void KJH_BondOnWhiteOut(void)
{
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
    case FRIENDSHIP_EVENT_FAINT_FIELD_PSN:
        return -KJH_BOND_LOSS_FAINT;
    case FRIENDSHIP_EVENT_MASSAGE:
        return 3;  // Daisy's grooming, as in FireRed
    default:
        return 0;  // levels, the League bonus and TMs give no Bond: battles and steps do
    }
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
    { 8, TRUE,  COMPOUND_STRING("Egg moves")},
    {10, FALSE, COMPOUND_STRING("Confusion")},
    {12, TRUE,  COMPOUND_STRING("Hidden Ab.")},
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
}
