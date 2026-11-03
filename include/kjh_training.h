#ifndef GUARD_KJH_TRAINING_H
#define GUARD_KJH_TRAINING_H

#include "kjh_levelless.h"
#include "kjh_pack.h"

// KJH: Training points (LV-7, docs/LEVELLESS_DESIGN.md §4 in the KJH repo). They replace Exp. and EVs: each KO (or
// catch) gives the party points (1 + the foe's level / 20, times the foe's tier), the Pokémon that fought all of
// them, the rest of the party half (half points kept, MON_DATA_TRAINING_HALF). They wait in the Pokémon's bank
// (MON_DATA_TRAINING_BANK) until the player places them in its stats, from the Summary: up to 255 in a stat, and a
// total set by its tier mark (regular 510, Leader 530, Alpha 630). An EV-lowering berry gives one stat's points back.

#define KJH_TRAINING_STAT_MAX       255    // per stat, as in Gen 3 (expansion's own cap is 252)
#define KJH_TRAINING_TOTAL_REGULAR  510
#define KJH_TRAINING_TOTAL_LEADER   530
#define KJH_TRAINING_TOTAL_ALPHA    630
#define KJH_TRAINING_LEVEL_STEP     20     // 1 point, plus 1 per 20 levels of the foe

// The foe's multiplier
#define KJH_TRAINING_MULT_PACK_HELPER  2  // a helper a pack leader called
#define KJH_TRAINING_MULT_LEADER       3  // a pack leader, a Leader (LV-15)
#define KJH_TRAINING_MULT_BOSS         3  // every Pokémon of a Gym Leader, an Elite Four member or a Champion
#define KJH_TRAINING_MULT_ALPHA        6

// The points an evolution by level or trade asks for (LV-9 checks them; the Summary shows how far along it is)
#define KJH_TRAINING_GOAL_SECOND_FORM  100
#define KJH_TRAINING_GOAL_THIRD_FORM   200
#define KJH_TRAINING_GOAL_PSEUDO_LAST  300  // Dragonite, Tyranitar, Salamence, Metagross

// Rules (no game state). Points are counted in halves where they can be half.
u32 KJH_TrainingFoeMultiplier(enum KjhPackRole packRole, enum KjhTierMark tier, bool32 bossTrainer);
u32 KJH_TrainingPointsPerKo(u32 foeLevel, u32 multiplier);
u32 KJH_TrainingHalvesFor(u32 points, bool32 fought);        // all of them in halves, or half of them
void KJH_TrainingAddHalves(u32 *bank, u32 *half, u32 halves); // the bank stops at KJH_TRAINING_BANK_MAX
u32 KJH_TrainingTotalLimit(enum KjhTierMark tier);
u32 KJH_TrainingRoom(const u8 *evs, enum KjhTierMark tier, enum Stat stat); // how many more points this stat takes
u32 KJH_TrainingEvolutionGoal(enum Species species);        // its first evolution that needs points; 0: none
// KJH (LV-9): the points one of the species' evolutions (index in GetSpeciesEvolutions) needs: 0 for a stone or a
// friendship evolution
u32 KJH_TrainingGoalOfEvolution(enum Species species, u32 index);

// The game
void KJH_GiveTrainingPoints(enum BattlerId fainted, u32 foughtBits); // a foe was knocked out: the whole party
u32 KJH_TrainingBank(struct Pokemon *mon);
u32 KJH_TrainingPlaced(struct Pokemon *mon);                         // the sum of its EVs
u32 KJH_TrainingPointsToPlace(struct Pokemon *mon);                  // the bank, as far as the stats have room
u32 KJH_PlaceTrainingPoints(struct Pokemon *mon, enum Stat stat, u32 count); // returns how many were placed
void KJH_TrainingRefund(struct Pokemon *mon, u32 points);            // points taken out of a stat, back to the bank
u32 KJH_TrainingEarned(struct Pokemon *mon);                         // placed + in the bank
// The points earned toward the next evolution, up to its goal (0 and goal 0: no evolution by level)
u32 KJH_TrainingTowardEvolution(struct Pokemon *mon, u32 *goal);
u8 *KJH_StringTrainingEarned(u8 *dest, struct Pokemon *mon);         // "87/100", or all the points earned

#endif // GUARD_KJH_TRAINING_H
