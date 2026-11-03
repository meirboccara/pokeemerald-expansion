#ifndef GUARD_KJH_SWARMS_H
#define GUARD_KJH_SWARMS_H

// KJH: the daily swarm (CF-5, CF-6). Each in-game day (CF-4's clock), each region the player has reached gets one entry
// of its swarm table for the day: its species shows up on its map much more often, at its chance, at the level of the
// encounter it replaces. Kanto's runs on expansion's mass outbreak record (grass only); Johto's (Crystal's swarms, in
// grass and by fishing) and Hoenn's (Emerald's five outbreaks, in the grass) on SaveBlock3's kjhSwarms. A Pokemon
// Center NPC names the swarm of his region.

#include "wild_encounter.h"

enum
{
    KJH_SWARM_LAND,
    KJH_SWARM_FISHING,
};

enum
{
    KJH_SWARM_JOHTO,
    KJH_SWARM_HOENN,
};

struct KjhSwarm
{
    u16 species;
    u16 map;      // MAP_*
    u8 chance;    // % of that method's encounters on that map
    u8 method;    // KJH_SWARM_*; Kanto's are all KJH_SWARM_LAND
};

u32 KJH_SwarmCount(void);
const struct KjhSwarm *KJH_GetSwarm(u32 index);
void KJH_StartSwarm(u32 index);
void KJH_StartDailySwarm(void);
// Johto's and Hoenn's swarms (KJH_SWARM_JOHTO, KJH_SWARM_HOENN). A region the player hasn't reached has none.
u32 KJH_RegionSwarmCount(u32 region);
const struct KjhSwarm *KJH_GetRegionSwarm(u32 region, u32 index);
void KJH_StartRegionSwarm(u32 region, u32 index);
// The species of a Johto or Hoenn encounter about to be made on the current map (TryGenerateWildMon,
// GenerateFishingWildMon): today's swarm species at its chance, when the map and method are the swarm's, else species
enum Species KJH_RegionSwarmSpecies(enum Species species, enum WildPokemonArea area);
u16 KJH_BufferTodaysSwarm(void); // special: STR_VAR_1 species, STR_VAR_2 route; TRUE if this region has a swarm today
u8 KJH_GetRouteWildLevel(void);  // a level from the current map's grass table, as a wild Pokemon there gets

#endif // GUARD_KJH_SWARMS_H
