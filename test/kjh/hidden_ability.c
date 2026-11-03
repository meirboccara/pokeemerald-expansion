// KJH: Hidden Abilities (ENG-7, src/kjh_hidden_ability.c), after docs/HIDDEN_ABILITIES.md in the KJH repo.
#include "global.h"
#include "event_data.h"
#include "kjh_hidden_ability.h"
#include "pokemon.h"
#include "random.h"
#include "script.h"
#include "test/overworld_script.h"
#include "test/test.h"

TEST("KJH: a species' Hidden Ability is expansion's third ability, when it's not one of the first two")
{
    ASSUME(GetSpeciesAbility(SPECIES_CHARMANDER, 2) == ABILITY_SOLAR_POWER);
    EXPECT_EQ(KJH_HiddenAbility(SPECIES_CHARMANDER), ABILITY_SOLAR_POWER);
    EXPECT_EQ(KJH_HiddenAbility(SPECIES_UNOWN), ABILITY_NONE); // Levitate only
}

TEST("KJH: the abilities to pick from are the first, the second if any, and the Hidden one if any")
{
    u8 nums[KJH_MAX_ABILITY_CHOICES];

    ASSUME(GetSpeciesAbility(SPECIES_CHARMANDER, 1) == ABILITY_NONE);
    EXPECT_EQ(KJH_AbilityChoices(SPECIES_CHARMANDER, nums), 2);
    EXPECT_EQ(nums[0], 0);
    EXPECT_EQ(nums[1], KJH_ABILITY_NUM_HIDDEN);

    ASSUME(GetSpeciesAbility(SPECIES_PIDGEY, 1) != ABILITY_NONE);
    EXPECT_EQ(KJH_AbilityChoices(SPECIES_PIDGEY, nums), 3);
    EXPECT_EQ(nums[1], 1);
    EXPECT_EQ(nums[2], KJH_ABILITY_NUM_HIDDEN);

    EXPECT_EQ(KJH_AbilityChoices(SPECIES_UNOWN, nums), 1);
}

TEST("KJH: a wild Pokemon that wins the 1 in 20 roll has its Hidden Ability")
{
    struct Pokemon mon;

    CreateMon(&mon, SPECIES_CHARMANDER, 5, 0, OTID_STRUCT_PLAYER_ID);
    KJH_RollWildHiddenAbility(&mon);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_ABILITY_NUM), 0);
    SET_RNG(RNG_KJH_HIDDEN_ABILITY, 0); // outcome 0: it has it
    KJH_RollWildHiddenAbility(&mon);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_ABILITY_NUM), KJH_ABILITY_NUM_HIDDEN);
    EXPECT_EQ(GetMonAbility(&mon), ABILITY_SOLAR_POWER);
}

TEST("KJH: a boss's Pokemon uses its Hidden Ability, unless it does nothing for a trainer")
{
    ASSUME(KJH_HiddenAbility(SPECIES_ONIX) == ABILITY_WEAK_ARMOR);
    EXPECT_EQ(KJH_BossAbilityNum(SPECIES_ONIX, 0), KJH_ABILITY_NUM_HIDDEN);
    ASSUME(KJH_HiddenAbility(SPECIES_CATERPIE) == ABILITY_RUN_AWAY);
    EXPECT_EQ(KJH_BossAbilityNum(SPECIES_CATERPIE, 0), 0);
    EXPECT_EQ(KJH_BossAbilityNum(SPECIES_UNOWN, 0), 0);
}

TEST("KJH: Prof. Oak switches abilities from the player's 4th badge")
{
    for (u32 i = 0; i < KJH_ABILITY_SWITCH_BADGES - 1; i++)
    {
        FlagSet(FLAG_BADGE01_GET + i);
    }
    RUN_OVERWORLD_SCRIPT(callnative KJH_ScriptIsAbilitySwitchUnlocked, requests_effects=1;);
    EXPECT_EQ(gSpecialVar_Result, FALSE);
    FlagSet(FLAG_BADGE01_GET + KJH_ABILITY_SWITCH_BADGES - 1);
    RUN_OVERWORLD_SCRIPT(callnative KJH_ScriptIsAbilitySwitchUnlocked, requests_effects=1;);
    EXPECT_EQ(gSpecialVar_Result, TRUE);
    for (u32 i = 0; i < KJH_ABILITY_SWITCH_BADGES; i++)
    {
        FlagClear(FLAG_BADGE01_GET + i);
    }
}
