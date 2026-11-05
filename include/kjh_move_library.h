#ifndef GUARD_KJH_MOVE_LIBRARY_H
#define GUARD_KJH_MOVE_LIBRARY_H

// KJH (LV-10): the move library (docs/LEVELLESS_DESIGN.md §2, §6). Every move a Pokemon may use: its level-up moves
// up to its library level (its pre-evolutions' too), TMs in the bag it can learn, the tutor moves of the tutors that have
// taught once (FireRed's tutors teach one Pokemon, then the move is in every compatible Pokemon's library), and its egg moves from Bond 8 (peak). It swaps them for free with expansion's move relearner
// ("Change moves" in the party menu, or START on the Summary's moves page). Nothing new is stored.

#define KJH_LIBRARY_EGG_MOVES_BOND 8

struct BoxPokemon;

// Its peak level (the highest it reached: a new region never takes moves away), or its level if higher; every
// level-up move once the League is beaten (FLAG_SYS_GAME_CLEAR)
u32 KJH_LibraryLevel(struct BoxPokemon *boxMon);
bool32 KJH_HasEggMovesInLibrary(struct BoxPokemon *boxMon);
bool32 KJH_IsTutorMoveInLibrary(u32 move);        // its Kanto tutor has taught it once (FireRed's FLAG_TUTOR_*)
bool32 KJH_IsMoveInLibrary(struct BoxPokemon *boxMon, u32 move);
// Unknown library moves in ascending move-ID order, truncated to maxMoves.
u32 KJH_GetUnknownLibraryMoves(struct BoxPokemon *boxMon, u16 *moves, u32 maxMoves);
// The level-up moves a species (and its pre-evolutions) learns above fromLevel and up to toLevel, each once
u32 KJH_GetNewLevelUpMoves(u32 species, u32 fromLevel, u32 toLevel, u16 *moves, u32 maxMoves);
// From the League's first room until the run ends, moves can't be changed (FLAG_KJH_MOVES_LOCKED)
bool32 KJH_AreMovesLocked(void);
void KJH_LockMoves(void);    // special: entering the League
void KJH_UnlockMoves(void);  // the run ends (Hall of Fame or whiteout)
// A move swapped in keeps the PP percentage of the move it replaces (rounded down; a full move stays full)
u32 KJH_PpAfterSwap(u32 newMaxPP, u32 oldPP, u32 oldMaxPP);
u16 KJH_BufferNextNewLibraryMoves(void); // special, after a team level rise (data/scripts/kjh_team_level.inc)

bool32 KJH_CheckMoveReview(void);
bool32 KJH_HasPendingMoveReview(void);
void KJH_ClearMoveReview(void);

#endif // GUARD_KJH_MOVE_LIBRARY_H
