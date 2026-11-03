// KJH: the power cap for strong moves (LV-11, include/kjh_power_cap.h).
#include "global.h"
#include "battle.h"
#include "battle_message.h"
#include "config_changes.h"
#include "event_data.h"
#include "kjh_power_cap.h"
#include "kjh_team_level.h"
#include "main.h"
#include "move.h"
#include "string_util.h"

static EWRAM_DATA bool8 sHeldBackShown = FALSE;

// docs/LEVELLESS_DESIGN.md §7: the share of a strong move's power, by the region's badges; the last entry holds from
// there on
static const u8 sPercentByBadges[] = {50, 50, 60, 70, 80, 90, 100};

u32 KJH_PowerCapPercent(u32 regionBadges)
{
    return sPercentByBadges[min(regionBadges, ARRAY_COUNT(sPercentByBadges) - 1)];
}

u32 KJH_CappedPower(u32 power, u32 percent)
{
    u32 capped;

    if (power <= KJH_POWER_CAP_FLOOR || percent >= 100)
        return power;
    capped = power * percent / 100;
    return max(capped, KJH_POWER_CAP_FLOOR);
}

bool32 KJH_IsOhkoLocked(u32 regionBadges)
{
    return regionBadges < KJH_OHKO_UNLOCK_BADGES;
}

u32 KJH_RegionBadges(void)
{
    return KJH_CountBadgesHere(); // LV-18: the region the player stands in
}

// Off in the test build, and in link battles: the two players' badges differ
static bool32 IsCapOn(void)
{
    if (!GetConfig(B_KJH_POWER_CAP))
        return FALSE;
    if (gMain.inBattle && (gBattleTypeFlags & BATTLE_TYPE_LINK))
        return FALSE;
    return TRUE;
}

static u32 CurrentPercent(void)
{
    if (!IsCapOn())
        return 100;
    return KJH_PowerCapPercent(KJH_RegionBadges());
}

u32 KJH_PowerCapPercentNow(void)
{
    return CurrentPercent();
}

void KJH_PowerCapStartBattle(void)
{
    sHeldBackShown = FALSE;
}

u32 KJH_CapBattleMovePower(u32 power)
{
    return KJH_CappedPower(power, CurrentPercent());
}

bool32 KJH_IsOhkoLockedInBattle(void)
{
    return IsCapOn() && KJH_IsOhkoLocked(KJH_RegionBadges());
}

// "Overheat is held back… (50%)", the first time in a battle that a move of either side is. It goes by the move's
// listed power: a move whose power changes in battle (Eruption, Low Kick) may be held back without the message.
bool32 KJH_TryPreparePowerHeldBack(enum Move move)
{
    u32 percent = CurrentPercent();
    u32 power = GetMovePower(move);

    if (sHeldBackShown || KJH_CappedPower(power, percent) >= power)
        return FALSE;
    sHeldBackShown = TRUE;
    PREPARE_BYTE_NUMBER_BUFFER(gBattleTextBuff1, 3, percent);
    return TRUE;
}

// The Summary's POWER line: the power the move hits with now, or 0 when it isn't held back
u32 KJH_SummaryHeldBackPower(u32 power)
{
    u32 heldBackPower = KJH_CappedPower(power, CurrentPercent());

    return heldBackPower < power ? heldBackPower : 0;
}

// "60 (70)"
u8 *KJH_StringHeldBackPower(u8 *dest, u32 heldBackPower, u32 power)
{
    dest = ConvertIntToDecimalStringN(dest, heldBackPower, STR_CONV_MODE_LEFT_ALIGN, 3);
    dest = StringCopy(dest, COMPOUND_STRING(" ("));
    dest = ConvertIntToDecimalStringN(dest, power, STR_CONV_MODE_LEFT_ALIGN, 3);
    return StringCopy(dest, COMPOUND_STRING(")"));
}
