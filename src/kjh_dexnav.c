// KJH (ENG-8 follow-up): DexNav's searched Pokemon only sometimes scared off by a fast approach (include/kjh_dexnav.h).
#include "global.h"
#include "dexnav.h"
#include "kjh_dexnav.h"
#include "random.h"

u32 KJH_DexNavFleeChance(enum KjhDexNavPace pace, u32 proximity)
{
    if (proximity == 0) // this step reached it: the battle starts
        return 0;
    switch (pace)
    {
    case KJH_DEXNAV_PACE_RUN:
        return (proximity <= SNEAKING_PROXIMITY) ? KJH_DEXNAV_FLEE_RUN_PERCENT : 0;
    case KJH_DEXNAV_PACE_WALK:
        return (proximity <= CREEPING_PROXIMITY) ? KJH_DEXNAV_FLEE_WALK_PERCENT : 0;
    default:
        return 0;
    }
}

bool32 KJH_DexNavScared(enum KjhDexNavPace pace, u32 proximity)
{
    u32 chance = KJH_DexNavFleeChance(pace, proximity);

    return chance != 0 && RandomPercentage(RNG_KJH_DEXNAV_FLEE, chance);
}
