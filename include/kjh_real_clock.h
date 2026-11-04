#ifndef GUARD_KJH_REAL_CLOCK_H
#define GUARD_KJH_REAL_CLOCK_H

#include "global.h"
#include "siirtc.h"

// Hardware wall clock, independent of the accelerated story clock. No playtime fallback.
// Seconds since 2000-01-01. Invalid/unavailable/backward clocks return FALSE.
bool32 KJH_RealClockNow(u32 *seconds);
bool32 KJH_RealClockDecode(const struct SiiRtcInfo *rtc, u32 *seconds);

#endif
