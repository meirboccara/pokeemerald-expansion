#ifndef GUARD_KJH_TRAVEL_H
#define GUARD_KJH_TRAVEL_H

// KJH: faster travel (CF-11). L turns auto-run on or off (with the Running Shoes; not in the L=A button mode);
// with it on, the player runs without B and walks while B is held. Holding B on the bike or while surfing goes
// faster than normal.

bool32 KJH_CanToggleAutoRun(void);
void KJH_ToggleAutoRun(void);
bool32 KJH_IsRunning(u16 heldKeys);
bool32 KJH_IsFastTravelHeld(u16 heldKeys);

#endif // GUARD_KJH_TRAVEL_H
