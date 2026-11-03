#ifndef GUARD_CONSTANTS_KJH_STAT_TRAINER_H
#define GUARD_CONSTANTS_KJH_STAT_TRAINER_H

// KJH: the stat trainer's menu (VAR_0x8005, data/scripts/kjh_stat_trainer.inc, src/kjh_stat_trainer.c), as #defines
// so the scripts can use them
#define KJH_STAT_TRAINER_IVS     0
#define KJH_STAT_TRAINER_EVS     1
#define KJH_STAT_TRAINER_NATURE  2
#define KJH_STAT_TRAINER_ABILITY 3
#define KJH_STAT_TRAINER_CANCEL  4

// An ability switch's result (VAR_RESULT, KJH_ScriptSetChosenAbility, data/scripts/kjh_hidden_ability.inc)
#define KJH_ABILITY_SAME    0 // it already had that ability
#define KJH_ABILITY_CHANGED 1
#define KJH_ABILITY_HIDDEN  2 // it has its Hidden Ability now

#endif // GUARD_CONSTANTS_KJH_STAT_TRAINER_H
