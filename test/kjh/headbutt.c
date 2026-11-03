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

// CF-10: Johto's trees follow Crystal (engine/events/treemons.asm). Each tree scores against the player's trainer ID:
// rare (the rare table, 80%), good (the common table, 50%) or poor (the common table, 10%).
static void SetTrainerId(u32 id)
{
    gSaveBlock2Ptr->playerTrainerId[0] = id & 0xFF;
    gSaveBlock2Ptr->playerTrainerId[1] = (id >> 8) & 0xFF;
}

TEST("KJH: a Johto tree scores as in Crystal: rare, good or poor for the player's trainer ID")
{
    // tree (0, 0): coordinates + 4 (Crystal's map border), ((4 * 4 + 4 + 4) / 5) % 10 = 4
    EXPECT_EQ(KJH_HeadbuttTreeScore(0, 0, 4), KJH_TREE_RARE);
    EXPECT_EQ(KJH_HeadbuttTreeScore(0, 0, 14), KJH_TREE_RARE);  // the ID's last digit counts
    EXPECT_EQ(KJH_HeadbuttTreeScore(0, 0, 3), KJH_TREE_GOOD);   // 4 - 3 = 1
    EXPECT_EQ(KJH_HeadbuttTreeScore(0, 0, 0), KJH_TREE_GOOD);   // 4
    EXPECT_EQ(KJH_HeadbuttTreeScore(0, 0, 9), KJH_TREE_POOR);   // 4 - 9 + 10 = 5
    EXPECT_EQ(KJH_HeadbuttTreeScore(0, 0, 5), KJH_TREE_POOR);   // 9
    // tree (11, 0): (15 * 4 + 15 + 4) / 5 = 15, % 10 = 5
    EXPECT_EQ(KJH_HeadbuttTreeScore(11, 0, 5), KJH_TREE_RARE);
    EXPECT_EQ(KJH_HeadbuttTreeScore(11, 0, 1), KJH_TREE_GOOD);
}

static bool32 InTable(const struct WildPokemonInfo *table, enum Species species)
{
    for (u32 slot = 0; slot < TREE_SLOTS; slot++)
    {
        if (table->wildPokemon[slot].species == species)
            return TRUE;
    }
    return FALSE;
}

static u32 Headbutts(u32 trainerId, const struct WildPokemonInfo *table, u32 *otherSlots)
{
    u32 battles = 0;

    *otherSlots = 0;
    SetTrainerId(trainerId);
    SeedRng(11);
    for (u32 i = 0; i < 200; i++)
    {
        if (!KJH_TryCreateHeadbuttMonAtTree(0, 0))
            continue;
        battles++;
        EXPECT(InTable(table, GetMonData(&gParties[B_TRAINER_OPPONENT_A][0], MON_DATA_SPECIES)));
        if (GetMonData(&gParties[B_TRAINER_OPPONENT_A][0], MON_DATA_SPECIES) != table->wildPokemon[0].species)
            (*otherSlots)++;
        // LV-18: Route 29's zone, 5-8 (Crystal's trees were all at 10)
        EXPECT_GE(GetMonData(&gParties[B_TRAINER_OPPONENT_A][0], MON_DATA_LEVEL), 5);
        EXPECT_LE(GetMonData(&gParties[B_TRAINER_OPPONENT_A][0], MON_DATA_LEVEL), 8);
    }
    return battles;
}

TEST("KJH: on Route 29 a rare tree gives the rare table 80% of the time, a good one the common table 50%, a poor one 10%")
{
    const struct WildPokemonInfo *common, *rare;
    u32 battles, otherSlots = 0;

    GoTo(MAP_JOHTO_ROUTE_29);
    common = KJH_GetHeadbuttTable();
    rare = KJH_GetHeadbuttRareTable();
    EXPECT(common != NULL && rare != NULL);
    if (common == NULL || rare == NULL)
        return;
    EXPECT(InTable(rare, SPECIES_PINECO));     // Crystal's TreeMonSet_Route
    EXPECT(!InTable(common, SPECIES_PINECO));

    battles = Headbutts(4, rare, &otherSlots); // tree (0, 0) is rare for ID ...4
    EXPECT_GT(battles, 130);
    EXPECT_LT(battles, 190);
    EXPECT_GT(otherSlots, battles / 4);        // half the battles are slot 0 (50%), the rest the other slots
    EXPECT_LT(otherSlots, 3 * battles / 4);
    battles = Headbutts(3, common, &otherSlots); // good
    EXPECT_GT(battles, 70);
    EXPECT_LT(battles, 130);
    battles = Headbutts(9, common, &otherSlots); // poor
    EXPECT_GT(battles, 5);
    EXPECT_LT(battles, 40);
}

TEST("KJH: Johto's maps with Crystal's tree Pokemon have both tables; Kanto's routes keep one")
{
    static const u16 sJohto[] =
    {
        MAP_JOHTO_ROUTE_29, MAP_JOHTO_ROUTE_44, MAP_JOHTO_AZALEA_TOWN, MAP_JOHTO_ILEX_FOREST, MAP_JOHTO_LAKE_OF_RAGE,
        MAP_JOHTO_ROUTE_26,
    };

    for (u32 i = 0; i < ARRAY_COUNT(sJohto); i++)
    {
        GoTo(sJohto[i]);
        EXPECT(KJH_GetHeadbuttTable() != NULL);
        EXPECT(KJH_GetHeadbuttRareTable() != NULL);
    }
    GoTo(MAP_JOHTO_NEW_BARK_TOWN);             // TREEMON_SET_NONE
    EXPECT(KJH_GetHeadbuttTable() == NULL);
    GoTo(MAP_ROUTE2);
    EXPECT(KJH_GetHeadbuttTable() != NULL);
    EXPECT(KJH_GetHeadbuttRareTable() == NULL);
}
