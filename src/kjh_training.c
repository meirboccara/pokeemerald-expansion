// KJH: Training points (LV-7, include/kjh_training.h).
#include "global.h"
#include "battle.h"
#include "battle_controllers.h"
#include "battle_setup.h"
#include "data.h"
#include "kjh_pack.h"
#include "kjh_progression.h"
#include "kjh_training.h"
#include "pokemon.h"
#include "string_util.h"
#include "constants/characters.h"
#include "constants/trainers.h"

u32 KJH_TrainingFoeMultiplier(enum KjhPackRole packRole, enum KjhTierMark tier, bool32 bossTrainer)
{
    if (tier == KJH_TIER_ALPHA)
        return KJH_TRAINING_MULT_ALPHA;
    if (tier == KJH_TIER_LEADER || packRole == KJH_PACK_ROLE_LEADER)
        return KJH_TRAINING_MULT_LEADER;
    if (bossTrainer)
        return KJH_TRAINING_MULT_BOSS;
    if (packRole == KJH_PACK_ROLE_LEADER_HELPER)
        return KJH_TRAINING_MULT_PACK_HELPER;
    return 1;
}

// docs/LEVELLESS_DESIGN.md §4: 1 + level ÷ 20 (Lv 5: 1, Lv 20: 2, Lv 40: 3, Lv 80: 5)
u32 KJH_TrainingPointsPerKo(u32 foeLevel, u32 multiplier)
{
    return (1 + foeLevel / KJH_TRAINING_LEVEL_STEP) * multiplier;
}

// The Pokémon that fought get all the points (2 halves each), the rest of the party half of them
u32 KJH_TrainingHalvesFor(u32 points, bool32 fought)
{
    return fought ? 2 * points : points;
}

void KJH_TrainingAddHalves(u32 *bank, u32 *half, u32 halves)
{
    u32 total = 2 * *bank + *half + halves;

    if (total >= 2 * KJH_TRAINING_BANK_MAX)
    {
        *bank = KJH_TRAINING_BANK_MAX;
        *half = 0;
        return;
    }
    *bank = total / 2;
    *half = total % 2;
}

u32 KJH_TrainingTotalLimit(enum KjhTierMark tier)
{
    switch (tier)
    {
    case KJH_TIER_ALPHA:
        return KJH_TRAINING_TOTAL_ALPHA;
    case KJH_TIER_LEADER:
        return KJH_TRAINING_TOTAL_LEADER;
    default:
        return KJH_TRAINING_TOTAL_REGULAR;
    }
}

static u32 SumEvs(const u8 *evs)
{
    u32 sum = 0;

    for (enum Stat i = 0; i < NUM_STATS; i++)
        sum += evs[i];
    return sum;
}

// What the total limit still allows, 0 at or past it
static u32 TotalRoom(u32 placed, enum KjhTierMark tier)
{
    u32 limit = KJH_TrainingTotalLimit(tier);

    return (placed >= limit) ? 0 : limit - placed;
}

u32 KJH_TrainingRoom(const u8 *evs, enum KjhTierMark tier, enum Stat stat)
{
    if (evs[stat] >= KJH_TRAINING_STAT_MAX)
        return 0;
    return min(TotalRoom(SumEvs(evs), tier), KJH_TRAINING_STAT_MAX - evs[stat]);
}

static bool32 IsPseudoLegendaryLastForm(enum Species species)
{
    switch (species)
    {
    case SPECIES_DRAGONITE:
    case SPECIES_TYRANITAR:
    case SPECIES_SALAMENCE:
    case SPECIES_METAGROSS:
        return TRUE;
    default:
        return FALSE;
    }
}

static bool32 IsFriendshipEvolution(const struct Evolution *evolution)
{
    for (const struct EvolutionParam *param = evolution->params; param != NULL && param->condition != CONDITIONS_END; param++)
    {
        if (param->condition == IF_MIN_FRIENDSHIP)
            return TRUE;
    }
    return FALSE;
}

