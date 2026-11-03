#ifndef GUARD_KJH_POWER_CAP_H
#define GUARD_KJH_POWER_CAP_H

// KJH: the power cap for strong moves (LV-11, docs/LEVELLESS_DESIGN.md §7 in the KJH repo). A move above 60 power
// hits at a percentage set by the badges of the region the battle is in: power = max(60, power x %), never more
// than its real power. One-hit KO moves are locked until the region's 6th badge (MOVE_LIMITATION_KJH_OHKO_LOCK).
// Status moves have no power, so they are never limited. Both sides follow it; link battles don't.
// B_KJH_POWER_CAP turns it off in the test build (include/config/test.h); KJH's tests turn it on with WITH_CONFIG.

#define KJH_POWER_CAP_FLOOR      60   // moves at or below it are never limited, and none is cut below it
#define KJH_OHKO_UNLOCK_BADGES   6

// Rules (no game state)
u32 KJH_PowerCapPercent(u32 regionBadges);
u32 KJH_CappedPower(u32 power, u32 percent);
bool32 KJH_IsOhkoLocked(u32 regionBadges);

// The badges of the region the player stands in (LV-18: Kanto's, Johto's or Hoenn's; Kanto's outside every region)
u32 KJH_RegionBadges(void);
// The cap where the player stands, whether or not it is on (B_KJH_POWER_CAP): by the region's badges, and none once
// the three Leagues are beaten (LV-18)
u32 KJH_PowerCapPercentHere(void);
bool32 KJH_IsOhkoLockedHere(void);

// In battle
void KJH_PowerCapStartBattle(void);
u32 KJH_PowerCapPercentNow(void); // the cap's share now: 100 when it is off (test build, link battles)
u32 KJH_CapBattleMovePower(u32 power);
bool32 KJH_IsOhkoLockedInBattle(void);
bool32 KJH_TryPreparePowerHeldBack(enum Move move); // TRUE once per battle, with the % in gBattleTextBuff1

// The Summary's POWER line
u32 KJH_SummaryHeldBackPower(u32 power);            // 0 when the move isn't held back
u8 *KJH_StringHeldBackPower(u8 *dest, u32 heldBackPower, u32 power);

#endif // GUARD_KJH_POWER_CAP_H
