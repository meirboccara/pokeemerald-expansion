#ifndef GUARD_CONSTANTS_KJH_MEGA_H
#define GUARD_CONSTANTS_KJH_MEGA_H

// KJH (LV-20): where the player's starter stands for its first Mega Evolution (KJH_ScriptMegaStarterReady,
// data/scripts/kjh_mega.inc), as #defines so the scripts can use them
#define KJH_MEGA_STARTER_MISSING 0 // not in the party (STR_VAR_1: its final form's name)
#define KJH_MEGA_STARTER_EVOLVE  1 // not fully evolved yet (STR_VAR_1: its nickname, STR_VAR_2: its final form)
#define KJH_MEGA_STARTER_BOND    2 // below Bond 18 (STR_VAR_1: its nickname)
#define KJH_MEGA_STARTER_READY   3 // the scene (STR_VAR_1: its nickname, VAR_0x8005: its species, VAR_0x8006: Mega)

#endif // GUARD_CONSTANTS_KJH_MEGA_H
