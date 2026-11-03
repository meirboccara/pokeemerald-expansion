// KJH (ENG-8, CF-7): the route radar, the game side (include/kjh_dex_radar.h): reads the wild encounter tables, the
// regions reached, today's swarms and the Pokedex flags. The rules are in kjh_dex_radar_rules.c, the screen in
// kjh_dex_radar_screen.c.
#include "global.h"
#include "event_data.h"
#include "kjh_dex_radar.h"
#include "kjh_map_regions.h"
#include "kjh_swarms.h"
#include "malloc.h"
#include "mass_outbreak.h"
#include "overworld.h"
#include "pokedex.h"
#include "pokemon.h"
#include "wild_encounter.h"
#include "constants/johto_flags.h"
#include "constants/map_groups.h"
#include "constants/region_map_sections.h"

static const u8 sText_RadarKanto[] = _("KANTO");
static const u8 sText_RadarJohto[] = _("JOHTO");
static const u8 sText_RadarHoenn[] = _("HOENN");
static const u8 sText_RadarUnseen[] = _("?????");

// Johto's map sections were added in no particular order: list them the way the player travels
static const u16 sJohtoTravelOrder[] =
{
    MAPSEC_J_NEW_BARK_TOWN, MAPSEC_J_ROUTE_29, MAPSEC_J_CHERRYGROVE_CITY, MAPSEC_J_ROUTE_30, MAPSEC_J_ROUTE_31,
    MAPSEC_J_DARK_CAVE, MAPSEC_J_VIOLET_CITY, MAPSEC_J_SPROUT_TOWER, MAPSEC_J_ROUTE_32, MAPSEC_J_RUINS_OF_ALPH,
    MAPSEC_J_UNION_CAVE, MAPSEC_J_ROUTE_33, MAPSEC_J_SLOWPOKE_WELL, MAPSEC_J_AZALEA_TOWN, MAPSEC_J_ILEX_FOREST,
    MAPSEC_J_ROUTE_34, MAPSEC_J_GOLDENROD_CITY, MAPSEC_J_RADIO_TOWER, MAPSEC_J_ROUTE_35, MAPSEC_J_NATIONAL_PARK,
    MAPSEC_J_ROUTE_36, MAPSEC_J_ROUTE_37, MAPSEC_J_ECRUTEAK_CITY, MAPSEC_J_BURNED_TOWER, MAPSEC_J_TIN_TOWER,
    MAPSEC_J_ROUTE_38, MAPSEC_J_ROUTE_39, MAPSEC_J_OLIVINE_CITY, MAPSEC_J_LIGHTHOUSE, MAPSEC_J_ROUTE_40,
    MAPSEC_J_ROUTE_41, MAPSEC_J_WHIRL_ISLANDS, MAPSEC_J_CIANWOOD_CITY, MAPSEC_J_ROUTE_42, MAPSEC_J_MT_MORTAR,
    MAPSEC_J_MAHOGANY_TOWN, MAPSEC_J_ROUTE_43, MAPSEC_J_LAKE_OF_RAGE, MAPSEC_J_ROUTE_44, MAPSEC_J_ICE_PATH,
    MAPSEC_J_BLACKTHORN_CITY, MAPSEC_J_DRAGONS_DEN, MAPSEC_J_ROUTE_45, MAPSEC_J_ROUTE_46, MAPSEC_J_ROUTE_27,
    MAPSEC_J_TOHJO_FALLS, MAPSEC_J_ROUTE_26, MAPSEC_J_ROUTE_28, MAPSEC_J_SILVER_CAVE,
};

