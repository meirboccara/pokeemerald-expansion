#include "global.h"
#include "battle_setup.h"
#include "event_data.h"
#include "item.h"
#include "safari_zone.h"
#include "kjh_alpha_locator.h"
#include "kjh_pack.h"
#include "kjh_real_clock.h"
#include "money.h"
#include "random.h"
#include "script.h"
#include "wild_encounter.h"
#include "constants/flags.h"
#include "constants/items.h"
#include "constants/vars.h"

#define SEVEN_DAYS_SECONDS (7 * 86400)

#if IS_FRLG
#define VAR_LOCATOR_DAY_LO (HOENN_KJH_SPARE_VARS_START + 7)
#define VAR_LOCATOR_DAY_HI (HOENN_KJH_SPARE_VARS_START + 8)
#else
#define VAR_LOCATOR_DAY_LO 0x40FC
#define VAR_LOCATOR_DAY_HI 0x40FD
#endif

static bool32 HasEligibleAlpha(void)
{
    bool8 isWater;
    enum Species species = GetLocalWildMon(&isWater);
    if (species == SPECIES_NONE)
        return FALSE;
    if (!KJH_PackSpeciesAllowed(species))
        return FALSE;
    if (GetSafariZoneFlag())
        return FALSE;
    if (CheckSilphScopeInPokemonTower(gSaveBlock1Ptr->location.mapGroup, gSaveBlock1Ptr->location.mapNum))
        return FALSE;
    return TRUE;
}

bool32 KJH_AlphaLocatorUnlocked(void)
{
    return FlagGet(FLAG_BADGE03_GET);
}

u32 KJH_AlphaLocatorCooldownRemaining(u32 seconds)
{
    u32 last = VarGet(VAR_LOCATOR_DAY_LO) | ((u32)VarGet(VAR_LOCATOR_DAY_HI) << 16);
    u32 elapsed;
    if (last == 0)
        return 0;
    elapsed = seconds >= last ? seconds - last : 0;
    return elapsed < SEVEN_DAYS_SECONDS ? SEVEN_DAYS_SECONDS - elapsed : 0;
}

enum KjhAlphaLocatorStatus KJH_AlphaLocatorCanUse(u32 *seconds)
{
    u32 remaining;
    if (!KJH_AlphaLocatorUnlocked())
        return KJH_ALPHA_LOCATOR_LOCKED;
    if (!KJH_RealClockNow(seconds))
        return KJH_ALPHA_LOCATOR_NO_CLOCK;
    remaining = KJH_AlphaLocatorCooldownRemaining(*seconds);
    if (remaining > 0)
        return KJH_ALPHA_LOCATOR_COOLDOWN;
    if (!HasEligibleAlpha())
        return KJH_ALPHA_LOCATOR_NO_ELIGIBLE;
    return KJH_ALPHA_LOCATOR_OK;
}

bool32 KJH_TryActivateAlphaLocator(void)
{
    u32 seconds;
    if (KJH_AlphaLocatorCanUse(&seconds) != KJH_ALPHA_LOCATOR_OK)
        return FALSE;
    KJH_PackSetNextEncounterAlpha();
    VarSet(VAR_LOCATOR_DAY_LO, (seconds + 1) & 0xFFFF);
    VarSet(VAR_LOCATOR_DAY_HI, (seconds + 1) >> 16);
    return TRUE;
}

void KJH_AlphaLocatorPreview(void)
{
    u32 seconds;
    gSpecialVar_Result = KJH_AlphaLocatorCanUse(&seconds);
}

void KJH_AlphaLocatorNextAvailability(void)
{
    u32 seconds;
    u32 remaining;
    if (!KJH_RealClockNow(&seconds))
    {
        gSpecialVar_Result = (u16)0xFFFF;
        return;
    }
    remaining = KJH_AlphaLocatorCooldownRemaining(seconds);
    gSpecialVar_Result = remaining / 86400;
}
