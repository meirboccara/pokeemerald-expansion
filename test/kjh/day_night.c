// KJH (DN-E): day and night on CF-4's in-game clock. DN-1 chose HGSS's periods (OW_TIMES_OF_DAY GEN_4: morning 4-10,
// day 10-20, night 20-4); DN-4's night wild tables (kjh_tools/night_tables.py) take over at night, a map without one
// keeps its base table; DN-7's radar marks the species met only by day or only at night.
#include "global.h"
#include "fake_rtc.h"
#include "kjh_dex_radar.h"
#include "kjh_swarms.h"
#include "malloc.h"
#include "mass_outbreak.h"
#include "pokedex.h"
#include "rtc.h"
#include "wild_encounter.h"
#include "test/test.h"
#include "constants/map_groups.h"
#include "constants/region_map_sections.h"

#define NATIONAL_GEN3 386

static EWRAM_DATA struct KjhRadarEntry sEntries[KJH_RADAR_MAX_ENTRIES] = {0};

static void At(u32 hour)
{
    FakeRtc_ManuallySetTime(0, hour, 0, 0);
}

static u32 HeaderOf(u32 map)
{
    for (u32 i = 0; gWildMonHeaders[i].mapGroup != MAP_GROUP(MAP_UNDEFINED); i++)
    {
        if (gWildMonHeaders[i].mapGroup == MAP_GROUP(map) && gWildMonHeaders[i].mapNum == MAP_NUM(map))
            return i;
    }
    return HEADER_NONE;
}

// Whether a species is in the grass table the game uses now on a map (GetTimeOfDayForEncounters' pick)
static bool32 InGrassNow(u32 map, u32 species)
{
    u32 header = HeaderOf(map);
    const struct WildPokemonInfo *info = gWildMonHeaders[header].encounterTypes[GetTimeOfDayForEncounters(header, WILD_AREA_LAND)].landMonsInfo;

    for (u32 slot = 0; info != NULL && slot < KJH_RadarTableSlots(KJH_RADAR_TABLE_LAND); slot++)
    {
        if (info->wildPokemon[slot].species == species)
            return TRUE;
    }
    return FALSE;
}

static bool32 InFishingNow(u32 map, u32 species)
{
    u32 header = HeaderOf(map);
    const struct WildPokemonInfo *info = gWildMonHeaders[header].encounterTypes[GetTimeOfDayForEncounters(header, WILD_AREA_FISHING)].fishingMonsInfo;

    for (u32 slot = 0; info != NULL && slot < KJH_RadarTableSlots(KJH_RADAR_TABLE_FISHING); slot++)
    {
        if (info->wildPokemon[slot].species == species)
            return TRUE;
    }
    return FALSE;
}

static const struct KjhRadarEntry *Entry(u32 count, u32 species, u32 method)
{
    for (u32 i = 0; i < count; i++)
    {
        if (sEntries[i].species == species && sEntries[i].method == method)
            return &sEntries[i];
    }
    return NULL;
}

static void NoSwarms(void)
{
    ZeroMassOutbreak();
    for (u32 i = 0; i < KJH_SWARM_REGIONS; i++)
        gSaveBlock3Ptr->kjhSwarms[i].species = SPECIES_NONE;
}

TEST("KJH day/night: HGSS's periods, morning 4-10, day 10-20, night 20-4")
{
    At(3);  EXPECT_EQ(GetTimeOfDay(), TIME_NIGHT);
    At(4);  EXPECT_EQ(GetTimeOfDay(), TIME_MORNING);
    At(9);  EXPECT_EQ(GetTimeOfDay(), TIME_MORNING);
    At(10); EXPECT_EQ(GetTimeOfDay(), TIME_DAY);
    At(19); EXPECT_EQ(GetTimeOfDay(), TIME_DAY);
    At(20); EXPECT_EQ(GetTimeOfDay(), TIME_NIGHT);
    At(23); EXPECT_EQ(GetTimeOfDay(), TIME_NIGHT);
}

