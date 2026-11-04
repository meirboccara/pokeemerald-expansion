#ifndef GUARD_KJH_ALPHA_LOCATOR_H
#define GUARD_KJH_ALPHA_LOCATOR_H

#include "global.h"

// Reusable item, 50000, unlocked after third badge
#define KJH_ALPHA_LOCATOR_PRICE 50000

enum KjhAlphaLocatorStatus
{
    KJH_ALPHA_LOCATOR_OK,
    KJH_ALPHA_LOCATOR_NO_CLOCK,
    KJH_ALPHA_LOCATOR_COOLDOWN,
    KJH_ALPHA_LOCATOR_NO_ELIGIBLE,
    KJH_ALPHA_LOCATOR_LOCKED,
};

bool32 KJH_AlphaLocatorUnlocked(void);
u32 KJH_AlphaLocatorCooldownRemaining(u32 seconds);
enum KjhAlphaLocatorStatus KJH_AlphaLocatorCanUse(u32 *seconds);
bool32 KJH_TryActivateAlphaLocator(void);
void KJH_AlphaLocatorPreview(void);
void KJH_AlphaLocatorNextAvailability(void);

#endif