// Hoenn's, the way Emerald's story goes (its map sections are in the Town Map's order); the post-game's caves last
static const u16 sHoennTravelOrder[] =
{
    MAPSEC_ROUTE_101, MAPSEC_ROUTE_103, MAPSEC_ROUTE_102, MAPSEC_PETALBURG_CITY, MAPSEC_ROUTE_104,
    MAPSEC_PETALBURG_WOODS, MAPSEC_ROUTE_116, MAPSEC_RUSTURF_TUNNEL, MAPSEC_DEWFORD_TOWN, MAPSEC_ROUTE_106,
    MAPSEC_GRANITE_CAVE, MAPSEC_ROUTE_107, MAPSEC_ROUTE_108, MAPSEC_ROUTE_109, MAPSEC_SLATEPORT_CITY, MAPSEC_ROUTE_110,
    MAPSEC_ROUTE_117, MAPSEC_ROUTE_111, MAPSEC_ROUTE_112, MAPSEC_FIERY_PATH, MAPSEC_ROUTE_113, MAPSEC_ROUTE_114,
    MAPSEC_METEOR_FALLS, MAPSEC_ROUTE_115, MAPSEC_JAGGED_PASS, MAPSEC_MIRAGE_TOWER, MAPSEC_NEW_MAUVILLE,
    MAPSEC_ROUTE_105, MAPSEC_ABANDONED_SHIP, MAPSEC_ROUTE_118, MAPSEC_ROUTE_119, MAPSEC_ROUTE_120, MAPSEC_ROUTE_121,
    MAPSEC_SAFARI_ZONE, MAPSEC_LILYCOVE_CITY, MAPSEC_ROUTE_122, MAPSEC_MT_PYRE, MAPSEC_ROUTE_123, MAPSEC_MAGMA_HIDEOUT,
    MAPSEC_ROUTE_124, MAPSEC_UNDERWATER_124, MAPSEC_MOSSDEEP_CITY, MAPSEC_ROUTE_125, MAPSEC_SHOAL_CAVE,
    MAPSEC_ROUTE_127, MAPSEC_ROUTE_126, MAPSEC_UNDERWATER_126, MAPSEC_ROUTE_128, MAPSEC_SEAFLOOR_CAVERN,
    MAPSEC_SOOTOPOLIS_CITY, MAPSEC_CAVE_OF_ORIGIN, MAPSEC_SKY_PILLAR, MAPSEC_ROUTE_129, MAPSEC_ROUTE_130,
    MAPSEC_ROUTE_131, MAPSEC_PACIFIDLOG_TOWN, MAPSEC_ROUTE_132, MAPSEC_ROUTE_133, MAPSEC_ROUTE_134,
    MAPSEC_EVER_GRANDE_CITY, MAPSEC_VICTORY_ROAD, MAPSEC_DESERT_UNDERPASS, MAPSEC_ARTISAN_CAVE, MAPSEC_ALTERING_CAVE,
};

static bool32 IsKantoReached(void)
{
    return TRUE;
}

static bool32 IsJohtoReached(void)
{
    return FlagGet(FLAG_KJH_JOHTO_ARRIVED);
}

static bool32 IsHoennReached(void)
{
    return FlagGet(KJH_HOENN_REACHED_FLAG);
}

// The radar's regions, in the order the route list shows them. A region's wild tables are those of its map groups
// (include/kjh_map_regions.h: Emerald's Hoenn groups come first, then FireRed's, then Johto's). A region
// without a travel order lists its routes by map section. Hoenn's wild tables are Emerald's own (wild_encounters.json,
// built in the FireRed version with Hoenn's maps, HAS_HOENN_MAPS).
static const struct RadarRegion
{
    const u8 *name;
    bool32 (*hasMapGroup)(u32 mapGroup);
    bool32 (*isReached)(void);
    const u16 *travelOrder;
    u16 travelOrderCount;
} sRadarRegions[] =
{
    {
        .name = sText_RadarKanto,
        .hasMapGroup = KJH_IsKantoMapGroup,
        .isReached = IsKantoReached,
    },
    {
        .name = sText_RadarJohto,
        .hasMapGroup = KJH_IsJohtoMapGroup,
        .isReached = IsJohtoReached,
        .travelOrder = sJohtoTravelOrder,
        .travelOrderCount = ARRAY_COUNT(sJohtoTravelOrder),
    },
    {
        .name = sText_RadarHoenn,
        .hasMapGroup = KJH_IsHoennMapGroup,
        .isReached = IsHoennReached,
        .travelOrder = sHoennTravelOrder,
        .travelOrderCount = ARRAY_COUNT(sHoennTravelOrder),
    },
};

#define NO_REGION 0xFF