TEST("KJH day/night: Kanto's Route 1 has Pidgey by day, Hoothoot and Noctowl at night")
{
    At(12);
    EXPECT(InGrassNow(MAP_ROUTE1, SPECIES_PIDGEY));
    EXPECT(!InGrassNow(MAP_ROUTE1, SPECIES_HOOTHOOT));
    At(7); // the morning uses the base table too
    EXPECT(InGrassNow(MAP_ROUTE1, SPECIES_PIDGEY));
    At(22);
    EXPECT(InGrassNow(MAP_ROUTE1, SPECIES_HOOTHOOT));
    EXPECT(InGrassNow(MAP_ROUTE1, SPECIES_NOCTOWL));
    EXPECT(InGrassNow(MAP_ROUTE1, SPECIES_RATTATA));
    EXPECT(!InGrassNow(MAP_ROUTE1, SPECIES_PIDGEY));
}

TEST("KJH day/night: Johto takes Crystal's night tables: Hoothoot on Route 29, Sneasel in the Ice Path, Staryu by rod")
{
    At(12);
    EXPECT(!InGrassNow(MAP_JOHTO_ROUTE_29, SPECIES_HOOTHOOT));
    EXPECT(!InGrassNow(MAP_JOHTO_ICE_PATH_B1F, SPECIES_SNEASEL));
    EXPECT(InFishingNow(MAP_JOHTO_OLIVINE_CITY, SPECIES_CORSOLA));
    At(22);
    EXPECT(InGrassNow(MAP_JOHTO_ROUTE_29, SPECIES_HOOTHOOT));
    EXPECT(InGrassNow(MAP_JOHTO_ICE_PATH_B1F, SPECIES_SNEASEL));
    EXPECT(InFishingNow(MAP_JOHTO_OLIVINE_CITY, SPECIES_STARYU));
    EXPECT(!InFishingNow(MAP_JOHTO_OLIVINE_CITY, SPECIES_CORSOLA));
}

TEST("KJH day/night: Hoenn's Route 120 has Duskull at night; a map with no night table keeps its table")
{
    At(12);
    EXPECT(!InGrassNow(MAP_ROUTE120, SPECIES_DUSKULL));
    At(22);
    EXPECT(InGrassNow(MAP_ROUTE120, SPECIES_DUSKULL));
    // Pallet Town's water and Route 19's sea have no night table: the base table at night
    EXPECT_EQ(GetTimeOfDayForEncounters(HeaderOf(MAP_ROUTE19), WILD_AREA_WATER), OW_TIME_OF_DAY_FALLBACK);
    EXPECT_EQ(GetTimeOfDayForEncounters(HeaderOf(MAP_ROUTE1), WILD_AREA_LAND), TIME_NIGHT);
}

TEST("KJH day/night: every night table has its 12 grass slots, all of the National Pokedex's first 386")
{
    u32 tables = 0;

    for (u32 i = 0; gWildMonHeaders[i].mapGroup != MAP_GROUP(MAP_UNDEFINED); i++)
    {
        const struct WildPokemonInfo *info = gWildMonHeaders[i].encounterTypes[TIME_NIGHT].landMonsInfo;

        if (info == NULL)
            continue;
        tables++;
        for (u32 slot = 0; slot < KJH_RadarTableSlots(KJH_RADAR_TABLE_LAND); slot++)
        {
            u32 dex = SpeciesToNationalPokedexNum(info->wildPokemon[slot].species);
            EXPECT_GT(dex, 0);
            EXPECT_LE(dex, NATIONAL_GEN3);
        }
    }
    EXPECT_GT(tables, 90); // Kanto 27, Johto's routes, caves and towers, Hoenn 19
}

