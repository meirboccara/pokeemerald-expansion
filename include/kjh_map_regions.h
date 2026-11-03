#ifndef GUARD_KJH_MAP_REGIONS_H
#define GUARD_KJH_MAP_REGIONS_H

#include "constants/map_groups.h"

// KJH (ENG-9): the region of a map group. data/maps/map_groups.json (include/constants/map_groups.h) lists
// expansion's own map groups first, which are Emerald's Hoenn, then FireRed's (Kanto and the Sevii Islands), then
// Johto's. The team's level (KJH_RegionOf), the daily swarms and the route radar all go by these.
#define KJH_FIRST_KANTO_MAP_GROUP MAP_GROUP(MAP_BATTLE_COLOSSEUM_2P_FRLG)
#define KJH_FIRST_JOHTO_MAP_GROUP MAP_GROUP(MAP_JOHTO_OLIVINE_POKECENTER_1F)

// The blocks touch and cover every group: Hoenn's last group comes right before Kanto's first, Kanto's (the Sevii
// Islands') last right before Johto's first, and Johto's last is the last of all. A group added to map_groups.json
// in the wrong place stops the build here.
STATIC_ASSERT(MAP_GROUP(MAP_PETALBURG_CITY) == 0, KjhHoennMapGroupsFirst);
STATIC_ASSERT(MAP_GROUP(MAP_ROUTE124_DIVING_TREASURE_HUNTERS_HOUSE) + 1 == KJH_FIRST_KANTO_MAP_GROUP,
              KjhKantoMapGroupsAfterHoenn);
STATIC_ASSERT(MAP_GROUP(MAP_SEVEN_ISLAND_SEVAULT_CANYON_HOUSE) + 1 == KJH_FIRST_JOHTO_MAP_GROUP,
              KjhJohtoMapGroupsAfterKanto);
STATIC_ASSERT(MAP_GROUP(MAP_JOHTO_CHERRYGROVE_CITY) + 1 == MAP_GROUPS_COUNT, KjhJohtoMapGroupsLast);

static inline bool32 KJH_IsHoennMapGroup(u32 mapGroup)
{
    return mapGroup < KJH_FIRST_KANTO_MAP_GROUP;
}

static inline bool32 KJH_IsJohtoMapGroup(u32 mapGroup)
{
    return mapGroup >= KJH_FIRST_JOHTO_MAP_GROUP;
}

static inline bool32 KJH_IsKantoMapGroup(u32 mapGroup)
{
    return !KJH_IsHoennMapGroup(mapGroup) && !KJH_IsJohtoMapGroup(mapGroup);
}

#endif // GUARD_KJH_MAP_REGIONS_H
