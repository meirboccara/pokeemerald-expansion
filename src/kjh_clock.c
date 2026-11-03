// KJH: the in-game clock (CF-4, include/kjh_clock.h).
#include "global.h"
#include "clock.h"
#include "event_data.h"
#include "fake_rtc.h"
#include "kjh_clock.h"

// Day 0 at KJH_CLOCK_START_HOUR, then the daily events' day count (VAR_DAYS) and FLAG_SYS_CLOCK_SET
void KJH_StartClock(void)
{
    FakeRtc_ManuallySetTime(0, KJH_CLOCK_START_HOUR, 0, 0);
    InitTimeBasedEvents();
}

// A save made before the clock existed (FLAG_SYS_CLOCK_SET unset) gets one when it's loaded
void KJH_StartClockIfUnset(void)
{
    if (OW_USE_FAKE_RTC && !FlagGet(FLAG_SYS_CLOCK_SET))
        KJH_StartClock();
}
