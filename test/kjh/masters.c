// KJH (LV-13): matching spots and training masters (src/kjh_masters.c, src/kjh_move_stars.c).
#include "global.h"
#include "event_data.h"
#include "kjh_masters.h"
#include "kjh_move_stars.h"
#include "test/battle.h"
#include "constants/opponents.h"

TEST("KJH: Kanto has 11 training masters, one per type, with their daily flags")
{
    static const enum Type sTypes[] = {TYPE_WATER, TYPE_FIRE, TYPE_ELECTRIC, TYPE_GHOST, TYPE_ICE, TYPE_BUG, TYPE_ROCK,
                                       TYPE_FIGHTING, TYPE_POISON, TYPE_GROUND, TYPE_NORMAL};

    for (u32 i = 0; i < KJH_MASTERS_COUNT; i++)
    {
        const struct KjhMaster *master = KJH_GetMaster(TRAINER_KJH_MASTER_WATER + i);

        EXPECT(master != NULL);
        if (master == NULL)
            continue;
        EXPECT_EQ(master->type, sTypes[i]);
        EXPECT_GE(master->flagOnce, DAILY_FLAGS_START);
        EXPECT_LE(master->flagTwice, DAILY_FLAGS_END);
    }
    EXPECT(KJH_GetMaster(TRAINER_LEADER_BROCK) == NULL);
}

TEST("KJH: a master can be fought twice per in-game day")
{
    FlagClear(FLAG_KJH_MASTER_FIRE_ONCE);
    FlagClear(FLAG_KJH_MASTER_FIRE_TWICE);
    EXPECT_EQ(KJH_MasterFightsLeftToday(TRAINER_KJH_MASTER_FIRE), 2);
    KJH_NoteMasterFought(TRAINER_KJH_MASTER_FIRE);
    EXPECT_EQ(KJH_MasterFightsLeftToday(TRAINER_KJH_MASTER_FIRE), 1);
    KJH_NoteMasterFought(TRAINER_KJH_MASTER_FIRE);
    EXPECT_EQ(KJH_MasterFightsLeftToday(TRAINER_KJH_MASTER_FIRE), 0);
    KJH_NoteMasterFought(TRAINER_KJH_MASTER_FIRE);
    EXPECT_EQ(KJH_MasterFightsLeftToday(TRAINER_KJH_MASTER_FIRE), 0);
    ClearDailyFlags();      // a new day (CF-4's daily events)
    EXPECT_EQ(KJH_MasterFightsLeftToday(TRAINER_KJH_MASTER_FIRE), 2);
}

TEST("KJH: a move of the field's type trains twice as fast; a master gives +20 to moves of its type, never doubled")
{
    // basic points, the move's type, the field, the master's type (TYPE_NONE: not a master)
    EXPECT_EQ(KJH_MovePointsForMove(1, TYPE_WATER, TYPE_WATER, TYPE_NONE), 2);     // a wild battle on water
    EXPECT_EQ(KJH_MovePointsForMove(1, TYPE_FIRE, TYPE_WATER, TYPE_NONE), 1);
    EXPECT_EQ(KJH_MovePointsForMove(5, TYPE_ROCK, TYPE_ROCK, TYPE_NONE), 10);      // Brock, Rock moves on his field
    EXPECT_EQ(KJH_MovePointsForMove(2, TYPE_GHOST, TYPE_GHOST, TYPE_GHOST), 20);   // the master's type: +20 flat
    EXPECT_EQ(KJH_MovePointsForMove(2, TYPE_DARK, TYPE_GHOST, TYPE_GHOST), 2);     // the rest: a trainer's
    EXPECT_EQ(KJH_MovePointsForMove(1, TYPE_NORMAL, TYPE_NONE, TYPE_NONE), 1);
}
