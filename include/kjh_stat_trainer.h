#ifndef GUARD_KJH_STAT_TRAINER_H
#define GUARD_KJH_STAT_TRAINER_H

#include "constants/kjh_stat_trainer.h"

struct ScriptContext;

// KJH: the stat trainer (ENG-7, src/kjh_stat_trainer.c, data/scripts/kjh_stat_trainer.inc). In a Pokemon Center
// (Celadon, Goldenrod; Slateport comes with ENG-9) he sets a party Pokemon's IVs, EVs or nature exactly, for free,
// or switches its ability (data/scripts/kjh_hidden_ability.inc).
// LV-8, in the levels-free game (docs/LEVELLESS_DESIGN.md §3 and §4 in the KJH repo): EVs are Training points, which
// he puts back in the bank for free (a full reset; they are placed from the Summary); he sets IVs only from peak
// Bond KJH_STAT_TRAINER_IV_BOND; the nature stays free; the Hidden Ability needs peak Bond KJH_HIDDEN_ABILITY_BOND.

// The BOND page's "IV training" milestone (gKjhBondMilestones)
#define KJH_STAT_TRAINER_IV_BOND 20

// An IV, kept within 0..MAX_PER_STAT_IVS
u32 KJH_ClampIv(s32 iv);
// evs[NUM_STATS]: the Pokemon's EVs. The EV wanted for stat row, kept within 0..MAX_PER_STAT_EVS and so that the
// total stays within MAX_TOTAL_EVS.
u32 KJH_ClampEv(const u8 *evs, u32 row, s32 ev);

// He may set this Pokemon's IVs: always in the classic game, from peak Bond KJH_STAT_TRAINER_IV_BOND in the
// levels-free one
bool32 KJH_CanTrainIvs(struct Pokemon *mon);
// Every placed Training point (its EVs, vitamins' too) back in its bank. The bank stops at KJH_TRAINING_BANK_MAX
// (LV-7), the largest total any Pokemon can place: points beyond it are lost, but a full build can always be placed
// again, and LV-9's evolution goals are far below it.
void KJH_ResetTrainingPoints(struct Pokemon *mon);

// Scripts, callnative, for the party Pokemon VAR_0x8004
// VAR_RESULT: KJH_CanTrainIvs
void KJH_ScriptCanTrainIvs(struct ScriptContext *ctx);
// VAR_RESULT: its placed Training points, also in STR_VAR_2; its nickname in STR_VAR_1
void KJH_ScriptBufferPlacedPoints(struct ScriptContext *ctx);
// KJH_ResetTrainingPoints
void KJH_ScriptResetTrainingPoints(struct ScriptContext *ctx);

// callnative ..., waitstate=1: edits the party Pokemon VAR_0x8004's IVs, EVs or nature (VAR_0x8005,
// KJH_STAT_TRAINER_*) on a window.
// Left/right change a value by 1, SELECT/START by 10, A saves (VAR_RESULT TRUE), B cancels (FALSE).
void KJH_ScriptStatTrainerEdit(struct ScriptContext *ctx);

// Party slot of the Kanto starter line when Oak may still offer one nature change.
// PARTY_SIZE if the offer was already made or that Pokemon is not in the party. Does not set the flag.
u16 KJH_OakNatureOfferSlot(void);

#endif // GUARD_KJH_STAT_TRAINER_H
