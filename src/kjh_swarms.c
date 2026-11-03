// KJH: the daily swarms (CF-5, CF-6, include/kjh_swarms.h).
#include "global.h"
#include "event_data.h"
#include "kjh_swarms.h"
#include "mass_outbreak.h"
#include "overworld.h"
#include "random.h"
#include "region_map.h"
#include "string_util.h"
#include "wild_encounter.h"
#include "constants/johto_flags.h"
#include "constants/map_groups.h"
#include "constants/species.h"

// Kanto's swarms: rare Kanto species and Gen 2/3 Pokemon FireRed lacks, Gen 1-3 only (FEATURES.md). One is picked
// each day. Levels come from the route's own grass table, never from here.
static const struct KjhSwarm sKantoSwarms[] =
{
    {SPECIES_SENTRET,   MAP_ROUTE1,  50},
    {SPECIES_PIKACHU,   MAP_ROUTE2,  50},
    {SPECIES_CLEFAIRY,  MAP_ROUTE3,  40},
    {SPECIES_ZIGZAGOON, MAP_ROUTE22, 50},
    {SPECIES_RALTS,     MAP_ROUTE24, 40},
    {SPECIES_SKITTY,    MAP_ROUTE25, 50},
    {SPECIES_SNUBBULL,  MAP_ROUTE5,  50},
    {SPECIES_SHROOMISH, MAP_ROUTE6,  50},
    {SPECIES_EEVEE,     MAP_ROUTE8,  30},
    {SPECIES_PHANPY,    MAP_ROUTE9,  50},
    {SPECIES_ELECTRIKE, MAP_ROUTE11, 50},
    {SPECIES_DRATINI,   MAP_ROUTE12, 30},
    {SPECIES_YANMA,     MAP_ROUTE13, 50},
    {SPECIES_SKARMORY,  MAP_ROUTE14, 30},
    {SPECIES_CHANSEY,   MAP_ROUTE15, 30},
    {SPECIES_DUNSPARCE, MAP_ROUTE16, 50},
    {SPECIES_SWABLU,    MAP_ROUTE18, 50},
    {SPECIES_LARVITAR,  MAP_ROUTE23, 30},
};

// Johto's: Crystal's four swarms (pokecrystal data/wild/swarm_grass.asm and fish.asm), with Crystal's share of the
// encounters: Dunsparce has 40% of Dark Cave's grass slots, Yanma 30% of Route 35's; Qwilfish and Remoraid about half
// of a rod's catches on Route 32 and Route 44. Crystal's phone-call hints aren't ported: the Center NPC names them.
static const struct KjhSwarm sJohtoSwarms[] =
{
    {SPECIES_DUNSPARCE, MAP_JOHTO_DARK_CAVE_VIOLET_ENTRANCE, 40, KJH_SWARM_LAND},
    {SPECIES_YANMA,     MAP_JOHTO_ROUTE_35,                  30, KJH_SWARM_LAND},
    {SPECIES_QWILFISH,  MAP_JOHTO_ROUTE_32,                  50, KJH_SWARM_FISHING},
    {SPECIES_REMORAID,  MAP_JOHTO_ROUTE_44,                  50, KJH_SWARM_FISHING},
};

// Hoenn's: Emerald's five mass outbreaks (pokeemerald's sPokeOutbreakSpeciesList in src/tv.c, each at the 50% that
// TryStartRandomMassOutbreak gives them), all in the grass. In KJH, Emerald's TV doesn't start an outbreak of its own
// (src/tv.c): the Center reporter names this swarm instead.
static const struct KjhSwarm sHoennSwarms[] =
{
    {SPECIES_SEEDOT,  MAP_ROUTE102, 50, KJH_SWARM_LAND},
    {SPECIES_NUZLEAF, MAP_ROUTE114, 50, KJH_SWARM_LAND},
    {SPECIES_SEEDOT,  MAP_ROUTE117, 50, KJH_SWARM_LAND},
    {SPECIES_SEEDOT,  MAP_ROUTE120, 50, KJH_SWARM_LAND},
    {SPECIES_SKITTY,  MAP_ROUTE116, 50, KJH_SWARM_LAND},
};

static const struct { const struct KjhSwarm *swarms; u8 count; } sRegionSwarms[KJH_SWARM_REGIONS] =
{
    [KJH_SWARM_JOHTO] = {sJohtoSwarms, ARRAY_COUNT(sJohtoSwarms)},
    [KJH_SWARM_HOENN] = {sHoennSwarms, ARRAY_COUNT(sHoennSwarms)},
};

// Hoenn's map groups come first, then Kanto's, then Johto's (data/maps/map_groups.json)
#define FIRST_KANTO_MAP_GROUP MAP_GROUP(MAP_BATTLE_COLOSSEUM_2P_FRLG)
#define FIRST_JOHTO_MAP_GROUP MAP_GROUP(MAP_JOHTO_OLIVINE_POKECENTER_1F)
#define NO_SWARM_REGION       KJH_SWARM_REGIONS // Kanto's swarm is expansion's outbreak record

u32 KJH_SwarmCount(void)
{
    return ARRAY_COUNT(sKantoSwarms);
}

const struct KjhSwarm *KJH_GetSwarm(u32 index)
{
    return &sKantoSwarms[index];
}

