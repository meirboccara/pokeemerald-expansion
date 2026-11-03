#ifndef GUARD_KJH_CLOCK_H
#define GUARD_KJH_CLOCK_H

// KJH: the in-game clock (CF-4). Expansion's fake RTC runs with play time, 20x (OW_ALTERED_TIME_RATIO, Gen 9):
// one in-game day is 72 minutes of play. A new game starts it in the morning; a save without it gets it on load.
// Each new day, DoTimeBasedEvents runs the daily events once (clock.c): daily flags cleared, daily seed, outbreaks.

#define KJH_CLOCK_START_HOUR 8

void KJH_StartClock(void);
void KJH_StartClockIfUnset(void);

#endif // GUARD_KJH_CLOCK_H
