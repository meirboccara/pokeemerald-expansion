// KJH: level progression across regions and "strategy" for boss trainers, on pokeemerald-expansion. Ported from
// the KJH repo's source/pokefirered/src/kjh_progression.c; the rules are the same (docs/TRAINER_LEVELS.md there).
//
// Play order is KANTO -> KANTO LEAGUE -> JOHTO -> JOHTO LEAGUE -> HOENN -> HOENN LEAGUE. Kanto keeps
// FireRed's levels; each region opens just below the League before it and climbs past it (kjh_level_bands.c).
// Trainers follow the band of the map they are met on. On top of that, trainers catch up with a strong party
// (after Pokemon Unbound): against the average of your best Pokemon, as many as the trainer has, a normal
// trainer's team rises to 2-3 levels under it, a boss's ace from 1 under it early to 1 above it late, by
// badges; they never go down (kjh_level_bands.c, KJH_TrainerLevelBoost).
// Boss trainers (gym leaders, Elite Four, champions, rivals, team bosses) also get good IVs, EVs and a nature
// that grow with the badges (kjh_boss_rules.c), a held Sitrus Berry once the adventure is under way, the smart
// trainer AI and, outside Kanto or once raised, a moveset rebuilt for their new level (BuildBossMoveset).
//
// Not ported yet: the boss's Hidden Ability (ENG-5/ENG-7) and the Johto and Hoenn map bands (only Kanto is in
// the expansion build so far, ENG-3/ENG-9).
#include "global.h"
#include "battle.h"
#include "battle_util.h"
#include "event_data.h"
#include "move.h"
#include "pokemon.h"
#include "kjh_boss_rules.h"
#include "kjh_hidden_ability.h"
#include "kjh_level_bands.h"
#include "kjh_progression.h"
#include "constants/battle_ai.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/opponents.h"
#include "constants/trainers.h"

// Below this level (before catching up), a Kanto boss is an early one: IVs 20, no Sitrus Berry
#define KJH_LATE_BOSS_LEVEL 25
#define KJH_EARLY_BOSS_IV   20

// The band of the map the player is on. Only Kanto is in the expansion build so far.
static u8 CurrentMapBand(void)
{
    return KJH_BAND_KANTO;
}

// The Johto League is Indigo Plateau's second season: FireRed's Elite Four and Champion rematch teams
static u8 TrainerBand(u16 trainerNum)
{
#if IS_FRLG
    switch (trainerNum)
    {
    case TRAINER_ELITE_FOUR_LORELEI_2:
    case TRAINER_ELITE_FOUR_BRUNO_2:
    case TRAINER_ELITE_FOUR_AGATHA_2:
    case TRAINER_ELITE_FOUR_LANCE_2:
    case TRAINER_CHAMPION_REMATCH_SQUIRTLE:
    case TRAINER_CHAMPION_REMATCH_BULBASAUR:
    case TRAINER_CHAMPION_REMATCH_CHARMANDER:
        return KJH_BAND_JOHTO_LEAGUE;
    }
#endif
    return CurrentMapBand();
}

// The first rival battle, in Oak's lab, is a gentle one: the rival's Pokemon is at the level of yours, with
// FireRed's IVs, moves and AI
static bool32 IsFirstRivalBattle(u16 trainerNum)
{
#if IS_FRLG
    return trainerNum == TRAINER_RIVAL_OAKS_LAB_SQUIRTLE || trainerNum == TRAINER_RIVAL_OAKS_LAB_BULBASAUR
        || trainerNum == TRAINER_RIVAL_OAKS_LAB_CHARMANDER;
#else
    return FALSE;
#endif
}

// The player's party levels (eggs left out); returns how many
static u8 PlayerPartyLevels(u8 *levels)
{
    u8 count = 0;

    for (u32 i = 0; i < PARTY_SIZE; i++)
    {
        struct Pokemon *mon = &gParties[B_TRAINER_PLAYER][i];
        u32 species = GetMonData(mon, MON_DATA_SPECIES_OR_EGG);

        if (species != SPECIES_NONE && species != SPECIES_EGG)
            levels[count++] = GetMonData(mon, MON_DATA_LEVEL);
    }
    return count;
}

