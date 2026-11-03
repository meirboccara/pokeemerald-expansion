// KJH: the route radar (ENG-8, CF-7, CF-10's follow-up; src/kjh_dex_radar*.c): the route list, the route page with
// each method's chances (headbutt trees included), ????? for a species never seen, and today's swarms.
#include "global.h"
#include "event_data.h"
#include "kjh_dex_radar.h"
#include "kjh_swarms.h"
#include "malloc.h"
#include "mass_outbreak.h"
#include "pokedex.h"
#include "string_util.h"
#include "test/test.h"
#include "constants/johto_flags.h"
#include "constants/map_groups.h"
#include "constants/region_map_sections.h"

#define NOT_LISTED 0xFFFF

// EWRAM: a test file's .bss is in IWRAM (ld_script_test.ld), which has no room for these
static EWRAM_DATA struct KjhRadarRoute sRoutes[KJH_RADAR_MAX_ROUTES] = {0};
static EWRAM_DATA struct KjhRadarEntry sEntries[KJH_RADAR_MAX_ENTRIES] = {0};

static u32 RouteIndex(u32 count, u32 mapSec)
{
    for (u32 i = 0; i < count; i++)
    {
        if (sRoutes[i].mapSec == mapSec)
            return i;
    }
    return NOT_LISTED;
}

// The chance of a species by a method on a route page, or -1 when it isn't listed
static s32 Rate(u32 count, u32 species, u32 method)
{
    for (u32 i = 0; i < count; i++)
    {
        if (sEntries[i].species == species && sEntries[i].method == method)
            return sEntries[i].rate;
    }
    return -1;
}

static void NoSwarms(void)
{
    ZeroMassOutbreak();
    for (u32 i = 0; i < KJH_SWARM_REGIONS; i++)
        gSaveBlock3Ptr->kjhSwarms[i].species = SPECIES_NONE;
}

TEST("KJH radar: the radar lists Kanto's routes, and Johto's once the player has arrived, the way the player travels")
{
    u32 count, route29, route30, route46, route27;

    NoSwarms();
    FlagClear(FLAG_KJH_JOHTO_ARRIVED);
    count = KJH_RadarBuildRoutes(sRoutes, KJH_RADAR_MAX_ROUTES);
    EXPECT_NE(RouteIndex(count, MAPSEC_ROUTE_1), NOT_LISTED);
    EXPECT_NE(RouteIndex(count, MAPSEC_VIRIDIAN_FOREST), NOT_LISTED);
    EXPECT_EQ(RouteIndex(count, MAPSEC_J_ROUTE_29), NOT_LISTED);
    EXPECT_EQ(StringCompare(KJH_RadarRegionName(sRoutes[RouteIndex(count, MAPSEC_ROUTE_1)].region),
                            COMPOUND_STRING("KANTO")), 0);

    FlagSet(FLAG_KJH_JOHTO_ARRIVED);
    count = KJH_RadarBuildRoutes(sRoutes, KJH_RADAR_MAX_ROUTES);
    route29 = RouteIndex(count, MAPSEC_J_ROUTE_29);
    route30 = RouteIndex(count, MAPSEC_J_ROUTE_30);
    route46 = RouteIndex(count, MAPSEC_J_ROUTE_46);
    route27 = RouteIndex(count, MAPSEC_J_ROUTE_27);
    EXPECT_NE(route29, NOT_LISTED);
    EXPECT_EQ(StringCompare(KJH_RadarRegionName(sRoutes[route29].region), COMPOUND_STRING("JOHTO")), 0);
    EXPECT_GT(route29, RouteIndex(count, MAPSEC_ROUTE_1)); // Kanto first
    EXPECT_LT(route29, route30);
    EXPECT_LT(route30, route46);
    EXPECT_LT(route46, route27); // Route 27 comes after Route 46, from Blackthorn to the League
    FlagClear(FLAG_KJH_JOHTO_ARRIVED);
}

TEST("KJH radar: the radar lists a Sevii Island's routes once the island is on the Town Map")
{
    u32 count;

    NoSwarms();
    FlagClear(FLAG_WORLD_MAP_ONE_ISLAND);
    count = KJH_RadarBuildRoutes(sRoutes, KJH_RADAR_MAX_ROUTES);
    EXPECT_EQ(RouteIndex(count, MAPSEC_KINDLE_ROAD), NOT_LISTED);
    FlagSet(FLAG_WORLD_MAP_ONE_ISLAND);
    count = KJH_RadarBuildRoutes(sRoutes, KJH_RADAR_MAX_ROUTES);
    EXPECT_NE(RouteIndex(count, MAPSEC_KINDLE_ROAD), NOT_LISTED);
    FlagClear(FLAG_WORLD_MAP_ONE_ISLAND);
}

