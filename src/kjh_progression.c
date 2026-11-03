// KJH: trainer levels and "strategy" for boss trainers, on pokeemerald-expansion. Ported from the KJH repo's
// source/pokefirered/src/kjh_progression.c, then moved to the levels-free design (LV-3).
//
// Trainers' levels are the data's: kjh_tools/zone_levels.py rewrote src/data/trainers_frlg.party from the zones
// (route trainers at their zone's top, Gym trainers just under their Gym's ace, the League one step per room).
// In the levels-free game, a whole Gym moves so that its Leader's ace is the team's ceiling for the badges the
// player has (KJH_GymLevelShift: 14, 22 ... 80), so Kanto's middle Gyms can be done in any order.
// Boss trainers (gym leaders, Elite Four, champions, rivals, team bosses) also get good IVs, EVs and a nature
// that grow with the badges (kjh_boss_rules.c), a held Sitrus Berry once the adventure is under way, the smart
// trainer AI and, once moved, a moveset rebuilt for their new level (BuildBossMoveset).
#include "global.h"
#include "battle.h"
#include "battle_util.h"
#include "event_data.h"
#include "move.h"
#include "pokemon.h"
#include "kjh_bond.h"
#include "kjh_boss_rules.h"
#include "kjh_hidden_ability.h"
#include "kjh_progression.h"
#include "kjh_team_level.h"
#include "constants/battle_ai.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/opponents.h"
#include "constants/trainers.h"

// Below this level, a boss is an early one: IVs 20, no Sitrus Berry. On LV-3's curve, Brock, Misty and Lt. Surge
// (30) are early, Erika (40) is late, as Brock, Misty and Lt. Surge were in FireRed.
#define KJH_LATE_BOSS_LEVEL 31
#define KJH_EARLY_BOSS_IV   20

// The first rival battle, in Oak's lab, is a gentle one: the rival's Pokemon is at Pallet Town's level (the data's),
// with FireRed's IVs, moves and AI
static bool32 IsFirstRivalBattle(u16 trainerNum)
{
#if IS_FRLG
    return trainerNum == TRAINER_RIVAL_OAKS_LAB_SQUIRTLE || trainerNum == TRAINER_RIVAL_OAKS_LAB_BULBASAUR
        || trainerNum == TRAINER_RIVAL_OAKS_LAB_CHARMANDER;
#else
    return FALSE;
#endif
}

u8 KJH_BossKind(u8 trainerClass)
{
    switch (trainerClass)
    {
    case TRAINER_CLASS_LEADER_FRLG:
    case TRAINER_CLASS_LEADER:
        return KJH_BOSS_LEADER;
    case TRAINER_CLASS_ELITE_FOUR_FRLG:
    case TRAINER_CLASS_ELITE_FOUR:
        return KJH_BOSS_ELITE_FOUR;
    case TRAINER_CLASS_CHAMPION_FRLG:
    case TRAINER_CLASS_CHAMPION:
        return KJH_BOSS_CHAMPION;
    case TRAINER_CLASS_RIVAL_EARLY_FRLG:
    case TRAINER_CLASS_RIVAL_LATE_FRLG:
    case TRAINER_CLASS_RIVAL:
        return KJH_BOSS_RIVAL;
    case TRAINER_CLASS_BOSS_FRLG:
    case TRAINER_CLASS_AQUA_LEADER:
    case TRAINER_CLASS_MAGMA_LEADER:
    case TRAINER_CLASS_AQUA_ADMIN:
    case TRAINER_CLASS_MAGMA_ADMIN:
        return KJH_BOSS_TEAM;
    }
    return KJH_BOSS_NONE;
}

static bool32 IsBoss(u8 trainerClass, u16 trainerNum)
{
    return trainerNum != TRAINER_NONE && KJH_BossKind(trainerClass) != KJH_BOSS_NONE && !IsFirstRivalBattle(trainerNum);
}

bool32 KJH_IsBossTrainer(const struct Trainer *trainer, u16 trainerNum)
{
    return IsBoss(trainer->trainerClass, trainerNum);
}

s32 KJH_TeamLevelShift(u16 trainerNum)
{
    if (trainerNum == TRAINER_NONE)
        return 0;

    return KJH_GymLevelShift();
}

static bool32 HasCustomMoves(const struct TrainerMon *mon)
{
    for (u32 i = 0; i < MAX_MON_MOVES; i++)
    {
        if (mon->moves[i] != MOVE_NONE)
            return TRUE;
    }
    return FALSE;
}