// Badges of all regions together (only Kanto's so far)
static u8 CountAllBadges(void)
{
    u8 badges = 0;

    for (u32 i = 0; i < NUM_BADGES; i++)
    {
        if (FlagGet(FLAG_BADGE01_GET + i))
            badges++;
    }
    return badges;
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

u8 KJH_TeamLevelBoost(const struct Trainer *trainer, u16 trainerNum, const u32 *monIndices, u8 monsCount)
{
    u8 levels[PARTY_SIZE];
    u8 count = PlayerPartyLevels(levels);
    u8 teamTop = 0, partyBest = 0;

    if (count == 0 || trainerNum == TRAINER_NONE)
        return 0;
    for (u32 i = 0; i < monsCount; i++)
    {
        u8 level = KJH_BandLevel(TrainerBand(trainerNum), trainer->party[monIndices[i]].lvl);

        if (level > teamTop)
            teamTop = level;
    }
    for (u32 i = 0; i < count; i++)
    {
        if (levels[i] > partyBest)
            partyBest = levels[i];
    }
    if (IsFirstRivalBattle(trainerNum))
        return partyBest > teamTop ? partyBest - teamTop : 0;
    return KJH_TrainerLevelBoost(teamTop, KJH_PartyLevel(levels, count, monsCount), CountAllBadges(),
                                 KJH_IsBossTrainer(trainer, trainerNum));
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

void KJH_PrepareTrainerMon(struct TrainerMon *out, const struct TrainerMon *in, u16 trainerNum, u8 boost)
{
    u16 level = KJH_BandLevel(TrainerBand(trainerNum), in->lvl) + boost;

    *out = *in;
    if (trainerNum == TRAINER_NONE)
        return;
    out->lvl = level > MAX_LEVEL ? MAX_LEVEL : level;
    // Kanto keeps FireRed's handmade movesets; scaled regions and raised teams use level-up moves at the new
    // level (a boss then rebuilds its moveset from them, KJH_FinishTrainerMon)
    if (TrainerBand(trainerNum) != KJH_BAND_KANTO || boost != 0)
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
static void SetBossEvsAndNature(struct Pokemon *mon)
{
    u16 species = GetMonData(mon, MON_DATA_SPECIES);
    u8 baseStats[NUM_STATS], evs[NUM_STATS];
    u16 physicalPower = 0, specialPower = 0;
    u32 nature;

    for (u32 i = 0; i < NUM_STATS; i++)
        baseStats[i] = GetSpeciesBaseStat(species, i);
    for (u32 i = 0; i < MAX_MON_MOVES; i++)
    {
        u16 move = GetMonData(mon, MON_DATA_MOVE1 + i);

        if (move == MOVE_NONE)
            continue;
        if (GetMoveCategory(move) == DAMAGE_CATEGORY_PHYSICAL)
            physicalPower += EffectivePower(move);
        else if (GetMoveCategory(move) == DAMAGE_CATEGORY_SPECIAL)
            specialPower += EffectivePower(move);
    }
    KJH_BossEvs(baseStats, physicalPower, specialPower, CountAllBadges(), evs);
    for (u32 i = 0; i < NUM_STATS; i++)
        SetMonData(mon, MON_DATA_HP_EV + i, &evs[i]);
    // the nature that counts for stats (as a mint sets it); the Pokemon's personality stays as generated
    nature = KJH_BossNature(baseStats, physicalPower, specialPower);
    SetMonData(mon, MON_DATA_HIDDEN_NATURE, &nature);
}

void KJH_FinishTrainerMon(struct Pokemon *mon, const struct TrainerMon *in, const struct Trainer *trainer, u16 trainerNum, u8 boost)
{
    bool32 scaled = TrainerBand(trainerNum) != KJH_BAND_KANTO;
    bool32 raised = boost != 0;
    bool32 hasCustomMoves = HasCustomMoves(in);
    bool32 late;
    u32 iv, item;

    if (!KJH_IsBossTrainer(trainer, trainerNum))
        return; // KJH_PrepareTrainerMon already chose its moves

    // Bosses get tougher as the adventure goes on: early Kanto bosses (below Lv 25, before they catch up with
    // the party) get good IVs, later ones perfect IVs and a Sitrus Berry.
    late = scaled || GetMonData(mon, MON_DATA_LEVEL) - boost >= KJH_LATE_BOSS_LEVEL;
    iv = late ? MAX_PER_STAT_IVS : KJH_EARLY_BOSS_IV;
    for (u32 i = 0; i < NUM_STATS; i++)
        SetMonData(mon, MON_DATA_HP_IV + i, &iv);
    item = GetMonData(mon, MON_DATA_HELD_ITEM);
    if (item == ITEM_NONE && late)
    {
        item = ITEM_SITRUS_BERRY;
        SetMonData(mon, MON_DATA_HELD_ITEM, &item);
    }
    // Kanto bosses that weren't raised keep FireRed's handmade movesets (GenerateMonFromTrainerMon set them)
    if (scaled || raised || !hasCustomMoves)
        BuildBossMoveset(mon, hasCustomMoves ? in->moves : NULL);
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
    if (TrainerBand(trainerNum) != KJH_BAND_KANTO)
        return baseFlags | AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT;
    return baseFlags | AI_FLAG_CHECK_BAD_MOVE; // every trainer avoids moves that would do nothing
}
