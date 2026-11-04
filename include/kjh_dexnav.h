#ifndef GUARD_KJH_DEXNAV_H
#define GUARD_KJH_DEXNAV_H

// KJH (ENG-8 follow-up): DexNav's searched Pokemon, scared off by a fast approach (src/dexnav.c's OnStep_DexNavSearch). Expansion's
// DexNav makes it flee for sure as soon as the player runs within SNEAKING_PROXIMITY tiles or walks within
// CREEPING_PROXIMITY; with KJH's auto-run (CF-11) the player runs nearly all the time, so it fled nearly every
// search. Here each step that close only has a chance to scare it: running a little, walking less, creeping (A
// held) never, and the step that reaches it never.

#define KJH_DEXNAV_FLEE_RUN_PERCENT   6 // per step within SNEAKING_PROXIMITY, running or on a Bike: ~78% get there
#define KJH_DEXNAV_FLEE_WALK_PERCENT  3 // per step within CREEPING_PROXIMITY, walking: ~94% get there

enum KjhDexNavPace
{
    KJH_DEXNAV_PACE_CREEP,
    KJH_DEXNAV_PACE_WALK,
    KJH_DEXNAV_PACE_RUN,   // running or on a Bike
};

u32 KJH_DexNavFleeChance(enum KjhDexNavPace pace, u32 proximity); // percent, for this step
bool32 KJH_DexNavScared(enum KjhDexNavPace pace, u32 proximity);  // rolls RNG_KJH_DEXNAV_FLEE

#endif // GUARD_KJH_DEXNAV_H
