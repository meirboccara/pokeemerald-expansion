#ifndef GUARD_KJH_MOVE_STARS_H
#define GUARD_KJH_MOVE_STARS_H

// KJH (LV-12): move stars and the training notebook (docs/LEVELLESS_DESIGN.md §12 in the KJH repo).
// Each move a Pokemon knows or knew has 1 to 5 stars, from its move points (10, 30, 60, 100 for 2 to 5 stars), and
// hits at 60/70/80/90/100% of its power. Only moves above 60 power are held back, never below 60, as with the power
// cap (LV-11); with both, the lower percentage wins. A level-up move learned above the met level starts at 30 points
// (3 stars), every other move at 0 (1 star). Won battles give the moves used in them points.
// The notebook remembers the points of KJH_NOTEBOOK_SIZE moves, PC included, so a move keeps its stars when it is
// forgotten and relearned. A move at its starting points takes no entry; when the notebook is full, the entry
// unused the longest is dropped. It lives in the PC's save sectors (struct PokemonStorage, spare room there).

#include "kjh_notebook.h"

#define KJH_STARS_MAX        5
#define KJH_MOVE_POINTS_MAX  100

enum KjhWinKind
{
    KJH_WIN_WILD,
    KJH_WIN_TRAINER,
    KJH_WIN_BOSS,     // Gym Leaders, the Elite Four, Champions, rivals (KJH_IsBossTrainer)
};

// Rules (no game state)
u32 KJH_StarsFromPoints(u32 points);
u32 KJH_PointsForStars(u32 stars);
u32 KJH_StarsPercent(u32 stars);
u32 KJH_StarsAndCapPercent(u32 stars, u32 capPercent);
u32 KJH_StarredPower(u32 power, u32 stars);
u32 KJH_MovePointsForWin(enum KjhWinKind kind, u32 tierMark);

// A Pokemon's moves
u32 KJH_StartingMovePoints(struct BoxPokemon *boxMon, enum Move move);
u32 KJH_GetMovePoints(struct BoxPokemon *boxMon, enum Move move);
u32 KJH_GetMoveStars(struct BoxPokemon *boxMon, enum Move move);
u32 KJH_AddMovePoints(struct BoxPokemon *boxMon, enum Move move, u32 points); // the stars after

// In battle: the lower of the power cap and, for a move the player's own Pokemon knows, its stars (B_KJH_MOVE_STARS)
u32 KJH_BattleMovePercent(u32 battler, enum Move move);

// The notebook
void KJH_ClearNotebook(void);
u32 KJH_NotebookCount(void);

#endif // GUARD_KJH_MOVE_STARS_H