void KJH_PrepareTrainerMon(struct TrainerMon *out, const struct TrainerMon *in, u16 trainerNum, s32 shift)
{
    s32 level = in->lvl + shift;

    *out = *in;
    if (trainerNum == TRAINER_NONE)
        return;

    out->lvl = min(max(level, 1), MAX_LEVEL);
    // A moved team gets level-up moves at its new level (a boss then rebuilds its moveset from them,
    // KJH_FinishTrainerMon); the others keep FireRed's handmade movesets.
    if (shift != 0)
    {
        for (u32 i = 0; i < MAX_MON_MOVES; i++)
            out->moves[i] = MOVE_NONE;
    }
}

static bool32 HasMove(const u16 *moves, u32 n, u16 move)
{
    for (u32 i = 0; i < n; i++)
    {
        if (moves[i] == move)
            return TRUE;
    }
    return FALSE;
}

static bool32 IsStab(u16 move, u16 species)
{
    enum Type type = GetMoveType(move);
    return type == GetSpeciesType(species, 0) || type == GetSpeciesType(species, 1);
}

// A move's base power for KJH's boss rules: power 1 = variable damage (Night Shade, Seismic Toss, Low Kick...),
// counted as 60
static u32 EffectivePower(u16 move)
{
    u32 power = GetMovePower(move);
    return power == 1 ? 60 : power;
}

static u16 MoveScore(u16 move, u16 species)
{
    u32 accuracy = GetMoveAccuracy(move);
    u32 s;
    enum BattleMoveEffects effect;

    if (move == MOVE_NONE || GetMoveCategory(move) == DAMAGE_CATEGORY_STATUS || EffectivePower(move) == 0)
        return 0;
    s = EffectivePower(move) * (accuracy ? accuracy : 100) / 100;
    if (IsStab(move, species))
        s = s * 3 / 2;
    effect = GetMoveEffect(move);
    if (MoveHasAdditionalEffectSelf(move, MOVE_EFFECT_RECHARGE) || IsExplosionMove(move)
     || effect == EFFECT_DREAM_EATER || effect == EFFECT_FOCUS_PUNCH || effect == EFFECT_SNORE
     || effect == EFFECT_FALSE_SWIPE)
        s /= 3;
    return s;
}

// A boss moveset: the best STAB attack, the best attack of another type, the next best attack, and a
// support move (status / stat boost / healing) if the trainer's original moveset had one.
static void BuildBossMoveset(struct Pokemon *mon, const enum Move *customMoves)
{
    u16 species = GetMonData(mon, MON_DATA_SPECIES);
    u16 pool[MAX_MON_MOVES * 2];
    u16 chosen[MAX_MON_MOVES];
    u32 n = 0, c = 0;
    u16 support = MOVE_NONE;

    for (u32 i = 0; i < MAX_MON_MOVES; i++)
    {
        u16 mv = GetMonData(mon, MON_DATA_MOVE1 + i);
        if (mv != MOVE_NONE && !HasMove(pool, n, mv))
            pool[n++] = mv;
    }
    if (customMoves != NULL)
    {
        for (u32 i = 0; i < MAX_MON_MOVES; i++)
        {
            u16 mv = customMoves[i];
            if (mv == MOVE_NONE)
                continue;
            if (GetMoveCategory(mv) == DAMAGE_CATEGORY_STATUS && support == MOVE_NONE)
                support = mv;
            if (!HasMove(pool, n, mv))
                pool[n++] = mv;
        }
    }
    // 1) best STAB, 2) best off-type attack, 3) next best attack
    for (u32 j = 0; j < 3; j++)
    {
        u16 best = MOVE_NONE, bestScore = 0;
        for (u32 i = 0; i < n; i++)
        {
            u16 mv = pool[i];
            u16 sc = MoveScore(mv, species);
            if (HasMove(chosen, c, mv) || sc == 0)
                continue;
            if (j == 0 && !IsStab(mv, species))
                continue;
            if (j == 1 && c > 0 && GetMoveType(mv) == GetMoveType(chosen[0]))
                continue;
            if (sc > bestScore)
            {
                best = mv;
                bestScore = sc;
            }
        }
        if (best != MOVE_NONE)
            chosen[c++] = best;
    }
    if (support != MOVE_NONE && !HasMove(chosen, c, support) && c < MAX_MON_MOVES)
        chosen[c++] = support;
    // fill the remaining slots with whatever is left, strongest first
    while (c < MAX_MON_MOVES)
    {
        u16 best = MOVE_NONE, bestScore = 0;
        for (u32 i = 0; i < n; i++)
        {
            u16 sc = MoveScore(pool[i], species);
            if (!HasMove(chosen, c, pool[i]) && sc >= bestScore)
            {
                best = pool[i];
                bestScore = sc;
            }
        }
        if (best == MOVE_NONE)
            break;
        chosen[c++] = best;
    }
    if (c == 0)
        return;
    for (u32 i = 0; i < MAX_MON_MOVES; i++)
    {
        u16 mv = i < c ? chosen[i] : MOVE_NONE;
        u8 pp = i < c ? GetMovePP(mv) : 0;
        SetMonData(mon, MON_DATA_MOVE1 + i, &mv);
        SetMonData(mon, MON_DATA_PP1 + i, &pp);
    }
}

