// KJH: Johto's daily swarm (CF-6, src/kjh_swarms.c): Crystal's swarms, in grass and by fishing.
#include "global.h"
#include "event_data.h"
#include "kjh_swarms.h"
#include "mass_outbreak.h"
#include "random.h"
#include "string_util.h"
#include "test/test.h"
#include "constants/johto_flags.h"
#include "constants/map_groups.h"

static void StandOn(u32 map)
{
    gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(map);
    gSaveBlock1Ptr->location.mapNum = MAP_NUM(map);
}

static u32 FindJohtoSwarm(enum Species species)
{
    u32 i;

    for (i = 0; i < KJH_RegionSwarmCount(KJH_SWARM_JOHTO); i++)
    {
        if (KJH_GetRegionSwarm(KJH_SWARM_JOHTO, i)->species == species) break;
    }

    return i;
}

TEST("KJH: Johto's swarms are Crystal's: Dunsparce and Yanma in the grass, Qwilfish and Remoraid by fishing")
{
    EXPECT_EQ(KJH_RegionSwarmCount(KJH_SWARM_JOHTO), 4);
    EXPECT_EQ(KJH_GetRegionSwarm(KJH_SWARM_JOHTO, FindJohtoSwarm(SPECIES_DUNSPARCE))->map, MAP_JOHTO_DARK_CAVE_VIOLET_ENTRANCE);
    EXPECT_EQ(KJH_GetRegionSwarm(KJH_SWARM_JOHTO, FindJohtoSwarm(SPECIES_YANMA))->method, KJH_SWARM_LAND);
    EXPECT_EQ(KJH_GetRegionSwarm(KJH_SWARM_JOHTO, FindJohtoSwarm(SPECIES_QWILFISH))->method, KJH_SWARM_FISHING);
    EXPECT_EQ(KJH_GetRegionSwarm(KJH_SWARM_JOHTO, FindJohtoSwarm(SPECIES_REMORAID))->map, MAP_JOHTO_ROUTE_44);
}

TEST("KJH: Johto has no swarm until the player reaches it; then Kanto and Johto each have one the same day")
{
    FlagClear(FLAG_KJH_JOHTO_ARRIVED);
    KJH_StartDailySwarm();
    EXPECT(IsMassOutbreakActive());
    EXPECT_EQ(gSaveBlock3Ptr->kjhSwarms[KJH_SWARM_JOHTO].species, SPECIES_NONE);

    FlagSet(FLAG_KJH_JOHTO_ARRIVED);
    KJH_StartDailySwarm();
    EXPECT(IsMassOutbreakActive());
    EXPECT_NE(gSaveBlock3Ptr->kjhSwarms[KJH_SWARM_JOHTO].species, SPECIES_NONE);
    FlagClear(FLAG_KJH_JOHTO_ARRIVED);
}

TEST("KJH: a Johto swarm shows up on its own map and by its own method, at its chance")
{
    KJH_StartRegionSwarm(KJH_SWARM_JOHTO, FindJohtoSwarm(SPECIES_YANMA));
    StandOn(MAP_JOHTO_ROUTE_35);
    EXPECT_EQ(KJH_RegionSwarmSpecies(SPECIES_PIDGEY, WILD_AREA_LAND), SPECIES_PIDGEY); // the roll's default: no swarm
    SET_RNG(RNG_KJH_SWARM, 0); // outcome 0: the swarm
    EXPECT_EQ(KJH_RegionSwarmSpecies(SPECIES_PIDGEY, WILD_AREA_LAND), SPECIES_YANMA);
    EXPECT_EQ(KJH_RegionSwarmSpecies(SPECIES_MAGIKARP, WILD_AREA_FISHING), SPECIES_MAGIKARP); // Yanma's is in the grass
    StandOn(MAP_JOHTO_ROUTE_36);
    EXPECT_EQ(KJH_RegionSwarmSpecies(SPECIES_PIDGEY, WILD_AREA_LAND), SPECIES_PIDGEY);

    KJH_StartRegionSwarm(KJH_SWARM_JOHTO, FindJohtoSwarm(SPECIES_QWILFISH));
    StandOn(MAP_JOHTO_ROUTE_32);
    EXPECT_EQ(KJH_RegionSwarmSpecies(SPECIES_MAGIKARP, WILD_AREA_FISHING), SPECIES_QWILFISH);
    EXPECT_EQ(KJH_RegionSwarmSpecies(SPECIES_RATTATA, WILD_AREA_LAND), SPECIES_RATTATA);
    gSaveBlock3Ptr->kjhSwarms[KJH_SWARM_JOHTO].species = SPECIES_NONE;
}

TEST("KJH: a Johto Pokemon Center's reporter names Johto's swarm, a Kanto one Kanto's")
{
    u8 species[POKEMON_NAME_LENGTH + 1];

    KJH_StartSwarm(0); // Kanto: Sentret on Route 1
    KJH_StartRegionSwarm(KJH_SWARM_JOHTO, FindJohtoSwarm(SPECIES_REMORAID));
    StandOn(MAP_JOHTO_GOLDENROD_POKECENTER_1F);
    EXPECT(KJH_BufferTodaysSwarm());
    StringCopy(species, gStringVar1);
    EXPECT_EQ(StringCompare(species, GetSpeciesName(SPECIES_REMORAID)), 0);
    StandOn(MAP_CELADON_CITY_POKEMON_CENTER_1F);
    EXPECT(KJH_BufferTodaysSwarm());
    EXPECT_EQ(StringCompare(gStringVar1, GetSpeciesName(KJH_GetSwarm(0)->species)), 0);

    gSaveBlock3Ptr->kjhSwarms[KJH_SWARM_JOHTO].species = SPECIES_NONE;
    StandOn(MAP_JOHTO_GOLDENROD_POKECENTER_1F);
    EXPECT(!KJH_BufferTodaysSwarm());
}
