// KJH: expansion's DexNav in the FireRed build (ENG-8, src/dexnav.c): on, with FireRed's free flags and variables,
// and its Pokemon follow KJH's rules: the map's own (zone) level without DexNav's chain bonus, and ENG-7's Hidden
// Ability roll.
#include "global.h"
#include "dexnav.h"
#include "event_data.h"
#include "kjh_hidden_ability.h"
#include "pokemon.h"
#include "random.h"
#include "test/test.h"
#include "constants/map_groups.h"

TEST("KJH dexnav: DexNav is on and uses FireRed's free flags and variables")
{
    EXPECT(DEXNAV_ENABLED);
    EXPECT_EQ(DN_FLAG_SEARCHING, 0x0CA);
    EXPECT_EQ(DN_FLAG_DETECTOR_MODE, 0x0CB);
    EXPECT_EQ(DN_FLAG_DEXNAV_GET, 0x0CC);
    EXPECT_EQ(DN_VAR_SPECIES, 0x40C8);
    EXPECT_EQ(DN_VAR_STEP_COUNTER, 0x40C9);
    EXPECT(!USE_DEXNAV_SEARCH_LEVELS); // no byte per species in SaveBlock3
}

TEST("KJH dexnav: a DexNav Pokemon has its map's own level, whatever the chain")
{
    gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(MAP_ROUTE1);
    gSaveBlock1Ptr->location.mapNum = MAP_NUM(MAP_ROUTE1);
    gSaveBlock3Ptr->dexNavChain = 100; // expansion: +20 levels, and 4% of the time +10 more
    for (u32 i = 0; i < 50; i++)
    {
        u32 level = DexNavTryGenerateMonLevel(SPECIES_PIDGEY, ENCOUNTER_TYPE_LAND); // Route 1's Pidgey: 5 to 8
        EXPECT_GE(level, 5);
        EXPECT_LE(level, 8);
    }
    EXPECT_EQ(DexNavTryGenerateMonLevel(SPECIES_MEWTWO, ENCOUNTER_TYPE_LAND), MON_LEVEL_NONEXISTENT);
    gSaveBlock3Ptr->dexNavChain = 0;
}

TEST("KJH dexnav: a DexNav Pokemon gets its Hidden Ability by KJH's wild roll, not DexNav's pick")
{
    enum Move moves[MAX_MON_MOVES] = {MOVE_TACKLE};
    struct Pokemon *mon = &gParties[B_TRAINER_OPPONENT_A][0];

    ASSUME(KJH_HiddenAbility(SPECIES_PIDGEY) != ABILITY_NONE);
    SET_RNG(RNG_KJH_HIDDEN_ABILITY, 0); // outcome 0: the 1 in 20
    CreateDexNavWildMon(SPECIES_PIDGEY, 0, 5, 0, ITEM_NONE, moves);
    EXPECT_EQ(GetMonData(mon, MON_DATA_ABILITY_NUM), KJH_ABILITY_NUM_HIDDEN);
}

TEST("KJH dexnav: without the roll, a DexNav Pokemon has one of its usual abilities")
{
    enum Move moves[MAX_MON_MOVES] = {MOVE_TACKLE};
    struct Pokemon *mon = &gParties[B_TRAINER_OPPONENT_A][0];

    CreateDexNavWildMon(SPECIES_PIDGEY, 0, 5, 2, ITEM_NONE, moves); // DexNav asking for 2 doesn't give it
    EXPECT_NE(GetMonData(mon, MON_DATA_ABILITY_NUM), KJH_ABILITY_NUM_HIDDEN);
    EXPECT_EQ(GetMonData(mon, MON_DATA_LEVEL), 5);
}
