// KJH: the daily swarm (CF-5, src/kjh_swarms.c), on top of expansion's mass outbreak record.
#include "global.h"
#include "event_data.h"
#include "fake_rtc.h"
#include "clock.h"
#include "kjh_clock.h"
#include "kjh_swarms.h"
#include "mass_outbreak.h"
#include "pokedex.h"
#include "pokemon.h"
#include "wild_encounter.h"
#include "test/overworld_script.h"
#include "test/test.h"
#include "constants/map_groups.h"

#define LAND_SLOTS 12 // a Gen 3 grass table (ChooseWildMonIndex_Land)

static void GoTo(u16 map)
{
    gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(map);
    gSaveBlock1Ptr->location.mapNum = MAP_NUM(map);
}

static const struct WildPokemonInfo *Grass(u16 map)
{
    u32 headerId;

    GoTo(map);
    headerId = GetCurrentMapWildMonHeaderId();
    if (headerId == HEADER_NONE)
        return NULL;
    return gWildMonHeaders[headerId].encounterTypes[TIME_OF_DAY_DEFAULT].landMonsInfo;
}

static u32 FindSwarm(u16 species)
{
    u32 i;
    for (i = 0; i < KJH_SwarmCount(); i++)
    {
        if (KJH_GetSwarm(i)->species == species)
            break;
    }
    return i;
}

static bool32 IsTodaysSwarmInTable(void)
{
    for (u32 i = 0; i < KJH_SwarmCount(); i++)
    {
        const struct KjhSwarm *swarm = KJH_GetSwarm(i);
        if (swarm->species == gSaveBlock1Ptr->outbreakPokemonSpecies
         && MAP_GROUP(swarm->map) == gSaveBlock1Ptr->outbreakLocationMapGroup
         && MAP_NUM(swarm->map) == gSaveBlock1Ptr->outbreakLocationMapNum
         && swarm->chance == gSaveBlock1Ptr->outbreakPokemonProbability)
            return TRUE;
    }
    return FALSE;
}

TEST("KJH: every Kanto swarm is a Gen 1-3 species on a route with grass")
{
    for (u32 i = 0; i < KJH_SwarmCount(); i++)
    {
        const struct KjhSwarm *swarm = KJH_GetSwarm(i);
        EXPECT_LE(SpeciesToNationalPokedexNum(swarm->species), NATIONAL_DEX_DEOXYS);
        EXPECT(Grass(swarm->map) != NULL);
        EXPECT_GT(swarm->chance, 0);
        EXPECT_LE(swarm->chance, 100);
    }
}

TEST("KJH: the clock starts a swarm, and each new day picks one for that day")
{
    ZeroMassOutbreak();
    KJH_StartClock();
    EXPECT(IsMassOutbreakActive());
    EXPECT(IsTodaysSwarmInTable());
    EXPECT_EQ(gSaveBlock1Ptr->outbreakDaysLeft, 1);
    EXPECT_EQ(gSaveBlock1Ptr->outbreakPokemonLevel, 0); // the route's level, at the encounter

    for (u32 day = 0; day < 5; day++)
    {
        FakeRtc_AdvanceTimeBy(1, 0, 0, 0);
        DoTimeBasedEvents();
        EXPECT(IsMassOutbreakActive());
        EXPECT(IsTodaysSwarmInTable());
        EXPECT_EQ(gSaveBlock1Ptr->outbreakDaysLeft, 1);
    }
}

TEST("KJH: a swarm Pokemon has the route's wild level and its own moves")
{
    u32 dratini = FindSwarm(SPECIES_DRATINI);
    const struct WildPokemonInfo *grass;
    u32 minLevel = MAX_LEVEL, maxLevel = 0, level;

    ASSUME(dratini < KJH_SwarmCount());
    grass = Grass(KJH_GetSwarm(dratini)->map);
    for (u32 slot = 0; slot < LAND_SLOTS; slot++)
    {
        minLevel = min(minLevel, grass->wildPokemon[slot].minLevel);
        maxLevel = max(maxLevel, grass->wildPokemon[slot].maxLevel);
    }
    KJH_StartSwarm(dratini);
    for (u32 i = 0; i < 20; i++)
    {
        EXPECT(SetUpMassOutbreakEncounter(0));
        EXPECT_EQ(GetMonData(&gParties[B_TRAINER_OPPONENT_A][0], MON_DATA_SPECIES), SPECIES_DRATINI);
        level = GetMonData(&gParties[B_TRAINER_OPPONENT_A][0], MON_DATA_LEVEL);
        EXPECT_GE(level, minLevel);
        EXPECT_LE(level, maxLevel);
        EXPECT_NE(GetMonData(&gParties[B_TRAINER_OPPONENT_A][0], MON_DATA_MOVE1), MOVE_NONE);
    }
}

TEST("KJH: a swarm shows up at its chance on its own route, never elsewhere")
{
    // RNG_NONE rolls always come out as 0 in function tests, so the chance is read, then forced to 100%
    u32 sentret = FindSwarm(SPECIES_SENTRET);

    ASSUME(sentret < KJH_SwarmCount());
    ASSUME(KJH_GetSwarm(sentret)->map != MAP_ROUTE2);
    KJH_StartSwarm(sentret);
    EXPECT_EQ(gSaveBlock1Ptr->outbreakPokemonProbability, KJH_GetSwarm(sentret)->chance);
    gSaveBlock1Ptr->outbreakPokemonProbability = 100;
    GoTo(KJH_GetSwarm(sentret)->map);
    EXPECT(DoMassOutbreakEncounterTest());
    GoTo(MAP_ROUTE2);
    EXPECT(!DoMassOutbreakEncounterTest());
    gSaveBlock1Ptr->outbreakDaysLeft = 0; // over
    GoTo(KJH_GetSwarm(sentret)->map);
    EXPECT(!DoMassOutbreakEncounterTest());
}

TEST("KJH: a Repel keeps a swarm Pokemon away like any wild Pokemon of its level")
{
    u32 sentret = FindSwarm(SPECIES_SENTRET);

    ASSUME(sentret < KJH_SwarmCount());
    ZeroPlayerPartyMons();
    RUN_OVERWORLD_SCRIPT(givemon SPECIES_WOBBUFFET, 50;);
    KJH_StartSwarm(sentret);
    GoTo(KJH_GetSwarm(sentret)->map); // Route 1: levels 2-5
    VarSet(VAR_REPEL_STEP_COUNT, 100);
    EXPECT(!SetUpMassOutbreakEncounter(WILD_CHECK_REPEL));
    VarSet(VAR_REPEL_STEP_COUNT, 0);
    EXPECT(SetUpMassOutbreakEncounter(WILD_CHECK_REPEL));
}