// docs/LEVELLESS_DESIGN.md, evolution (LV-9): Training points open the evolutions by level (not by friendship: the
// Bond is their key), by trade, and by the item standing in for a trade (Linking Cord, Metal Coat...: the species also
// evolves into the same form by trade). Stones need none.
static bool32 NeedsTrainingPoints(const struct Evolution *evolutions, u32 index)
{
    switch (evolutions[index].method)
    {
    case EVO_LEVEL:
    case EVO_LEVEL_BATTLE_ONLY:
        return !IsFriendshipEvolution(&evolutions[index]);
    case EVO_TRADE:
        return TRUE;
    case EVO_ITEM:
        for (u32 i = 0; evolutions[i].method != EVOLUTIONS_END; i++)
        {
            if (evolutions[i].method == EVO_TRADE && evolutions[i].targetSpecies == evolutions[index].targetSpecies)
                return TRUE;
        }
        return FALSE;
    default:
        return FALSE;
    }
}

u32 KJH_TrainingGoalOfEvolution(enum Species species, u32 index)
{
    const struct Evolution *evolutions = GetSpeciesEvolutions(species);

    if (!NeedsTrainingPoints(evolutions, index))
        return 0;
    // Level-based evolutions: original evolution level × 5 (e.g. lv16 → 80 TP)
    if (evolutions[index].method == EVO_LEVEL || evolutions[index].method == EVO_LEVEL_BATTLE_ONLY)
        return min(evolutions[index].param * KJH_TRAINING_POINTS_PER_LEVEL, KJH_TRAINING_LIFETIME_HALVES_MAX / 2);
    // Trade / trade-substitute evolutions keep their fixed goals
    if (IsPseudoLegendaryLastForm(evolutions[index].targetSpecies))
        return KJH_TRAINING_GOAL_PSEUDO_LAST;
    if (GetSpeciesPreEvolution(species) == SPECIES_NONE)
        return KJH_TRAINING_GOAL_SECOND_FORM;
    return KJH_TRAINING_GOAL_THIRD_FORM;
}

// The goal the Summary shows: the first of its evolutions that needs points, 0 for none
u32 KJH_TrainingEvolutionGoal(enum Species species)
{
    const struct Evolution *evolutions = GetSpeciesEvolutions(species);

    for (u32 i = 0; evolutions != NULL && evolutions[i].method != EVOLUTIONS_END; i++)
    {
        u32 goal;

        if (SanitizeSpeciesId(evolutions[i].targetSpecies) == SPECIES_NONE)
            continue;
        goal = KJH_TrainingGoalOfEvolution(species, i);
        if (goal != 0)
            return goal;
    }
    return 0;
}

// Gym Leaders, the Elite Four and Champions: every Pokémon of theirs counts x3 (not rivals or team bosses)
static bool32 IsBossTrainerMon(enum BattlerId battler)
{
    u32 trainerId;

    if (!(gBattleTypeFlags & BATTLE_TYPE_TRAINER))
        return FALSE;
    trainerId = (GetBattlerTrainer(battler) == B_TRAINER_OPPONENT_B) ? TRAINER_BATTLE_PARAM.opponentB
                                                                     : TRAINER_BATTLE_PARAM.opponentA;
    if (trainerId == TRAINER_NONE || IsSpecialTrainer(trainerId))
        return FALSE;
    switch (KJH_BossKind(GetTrainerClassFromId(trainerId)))
    {
    case KJH_BOSS_LEADER:
    case KJH_BOSS_ELITE_FOUR:
    case KJH_BOSS_CHAMPION:
        return TRUE;
    default:
        return FALSE;
    }
}

static void GetEvs(struct Pokemon *mon, u8 *evs)
{
    for (enum Stat i = 0; i < NUM_STATS; i++)
        evs[i] = GetMonData(mon, MON_DATA_HP_EV + i);
}