TEST("KJH radar: a route page marks the species met only by day or only at night, with their chance then")
{
    u32 count;
    const struct KjhRadarEntry *e;

    NoSwarms();
    At(12); // FireRed's Route 1 by day: Pidgey 50, Rattata 50; at night Pidgey's slots are Hoothoot 49 and Noctowl 1
    count = KJH_RadarBuildRoute(MAPSEC_ROUTE_1, sEntries, KJH_RADAR_MAX_ENTRIES);
    e = Entry(count, SPECIES_PIDGEY, KJH_RADAR_GRASS);
    EXPECT(e != NULL && e->rate == 50 && e->period == KJH_RADAR_PERIOD_DAY);
    e = Entry(count, SPECIES_RATTATA, KJH_RADAR_GRASS);
    EXPECT(e != NULL && e->rate == 50 && e->period == KJH_RADAR_PERIOD_ANY);
    e = Entry(count, SPECIES_HOOTHOOT, KJH_RADAR_GRASS);
    EXPECT(e != NULL && e->rate == 49 && e->period == KJH_RADAR_PERIOD_NIGHT);
    e = Entry(count, SPECIES_NOCTOWL, KJH_RADAR_GRASS);
    EXPECT(e != NULL && e->rate == 1 && e->period == KJH_RADAR_PERIOD_NIGHT);

    At(22); // the same marks at night
    count = KJH_RadarBuildRoute(MAPSEC_ROUTE_1, sEntries, KJH_RADAR_MAX_ENTRIES);
    e = Entry(count, SPECIES_HOOTHOOT, KJH_RADAR_GRASS);
    EXPECT(e != NULL && e->rate == 49 && e->period == KJH_RADAR_PERIOD_NIGHT);
    e = Entry(count, SPECIES_PIDGEY, KJH_RADAR_GRASS);
    EXPECT(e != NULL && e->rate == 50 && e->period == KJH_RADAR_PERIOD_DAY);
    e = Entry(count, SPECIES_RATTATA, KJH_RADAR_GRASS);
    EXPECT(e != NULL && e->period == KJH_RADAR_PERIOD_ANY);
}

TEST("KJH radar: the route list counts a route's night species too")
{
    struct KjhRadarRoute *routes = Alloc(KJH_RADAR_MAX_ROUTES * sizeof(struct KjhRadarRoute));
    u32 count, species = 0;

    NoSwarms();
    At(12);
    count = KJH_RadarBuildRoutes(routes, KJH_RADAR_MAX_ROUTES);
    for (u32 i = 0; i < count; i++)
    {
        if (routes[i].mapSec == MAPSEC_ROUTE_1)
            species = routes[i].speciesCount;
    }
    EXPECT_EQ(species, 4); // Pidgey, Rattata, Hoothoot, Noctowl (Route 1 has no water, rocks or trees in FireRed)
    Free(routes);
}

TEST("KJH radar: periods of one map's entries (rules)")
{
    struct KjhRadarEntry now[4] = {
        {.species = SPECIES_PIDGEY, .method = KJH_RADAR_GRASS, .rate = 50},
        {.species = SPECIES_RATTATA, .method = KJH_RADAR_GRASS, .rate = 50},
    };
    const struct KjhRadarEntry night[] = {
        {.species = SPECIES_RATTATA, .method = KJH_RADAR_GRASS, .rate = 50},
        {.species = SPECIES_HOOTHOOT, .method = KJH_RADAR_GRASS, .rate = 50},
    };
    u32 count = KJH_RadarAddPeriods(now, 2, ARRAY_COUNT(now), night, ARRAY_COUNT(night), KJH_RADAR_PERIOD_DAY,
                                    KJH_RADAR_PERIOD_NIGHT);

    EXPECT_EQ(count, 3);
    EXPECT_EQ(now[0].period, KJH_RADAR_PERIOD_DAY);
    EXPECT_EQ(now[1].period, KJH_RADAR_PERIOD_ANY);
    EXPECT_EQ(now[2].species, SPECIES_HOOTHOOT);
    EXPECT_EQ(now[2].period, KJH_RADAR_PERIOD_NIGHT);
    EXPECT_EQ(now[2].rate, 50);
}
