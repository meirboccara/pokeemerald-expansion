// KJH: Training points (LV-7, src/kjh_training.c), with the numbers of docs/LEVELLESS_DESIGN.md §4 in the KJH repo:
// a KO gives 1 + the foe's level / 20, times its tier; the Pokemon that fought get them all, the rest of the party
// half (half points kept). They are placed in the stats: 255 a stat, a total of 510 / 530 / 630 by tier mark.
#include "global.h"
#include "event_data.h"
#include "item.h"
#include "kjh_training.h"
#include "test/battle.h"
#include "constants/items.h"

TEST("KJH: training, the points for a KO follow the foe's level")
{
    EXPECT_EQ(KJH_TrainingPointsPerKo(5, 1), 1);
    EXPECT_EQ(KJH_TrainingPointsPerKo(19, 1), 1);
    EXPECT_EQ(KJH_TrainingPointsPerKo(20, 1), 2);
    EXPECT_EQ(KJH_TrainingPointsPerKo(40, 1), 3);
    EXPECT_EQ(KJH_TrainingPointsPerKo(80, 1), 5);
    EXPECT_EQ(KJH_TrainingPointsPerKo(20, 3), 6);
}

TEST("KJH: training, the foe's tier multiplies them")
{
    EXPECT_EQ(KJH_TrainingFoeMultiplier(KJH_PACK_ROLE_NONE, KJH_TIER_REGULAR, FALSE), 1);
    EXPECT_EQ(KJH_TrainingFoeMultiplier(KJH_PACK_ROLE_LEADER_HELPER, KJH_TIER_REGULAR, FALSE), 2);
    EXPECT_EQ(KJH_TrainingFoeMultiplier(KJH_PACK_ROLE_LEADER, KJH_TIER_REGULAR, FALSE), 3);
    EXPECT_EQ(KJH_TrainingFoeMultiplier(KJH_PACK_ROLE_NONE, KJH_TIER_LEADER, FALSE), 3);
    EXPECT_EQ(KJH_TrainingFoeMultiplier(KJH_PACK_ROLE_NONE, KJH_TIER_REGULAR, TRUE), 3);
    EXPECT_EQ(KJH_TrainingFoeMultiplier(KJH_PACK_ROLE_NONE, KJH_TIER_ALPHA, FALSE), 6);
    EXPECT_EQ(KJH_TrainingFoeMultiplier(KJH_PACK_ROLE_NONE, KJH_TIER_ALPHA, TRUE), 6);
}

TEST("KJH: training, the bench gets half, and half points are kept")
{
    u32 bank = 0, half = 0;

    EXPECT_EQ(KJH_TrainingHalvesFor(3, TRUE), 6);
    EXPECT_EQ(KJH_TrainingHalvesFor(3, FALSE), 3);
    KJH_TrainingAddHalves(&bank, &half, KJH_TrainingHalvesFor(1, FALSE));
    EXPECT_EQ(bank, 0);
    EXPECT_EQ(half, 1);
    KJH_TrainingAddHalves(&bank, &half, KJH_TrainingHalvesFor(1, FALSE));
    EXPECT_EQ(bank, 1);
    EXPECT_EQ(half, 0);
}

TEST("KJH: training, the bank stops at 630")
{
    u32 bank = 629, half = 1;

    KJH_TrainingAddHalves(&bank, &half, 4);
    EXPECT_EQ(bank, KJH_TRAINING_BANK_MAX);
    EXPECT_EQ(half, 0);
}

TEST("KJH: training, 255 a stat and 510 / 530 / 630 in all by tier mark")
{
    u8 none[NUM_STATS] = {0};
    u8 full[NUM_STATS] = {255, 255, 0, 0, 0, 0};
    u8 alpha[NUM_STATS] = {255, 255, 100, 0, 0, 0};

    EXPECT_EQ(KJH_TrainingTotalLimit(KJH_TIER_REGULAR), 510);
    EXPECT_EQ(KJH_TrainingTotalLimit(KJH_TIER_LEADER), 530);
    EXPECT_EQ(KJH_TrainingTotalLimit(KJH_TIER_ALPHA), 630);
    EXPECT_EQ(KJH_TrainingRoom(none, KJH_TIER_REGULAR, STAT_ATK), 255);
    EXPECT_EQ(KJH_TrainingRoom(full, KJH_TIER_REGULAR, STAT_ATK), 0);
    EXPECT_EQ(KJH_TrainingRoom(full, KJH_TIER_REGULAR, STAT_SPEED), 0);
    EXPECT_EQ(KJH_TrainingRoom(full, KJH_TIER_LEADER, STAT_SPEED), 20);
    EXPECT_EQ(KJH_TrainingRoom(alpha, KJH_TIER_ALPHA, STAT_SPEED), 20);
}

TEST("KJH: training, placing points moves them from the bank to a stat")
{
    struct Pokemon mon;
    u32 bank = 10;

    CreateMon(&mon, SPECIES_WOBBUFFET, 100, 0, OTID_STRUCT_PRESET(0));
    SetMonData(&mon, MON_DATA_TRAINING_BANK, &bank);
    CalculateMonStats(&mon);
    u32 attack = GetMonData(&mon, MON_DATA_ATK);
    EXPECT_EQ(KJH_TrainingPointsToPlace(&mon), 10);
    EXPECT_EQ(KJH_PlaceTrainingPoints(&mon, STAT_ATK, 4), 4);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_ATK_EV), 4);
    EXPECT_EQ(KJH_TrainingBank(&mon), 6);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_ATK), attack + 1);
    EXPECT_EQ(KJH_PlaceTrainingPoints(&mon, STAT_ATK, 20), 6); // only what the bank has
    EXPECT_EQ(KJH_TrainingBank(&mon), 0);
}