// A boss Pokemon's EVs, growing with the player's badges, and a nature that fits its moves (kjh_boss_rules.c).
// On expansion each move has its own physical/special category (in FireRed it came from the move's type).
// The species' base stats and the summed power of its physical and special moves.
static void GetBaseStatsAndPower(struct Pokemon *mon, u8 *baseStats, u16 *physicalPower, u16 *specialPower)
{
    u16 species = GetMonData(mon, MON_DATA_SPECIES);

    *physicalPower = *specialPower = 0;
    for (u32 i = 0; i < NUM_STATS; i++)
        baseStats[i] = GetSpeciesBaseStat(species, i);
    for (u32 i = 0; i < MAX_MON_MOVES; i++)
    {
        u16 move = GetMonData(mon, MON_DATA_MOVE1 + i);

        if (move == MOVE_NONE)
            continue;
        if (GetMoveCategory(move) == DAMAGE_CATEGORY_PHYSICAL)
            *physicalPower += EffectivePower(move);
        else if (GetMoveCategory(move) == DAMAGE_CATEGORY_SPECIAL)
            *specialPower += EffectivePower(move);
    }
}

// The nature that counts for stats (as a mint sets it); the Pokemon's personality stays as generated.
static void SetBossNature(struct Pokemon *mon, const u8 *baseStats, u16 physicalPower, u16 specialPower)
{
    u32 nature = KJH_BossNature(baseStats, physicalPower, specialPower);

    SetMonData(mon, MON_DATA_HIDDEN_NATURE, &nature);
}

static void SetBossEvsAndNature(struct Pokemon *mon)
{
    u8 baseStats[NUM_STATS], evs[NUM_STATS];
    u16 physicalPower, specialPower;

    GetBaseStatsAndPower(mon, baseStats, &physicalPower, &specialPower);
    KJH_BossEvs(baseStats, physicalPower, specialPower, KJH_CountBadgesHere(), evs);
    for (u32 i = 0; i < NUM_STATS; i++)
        SetMonData(mon, MON_DATA_HP_EV + i, &evs[i]);
    SetBossNature(mon, baseStats, physicalPower, specialPower);
}

// The rival's battles in order (each has a party per starter, in a row); 0 for another trainer.
#define RIVAL_PARTIES_PER_BATTLE 3
static u32 RivalBattleNumber(u16 trainerNum)
{
#if IS_FRLG
    static const u16 sFirstParties[] =
    {
        TRAINER_RIVAL_OAKS_LAB_SQUIRTLE, TRAINER_RIVAL_ROUTE22_EARLY_SQUIRTLE, TRAINER_RIVAL_CERULEAN_SQUIRTLE,
        TRAINER_RIVAL_SS_ANNE_SQUIRTLE, TRAINER_RIVAL_POKEMON_TOWER_SQUIRTLE, TRAINER_RIVAL_SILPH_SQUIRTLE,
        TRAINER_RIVAL_ROUTE22_LATE_SQUIRTLE,
    };

    for (u32 i = 0; i < ARRAY_COUNT(sFirstParties); i++)
    {
        if (trainerNum >= sFirstParties[i] && trainerNum < sFirstParties[i] + RIVAL_PARTIES_PER_BATTLE)
            return i + 1;
    }
#endif

    return 0;
}

// LV-16: the trainer's group and step for KJH_TrainerTraining.
static struct KjhTraining GetTraining(const struct Trainer *trainer, u16 trainerNum, bool32 ace)
{
    u32 badges = KJH_CountBadgesHere(), rivalBattle = RivalBattleNumber(trainerNum);
    u8 gymNumber = min(badges + 1, NUM_BADGES);

