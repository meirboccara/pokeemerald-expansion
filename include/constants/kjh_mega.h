#ifndef GUARD_CONSTANTS_KJH_MEGA_H
#define GUARD_CONSTANTS_KJH_MEGA_H

// KJH (LV-20): where the player's starter stands for its first Mega Evolution (KJH_ScriptMegaStarterReady,
// data/scripts/kjh_mega.inc), as #defines so the scripts can use them
#define KJH_MEGA_STARTER_MISSING 0 // not in the party (STR_VAR_1: its final form's name)
#define KJH_MEGA_STARTER_EVOLVE  1 // not fully evolved yet (STR_VAR_1: its nickname, STR_VAR_2: its final form)
#define KJH_MEGA_STARTER_BOND    2 // below Bond 18 (STR_VAR_1: its nickname)
#define KJH_MEGA_STARTER_READY   3 // the scene (STR_VAR_1: its nickname, VAR_0x8005: its species, VAR_0x8006: Mega)
#define KJH_MEGA_STARTER_NO_MEGA 4 // LV-23: the line has no Mega (Typhlosion): the player picks a free stone

// The region of the starter (VAR_0x8004 for KJH_ScriptMegaStarterReady)
#define KJH_MEGA_STARTER_KANTO 0 // VAR_STARTER_MON
#define KJH_MEGA_STARTER_JOHTO 1 // Prof. Elm's: FLAG_J_GOT_*_FROM_ELM

#endif // GUARD_CONSTANTS_KJH_MEGA_H