static void AddLifetime(struct Pokemon *mon, u32 halves)
{
    u32 current = GetMonData(mon, MON_DATA_TRAINING_LIFETIME_HALVES);
    u32 updated = min(current + halves, KJH_TRAINING_LIFETIME_HALVES_MAX);
    SetMonData(mon, MON_DATA_TRAINING_LIFETIME_HALVES, &updated);
}

static void AddHalves(struct Pokemon *mon, u32 halves)
{
    u32 bank = GetMonData(mon, MON_DATA_TRAINING_BANK);
    u32 half = GetMonData(mon, MON_DATA_TRAINING_HALF);

    KJH_TrainingAddHalves(&bank, &half, halves);
    SetMonData(mon, MON_DATA_TRAINING_BANK, &bank);
    SetMonData(mon, MON_DATA_TRAINING_HALF, &half);
    AddLifetime(mon, halves);
}

#if IS_FRLG
static bool32 CenterCareClaimed(u32 section)
{
    return (gSaveBlock3Ptr->kjhCenterCare[section / 8] >> (section % 8)) & 1;
}

static void ClaimCenterCare(u32 section)
{
    gSaveBlock3Ptr->kjhCenterCare[section / 8] |= 1 << (section % 8);
}
#endif

// A voluntary Center heal. The nurse scripts call this before HealPlayerParty; a whiteout does not.
u16 KJH_GrantCenterCarePoint(void)
{
#if !IS_FRLG
    return FALSE;
#else
    u32 section = gMapHeader.regionMapSectionId;

    if (section >= MAPSEC_COUNT || CenterCareClaimed(section))
        return FALSE;
    for (u32 i = 0; i < PARTY_SIZE; i++)
    {
        struct Pokemon *mon = &gParties[B_TRAINER_PLAYER][i];
        u32 hp, maxHp;

        if (GetMonData(mon, MON_DATA_SPECIES) == SPECIES_NONE || GetMonData(mon, MON_DATA_IS_EGG))
            continue;
        hp = GetMonData(mon, MON_DATA_HP);
        maxHp = GetMonData(mon, MON_DATA_MAX_HP);
        if (maxHp == 0 || (u32)hp * 2 >= maxHp)
            continue;
        AddHalves(mon, 2); // one training point
        ClaimCenterCare(section);
        return TRUE;
    }
    return FALSE;
#endif
}

void KJH_ClearCenterCare(void)
{
#if IS_FRLG
    memset(gSaveBlock3Ptr->kjhCenterCare, 0, sizeof(gSaveBlock3Ptr->kjhCenterCare));
#endif
}

// Called once per foe knocked out or caught (Cmd_getexp). foughtBits: the party slots that fought it. A fainted
// Pokémon gets nothing, as with the newer games' Exp. Share.
void KJH_GiveTrainingPoints(enum BattlerId fainted, u32 foughtBits)
{
    struct Pokemon *foe = GetBattlerMon(fainted);
    u32 multiplier = KJH_TrainingFoeMultiplier(KJH_PackRole(fainted), GetMonData(foe, MON_DATA_TIER_MARK),
                                               IsBossTrainerMon(fainted));
    u32 points = KJH_TrainingPointsPerKo(gBattleMons[fainted].level, multiplier);

    for (u32 i = 0; i < PARTY_SIZE; i++)
    {
        struct Pokemon *mon = &gParties[B_TRAINER_PLAYER][i];

        if (IsValidForBattle(mon))
            AddHalves(mon, KJH_TrainingHalvesFor(points, (foughtBits >> i) & 1));
    }
}

u32 KJH_TrainingBank(struct Pokemon *mon)
{
    return GetMonData(mon, MON_DATA_TRAINING_BANK);
}

u32 KJH_TrainingPlaced(struct Pokemon *mon)
{
    u8 evs[NUM_STATS];

    GetEvs(mon, evs);
    return SumEvs(evs);
}

u32 KJH_TrainingPointsToPlace(struct Pokemon *mon)
{
    return min(KJH_TrainingBank(mon), TotalRoom(KJH_TrainingPlaced(mon), GetMonData(mon, MON_DATA_TIER_MARK)));
}

