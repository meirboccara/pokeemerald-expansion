// KJH: Johto's and Hoenn's daily swarms (CF-6, src/kjh_swarms.c): Crystal's swarms, in grass and by fishing; Emerald's
// five outbreaks.
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

static u32 FindRegionSwarm(u32 region, enum Species species, u32 map)
{
    u32 i;

    for (i = 0; i < KJH_RegionSwarmCount(region); i++)
    {
        const struct KjhSwarm *swarm = KJH_GetRegionSwarm(region, i);

        if (swarm->species == species && (map == MAP_UNDEFINED || swarm->map == map)) break;
    }

    return i;
}

static u32 FindJohtoSwarm(enum Species species)
{
    return FindRegionSwarm(KJH_SWARM_JOHTO, species, MAP_UNDEFINED);
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

TEST("KJH: Hoenn's swarms are Emerald's five outbreaks, in the grass at Emerald's 50%")
{
    static const struct { u16 species; u16 map; } sEmerald[] =
    {
        {SPECIES_SEEDOT, MAP_ROUTE102}, {SPECIES_NUZLEAF, MAP_ROUTE114}, {SPECIES_SEEDOT, MAP_ROUTE117},
        {SPECIES_SEEDOT, MAP_ROUTE120}, {SPECIES_SKITTY, MAP_ROUTE116},
    };

    EXPECT_EQ(KJH_RegionSwarmCount(KJH_SWARM_HOENN), 5);
    for (u32 i = 0; i < ARRAY_COUNT(sEmerald); i++)
    {
        u32 index = FindRegionSwarm(KJH_SWARM_HOENN, sEmerald[i].species, sEmerald[i].map);

        EXPECT_LT(index, KJH_RegionSwarmCount(KJH_SWARM_HOENN));
        if (index >= KJH_RegionSwarmCount(KJH_SWARM_HOENN))
            continue;
        EXPECT_EQ(KJH_GetRegionSwarm(KJH_SWARM_HOENN, index)->method, KJH_SWARM_LAND);
        EXPECT_EQ(KJH_GetRegionSwarm(KJH_SWARM_HOENN, index)->chance, 50);
    }
}

TEST("KJH: Hoenn has no swarm until the player reaches it; then Kanto, Johto and Hoenn each have one the same day")
{
    FlagSet(FLAG_KJH_JOHTO_ARRIVED);
    FlagClear(KJH_HOENN_REACHED_FLAG);
    KJH_StartDailySwarm();
    EXPECT_NE(gSaveBlock3Ptr->kjhSwarms[KJH_SWARM_JOHTO].species, SPECIES_NONE);
    EXPECT_EQ(gSaveBlock3Ptr->kjhSwarms[KJH_SWARM_HOENN].species, SPECIES_NONE);

    FlagSet(KJH_HOENN_REACHED_FLAG);
    KJH_StartDailySwarm();
    EXPECT(IsMassOutbreakActive());
    EXPECT_NE(gSaveBlock3Ptr->kjhSwarms[KJH_SWARM_JOHTO].species, SPECIES_NONE);
    EXPECT_NE(gSaveBlock3Ptr->kjhSwarms[KJH_SWARM_HOENN].species, SPECIES_NONE);

    FlagClear(KJH_HOENN_REACHED_FLAG); // the next day, Hoenn not reached: its swarm is gone
    KJH_StartDailySwarm();
    EXPECT_EQ(gSaveBlock3Ptr->kjhSwarms[KJH_SWARM_HOENN].species, SPECIES_NONE);
    FlagClear(FLAG_KJH_JOHTO_ARRIVED);
}

TEST("KJH: the same day, a Johto swarm and a Hoenn swarm each show up on their own map")
{
    KJH_StartRegionSwarm(KJH_SWARM_JOHTO, FindJohtoSwarm(SPECIES_YANMA));
    KJH_StartRegionSwarm(KJH_SWARM_HOENN, FindRegionSwarm(KJH_SWARM_HOENN, SPECIES_SKITTY, MAP_ROUTE116));
    SET_RNG(RNG_KJH_SWARM, 0); // outcome 0: the swarm

    StandOn(MAP_JOHTO_ROUTE_35);
    EXPECT_EQ(KJH_RegionSwarmSpecies(SPECIES_PIDGEY, WILD_AREA_LAND), SPECIES_YANMA);
    StandOn(MAP_ROUTE116);
    EXPECT_EQ(KJH_RegionSwarmSpecies(SPECIES_ZIGZAGOON, WILD_AREA_LAND), SPECIES_SKITTY);
    EXPECT_EQ(KJH_RegionSwarmSpecies(SPECIES_TENTACOOL, WILD_AREA_FISHING), SPECIES_TENTACOOL); // Skitty's is in the grass
    StandOn(MAP_ROUTE117);
    EXPECT_EQ(KJH_RegionSwarmSpecies(SPECIES_ZIGZAGOON, WILD_AREA_LAND), SPECIES_ZIGZAGOON);
    StandOn(MAP_ROUTE1); // Kanto's swarm is expansion's outbreak, not these
    EXPECT_EQ(KJH_RegionSwarmSpecies(SPECIES_PIDGEY, WILD_AREA_LAND), SPECIES_PIDGEY);

    gSaveBlock3Ptr->kjhSwarms[KJH_SWARM_JOHTO].species = SPECIES_NONE;
    gSaveBlock3Ptr->kjhSwarms[KJH_SWARM_HOENN].species = SPECIES_NONE;
}

TEST("KJH: a Hoenn Pokemon Center's reporter names Hoenn's swarm")
{
    KJH_StartSwarm(0); // Kanto: Sentret on Route 1
    KJH_StartRegionSwarm(KJH_SWARM_JOHTO, FindJohtoSwarm(SPECIES_REMORAID));
    KJH_StartRegionSwarm(KJH_SWARM_HOENN, FindRegionSwarm(KJH_SWARM_HOENN, SPECIES_NUZLEAF, MAP_ROUTE114));
    StandOn(MAP_SLATEPORT_CITY_POKEMON_CENTER_1F);
    EXPECT(KJH_BufferTodaysSwarm());
    EXPECT_EQ(StringCompare(gStringVar1, GetSpeciesName(SPECIES_NUZLEAF)), 0);

    gSaveBlock3Ptr->kjhSwarms[KJH_SWARM_HOENN].species = SPECIES_NONE;
    EXPECT(!KJH_BufferTodaysSwarm());
    gSaveBlock3Ptr->kjhSwarms[KJH_SWARM_JOHTO].species = SPECIES_NONE;
}