const u8 *KJH_RadarRegionName(u8 region)
{
    return region < ARRAY_COUNT(sRadarRegions) ? sRadarRegions[region].name : sText_RadarUnseen;
}

const u8 *KJH_RadarSpeciesName(u16 species)
{
    if (GetSetPokedexFlag(SpeciesToNationalPokedexNum(species), FLAG_GET_SEEN))
        return GetSpeciesName(species);
    return sText_RadarUnseen;
}

static u32 RegionOfMapGroup(u32 mapGroup)
{
    for (u32 i = 0; i < ARRAY_COUNT(sRadarRegions); i++)
    {
        if (sRadarRegions[i].hasMapGroup(mapGroup))
            return i;
    }
    return NO_REGION;
}

// The Sevii Islands' sections show once their island is on the Town Map (as FireRed's Pokedex area pages did)
static const struct { u16 mapSec; u16 flag; } sSeviiSections[] =
{
    {MAPSEC_KINDLE_ROAD, FLAG_WORLD_MAP_ONE_ISLAND},     {MAPSEC_TREASURE_BEACH, FLAG_WORLD_MAP_ONE_ISLAND},
    {MAPSEC_ONE_ISLAND, FLAG_WORLD_MAP_ONE_ISLAND},      {MAPSEC_MT_EMBER, FLAG_WORLD_MAP_ONE_ISLAND},
    {MAPSEC_CAPE_BRINK, FLAG_WORLD_MAP_TWO_ISLAND},      {MAPSEC_TWO_ISLAND, FLAG_WORLD_MAP_TWO_ISLAND},
    {MAPSEC_BOND_BRIDGE, FLAG_WORLD_MAP_THREE_ISLAND},   {MAPSEC_THREE_ISLE_PORT, FLAG_WORLD_MAP_THREE_ISLAND},
    {MAPSEC_THREE_ISLAND, FLAG_WORLD_MAP_THREE_ISLAND},  {MAPSEC_BERRY_FOREST, FLAG_WORLD_MAP_THREE_ISLAND},
    {MAPSEC_THREE_ISLE_PATH, FLAG_WORLD_MAP_THREE_ISLAND},
    {MAPSEC_FOUR_ISLAND, FLAG_WORLD_MAP_FOUR_ISLAND},    {MAPSEC_ICEFALL_CAVE, FLAG_WORLD_MAP_FOUR_ISLAND},
    {MAPSEC_RESORT_GORGEOUS, FLAG_WORLD_MAP_FIVE_ISLAND}, {MAPSEC_WATER_LABYRINTH, FLAG_WORLD_MAP_FIVE_ISLAND},
    {MAPSEC_FIVE_ISLE_MEADOW, FLAG_WORLD_MAP_FIVE_ISLAND}, {MAPSEC_MEMORIAL_PILLAR, FLAG_WORLD_MAP_FIVE_ISLAND},
    {MAPSEC_FIVE_ISLAND, FLAG_WORLD_MAP_FIVE_ISLAND},    {MAPSEC_ROCKET_WAREHOUSE, FLAG_WORLD_MAP_FIVE_ISLAND},
    {MAPSEC_LOST_CAVE, FLAG_WORLD_MAP_FIVE_ISLAND},
    {MAPSEC_OUTCAST_ISLAND, FLAG_WORLD_MAP_SIX_ISLAND},  {MAPSEC_GREEN_PATH, FLAG_WORLD_MAP_SIX_ISLAND},
    {MAPSEC_WATER_PATH, FLAG_WORLD_MAP_SIX_ISLAND},      {MAPSEC_RUIN_VALLEY, FLAG_WORLD_MAP_SIX_ISLAND},
    {MAPSEC_DOTTED_HOLE, FLAG_WORLD_MAP_SIX_ISLAND},     {MAPSEC_PATTERN_BUSH, FLAG_WORLD_MAP_SIX_ISLAND},
    {MAPSEC_ALTERING_CAVE_FRLG, FLAG_WORLD_MAP_SIX_ISLAND}, {MAPSEC_SIX_ISLAND, FLAG_WORLD_MAP_SIX_ISLAND},
    {MAPSEC_TRAINER_TOWER, FLAG_WORLD_MAP_SEVEN_ISLAND}, {MAPSEC_CANYON_ENTRANCE, FLAG_WORLD_MAP_SEVEN_ISLAND},
    {MAPSEC_SEVAULT_CANYON, FLAG_WORLD_MAP_SEVEN_ISLAND}, {MAPSEC_TANOBY_RUINS, FLAG_WORLD_MAP_SEVEN_ISLAND},
    {MAPSEC_SEVEN_ISLAND, FLAG_WORLD_MAP_SEVEN_ISLAND},
};

