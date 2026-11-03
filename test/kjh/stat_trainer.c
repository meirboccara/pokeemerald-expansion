// KJH: the stat trainer's limits (ENG-7, src/kjh_stat_trainer.c)
#include "global.h"
#include "kjh_stat_trainer.h"
#include "test/test.h"

TEST("KJH: the stat trainer keeps IVs within 0 to 31")
{
    EXPECT_EQ(KJH_ClampIv(-1), 0);
    EXPECT_EQ(KJH_ClampIv(20), 20);
    EXPECT_EQ(KJH_ClampIv(40), MAX_PER_STAT_IVS);
}

TEST("KJH: the stat trainer keeps an EV within 252, and all of them within 510")
{
    u8 evs[NUM_STATS] = {252, 252, 0, 0, 0, 0};

    EXPECT_EQ(KJH_SetEv(evs, 2, 10), 6);   // 504 in the other stats: 6 left
    EXPECT_EQ(KJH_SetEv(evs, 0, 300), MAX_PER_STAT_EVS);
    EXPECT_EQ(KJH_SetEv(evs, 0, -5), 0);
    EXPECT_EQ(KJH_SetEv(evs, 0, 100), 100);
}