TEST("KJH: training, a stat and the total have their limits when placing")
{
    struct Pokemon mon;
    u32 bank = 600, ev = 250;

    CreateMon(&mon, SPECIES_WOBBUFFET, 100, 0, OTID_STRUCT_PRESET(0));
    SetMonData(&mon, MON_DATA_TRAINING_BANK, &bank);
    SetMonData(&mon, MON_DATA_ATK_EV, &ev);
    EXPECT_EQ(KJH_PlaceTrainingPoints(&mon, STAT_ATK, 20), 5);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_ATK_EV), 255);
    SetMonData(&mon, MON_DATA_DEF_EV, &ev);
    EXPECT_EQ(KJH_PlaceTrainingPoints(&mon, STAT_SPEED, 20), 5); // 255 + 250 + 5 = 510
    EXPECT_EQ(KJH_TrainingPointsToPlace(&mon), 0);
}

WILD_BATTLE_TEST("KJH: training, a KO gives the fighter all its points, the bench half, and no EVs")
{
    GIVEN {
        FLAG_SET(FLAG_KJH_LEVELLESS);
        PLAYER(SPECIES_WOBBUFFET);
        PLAYER(SPECIES_WYNAUT);
        OPPONENT(SPECIES_CATERPIE) { Level(20); HP(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_TACKLE); }
    } THEN {
        // Lv 20: 1 + 20 / 20 = 2 points; the bench gets 1
        EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_TRAINING_BANK), 2);
        EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][1], MON_DATA_TRAINING_BANK), 1);
        EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_HP_EV), 0);
        EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_SPEED_EV), 0);
    }
}

WILD_BATTLE_TEST("KJH: training, the bench keeps a half point")
{
    GIVEN {
        FLAG_SET(FLAG_KJH_LEVELLESS);
        PLAYER(SPECIES_WOBBUFFET);
        PLAYER(SPECIES_WYNAUT);
        OPPONENT(SPECIES_CATERPIE) { Level(5); HP(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_TACKLE); }
    } THEN {
        EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_TRAINING_BANK), 1);
        EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][1], MON_DATA_TRAINING_BANK), 0);
        EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][1], MON_DATA_TRAINING_HALF), 1);
    }
}

// The test runner clears the flags before each test: FLAG_KJH_LEVELLESS is off
WILD_BATTLE_TEST("KJH: training, none outside the levels-free game")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_CATERPIE) { Level(20); HP(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_TACKLE); }
    } THEN {
        EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_TRAINING_BANK), 0);
    }
}

TEST("KJH: training, an EV-lowering berry gives the stat's points back to the bank")
{
    u32 ev = 40;

    FlagSet(FLAG_KJH_LEVELLESS);
    CreateMon(&gParties[B_TRAINER_PLAYER][0], SPECIES_WOBBUFFET, 50, 0, OTID_STRUCT_PRESET(0));
    SetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_ATK_EV, &ev);
    EXPECT_EQ(PokemonUseItemEffects(&gParties[B_TRAINER_PLAYER][0], ITEM_KELPSY_BERRY, 0, 0, FALSE), FALSE);
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_ATK_EV), 0);
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_TRAINING_BANK), 40);
}

// KJH: the Summary's Training menu asks to keep the points placed before it closes (a snapshot when it opens; NO
// puts it back)
TEST("KJH: training, a snapshot sees points placed since it was taken")
{
    struct Pokemon mon;
    struct KjhTrainingSnapshot snapshot;
    u32 bank = 10;

    CreateMon(&mon, SPECIES_WOBBUFFET, 50, 0, OTID_STRUCT_PRESET(0));
    SetMonData(&mon, MON_DATA_TRAINING_BANK, &bank);
    KJH_TrainingSnapshot(&mon, &snapshot);
    EXPECT(!KJH_TrainingChanged(&mon, &snapshot));
    KJH_PlaceTrainingPoints(&mon, STAT_SPEED, 3);
    EXPECT(KJH_TrainingChanged(&mon, &snapshot));
}

TEST("KJH: training, restoring a snapshot gives the placed points back to the bank")
{
    struct Pokemon mon;
    struct KjhTrainingSnapshot snapshot;
    u32 bank = 30, ev = 8;

    CreateMon(&mon, SPECIES_WOBBUFFET, 50, 0, OTID_STRUCT_PRESET(0));
    SetMonData(&mon, MON_DATA_TRAINING_BANK, &bank);
    SetMonData(&mon, MON_DATA_DEF_EV, &ev);
    CalculateMonStats(&mon);
    u32 hp = GetMonData(&mon, MON_DATA_MAX_HP), attack = GetMonData(&mon, MON_DATA_ATK);
    KJH_TrainingSnapshot(&mon, &snapshot);
    KJH_PlaceTrainingPoints(&mon, STAT_HP, 10);
    KJH_PlaceTrainingPoints(&mon, STAT_ATK, 12);
    KJH_TrainingRestore(&mon, &snapshot);
    EXPECT_EQ(KJH_TrainingBank(&mon), 30);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_HP_EV), 0);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_ATK_EV), 0);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_DEF_EV), 8);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_MAX_HP), hp);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_HP), hp);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_ATK), attack);
    EXPECT(!KJH_TrainingChanged(&mon, &snapshot));
}
