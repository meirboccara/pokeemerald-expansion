// KJH: the stat trainer's limits (ENG-7, src/kjh_stat_trainer.c), and its levels-free rules (LV-8)
#include "global.h"
#include "event_data.h"
#include "kjh_bond.h"
#include "kjh_hidden_ability.h"
#include "kjh_stat_trainer.h"
#include "kjh_training.h"
#include "pokemon.h"
#include "script.h"
#include "string_util.h"
#include "test/overworld_script.h"
#include "test/test.h"

TEST("KJH: the stat trainer keeps IVs within 0 to 31")
{
    EXPECT_EQ(KJH_ClampIv(-1), 0);
    EXPECT_EQ(KJH_ClampIv(20), 20);
    EXPECT_EQ(KJH_ClampIv(40), MAX_PER_STAT_IVS);
}

TEST("KJH: the stat trainer keeps an EV within 252, and all of them within 510")
{
    u8 evs[NUM_STATS] = {252, 252, 0, 0, 0, 0};

    EXPECT_EQ(KJH_ClampEv(evs, 2, 10), 6);   // 504 in the other stats: 6 left
    EXPECT_EQ(KJH_ClampEv(evs, 0, 300), MAX_PER_STAT_EVS);
    EXPECT_EQ(KJH_ClampEv(evs, 0, -5), 0);
    EXPECT_EQ(KJH_ClampEv(evs, 0, 100), 100);
}

// LV-8: in the levels-free game, the stat trainer resets Training points for free, sets IVs only from Bond 20 and
// gives the Hidden Ability only from Bond 12 (peak Bonds)
static void CreateBondMon(struct Pokemon *mon, enum Species species, u32 bond)
{
    u32 friendship = KJH_BondToFriendship(bond);

    CreateMon(mon, species, 20, 0, OTID_STRUCT_PRESET(0));
    SetMonData(mon, MON_DATA_FRIENDSHIP, &friendship);
}

TEST("KJH: the stat trainer's full reset puts every placed point back in the bank, for free")
{
    struct Pokemon mon;
    u32 attack = 100, speed = 50, bank = 20, attackBefore;

    CreateBondMon(&mon, SPECIES_CHARMANDER, 1);
    SetMonData(&mon, MON_DATA_ATK_EV, &attack);
    SetMonData(&mon, MON_DATA_SPEED_EV, &speed);
    SetMonData(&mon, MON_DATA_TRAINING_BANK, &bank);
    CalculateMonStats(&mon);
    attackBefore = GetMonData(&mon, MON_DATA_ATK);
    KJH_ResetTrainingPoints(&mon);
    EXPECT_EQ(KJH_TrainingPlaced(&mon), 0);
    EXPECT_EQ(KJH_TrainingBank(&mon), 100 + 50 + 20);
    EXPECT_LT(GetMonData(&mon, MON_DATA_ATK), attackBefore);
}

TEST("KJH: the full reset stops at the bank's limit, still enough to place a whole build again")
{
    struct Pokemon mon;
    u32 evs = 255, bank = 300;

    CreateBondMon(&mon, SPECIES_CHARMANDER, 1);
    SetMonData(&mon, MON_DATA_ATK_EV, &evs);
    SetMonData(&mon, MON_DATA_SPEED_EV, &evs);
    SetMonData(&mon, MON_DATA_TRAINING_BANK, &bank);
    KJH_ResetTrainingPoints(&mon);
    EXPECT_EQ(KJH_TrainingBank(&mon), KJH_TRAINING_BANK_MAX);
    EXPECT_GE(KJH_TrainingBank(&mon), KJH_TrainingTotalLimit(KJH_TIER_ALPHA));
}

TEST("KJH: in the levels-free game the stat trainer sets IVs only from Bond 20, kept at the peak")
{
    struct Pokemon mon;
    u32 friendship = KJH_BondToFriendship(1);

    FlagSet(FLAG_KJH_LEVELLESS);
    CreateBondMon(&mon, SPECIES_CHARMANDER, 19);
    EXPECT(!KJH_CanTrainIvs(&mon));
    CreateBondMon(&mon, SPECIES_CHARMANDER, 20);
    EXPECT(KJH_CanTrainIvs(&mon));
    SetMonData(&mon, MON_DATA_FRIENDSHIP, &friendship); // Bond 1 now, 20 at its peak
    EXPECT(KJH_CanTrainIvs(&mon));
    FlagClear(FLAG_KJH_LEVELLESS);
    CreateBondMon(&mon, SPECIES_CHARMANDER, 1);
    EXPECT(KJH_CanTrainIvs(&mon));
}

TEST("KJH: in the levels-free game the Hidden Ability needs Bond 12, the other abilities stay free")
{
    u32 friendship;

    ZeroPlayerPartyMons();
    FlagSet(FLAG_KJH_LEVELLESS);
    CreateBondMon(&gPlayerParty[0], SPECIES_CHARMANDER, 11); // Blaze, Solar Power (Hidden)
    gSpecialVar_0x8004 = 0;
    gSpecialVar_0x8005 = 1;
    RUN_OVERWORLD_SCRIPT(callnative KJH_ScriptSetChosenAbility, requests_effects=1;);
    EXPECT_EQ(gSpecialVar_Result, KJH_ABILITY_NEEDS_BOND);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_ABILITY_NUM), 0);

    CreateBondMon(&gPlayerParty[0], SPECIES_GEODUDE, 1); // Rock Head, Sturdy, Sand Veil (Hidden)
    gSpecialVar_0x8005 = 1;
    RUN_OVERWORLD_SCRIPT(callnative KJH_ScriptSetChosenAbility, requests_effects=1;);
    EXPECT_EQ(gSpecialVar_Result, KJH_ABILITY_CHANGED);
    gSpecialVar_0x8005 = 2;
    RUN_OVERWORLD_SCRIPT(callnative KJH_ScriptSetChosenAbility, requests_effects=1;);
    EXPECT_EQ(gSpecialVar_Result, KJH_ABILITY_NEEDS_BOND);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_ABILITY_NUM), 1);

    RUN_OVERWORLD_SCRIPT(callnative KJH_ScriptBufferAbilityChoices, requests_effects=1;);
    EXPECT_EQ(StringCompare(gStringVar3, COMPOUND_STRING("Sand Veil (BOND 12)")), 0);

    CreateBondMon(&gPlayerParty[0], SPECIES_CHARMANDER, 12);
    friendship = KJH_BondToFriendship(1); // Bond 1 now, 12 at its peak
    SetMonData(&gPlayerParty[0], MON_DATA_FRIENDSHIP, &friendship);
    gSpecialVar_0x8005 = 1;
    RUN_OVERWORLD_SCRIPT(callnative KJH_ScriptSetChosenAbility, requests_effects=1;);
    EXPECT_EQ(gSpecialVar_Result, KJH_ABILITY_HIDDEN);

    FlagClear(FLAG_KJH_LEVELLESS);
    CreateBondMon(&gPlayerParty[0], SPECIES_CHARMANDER, 1);
    gSpecialVar_0x8005 = 1;
    RUN_OVERWORLD_SCRIPT(callnative KJH_ScriptSetChosenAbility, requests_effects=1;);
    EXPECT_EQ(gSpecialVar_Result, KJH_ABILITY_HIDDEN);
}