// A section is listed once its region is reached and, for the Sevii Islands, its island is unlocked. The Tanoby
// chambers have no wild Pokemon until the ruins are unlocked.
static bool32 IsMapSecListed(u32 mapSec, u32 region)
{
    if (region == NO_REGION || mapSec >= MAPSEC_NONE || !sRadarRegions[region].isReached())
        return FALSE;
    if (mapSec >= MAPSEC_MONEAN_CHAMBER && mapSec <= MAPSEC_VIAPOIS_CHAMBER)
        return FlagGet(FLAG_SYS_UNLOCKED_TANOBY_RUINS) && FlagGet(FLAG_WORLD_MAP_SEVEN_ISLAND);
    for (u32 i = 0; i < ARRAY_COUNT(sSeviiSections); i++)
    {
        if (sSeviiSections[i].mapSec == mapSec)
            return FlagGet(sSeviiSections[i].flag);
    }
    return TRUE;
}

static u32 MapSecOfHeader(const struct WildPokemonHeader *header)
{
    return Overworld_GetMapHeaderByGroupAndId(header->mapGroup, header->mapNum)->regionMapSectionId;
}

static bool32 IsSameMap(const struct WildPokemonHeader *a, const struct WildPokemonHeader *b)
{
    return a->mapGroup == b->mapGroup && a->mapNum == b->mapNum;
}

// The game uses a map's first table (GetCurrentMapWildMonHeaderId), but Emerald's Altering Cave picks one of its
// tables by VAR_ALTERING_CAVE_WILD_SET
static bool32 IsHeaderUsed(u32 headerId)
{
    const struct WildPokemonHeader *header = &gWildMonHeaders[headerId];
    u32 first = headerId, wanted = 0;

    while (first > 0 && IsSameMap(&gWildMonHeaders[first - 1], header))
        first--;
    if (header->mapGroup == MAP_GROUP(MAP_ALTERING_CAVE) && header->mapNum == MAP_NUM(MAP_ALTERING_CAVE))
    {
        wanted = VarGet(VAR_ALTERING_CAVE_WILD_SET);
        if (wanted >= NUM_ALTERING_CAVE_TABLES)
            wanted = 0;
    }
    return headerId - first == wanted;
}

static bool32 IsHeaderEnd(u32 headerId)
{
    return gWildMonHeaders[headerId].mapGroup == MAP_GROUP(MAP_UNDEFINED);
}

// The radar shows the default time's tables (time-of-day encounters are off in KJH)
static const struct WildPokemonInfo *GetTable(const struct WildPokemonHeader *header, u32 table)
{
    const struct WildEncounterTypes *types = &header->encounterTypes[TIME_OF_DAY_DEFAULT];

    switch (table)
    {
    case KJH_RADAR_TABLE_LAND:          return types->landMonsInfo;
    case KJH_RADAR_TABLE_WATER:         return types->waterMonsInfo;
    case KJH_RADAR_TABLE_ROCK_SMASH:    return types->rockSmashMonsInfo;
    case KJH_RADAR_TABLE_FISHING:       return types->fishingMonsInfo;
    case KJH_RADAR_TABLE_HEADBUTT:      return types->headbuttMonsInfo;
    case KJH_RADAR_TABLE_HEADBUTT_RARE: return types->headbuttRareMonsInfo;
    }
    return NULL;
}

// --- CF-7: today's swarms, every region's ---

struct RadarSwarm
{
    u16 species;
    u16 map;    // MAP_*
    u8 method;  // KJH_RADAR_SWARM_*
    u8 chance;
};

