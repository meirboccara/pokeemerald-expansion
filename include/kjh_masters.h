#ifndef GUARD_KJH_MASTERS_H
#define GUARD_KJH_MASTERS_H

// KJH (LV-13): Kanto's training masters (docs/LEVELLESS_DESIGN.md §12 in the KJH repo). One per type, each on a spot
// of its type (data/scripts/kjh_masters.inc). A master can be fought twice per in-game day (two of FireRed's daily
// flags each, cleared by CF-4's daily events); its team is at the team's current level, whatever the zone; its
// battle's field is its type; a win gives +20 move points to every move of its type used in it (src/kjh_move_stars.c).

#define KJH_MASTER_POINTS 20

struct KjhMaster
{
    u16 trainerId;
    enum Type type;
    u16 flagOnce;
    u16 flagTwice;
};

const struct KjhMaster *KJH_GetMaster(u32 trainerId); // NULL: not a master
u32 KJH_MasterFightsLeftToday(u32 trainerId);
void KJH_NoteMasterFought(u32 trainerId);
u32 KJH_MasterLevel(void);                  // the team's level; the party's highest when the levels-free game is off
enum Type KJH_MasterBattleType(void);       // in a master's battle, its type; else TYPE_NONE

// Specials: VAR_0x8004 = the master's trainer id
void KJH_SpecialMasterFightsLeft(void);     // VAR_RESULT = fights left today
void KJH_SpecialMasterFought(void);

#endif // GUARD_KJH_MASTERS_H