u32 KJH_PlaceTrainingPoints(struct Pokemon *mon, enum Stat stat, u32 count)
{
    u8 evs[NUM_STATS];
    u32 bank = KJH_TrainingBank(mon);
    u32 ev;

    GetEvs(mon, evs);
    count = min(count, min(bank, KJH_TrainingRoom(evs, GetMonData(mon, MON_DATA_TIER_MARK), stat)));
    if (count == 0)
        return 0;
    ev = evs[stat] + count;
    bank -= count;
    SetMonData(mon, MON_DATA_HP_EV + stat, &ev);
    SetMonData(mon, MON_DATA_TRAINING_BANK, &bank);
    CalculateMonStats(mon);
    return count;
}

// The EV-lowering berries (Pomeg, Kelpsy, Qualot, Hondew, Grepa, Tamato) take a stat's points out
// (PokemonUseItemEffects, which then sets the stat to 0): they go back to the bank
void KJH_TrainingRefund(struct Pokemon *mon, u32 points)
{
    AddHalves(mon, 2 * points);
}

// Lifetime earned TP: the monotonic counter, seeded from placed+bank on first read
u32 KJH_TrainingEarned(struct Pokemon *mon)
{
    u32 placed = KJH_TrainingPlaced(mon);
    u32 bank = KJH_TrainingBank(mon);
    u32 current = placed + bank;
    u32 lifetime = GetMonData(mon, MON_DATA_TRAINING_LIFETIME_HALVES) / 2;

    if (lifetime == 0 && current > 0)
    {
        lifetime = current;
        u32 halves = min(lifetime * 2, KJH_TRAINING_LIFETIME_HALVES_MAX);
        SetMonData(mon, MON_DATA_TRAINING_LIFETIME_HALVES, &halves);
    }
    return max(lifetime, current);
}

u32 KJH_TrainingTowardEvolution(struct Pokemon *mon, u32 *goal)
{
    *goal = KJH_TrainingEvolutionGoal(GetMonData(mon, MON_DATA_SPECIES));
    return (*goal == 0) ? 0 : min(KJH_TrainingEarned(mon), *goal);
}

u8 *KJH_StringTrainingEarned(u8 *dest, struct Pokemon *mon)
{
    u32 goal;
    u32 toward = KJH_TrainingTowardEvolution(mon, &goal);

    if (goal == 0)
        return ConvertIntToDecimalStringN(dest, KJH_TrainingEarned(mon), STR_CONV_MODE_LEFT_ALIGN, 4);
    dest = ConvertIntToDecimalStringN(dest, toward, STR_CONV_MODE_LEFT_ALIGN, 3);
    *dest++ = CHAR_SLASH;
    return ConvertIntToDecimalStringN(dest, goal, STR_CONV_MODE_LEFT_ALIGN, 3);
}

// The Summary's Training menu (LV-7): the stats' points and the bank when it opens; NO on "keep these?" puts them back
void KJH_TrainingSnapshot(struct Pokemon *mon, struct KjhTrainingSnapshot *snapshot)
{
    GetEvs(mon, snapshot->evs);
    snapshot->bank = KJH_TrainingBank(mon);
}

bool32 KJH_TrainingChanged(struct Pokemon *mon, const struct KjhTrainingSnapshot *snapshot)
{
    u8 evs[NUM_STATS];

    GetEvs(mon, evs);
    return KJH_TrainingBank(mon) != snapshot->bank || memcmp(evs, snapshot->evs, sizeof(evs)) != 0;
}

void KJH_TrainingRestore(struct Pokemon *mon, const struct KjhTrainingSnapshot *snapshot)
{
    u32 value;

    for (enum Stat i = 0; i < NUM_STATS; i++)
    {
        value = snapshot->evs[i];
        SetMonData(mon, MON_DATA_HP_EV + i, &value);
    }
    value = snapshot->bank;
    SetMonData(mon, MON_DATA_TRAINING_BANK, &value);
    CalculateMonStats(mon);
}
