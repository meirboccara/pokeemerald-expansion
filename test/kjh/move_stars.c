// KJH (LV-12): move stars and the training notebook (src/kjh_move_stars.c).
#include "global.h"
#include "kjh_levelless.h"
#include "kjh_move_stars.h"
#include "kjh_power_cap.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "event_data.h"
#include "test/battle.h"

static void Create(struct Pokemon *mon, u32 species, u32 level, u32 personality)
{
    CreateMon(mon, species, level, personality, OTID_STRUCT_PRESET(0));
}

static u32 FirstLevelUpMoveAbove(u32 species, u32 level)
{
    const struct LevelUpMove *learnset = GetSpeciesLevelUpLearnset(species);

    for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
    {
        if (learnset[i].level > level)
            return learnset[i].move;
    }
    return MOVE_NONE;
}

TEST("KJH: a move's stars come from its points: 10, 30, 60 and 100 for 2 to 5 stars")
{
    EXPECT_EQ(KJH_StarsFromPoints(0), 1);
    EXPECT_EQ(KJH_StarsFromPoints(9), 1);
    EXPECT_EQ(KJH_StarsFromPoints(10), 2);
    EXPECT_EQ(KJH_StarsFromPoints(29), 2);
    EXPECT_EQ(KJH_StarsFromPoints(30), 3);
    EXPECT_EQ(KJH_StarsFromPoints(59), 3);
    EXPECT_EQ(KJH_StarsFromPoints(60), 4);
    EXPECT_EQ(KJH_StarsFromPoints(99), 4);
    EXPECT_EQ(KJH_StarsFromPoints(100), 5);
    EXPECT_EQ(KJH_PointsForStars(3), 30);
    EXPECT_EQ(KJH_PointsForStars(5), 100);
    EXPECT_EQ(KJH_StarsPercent(1), 60);
    EXPECT_EQ(KJH_StarsPercent(3), 80);
    EXPECT_EQ(KJH_StarsPercent(5), 100);
}

TEST("KJH: a level-up move above the met level starts at 3 stars; older, TM and egg moves at 1")
{
    struct Pokemon mon;
    u32 later = FirstLevelUpMoveAbove(SPECIES_CHARMANDER, 10);

    ASSUME(later != MOVE_NONE);
    Create(&mon, SPECIES_CHARMANDER, 10, 1);
    ASSUME(GetMonData(&mon, MON_DATA_MET_LEVEL) == 10);
    KJH_ClearNotebook();
    EXPECT_EQ(KJH_GetMoveStars(&mon.box, later), 3);
    EXPECT_EQ(KJH_GetMovePoints(&mon.box, later), 30);
    EXPECT_EQ(KJH_GetMoveStars(&mon.box, MOVE_SCRATCH), 1);   // learned at level 1
    EXPECT_EQ(KJH_GetMoveStars(&mon.box, MOVE_DIG), 1);       // a TM move only
}

TEST("KJH: stars only hold back moves above 60 power, never below 60, and the lower of stars and power cap wins")
{
    EXPECT_EQ(KJH_StarredPower(90, 1), 60);     // 54, but never below 60
    EXPECT_EQ(KJH_StarredPower(120, 1), 72);
    EXPECT_EQ(KJH_StarredPower(120, 3), 96);
    EXPECT_EQ(KJH_StarredPower(120, 5), 120);
    EXPECT_EQ(KJH_StarredPower(40, 1), 40);     // Ember, Water Gun: always full
    EXPECT_EQ(KJH_StarredPower(60, 1), 60);
    EXPECT_EQ(KJH_StarsAndCapPercent(3, 50), 50);
    EXPECT_EQ(KJH_StarsAndCapPercent(3, 100), 80);
    EXPECT_EQ(KJH_StarsAndCapPercent(5, 90), 90);
}

TEST("KJH: a won battle gives each used move points: wild 1 (Leader x3, Alpha x6), trainer 2, boss 5")
{
    EXPECT_EQ(KJH_MovePointsForWin(KJH_WIN_WILD, KJH_TIER_REGULAR), 1);
    EXPECT_EQ(KJH_MovePointsForWin(KJH_WIN_WILD, KJH_TIER_LEADER), 3);
    EXPECT_EQ(KJH_MovePointsForWin(KJH_WIN_WILD, KJH_TIER_ALPHA), 6);
    EXPECT_EQ(KJH_MovePointsForWin(KJH_WIN_TRAINER, KJH_TIER_REGULAR), 2);
    EXPECT_EQ(KJH_MovePointsForWin(KJH_WIN_BOSS, KJH_TIER_REGULAR), 5);
}

TEST("KJH: points raise a move's stars, up to 100 points; the move keeps them when it is forgotten and relearned")
{
    struct Pokemon mon;

    Create(&mon, SPECIES_CHARMANDER, 10, 2);
    KJH_ClearNotebook();
    EXPECT_EQ(KJH_AddMovePoints(&mon.box, MOVE_SCRATCH, 9), 1);    // the stars after
    EXPECT_EQ(KJH_AddMovePoints(&mon.box, MOVE_SCRATCH, 1), 2);
    EXPECT_EQ(KJH_GetMovePoints(&mon.box, MOVE_SCRATCH), 10);

    SetMonMoveSlot(&mon, MOVE_DIG, 0);                              // Scratch forgotten
    EXPECT_EQ(KJH_GetMoveStars(&mon.box, MOVE_SCRATCH), 2);
    SetMonMoveSlot(&mon, MOVE_SCRATCH, 0);                          // and relearned
    EXPECT_EQ(KJH_GetMoveStars(&mon.box, MOVE_SCRATCH), 2);

    EXPECT_EQ(KJH_AddMovePoints(&mon.box, MOVE_SCRATCH, 200), 5);
    EXPECT_EQ(KJH_GetMovePoints(&mon.box, MOVE_SCRATCH), 100);

    // another Pokemon of the same species has its own
    Create(&mon, SPECIES_CHARMANDER, 10, 3);
    EXPECT_EQ(KJH_GetMoveStars(&mon.box, MOVE_SCRATCH), 1);
}