#define MAX_RADAR_SWARMS (1 + KJH_SWARM_REGIONS)

// Kanto's is expansion's mass outbreak record (grass only); Johto's and Hoenn's are SaveBlock3's (KJH_StartDailySwarm
// leaves a region not reached yet without one)
static u32 GetTodaysSwarms(struct RadarSwarm *swarms)
{
    u32 count = 0;

    if (IsMassOutbreakActive() && gSaveBlock1Ptr->outbreakPokemonSpecies != SPECIES_NONE)
    {
        swarms[count].species = gSaveBlock1Ptr->outbreakPokemonSpecies;
        swarms[count].map = gSaveBlock1Ptr->outbreakLocationMapNum | (gSaveBlock1Ptr->outbreakLocationMapGroup << 8);
        swarms[count].method = KJH_RADAR_SWARM_LAND;
        swarms[count].chance = gSaveBlock1Ptr->outbreakPokemonProbability;
        count++;
    }
    for (u32 i = 0; i < KJH_SWARM_REGIONS; i++)
    {
        const struct KjhRegionSwarm *swarm = &gSaveBlock3Ptr->kjhSwarms[i];

        if (swarm->species == SPECIES_NONE)
            continue;
        swarms[count].species = swarm->species;
        swarms[count].map = swarm->map;
        swarms[count].method = swarm->method == KJH_SWARM_FISHING ? KJH_RADAR_SWARM_FISHING : KJH_RADAR_SWARM_LAND;
        swarms[count].chance = swarm->chance;
        count++;
    }
    return count;
}

static u32 MapSecOfMap(u32 map)
{
    return Overworld_GetMapHeaderByGroupAndId(MAP_GROUP(map), MAP_NUM(map))->regionMapSectionId;
}

// --- The route page ---

u8 KJH_RadarBuildRoute(u16 mapSec, struct KjhRadarEntry *entries, u8 max)
{
    struct KjhRadarEntry map[KJH_RADAR_MAX_ENTRIES];
    struct RadarSwarm swarms[MAX_RADAR_SWARMS];
    const struct WildPokemonHeader *header;
    const struct WildPokemonInfo *info;
    u32 swarmCount = GetTodaysSwarms(swarms);
    u8 count = 0, mapCount;

    for (u32 i = 0; !IsHeaderEnd(i); i++)
    {
        header = &gWildMonHeaders[i];
        if (MapSecOfHeader(header) != mapSec || !IsHeaderUsed(i))
            continue;
        mapCount = 0;
        for (u32 table = 0; table < KJH_RADAR_TABLE_COUNT; table++)
        {
            info = GetTable(header, table);
            if (info == NULL)
                continue;
            for (u32 slot = 0; slot < KJH_RadarTableSlots(table); slot++)
                mapCount = KJH_RadarAddSlot(map, mapCount, ARRAY_COUNT(map), info->wildPokemon[slot].species, table, slot);
        }
        for (u32 s = 0; s < swarmCount; s++)
        {
            if (swarms[s].map == (header->mapNum | (header->mapGroup << 8)))
                mapCount = KJH_RadarApplySwarm(map, mapCount, ARRAY_COUNT(map), swarms[s].species, swarms[s].method,
                                               swarms[s].chance);
        }
        count = KJH_RadarMergeMap(entries, count, max, map, mapCount);
    }
    KJH_RadarSort(entries, count);
    return count;
}

// --- The route list ---

static u32 TravelRank(const struct RadarRegion *region, u32 mapSec)
{
    for (u32 i = 0; i < region->travelOrderCount; i++)
    {
        if (region->travelOrder[i] == mapSec)
            return i;
    }
    return region->travelOrderCount + mapSec;
}

// By region, then the region's order
static u32 RouteSortKey(const struct KjhRadarRoute *route)
{
    return (route->region << 16) | TravelRank(&sRadarRegions[route->region], route->mapSec);
}

#define NO_ROUTE 0xFF // KJH_RADAR_MAX_ROUTES stays below it

