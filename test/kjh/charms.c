// KJH: the Shiny Charm and the Oval Charm (CF-3). When they are earned (src/kjh_charms.c), and what each does with
// expansion's own rolls: more shiny rolls (ComputePlayerShinyOdds) and a higher egg chance at the Day Care
// (ModifyBreedingScoreForOvalCharm). Tagged randoms are fixed in function tests, so the egg roll's chance is checked
// rather than counted.
#include "global.h"
#include "daycare.h"
#include "event_data.h"
#include "item.h"
#include "kjh_charms.h"
#include "overworld.h"
#include "pokedex.h"
#include "pokemon.h"
#include "random.h"
#include "test/test.h"
#include "constants/game_stat.h"

#define NOT_SHINY_PERSONALITY 0xFFFF0000 // with an OT id of 0: shiny value 0xFFFF, far above SHINY_ODDS
#define SHINY_TRIALS 20000

static void SetCaught(u32 first, u32 last)
{
    for (u32 dexNum = first; dexNum <= last; dexNum++)
        GetSetPokedexFlag(dexNum, FLAG_SET_CAUGHT);
}

TEST("KJH: Oak's Shiny Charm counts the 386 species of Gen 1-3")
{
    EXPECT_EQ(KJH_ShinyCharmSpeciesCount(), 386);
}

TEST("KJH: Oak counts the species still to catch, Gen 4 catches don't count")
{
    SetCaught(NATIONAL_DEX_BULBASAUR, NATIONAL_DEX_MEWTWO);
    SetCaught(NATIONAL_DEX_CHIKORITA, NATIONAL_DEX_DEOXYS);
    SetCaught(NATIONAL_DEX_TURTWIG, NATIONAL_DEX_TURTWIG);
    EXPECT_EQ(KJH_ShinyCharmSpeciesLeft(), 1); // Mew
    SetCaught(NATIONAL_DEX_MEW, NATIONAL_DEX_MEW);
    EXPECT_EQ(KJH_ShinyCharmSpeciesLeft(), 0);
}

TEST("KJH: the Day Care man's Oval Charm waits for a hatched egg")
{
    SetGameStat(GAME_STAT_HATCHED_EGGS, 0);
    EXPECT_EQ(KJH_HasHatchedAnEgg(), FALSE);
    IncrementGameStat(GAME_STAT_HATCHED_EGGS);
    EXPECT_EQ(KJH_HasHatchedAnEgg(), TRUE);
}

static u32 CountShinyRolls(void)
{
    u32 shinies = 0;
    for (u32 seed = 0; seed < SHINY_TRIALS; seed++)
    {
        SeedRng(seed);
        shinies += ComputePlayerShinyOdds(NOT_SHINY_PERSONALITY, 0);
    }
    return shinies;
}

TEST("KJH: with the Shiny Charm, a roll that wasn't shiny can become shiny")
{
    u32 without, with;

    ASSUME(I_SHINY_CHARM_ADDITIONAL_ROLLS > 0);
    RemoveBagItem(ITEM_SHINY_CHARM, 1);
    without = CountShinyRolls();
    AddBagItem(ITEM_SHINY_CHARM, 1);
    with = CountShinyRolls();
    RemoveBagItem(ITEM_SHINY_CHARM, 1);
    EXPECT_EQ(without, 0);
    EXPECT_GT(with, 0); // about SHINY_TRIALS * 2 / 4096 = 10
}

TEST("KJH: with the Oval Charm, the Day Care's egg chance goes up")
{
    // the chance IncrementDaycareSteps rolls every 256 steps: 20 / 50 / 70% by compatibility, 40 / 80 / 88% with it
    RemoveBagItem(ITEM_OVAL_CHARM, 1);
    EXPECT_EQ(ModifyBreedingScoreForOvalCharm(PARENTS_LOW_COMPATIBILITY), 20);
    EXPECT_EQ(ModifyBreedingScoreForOvalCharm(PARENTS_MED_COMPATIBILITY), 50);
    EXPECT_EQ(ModifyBreedingScoreForOvalCharm(PARENTS_MAX_COMPATIBILITY), 70);
    AddBagItem(ITEM_OVAL_CHARM, 1);
    EXPECT_EQ(ModifyBreedingScoreForOvalCharm(PARENTS_LOW_COMPATIBILITY), 40);
    EXPECT_EQ(ModifyBreedingScoreForOvalCharm(PARENTS_MED_COMPATIBILITY), 80);
    EXPECT_EQ(ModifyBreedingScoreForOvalCharm(PARENTS_MAX_COMPATIBILITY), 88);
    EXPECT_EQ(ModifyBreedingScoreForOvalCharm(PARENTS_INCOMPATIBLE), PARENTS_INCOMPATIBLE);
    RemoveBagItem(ITEM_OVAL_CHARM, 1);
}