void KJH_StartSwarm(u32 index)
{
    struct MassOutbreak outbreak = {0};

    outbreak.species = sKantoSwarms[index].species;
    outbreak.location = sKantoSwarms[index].map;
    outbreak.level = 0; // the route's own level (SetUpMassOutbreakEncounter)
    outbreak.probability = sKantoSwarms[index].chance;
    outbreak.duration = 1;
    StartMassOutbreak(outbreak); // moves stay MOVE_NONE: the Pokemon keeps its level's moves
}

u32 KJH_RegionSwarmCount(u32 region)
{
    return region < KJH_SWARM_REGIONS ? sRegionSwarms[region].count : 0;
}

const struct KjhSwarm *KJH_GetRegionSwarm(u32 region, u32 index)
{
    return &sRegionSwarms[region].swarms[index];
}

void KJH_StartRegionSwarm(u32 region, u32 index)
{
    const struct KjhSwarm *swarm = KJH_GetRegionSwarm(region, index);

    gSaveBlock3Ptr->kjhSwarms[region] = (struct KjhRegionSwarm) {
        .species = swarm->species,
        .map = swarm->map,
        .method = swarm->method,
        .chance = swarm->chance,
    };
}

// Each new day (DoDailyEvents) and when the clock starts: one swarm for the day in each region reached
void KJH_StartDailySwarm(void)
{
    KJH_StartSwarm(Random() % ARRAY_COUNT(sKantoSwarms));
    for (u32 region = 0; region < KJH_SWARM_REGIONS; region++)
    {
        gSaveBlock3Ptr->kjhSwarms[region] = (struct KjhRegionSwarm) {0};
        if (FlagGet(region == KJH_SWARM_JOHTO ? FLAG_KJH_JOHTO_ARRIVED : KJH_HOENN_REACHED_FLAG))
            KJH_StartRegionSwarm(region, Random() % sRegionSwarms[region].count);
    }
}

// The swarm record of the region the player stands in: Johto's or Hoenn's, NO_SWARM_REGION in Kanto
static u32 SwarmRegionHere(void)
{
    if (gSaveBlock1Ptr->location.mapGroup >= FIRST_JOHTO_MAP_GROUP)
        return KJH_SWARM_JOHTO;
    if (gSaveBlock1Ptr->location.mapGroup < FIRST_KANTO_MAP_GROUP)
        return KJH_SWARM_HOENN;
    return NO_SWARM_REGION;
}

enum Species KJH_RegionSwarmSpecies(enum Species species, enum WildPokemonArea area)
{
    u32 region = SwarmRegionHere();
    const struct KjhRegionSwarm *swarm;
    u32 method = area == WILD_AREA_FISHING ? KJH_SWARM_FISHING : KJH_SWARM_LAND;
    u32 here = gSaveBlock1Ptr->location.mapNum | (gSaveBlock1Ptr->location.mapGroup << 8); // a MAP_* value

    if (region == NO_SWARM_REGION) return species;
    swarm = &gSaveBlock3Ptr->kjhSwarms[region];
    if (swarm->species == SPECIES_NONE || swarm->map != here || swarm->method != method) return species;
    if (area != WILD_AREA_LAND && area != WILD_AREA_FISHING) return species;
    // Outcome 0 is the swarm, so a test that doesn't set RNG_KJH_SWARM (its default is the last outcome) never sees it
    if (RandomWeighted(RNG_KJH_SWARM, swarm->chance, 100 - swarm->chance) != 0) return species;
    return swarm->species;
}

static void BufferSwarm(u32 species, u32 mapGroup, u32 mapNum)
{
    const struct MapHeader *map = Overworld_GetMapHeaderByGroupAndId(mapGroup, mapNum);

    StringCopy(gStringVar1, GetSpeciesName(species));
    GetMapName(gStringVar2, map->regionMapSectionId, 0);
}

u16 KJH_BufferTodaysSwarm(void)
{
    u32 region = SwarmRegionHere();

    if (region != NO_SWARM_REGION)
    {
        const struct KjhRegionSwarm *swarm = &gSaveBlock3Ptr->kjhSwarms[region];

        if (swarm->species == SPECIES_NONE) return FALSE;
        BufferSwarm(swarm->species, MAP_GROUP(swarm->map), MAP_NUM(swarm->map));
        return TRUE;
    }

    if (!IsMassOutbreakActive()) return FALSE;
    BufferSwarm(gSaveBlock1Ptr->outbreakPokemonSpecies, gSaveBlock1Ptr->outbreakLocationMapGroup,
                gSaveBlock1Ptr->outbreakLocationMapNum);
    return TRUE;
}

u8 KJH_GetRouteWildLevel(void)
{
    u32 headerId = GetCurrentMapWildMonHeaderId();
    const struct WildPokemonInfo *land;

    if (headerId == HEADER_NONE)
        return MIN_LEVEL;
    land = gWildMonHeaders[headerId].encounterTypes[GetTimeOfDayForEncounters(headerId, WILD_AREA_LAND)].landMonsInfo;
    if (land == NULL)
        return MIN_LEVEL;
    return ChooseWildMonLevel(land->wildPokemon, ChooseWildMonIndex_Land(), WILD_AREA_LAND);
}