TEST("KJH radar: a route page lists each method's Pokemon with its chance, Route 2's headbutt trees too")
{
    u32 count;

    NoSwarms();
    // FireRed's Route 1 grass: Pidgey in slots 0, 2, 4, 6, 8, 10 (20+10+10+5+4+1) and Rattata in the others
    count = KJH_RadarBuildRoute(MAPSEC_ROUTE_1, sEntries, KJH_RADAR_MAX_ENTRIES);
    EXPECT_EQ(Rate(count, SPECIES_PIDGEY, KJH_RADAR_GRASS), 50);
    EXPECT_EQ(Rate(count, SPECIES_RATTATA, KJH_RADAR_GRASS), 50);
    EXPECT_EQ(sEntries[0].method, KJH_RADAR_GRASS); // grass first

    // Route 2's trees (FireRed's table, slots 50/15/15/10/5/5): Hoothoot, Spinarak, Pineco, Wurmple, Spinarak, Pineco
    count = KJH_RadarBuildRoute(MAPSEC_ROUTE_2, sEntries, KJH_RADAR_MAX_ENTRIES);
    EXPECT_EQ(Rate(count, SPECIES_HOOTHOOT, KJH_RADAR_HEADBUTT), 50);
    EXPECT_EQ(Rate(count, SPECIES_SPINARAK, KJH_RADAR_HEADBUTT), 20);
    EXPECT_EQ(Rate(count, SPECIES_PINECO, KJH_RADAR_HEADBUTT), 20);
    EXPECT_EQ(Rate(count, SPECIES_WURMPLE, KJH_RADAR_HEADBUTT), 10);
    EXPECT_EQ(Rate(count, SPECIES_HOOTHOOT, KJH_RADAR_HEADBUTT_RARE), -1); // Kanto's trees have one table
    EXPECT_EQ(sEntries[count - 1].method, KJH_RADAR_HEADBUTT); // trees last
}

TEST("KJH radar: a Johto route page shows Crystal's common trees and its rare trees apart")
{
    u32 count;

    NoSwarms();
    // Route 29: common Hoothoot, Spinarak, Ledyba, Exeggcute x3; rare Hoothoot, Pineco x2, Exeggcute x3
    count = KJH_RadarBuildRoute(MAPSEC_J_ROUTE_29, sEntries, KJH_RADAR_MAX_ENTRIES);
    EXPECT_EQ(Rate(count, SPECIES_HOOTHOOT, KJH_RADAR_HEADBUTT), 50);
    EXPECT_EQ(Rate(count, SPECIES_LEDYBA, KJH_RADAR_HEADBUTT), 15);
    EXPECT_EQ(Rate(count, SPECIES_EXEGGCUTE, KJH_RADAR_HEADBUTT), 20);
    EXPECT_EQ(Rate(count, SPECIES_PINECO, KJH_RADAR_HEADBUTT), -1);
    EXPECT_EQ(Rate(count, SPECIES_HOOTHOOT, KJH_RADAR_HEADBUTT_RARE), 50);
    EXPECT_EQ(Rate(count, SPECIES_PINECO, KJH_RADAR_HEADBUTT_RARE), 30);
    EXPECT_EQ(Rate(count, SPECIES_EXEGGCUTE, KJH_RADAR_HEADBUTT_RARE), 20);
    EXPECT_EQ(Rate(count, SPECIES_SENTRET, KJH_RADAR_GRASS), 40); // slots 1, 3, 6, 7: 20+10+5+5
}

TEST("KJH radar: the radar names a species once it is seen, else ?????")
{
    ASSUME(!GetSetPokedexFlag(SpeciesToNationalPokedexNum(SPECIES_SPINARAK), FLAG_GET_SEEN));
    EXPECT_EQ(StringCompare(KJH_RadarSpeciesName(SPECIES_SPINARAK), COMPOUND_STRING("?????")), 0);
    GetSetPokedexFlag(SpeciesToNationalPokedexNum(SPECIES_HOOTHOOT), FLAG_SET_SEEN);
    EXPECT_EQ(StringCompare(KJH_RadarSpeciesName(SPECIES_HOOTHOOT), GetSpeciesName(SPECIES_HOOTHOOT)), 0);
}

