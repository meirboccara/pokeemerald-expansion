// KJH: the daily swarm (CF-5, include/kjh_swarms.h).
#include "global.h"
#include "event_data.h"
#include "kjh_swarms.h"
#include "mass_outbreak.h"
#include "overworld.h"
#include "random.h"
#include "region_map.h"
#include "string_util.h"
#include "wild_encounter.h"
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

// Each new day (DoDailyEvents) and when the clock starts: one swarm for the day
void KJH_StartDailySwarm(void)
{
    KJH_StartSwarm(Random() % ARRAY_COUNT(sKantoSwarms));
}

u16 KJH_BufferTodaysSwarm(void)
{
    const struct MapHeader *map;

    if (!IsMassOutbreakActive())
        return FALSE;
    StringCopy(gStringVar1, GetSpeciesName(gSaveBlock1Ptr->outbreakPokemonSpecies));
    map = Overworld_GetMapHeaderByGroupAndId(gSaveBlock1Ptr->outbreakLocationMapGroup,
                                             gSaveBlock1Ptr->outbreakLocationMapNum);
    GetMapName(gStringVar2, map->regionMapSectionId, 0);
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
