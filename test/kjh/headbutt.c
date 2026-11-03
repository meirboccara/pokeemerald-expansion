// KJH: headbutt trees (CF-8, src/kjh_headbutt.c).
#include "global.h"
#include "event_data.h"
#include "kjh_headbutt.h"
#include "pokemon.h"
#include "pokedex.h"
#include "random.h"
#include "wild_encounter.h"
#include "test/overworld_script.h"
#include "test/test.h"
#include "constants/map_groups.h"

#define TREE_SLOTS 6
#define GRASS_SLOTS 12

static void GoTo(u16 map)
{
    gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(map);
    gSaveBlock1Ptr->location.mapNum = MAP_NUM(map);
}

TEST("KJH: from the Cascade Badge, the first Pokemon that could learn Headbutt can headbutt")
{
    ASSUME(!KJH_CouldLearnMove(SPECIES_MAGIKARP, MOVE_HEADBUTT));
    ASSUME(KJH_CouldLearnMove(SPECIES_TAUROS, MOVE_HEADBUTT));
    ZeroPlayerPartyMons();
    RUN_OVERWORLD_SCRIPT(
        givemon SPECIES_MAGIKARP, 10;
        givemon SPECIES_TAUROS, 10;
    );
    FlagClear(FLAG_BADGE02_GET);
    EXPECT_EQ(KJH_GetHeadbuttPartySlot(), PARTY_SIZE);
    FlagSet(FLAG_BADGE02_GET);
    EXPECT_EQ(KJH_GetHeadbuttPartySlot(), 1);

    ZeroPlayerPartyMons();
    RUN_OVERWORLD_SCRIPT(givemon SPECIES_MAGIKARP, 10;);
    EXPECT_EQ(KJH_GetHeadbuttPartySlot(), PARTY_SIZE);
    FlagClear(FLAG_BADGE02_GET);
}

TEST("KJH: Route 2's trees are in its wild encounter data, a route without trees has none")
{
    GoTo(MAP_ROUTE3);
    EXPECT(KJH_GetHeadbuttTable() == NULL);
    EXPECT(!KJH_TryCreateHeadbuttMon());
    GoTo(MAP_ROUTE2);
    EXPECT(KJH_GetHeadbuttTable() != NULL);
}

TEST("KJH: a headbutt on Route 2 shakes out one of its tree Pokemon, at its level and chance")
{
    const struct WildPokemonInfo *tree;
    u32 battles = 0;

    GoTo(MAP_ROUTE2);
    tree = KJH_GetHeadbuttTable();
    SeedRng(7);
    for (u32 i = 0; i < 200; i++)
    {
        enum Species species;
        u32 level, slot;

        if (!KJH_TryCreateHeadbuttMon())
            continue;
        battles++;
        species = GetMonData(&gParties[B_TRAINER_OPPONENT_A][0], MON_DATA_SPECIES);
        level = GetMonData(&gParties[B_TRAINER_OPPONENT_A][0], MON_DATA_LEVEL);
        for (slot = 0; slot < TREE_SLOTS && tree->wildPokemon[slot].species != species; slot++)
            ;
        EXPECT_LT(slot, TREE_SLOTS);
        EXPECT_GE(level, tree->wildPokemon[slot].minLevel);
        EXPECT_LE(level, tree->wildPokemon[slot].maxLevel);
    }
    EXPECT_GT(battles, 2 * tree->encounterRate - 30); // 200 tries at 50%: about 100
    EXPECT_LT(battles, 2 * tree->encounterRate + 30);
}

TEST("KJH: every Kanto route with HeartGold's headbutt trees has a table of Gen 1-3 Pokemon at its grass levels")
{
    // kjh_tools/headbutt_trees.py; FireRed's Route 3 and Route 21 have no big tree next to a path, so no table
    static const u16 sRoutes[] =
    {
        MAP_ROUTE1, MAP_ROUTE2, MAP_ROUTE5, MAP_ROUTE6, MAP_ROUTE7, MAP_ROUTE8, MAP_ROUTE11, MAP_ROUTE12,
        MAP_ROUTE13, MAP_ROUTE14, MAP_ROUTE15, MAP_ROUTE16, MAP_ROUTE18, MAP_ROUTE22, MAP_ROUTE25,
    };

    for (u32 i = 0; i < ARRAY_COUNT(sRoutes); i++)
    {
        const struct WildPokemonInfo *tree;
        u32 headerId;

        GoTo(sRoutes[i]);
        tree = KJH_GetHeadbuttTable();
        EXPECT(tree != NULL);
        if (tree == NULL)
            continue;
        headerId = GetCurrentMapWildMonHeaderId();
        const struct WildPokemon *grass = gWildMonHeaders[headerId].encounterTypes[TIME_OF_DAY_DEFAULT].landMonsInfo->wildPokemon;
        u32 lo = MAX_LEVEL, hi = 0;
        for (u32 slot = 0; slot < GRASS_SLOTS; slot++)
        {
            lo = min(lo, grass[slot].minLevel);
            hi = max(hi, grass[slot].maxLevel);
        }
        for (u32 slot = 0; slot < TREE_SLOTS; slot++)
        {
            EXPECT_LE(SpeciesToNationalPokedexNum(tree->wildPokemon[slot].species), NATIONAL_DEX_DEOXYS);
            EXPECT_EQ(tree->wildPokemon[slot].minLevel, lo);
            EXPECT_EQ(tree->wildPokemon[slot].maxLevel, hi);
        }
    }
    GoTo(MAP_ROUTE3);
    EXPECT(KJH_GetHeadbuttTable() == NULL);
}