// The whole list opens at once, so this stays light: each table's route is found once, then each route only counts
// its species (no chances, no sorting).
u16 KJH_RadarBuildRoutes(struct KjhRadarRoute *routes, u16 max)
{
    u8 *routeOfMapSec = Alloc(MAPSEC_COUNT);
    u8 *routeOfHeader;
    u16 *species = Alloc(KJH_RADAR_MAX_ENTRIES * sizeof(u16));
    struct RadarSwarm swarms[MAX_RADAR_SWARMS];
    const struct WildPokemonHeader *header;
    const struct WildPokemonInfo *info;
    struct KjhRadarRoute route;
    u32 *keys, key;
    u16 count = 0, swarmCount;
    u32 mapSec, region, n, j, numHeaders;

    if (max > NO_ROUTE)
        max = NO_ROUTE;
    for (u32 i = 0; i < MAPSEC_COUNT; i++)
        routeOfMapSec[i] = NO_ROUTE;

    // the routes: sections of the regions reached that have wild Pokemon
    for (u32 i = 0; !IsHeaderEnd(i); i++)
    {
        header = &gWildMonHeaders[i];
        mapSec = MapSecOfHeader(header);
        region = RegionOfMapGroup(header->mapGroup);
        if (count >= max || !IsMapSecListed(mapSec, region) || routeOfMapSec[mapSec] != NO_ROUTE)
            continue;
        routeOfMapSec[mapSec] = count;
        routes[count] = (struct KjhRadarRoute) {.mapSec = mapSec, .region = region};
        count++;
    }

    // by region, then the region's order (insertion sort, each key worked out once)
    keys = Alloc(count * sizeof(u32) + 1);
    for (u32 i = 0; i < count; i++)
        keys[i] = RouteSortKey(&routes[i]);
    for (u32 i = 1; i < count; i++)
    {
        route = routes[i];
        key = keys[i];
        for (j = i; j > 0 && key < keys[j - 1]; j--)
        {
            routes[j] = routes[j - 1];
            keys[j] = keys[j - 1];
        }
        routes[j] = route;
        keys[j] = key;
    }
    Free(keys);
    for (u32 i = 0; i < count; i++)
        routeOfMapSec[routes[i].mapSec] = i;

    // each table's route, worked out once
    for (numHeaders = 0; !IsHeaderEnd(numHeaders); numHeaders++)
        ;
    routeOfHeader = Alloc(numHeaders + 1);
    for (u32 i = 0; i < numHeaders; i++)
    {
        mapSec = MapSecOfHeader(&gWildMonHeaders[i]);
        routeOfHeader[i] = (mapSec < MAPSEC_COUNT && IsHeaderUsed(i)) ? routeOfMapSec[mapSec] : NO_ROUTE;
    }

    // each route's species, and how many are caught
    for (u32 r = 0; r < count; r++)
    {
        n = 0;
        for (u32 i = 0; i < numHeaders; i++)
        {
            header = &gWildMonHeaders[i];
            if (routeOfHeader[i] != r)
                continue;
            for (u32 table = 0; table < KJH_RADAR_TABLE_COUNT; table++)
            {
                info = GetTable(header, table);
                if (info == NULL)
                    continue;
                for (u32 slot = 0; slot < KJH_RadarTableSlots(table); slot++)
                    n = KJH_RadarAddSpecies(species, n, KJH_RADAR_MAX_ENTRIES, info->wildPokemon[slot].species);
            }
        }
        routes[r].speciesCount = n;
        for (u32 k = 0; k < n; k++)
        {
            if (GetSetPokedexFlag(SpeciesToNationalPokedexNum(species[k]), FLAG_GET_CAUGHT))
                routes[r].caughtCount++;
        }
    }

    // CF-7: today's swarm routes
    swarmCount = GetTodaysSwarms(swarms);
    for (u32 s = 0; s < swarmCount; s++)
    {
        mapSec = MapSecOfMap(swarms[s].map);
        if (mapSec < MAPSEC_COUNT && routeOfMapSec[mapSec] != NO_ROUTE)
            routes[routeOfMapSec[mapSec]].swarm = TRUE;
    }

    Free(routeOfHeader);
    Free(species);
    Free(routeOfMapSec);
    return count;
}
