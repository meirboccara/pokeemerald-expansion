// KJH (ENG-9): the region of a map group (include/kjh_map_regions.h), which the team's level, the daily swarms and
// the route radar share: Hoenn's groups, then Kanto's (the Sevii Islands' last), then Johto's.
#include "global.h"
#include "kjh_map_regions.h"
#include "kjh_team_level.h"
#include "test/test.h"
#include "constants/map_groups.h"
#include "constants/region_map_sections.h"

static u32 RegionOfGroup(u32 mapGroup)
{
    if (KJH_IsHoennMapGroup(mapGroup))
        return KJH_REGION_HOENN;
    if (KJH_IsJohtoMapGroup(mapGroup))
        return KJH_REGION_JOHTO;
    if (KJH_IsKantoMapGroup(mapGroup))
        return KJH_REGION_KANTO;
    return KJH_REGION_NONE;
}

TEST("KJH: a map group is Hoenn's, Kanto's or Johto's, up to the boundary groups")
{
    // Hoenn: the first group, Littleroot, and the last group (just before Kanto's first)
    EXPECT_EQ(RegionOfGroup(0), KJH_REGION_HOENN);
    EXPECT_EQ(RegionOfGroup(MAP_GROUP(MAP_LITTLEROOT_TOWN)), KJH_REGION_HOENN);
    EXPECT_EQ(RegionOfGroup(MAP_GROUP(MAP_BATTLE_FRONTIER_OUTSIDE_WEST)), KJH_REGION_HOENN);
    EXPECT_EQ(RegionOfGroup(MAP_GROUP(MAP_ROUTE124_DIVING_TREASURE_HUNTERS_HOUSE)), KJH_REGION_HOENN);
    // Kanto: its first group (the link rooms), Pallet Town, and the Sevii Islands' last group
    EXPECT_EQ(RegionOfGroup(MAP_GROUP(MAP_BATTLE_COLOSSEUM_2P_FRLG)), KJH_REGION_KANTO);
    EXPECT_EQ(RegionOfGroup(MAP_GROUP(MAP_PALLET_TOWN)), KJH_REGION_KANTO);
    EXPECT_EQ(RegionOfGroup(MAP_GROUP(MAP_SEVEN_ISLAND_SEVAULT_CANYON_HOUSE)), KJH_REGION_KANTO);
    // Johto: its first group, Goldenrod, and the last group of all
    EXPECT_EQ(RegionOfGroup(MAP_GROUP(MAP_JOHTO_OLIVINE_POKECENTER_1F)), KJH_REGION_JOHTO);
    EXPECT_EQ(RegionOfGroup(MAP_GROUP(MAP_JOHTO_GOLDENROD_CITY)), KJH_REGION_JOHTO);
    EXPECT_EQ(RegionOfGroup(MAP_GROUP(MAP_JOHTO_CHERRYGROVE_CITY)), KJH_REGION_JOHTO);
    EXPECT_EQ(RegionOfGroup(MAP_GROUPS_COUNT - 1), KJH_REGION_JOHTO);
}

TEST("KJH: the team's level takes a Hoenn map for Hoenn's, with or without a zone, and no other")
{
    EXPECT_EQ(KJH_RegionOf(MAPSEC_NONE, MAP_ROUTE124_DIVING_TREASURE_HUNTERS_HOUSE), KJH_REGION_HOENN);
    EXPECT_EQ(KJH_RegionOf(MAPSEC_BATTLE_FRONTIER, MAP_BATTLE_FRONTIER_OUTSIDE_WEST), KJH_REGION_HOENN);
    EXPECT_EQ(KJH_RegionOf(MAPSEC_NONE, MAP_BATTLE_COLOSSEUM_2P_FRLG), KJH_REGION_NONE);
    EXPECT_EQ(KJH_RegionOf(MAPSEC_PALLET_TOWN, MAP_PALLET_TOWN), KJH_REGION_KANTO);
}
