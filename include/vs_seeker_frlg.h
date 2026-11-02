#ifndef GUARD_VS_SEEKER_FRLG_H
#define GUARD_VS_SEEKER_FRLG_H

// KJH: the VS Seeker's rematches in Kanto, with FireRed's table and rules.
// Expansion's own rematch table (gRematchTable) is Hoenn's; in a FireRed build, vs_seeker.c and battle_setup.c
// use these functions instead. A trainer id may be any party of a rematch row (first battle or a rematch).

// The party a trainer brings to a rematch now: the next one not yet beaten, held back to the last one the
// player's progress unlocks. 0 if the trainer has no rematches.
u16 FrlgRematch_GetOpponent(u16 trainerId);

// The trainer's row in Kanto's table, the same for all their parties; -1 if they have no rematches.
s32 FrlgRematch_GetRow(u16 trainerId);

// "Wants a rematch", set by the VS Seeker and cleared by the battle, a new map or the VS Seeker recharging.
void FrlgRematch_SetWaiting(u16 trainerId);
bool32 FrlgRematch_IsWaiting(u16 trainerId);
void FrlgRematch_ClearWaiting(u16 trainerId);

#endif // GUARD_VS_SEEKER_FRLG_H
