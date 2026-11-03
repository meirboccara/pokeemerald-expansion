#ifndef GUARD_KJH_FAIR_FIGHT_H
#define GUARD_KJH_FAIR_FIGHT_H

// KJH (LV-17): fair fights (docs/LEVELLESS_DESIGN.md §10). Before a Gym Leader, the player picks as many Pokemon as
// the Leader has ("BROCK uses 2 POKEMON. Choose 2."); the others wait and come back once the battle is over. With no
// more healthy Pokemon than that, there is no choice. Never in the League (its Elite Four and Champion aren't Gym
// Leaders; moves are locked there, LV-10).

#define KJH_FACILITY_FAIR_FIGHT 0xF0 // VAR_FRONTIER_FACILITY while the party menu picks the team

u16 KJH_FairFightCount(void);       // special, VAR_0x8004 = the trainer: how many to pick, 0 for no choice;
                                     // STR_VAR_1 the Leader's name, STR_VAR_2 the number
void KJH_ChooseFairFightParty(void); // special: the party menu picks VAR_0x8005 Pokemon; VAR_RESULT FALSE if cancelled
void KJH_ApplyFairFightParty(void);  // special: the party becomes the chosen Pokemon, the others wait
void KJH_RestoreFairFightParty(void); // the end of any battle: the others come back, the fighters keep what happened
bool32 KJH_IsFairFightActive(void);

#endif // GUARD_KJH_FAIR_FIGHT_H
