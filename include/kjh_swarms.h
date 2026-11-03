#ifndef GUARD_KJH_SWARMS_H
#define GUARD_KJH_SWARMS_H

// KJH: the daily swarm (CF-5). Each in-game day (CF-4's clock), one entry of a region's swarm table starts in
// expansion's mass outbreak record for one day: its species shows up on its route, in the grass, at its chance,
// at the route's own wild level. A Pokemon Center NPC names it.

struct KjhSwarm
{
    u16 species;
    u16 map;      // MAP_*, a route with grass
    u8 chance;    // % of the grass encounters on that route
};

u32 KJH_SwarmCount(void);
const struct KjhSwarm *KJH_GetSwarm(u32 index);
void KJH_StartSwarm(u32 index);
void KJH_StartDailySwarm(void);
u16 KJH_BufferTodaysSwarm(void); // special: STR_VAR_1 species, STR_VAR_2 route; TRUE if there's a swarm today
u8 KJH_GetRouteWildLevel(void);  // a level from the current map's grass table, as a wild Pokemon there gets

#endif // GUARD_KJH_SWARMS_H