TEST("KJH radar: a swarm takes its chance of its method's encounters; the others keep the rest")
{
    struct KjhRadarEntry e[8];
    u8 n = 0;

    for (u32 slot = 0; slot < 12; slot++) // Route 1's grass: Pidgey and Rattata, 50% each
        n = KJH_RadarAddSlot(e, n, 8, slot % 2 ? SPECIES_RATTATA : SPECIES_PIDGEY, KJH_RADAR_TABLE_LAND, slot);
    n = KJH_RadarAddSlot(e, n, 8, SPECIES_HOOTHOOT, KJH_RADAR_TABLE_HEADBUTT, 0);
    n = KJH_RadarAddSlot(e, n, 8, SPECIES_MAGIKARP, KJH_RADAR_TABLE_FISHING, 0);
    n = KJH_RadarAddSlot(e, n, 8, SPECIES_MAGIKARP, KJH_RADAR_TABLE_FISHING, 1);
    n = KJH_RadarAddSlot(e, n, 8, SPECIES_GOLDEEN, KJH_RADAR_TABLE_FISHING, 5);

    n = KJH_RadarApplySwarm(e, n, 8, SPECIES_SENTRET, KJH_RADAR_SWARM_LAND, 40);
    KJH_RadarSort(e, n);
    EXPECT_EQ(e[0].species, SPECIES_SENTRET); // the swarm comes first
    EXPECT_EQ(e[0].method, KJH_RADAR_SWARM_LAND);
    EXPECT_EQ(e[0].rate, 40);
    EXPECT_EQ(e[1].rate, 30); // Pidgey: 50% of 60%
    EXPECT_EQ(e[2].rate, 30); // Rattata
    EXPECT_EQ(e[n - 1].rate, 50); // the trees aren't part of it: Hoothoot keeps 50%

    // by fishing, each rod's catches: Magikarp's old rod 100% -> 50%, Goldeen's super rod 40% -> 20%
    n = KJH_RadarApplySwarm(e, n, 8, SPECIES_QWILFISH, KJH_RADAR_SWARM_FISHING, 50);
    KJH_RadarSort(e, n);
    EXPECT_EQ(e[1].species, SPECIES_QWILFISH);
    EXPECT_EQ(e[1].method, KJH_RADAR_SWARM_FISHING);
    EXPECT_EQ(e[1].rate, 50);
    for (u32 i = 0; i < n; i++)
    {
        if (e[i].species == SPECIES_MAGIKARP) EXPECT_EQ(e[i].rate, 50);
        if (e[i].species == SPECIES_GOLDEEN) EXPECT_EQ(e[i].rate, 20);
    }

    // no grass on the map: no swarm to show
    n = 0;
    n = KJH_RadarAddSlot(e, n, 8, SPECIES_TENTACOOL, KJH_RADAR_TABLE_WATER, 0);
    EXPECT_EQ(KJH_RadarApplySwarm(e, n, 8, SPECIES_SENTRET, KJH_RADAR_SWARM_LAND, 40), n);
}

TEST("KJH radar: the route list marks today's swarm routes, Kanto's and Johto's, and their pages show the swarm")
{
    u32 count, route1, route32;

    NoSwarms();
    FlagSet(FLAG_KJH_JOHTO_ARRIVED);
    KJH_StartSwarm(0); // Kanto: Sentret on Route 1, 50% of the grass
    for (u32 i = 0; i < KJH_RegionSwarmCount(KJH_SWARM_JOHTO); i++)
    {
        if (KJH_GetRegionSwarm(KJH_SWARM_JOHTO, i)->species == SPECIES_QWILFISH) // Route 32, 50% of the rods
            KJH_StartRegionSwarm(KJH_SWARM_JOHTO, i);
    }
    ASSUME(gSaveBlock3Ptr->kjhSwarms[KJH_SWARM_JOHTO].species == SPECIES_QWILFISH);

    count = KJH_RadarBuildRoutes(sRoutes, KJH_RADAR_MAX_ROUTES);
    route1 = RouteIndex(count, MAPSEC_ROUTE_1);
    route32 = RouteIndex(count, MAPSEC_J_ROUTE_32);
    EXPECT(sRoutes[route1].swarm);
    EXPECT(sRoutes[route32].swarm);
    EXPECT(!sRoutes[RouteIndex(count, MAPSEC_ROUTE_2)].swarm);
    EXPECT(!sRoutes[RouteIndex(count, MAPSEC_J_ROUTE_29)].swarm);

    count = KJH_RadarBuildRoute(MAPSEC_ROUTE_1, sEntries, KJH_RADAR_MAX_ENTRIES);
    EXPECT_EQ(sEntries[0].species, SPECIES_SENTRET);
    EXPECT_EQ(sEntries[0].method, KJH_RADAR_SWARM_LAND);
    EXPECT_EQ(sEntries[0].rate, 50);
    EXPECT_EQ(Rate(count, SPECIES_PIDGEY, KJH_RADAR_GRASS), 25);

    count = KJH_RadarBuildRoute(MAPSEC_J_ROUTE_32, sEntries, KJH_RADAR_MAX_ENTRIES);
    EXPECT_EQ(sEntries[0].species, SPECIES_QWILFISH);
    EXPECT_EQ(sEntries[0].method, KJH_RADAR_SWARM_FISHING);
    EXPECT_EQ(sEntries[0].rate, 50);

    // a swarm species never seen stays ?????
    ASSUME(!GetSetPokedexFlag(SpeciesToNationalPokedexNum(SPECIES_QWILFISH), FLAG_GET_SEEN));
    EXPECT_EQ(StringCompare(KJH_RadarSpeciesName(sEntries[0].species), COMPOUND_STRING("?????")), 0);

    NoSwarms();
    count = KJH_RadarBuildRoutes(sRoutes, KJH_RADAR_MAX_ROUTES);
    EXPECT(!sRoutes[RouteIndex(count, MAPSEC_ROUTE_1)].swarm);
    FlagClear(FLAG_KJH_JOHTO_ARRIVED);
}
