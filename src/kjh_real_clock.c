#include "global.h"
#include "event_data.h"
#include "kjh_real_clock.h"
#include "rtc.h"
#include "constants/vars.h"

// Reserved spare variables preserve the existing save layout.
#if IS_FRLG
#define VAR_REAL_CLOCK_LOW (HOENN_KJH_SPARE_VARS_START + 9)
#define VAR_REAL_CLOCK_HIGH (HOENN_KJH_SPARE_VARS_START + 10)
#else
#define VAR_REAL_CLOCK_LOW 0x40FE
#define VAR_REAL_CLOCK_HIGH 0x40FF
#endif

static u32 DecodeBcd(u8 value)
{
    if ((value & 15) > 9 || (value >> 4) > 9)
        return 0xFF;
    return (value >> 4) * 10 + (value & 15);
}

bool32 KJH_RealClockDecode(const struct SiiRtcInfo *rtc, u32 *seconds)
{
    u32 year = DecodeBcd(rtc->year);
    u32 month = DecodeBcd(rtc->month);
    u32 day = DecodeBcd(rtc->day);
    u32 hour = DecodeBcd(rtc->hour);
    u32 minute = DecodeBcd(rtc->minute);
    u32 second = DecodeBcd(rtc->second);
    u32 days = 0;

    if ((rtc->status & SIIRTCINFO_POWER) || !(rtc->status & SIIRTCINFO_24HOUR)
     || year > 99 || month < 1 || month > 12 || day < 1
     || hour > 23 || minute > 59 || second > 59)
        return FALSE;
    if (day > sNumDaysInMonths[month - 1] + (month == 2 && IsLeapYear(2000 + year)))
        return FALSE;
    for (u32 i = 0; i < year; i++)
        days += 365 + IsLeapYear(2000 + i);
    for (u32 i = 1; i < month; i++)
        days += sNumDaysInMonths[i - 1] + (i == 2 && IsLeapYear(2000 + year));
    days += day - 1;
    *seconds = days * 86400 + hour * 3600 + minute * 60 + second;
    return TRUE;
}

bool32 KJH_RealClockNow(u32 *seconds)
{
    struct SiiRtcInfo rtc = {0};
    u32 probe, now, previous;

    // RtcInit/GetInfo/CheckInfo intentionally bypass hardware in fake-RTC builds.
    // Probe and decode raw BCD here without changing the story clock or RTC status.
    RtcDisableInterrupts();
    probe = SiiRtcProbe();
    RtcRestoreInterrupts();
    if (probe != 1)
        return FALSE;
    RtcGetRawInfo(&rtc);
    if (!KJH_RealClockDecode(&rtc, &now))
        return FALSE;
    previous = VarGet(VAR_REAL_CLOCK_LOW) | ((u32)VarGet(VAR_REAL_CLOCK_HIGH) << 16);
    if (previous != 0 && now < previous - 1)
        return FALSE;
    VarSet(VAR_REAL_CLOCK_LOW, (now + 1) & 0xFFFF);
    VarSet(VAR_REAL_CLOCK_HIGH, (now + 1) >> 16);
    *seconds = now;
    return TRUE;
}