TEST("KJH: the notebook keeps 100 moves and drops the one unused the longest; untrained moves take no entry")
{
    struct Pokemon mon;

    KJH_ClearNotebook();
    Create(&mon, SPECIES_CHARMANDER, 10, 100);
    EXPECT_EQ(KJH_GetMoveStars(&mon.box, MOVE_SCRATCH), 1);
    EXPECT_EQ(KJH_NotebookCount(), 0);                              // reading takes no entry

    for (u32 i = 0; i < KJH_NOTEBOOK_SIZE; i++)
    {
        Create(&mon, SPECIES_CHARMANDER, 10, 100 + i);
        KJH_AddMovePoints(&mon.box, MOVE_SCRATCH, 10);
    }
    EXPECT_EQ(KJH_NotebookCount(), KJH_NOTEBOOK_SIZE);

    Create(&mon, SPECIES_CHARMANDER, 10, 100);                      // the first one trains again
    KJH_AddMovePoints(&mon.box, MOVE_SCRATCH, 1);
    Create(&mon, SPECIES_CHARMANDER, 10, 999);                      // a new one: the notebook is full
    KJH_AddMovePoints(&mon.box, MOVE_SCRATCH, 10);
    EXPECT_EQ(KJH_NotebookCount(), KJH_NOTEBOOK_SIZE);

    Create(&mon, SPECIES_CHARMANDER, 10, 100);
    EXPECT_EQ(KJH_GetMovePoints(&mon.box, MOVE_SCRATCH), 11);       // kept: used recently
    Create(&mon, SPECIES_CHARMANDER, 10, 101);
    EXPECT_EQ(KJH_GetMovePoints(&mon.box, MOVE_SCRATCH), 0);        // dropped: unused the longest
    Create(&mon, SPECIES_CHARMANDER, 10, 999);
    EXPECT_EQ(KJH_GetMovePoints(&mon.box, MOVE_SCRATCH), 10);
    KJH_ClearNotebook();
}

static void SetBadges(u32 count)
{
    for (u32 i = 0; i < NUM_BADGES; i++)
    {
        if (i < count)
            FlagSet(FLAG_BADGE01_GET + i);
        else
            FlagClear(FLAG_BADGE01_GET + i);
    }
}

// A test Pokemon's met level is its level, so its moves start at 1 star; points come from the notebook
SINGLE_BATTLE_TEST("KJH: move stars, a 150-power move at 1 star hits like a 90-power one at 5 stars", s16 damage)
{
    enum Move move;
    PARAMETRIZE { move = MOVE_ERUPTION; }
    PARAMETRIZE { move = MOVE_FLAMETHROWER; }
    GIVEN {
        ASSUME(GetMovePower(MOVE_ERUPTION) == 150);
        ASSUME(GetMovePower(MOVE_FLAMETHROWER) == 90);
        ASSUME(GetMoveCategory(MOVE_ERUPTION) == GetMoveCategory(MOVE_FLAMETHROWER));
        WITH_CONFIG(B_KJH_MOVE_STARS, TRUE);
        KJH_ClearNotebook();
        PLAYER(SPECIES_WOBBUFFET) { Moves(MOVE_ERUPTION, MOVE_FLAMETHROWER); }
        OPPONENT(SPECIES_WOBBUFFET);
        KJH_AddMovePoints(&gParties[B_TRAINER_PLAYER][0].box, MOVE_FLAMETHROWER, KJH_MOVE_POINTS_MAX);
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_EQ(results[0].damage, results[1].damage);
    }
}

// Eruption at 5 stars with 2 badges (cap 60%) and at 1 star (60%) with 6 badges (no cap): both hit at 90
SINGLE_BATTLE_TEST("KJH: move stars and the power cap don't stack, the lower percentage wins", s16 damage)
{
    u32 badges, points;
    PARAMETRIZE { badges = 2; points = KJH_MOVE_POINTS_MAX; }
    PARAMETRIZE { badges = 6; points = 0; }
    GIVEN {
        WITH_CONFIG(B_KJH_MOVE_STARS, TRUE);
        WITH_CONFIG(B_KJH_POWER_CAP, TRUE);
        SetBadges(badges);
        KJH_ClearNotebook();
        PLAYER(SPECIES_WOBBUFFET) { Moves(MOVE_ERUPTION); }
        OPPONENT(SPECIES_WOBBUFFET);
        if (points)
            KJH_AddMovePoints(&gParties[B_TRAINER_PLAYER][0].box, MOVE_ERUPTION, points);
    } WHEN {
        TURN { MOVE(player, MOVE_ERUPTION); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_EQ(results[0].damage, results[1].damage);
        SetBadges(0);
    }
}

SINGLE_BATTLE_TEST("KJH: move stars, the opponent's moves have none", s16 damage)
{
    u32 stars;
    PARAMETRIZE { stars = FALSE; }
    PARAMETRIZE { stars = TRUE; }
    GIVEN {
        WITH_CONFIG(B_KJH_MOVE_STARS, stars);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { Moves(MOVE_ERUPTION); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_ERUPTION); }
    } SCENE {
        HP_BAR(player, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_EQ(results[0].damage, results[1].damage);
    }
}
