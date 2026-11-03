#ifndef GUARD_KJH_TEAM_LEVEL_H
#define GUARD_KJH_TEAM_LEVEL_H

// KJH (LV-2): the team's level follows Kanto's zones (docs/LEVELLESS_DESIGN.md §1, variant C). The whole team's
// hidden level is the top of the furthest zone reached, never above the next Gym ace (by badge count). A new catch,
// a gift or a Pokémon from the PC joins at that level at once. No Exp. is earned. All of it is on only while
// FLAG_KJH_LEVELLESS is set (from a new game).

bool32 KJH_IsLevelsFree(void);

// The top of the zone a place belongs to, or 0 for a place outside the table. A map of its own (a League room)
// comes before its section.
u32 KJH_ZoneTop(u32 mapsec, u32 map);
// The team's ceiling with this many badges: the next Gym ace, then the Champion's 100.
u32 KJH_TeamLevelCap(u32 badges);
// Kanto's badges.
u32 KJH_CountKantoBadges(void);
// The team's level now (0 before any zone is reached): the Champion's level once the League is beaten (LV-3).
u32 KJH_TeamLevel(void);
// Records the zone the player stands in, if it is further than the furthest one so far.
void KJH_RecordZone(void);
// In the levels-free game, how many levels the trainers of the Gym the player stands in move (LV-3): the Gym's ace
// becomes the team's ceiling for the player's badges, so Gyms can be done in any order. 0 outside a Gym.
s32 KJH_GymLevelShift(void);

// Sets a Pokémon's level (and its peak level). Eggs and empty slots are left alone.
void KJH_SetMonLevel(struct Pokemon *mon, u32 level);
// A Pokémon joining the player (a catch, a gift, a withdrawal, a Day Care pickup) takes the team's level, on Kanto's
// maps only; a catch's met level becomes the team's level too.
void KJH_JoinTeam(struct Pokemon *mon, bool32 caught);
// Every Pokémon of the party at the team's level.
void KJH_ApplyTeamLevelToParty(void);
// Called on each step on Kanto's maps: records the zone, levels the party, and starts "Your team feels stronger!"
// when the team's level went up. TRUE if a script was started.
bool32 KJH_TryTeamLevelStep(void);

#endif // GUARD_KJH_TEAM_LEVEL_H
