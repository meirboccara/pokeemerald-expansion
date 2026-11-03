#ifndef GUARD_KJH_EVOLUTION_H
#define GUARD_KJH_EVOLUTION_H

// KJH (LV-9): evolution by Training points (docs/LEVELLESS_DESIGN.md, "Evolution brainstorm"). In the levels-free
// game an evolution by level, by trade, or by the item that stands in for a trade (Linking Cord, Metal Coat...)
// needs two keys: its own (the hidden level, the item) and the Training points of its stage
// (KJH_TrainingGoalOfEvolution: 100 for the second form, 200 for the third, 300 for a pseudo-legendary's last;
// earned = placed + banked). A stone
// is its own key; a friendship evolution needs the peak Bond 18. The player chooses when: "EVOLVE" in the party menu,
// after a battle in which the Pokemon became ready (B stops it: later), and when the team's level rises (a further
// zone; after a badge, the next zone) ("CHARMANDER is ready to evolve. Evolve now?").

#include "main.h"

#define KJH_EVOLUTION_BOND 18 // FireRed's 220 friendship

struct Pokemon;

// The levels-free key of one of its species' evolutions (index in GetSpeciesEvolutions): TRUE outside the
// levels-free game
bool32 KJH_EvolutionTrainingKeyMet(struct Pokemon *mon, u32 index);
// The level an evolution by level looks at: in the levels-free game the highest the Pokemon has reached, so a
// veteran that grew past it in another region (LV-18) stays ready, as its move library does (LV-10)
u32 KJH_LevelForEvolution(struct Pokemon *mon);
// A friendship evolution's key: the friendship threshold, or in the levels-free game the peak Bond 18
bool32 KJH_FriendshipEvolutionKeyMet(struct Pokemon *mon, u32 friendship, u32 threshold);
// What it could evolve into now with no item (by level, by Bond...), or SPECIES_NONE
enum Species KJH_ReadyEvolution(struct Pokemon *mon);
// The party Pokemon evolves now if it is ready (its scene, then afterwards); FALSE if it isn't
bool32 KJH_BeginReadyEvolution(u32 partyId, MainCallback afterwards);

// Battle: the Pokemon that became ready during a battle are offered the evolution once it is over
// (gLeveledUpInBattle). Those ready before it, whose evolution the player put off, are left for the party menu.
void KJH_EvolutionBattleStart(void);
void KJH_EvolutionBattleEnd(void);

// The team's level rose from VAR_0x8005 to VAR_0x8006 (EventScript_KjhOfferEvolutions): a veteran whose peak level is
// past VAR_0x8006 was ready before, so it isn't offered
u16 KJH_BufferNextRiseEvolution(void); // special: from party slot VAR_0x8004 on, the next Pokemon the rise made
                                       // ready: VAR_0x8004 its slot, STR_VAR_1 its name; FALSE when none is left
u16 KJH_EvolveFromScript(void);        // special: VAR_0x8004's Pokemon starts evolving (then waitstate), or FALSE

#endif // GUARD_KJH_EVOLUTION_H
