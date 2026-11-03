#ifndef GUARD_KJH_TEAM_LEVEL_H
#define GUARD_KJH_TEAM_LEVEL_H

// KJH (LV-2): the team's level follows Kanto's zones (docs/LEVELLESS_DESIGN.md §1, variant C). The whole team's
// hidden level is the top of the furthest zone reached, never above the next Gym ace (by badge count). A new catch,
// a gift or a Pokémon from the PC joins at that level at once. No Exp. is earned. All of it is on only while
// FLAG_KJH_LEVELLESS is set (from a new game).

// LV-18: Johto has its own zones (src/data/kjh_johto_zones.h), team level and badge count, on the same curve. A
// region's zone tables also say which maps are in it.
enum KjhRegion
{
    KJH_REGION_NONE,
    KJH_REGION_KANTO,
    KJH_REGION_JOHTO,
    KJH_REGION_COUNT,
};

// The zone tables' rows (src/data/kjh_kanto_zones.h, src/data/kjh_johto_zones.h).
struct KjhZoneRange { u8 min, max; };
struct KjhGymAce { u16 map; u8 ace; };
struct KjhMapZone { u16 map; u8 zone; };
struct KjhMapsecZone { u16 mapsec; u8 zone; };

bool32 KJH_IsLevelsFree(void);

// The top of the zone a place belongs to, or 0 for a place outside the tables. A map of its own (a League room)
// comes before its section.
u32 KJH_ZoneTop(u32 mapsec, u32 map);
// The region whose zone tables have this place, KJH_REGION_NONE for none.
enum KjhRegion KJH_RegionOf(u32 mapsec, u32 map);
// The team's ceiling with this many badges: the next Gym ace, then the Champion's 100.
u32 KJH_TeamLevelCap(u32 badges);
// Kanto's badges.
u32 KJH_CountKantoBadges(void);
// The badges of the region the player stands in; Kanto's outside every region.
u32 KJH_CountBadgesHere(void);
// The team's level now in the region the player stands in (Kanto's outside every region), 0 before any of its
// zones is reached: the Champion's level once the region's League is beaten (LV-3).
u32 KJH_TeamLevel(void);
// Records the zone the player stands in, if it is further than the furthest one so far in its region.
void KJH_RecordZone(void);
// In the levels-free game, how many levels the trainers of the Gym the player stands in move (LV-3): the Gym's ace
// becomes the team's ceiling for the player's badges, so Gyms can be done in any order. 0 outside a Gym.
s32 KJH_GymLevelShift(void);
// The player stands in one of Kanto's or Johto's Gyms (sKantoGyms, sJohtoGyms).
bool32 KJH_IsInGym(void);

// Sets a Pokémon's level (and its peak level). Eggs and empty slots are left alone.
void KJH_SetMonLevel(struct Pokemon *mon, u32 level);
// A Pokémon joining the player (a catch, a gift, a withdrawal, a Day Care pickup) takes the team's level, on the maps
// of a region only; a catch's met level becomes the team's level too.
void KJH_JoinTeam(struct Pokemon *mon, bool32 caught);
// Every Pokémon of the party at the team's level.
void KJH_ApplyTeamLevelToParty(void);
// Called on each step on a region's maps: records the zone, levels the party, and starts "Your team feels stronger!"
// when the team's level went up. TRUE if a script was started.
bool32 KJH_TryTeamLevelStep(void);

#endif // GUARD_KJH_TEAM_LEVEL_H