    switch (KJH_BossKind(trainer->trainerClass))
    {
    case KJH_BOSS_ELITE_FOUR:
    case KJH_BOSS_CHAMPION:
        return KJH_TrainerTraining(KJH_GROUP_LEAGUE, 0, ace);
    case KJH_BOSS_LEADER:
    case KJH_BOSS_TEAM:
        return KJH_TrainerTraining(KJH_GROUP_GYM_LEADER, gymNumber, ace);
    case KJH_BOSS_RIVAL:
        if (rivalBattle)
            return KJH_TrainerTraining(KJH_GROUP_RIVAL, rivalBattle, ace);
        break;
    default:
        if (KJH_IsInGym())
            return KJH_TrainerTraining(KJH_GROUP_GYM_TRAINER, gymNumber, ace);
        break;
    }
    return KJH_TrainerTraining(KJH_GROUP_ROUTE, badges, ace);
}

static void SetTraining(struct Pokemon *mon, struct KjhTraining training, bool32 boss)
{
    u8 baseStats[NUM_STATS], evs[NUM_STATS];
    u16 physicalPower, specialPower;
    u32 iv = training.iv, friendship = KJH_BondToFriendship(training.bond);

    GetBaseStatsAndPower(mon, baseStats, &physicalPower, &specialPower);
    KJH_TrainingEvs(baseStats, physicalPower, specialPower, training.evs, evs);
    for (u32 i = 0; i < NUM_STATS; i++)
    {
        SetMonData(mon, MON_DATA_HP_IV + i, &iv);
        SetMonData(mon, MON_DATA_HP_EV + i, &evs[i]);
    }

    if (boss)
        SetBossNature(mon, baseStats, physicalPower, specialPower);
    SetMonData(mon, MON_DATA_FRIENDSHIP, &friendship);
}

void KJH_FinishTrainerMon(struct Pokemon *mon, const struct TrainerMon *in, const struct Trainer *trainer,
                          u16 trainerNum, s32 shift, bool32 ace)
{
    bool32 moved = shift != 0;
    bool32 hasCustomMoves = HasCustomMoves(in);
    bool32 trained = trainerNum != TRAINER_NONE && KJH_IsLevelsFree() && !IsFirstRivalBattle(trainerNum);
    bool32 late;
    u32 iv, item;

    if (!KJH_IsBossTrainer(trainer, trainerNum))
    {
        // LV-16: in the levels-free game every trainer's Pokemon is trained by its group's table
        if (trained)
        {
            SetTraining(mon, GetTraining(trainer, trainerNum, ace), FALSE);
            CalculateMonStats(mon);
        }
        return; // KJH_PrepareTrainerMon already chose its moves
    }

    // Bosses get tougher as the adventure goes on: early bosses get good IVs, later ones perfect IVs and a Sitrus
    // Berry. A Gym met late (moved by the badges) is a late one. In the levels-free game, IVs come from the
    // boss's group table instead (below).
    late = GetMonData(mon, MON_DATA_LEVEL) >= KJH_LATE_BOSS_LEVEL;
    iv = late ? MAX_PER_STAT_IVS : KJH_EARLY_BOSS_IV;
    for (u32 i = 0; i < NUM_STATS; i++)
        SetMonData(mon, MON_DATA_HP_IV + i, &iv);
    item = GetMonData(mon, MON_DATA_HELD_ITEM);
    if (item == ITEM_NONE && late)
    {
        item = ITEM_SITRUS_BERRY;
        SetMonData(mon, MON_DATA_HELD_ITEM, &item);
    }
    // Bosses that weren't moved keep FireRed's handmade movesets (GenerateMonFromTrainerMon set them)
    if (moved || !hasCustomMoves)
        BuildBossMoveset(mon, hasCustomMoves ? in->moves : NULL);
    if (trained)
        SetTraining(mon, GetTraining(trainer, trainerNum, ace), TRUE);
    else
        SetBossEvsAndNature(mon);
    // Bosses use their Pokemon's Hidden Abilities (ENG-7), unless their party data sets an ability
    if (in->ability == ABILITY_NONE)
    {
        u32 abilityNum = KJH_BossAbilityNum(GetMonData(mon, MON_DATA_SPECIES), GetMonData(mon, MON_DATA_ABILITY_NUM));

        SetMonData(mon, MON_DATA_ABILITY_NUM, &abilityNum);
    }
    CalculateMonStats(mon);
}

u64 KJH_AiFlags(u64 baseFlags, u8 trainerClass, u16 trainerNum)
{
    if (IsBoss(trainerClass, trainerNum))
        return baseFlags | KJH_BOSS_AI_FLAGS;
    return baseFlags | AI_FLAG_CHECK_BAD_MOVE; // every trainer avoids moves that would do nothing
}
