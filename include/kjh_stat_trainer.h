#ifndef GUARD_KJH_STAT_TRAINER_H
#define GUARD_KJH_STAT_TRAINER_H

struct ScriptContext;

// KJH: the stat trainer (ENG-7, src/kjh_stat_trainer.c, data/scripts/kjh_stat_trainer.inc). In a Pokemon Center
// (Celadon; Goldenrod and Slateport come with ENG-9) he sets a party Pokemon's IVs, EVs or nature exactly, for free,
// or switches its ability (data/scripts/kjh_hidden_ability.inc). LV-8 will change what he may do (Bond).

// What to edit (VAR_0x8005), the stat trainer's menu
#define KJH_STAT_TRAINER_IVS    0
#define KJH_STAT_TRAINER_EVS    1
#define KJH_STAT_TRAINER_NATURE 2

// An IV, kept within 0..MAX_PER_STAT_IVS
u32 KJH_ClampIv(s32 iv);
// evs[NUM_STATS]: the Pokemon's EVs. The EV of stat row set to ev, kept within 0..MAX_PER_STAT_EVS and so that the
// total stays within MAX_TOTAL_EVS.
u32 KJH_SetEv(const u8 *evs, u32 row, s32 ev);

// callnative ..., waitstate=1: edits the party Pokemon VAR_0x8004's IVs, EVs or nature (VAR_0x8005) on a window.
// Left/right change a value by 1, SELECT/START by 10, A saves (VAR_RESULT TRUE), B cancels (FALSE).
void KJH_ScriptStatTrainerEdit(struct ScriptContext *ctx);

#endif // GUARD_KJH_STAT_TRAINER_H
