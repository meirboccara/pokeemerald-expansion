// KJH: the in-game clock and the daily events (CF-4, src/kjh_clock.c). Expansion's fake RTC at 20x play time:
// 72 minutes of play make one day; each new day, DoTimeBasedEvents runs the daily events once.
#include "global.h"
#include "clock.h"
#include "event_data.h"
#include "fake_rtc.h"
#include "kjh_clock.h"
#include "rtc.h"
#include "test/test.h"

#define DAILY_FLAG DAILY_FLAGS_START
#define SECONDS_PER_PLAY_DAY (72 * 60)

static void Now(struct Time *time)
{
    RtcCalcLocalTime();
    *time = gLocalTime;
}

TEST("KJH: a new game's clock is set, in the morning of day 0")
{
    struct Time now;

    FlagClear(FLAG_SYS_CLOCK_SET);
    KJH_StartClock();
    Now(&now);
    EXPECT(FlagGet(FLAG_SYS_CLOCK_SET));
    EXPECT_EQ(now.hours, KJH_CLOCK_START_HOUR);
    EXPECT_EQ(now.minutes, 0);
    EXPECT_EQ(GetTimeOfDay(), TIME_MORNING);
    EXPECT_EQ(VarGet(VAR_DAYS), now.days);
}

TEST("KJH: a save without the clock gets one when loaded, a save with it keeps its time")
{
    struct Time now;

    FlagClear(FLAG_SYS_CLOCK_SET);
    FakeRtc_ManuallySetTime(3, 22, 0, 0);
    KJH_StartClockIfUnset();
    Now(&now);
    EXPECT_EQ(now.hours, KJH_CLOCK_START_HOUR);

    FakeRtc_ManuallySetTime(3, 22, 0, 0);
    KJH_StartClockIfUnset();
    Now(&now);
    EXPECT_EQ(now.hours, 22);
}

TEST("KJH: 72 minutes of play make one in-game day")
{
    struct Time start, end;

    KJH_StartClock();
    Now(&start);
    EXPECT_EQ(FakeRtc_GetSecondsRatio(), 20);
    for (u32 second = 0; second < SECONDS_PER_PLAY_DAY - 1; second++) // what PlayTimeCounter_Update does each second
        FakeRtc_TickTimeForward();
    Now(&end); // 20 in-game seconds short of a day: 07:59:40 the next day
    EXPECT_EQ(end.days, start.days + 1);
    EXPECT_EQ(end.hours, KJH_CLOCK_START_HOUR - 1);
    EXPECT_EQ(end.minutes, 59);
    FakeRtc_TickTimeForward();
    Now(&end);
    EXPECT_EQ(end.days, start.days + 1);
    EXPECT_EQ(end.hours, start.hours);
    EXPECT_EQ(end.minutes, start.minutes);
}

TEST("KJH: a new day clears the daily flags and runs the daily events once")
{
    u32 seed;

    KJH_StartClock();
    FlagSet(DAILY_FLAG);
    DoTimeBasedEvents(); // the same day: nothing runs
    EXPECT(FlagGet(DAILY_FLAG));

    seed = gSaveBlock1Ptr->dailySeed;
    FakeRtc_AdvanceTimeBy(1, 0, 0, 0);
    DoTimeBasedEvents();
    EXPECT(!FlagGet(DAILY_FLAG));
    EXPECT_NE(gSaveBlock1Ptr->dailySeed, seed);

    FlagSet(DAILY_FLAG);
    seed = gSaveBlock1Ptr->dailySeed;
    DoTimeBasedEvents(); // once per day
    EXPECT(FlagGet(DAILY_FLAG));
    EXPECT_EQ(gSaveBlock1Ptr->dailySeed, seed);
}

TEST("KJH: the daily events leave FireRed's story variables alone")
{
    // Emerald's daily events and day count use variables that a FireRed build gives to its own story
    static const u16 sFireRedVars[] =
    {
        VAR_MAGIKARP_SIZE_RECORD,          // Emerald's VAR_DAYS
        VAR_HOF_BRAG_STATE,                // VAR_BIRCH_STATE
        VAR_ICE_STEP_COUNT_FRLG,           // VAR_FRONTIER_GAMBLER_CHALLENGE
        VAR_ALTERING_CAVE_WILD_SET_FRLG,   // VAR_MIRAGE_RND_H
        VAR_MASSAGE_COOLDOWN_STEP_COUNTER, // VAR_MIRAGE_RND_L
        VAR_LINK_WIN_BRAG_STATE,           // VAR_POKELOT_RND1
    };

    KJH_StartClock();
    for (u32 i = 0; i < ARRAY_COUNT(sFireRedVars); i++)
        VarSet(sFireRedVars[i], 1000 + i);
    FakeRtc_AdvanceTimeBy(1, 0, 0, 0);
    DoTimeBasedEvents();
    FakeRtc_AdvanceTimeBy(5, 0, 0, 0);
    DoTimeBasedEvents();
    for (u32 i = 0; i < ARRAY_COUNT(sFireRedVars); i++)
        EXPECT_EQ(VarGet(sFireRedVars[i]), 1000 + i);
}
