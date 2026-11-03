// KJH: evolution by Training points (LV-9, src/kjh_evolution.c), with the rules of docs/LEVELLESS_DESIGN.md
// ("Evolution brainstorm") in the KJH repo: in the levels-free game a level or trade evolution needs its own key (the
// level, the trade's item) and the Training points of its stage (earned = placed + banked: 100 for the second form,
// 200 for the third, 300 for a pseudo-legendary's last); a stone is enough alone; a friendship evolution needs the
// peak Bond 18. The test runner clears the flags before each test: FLAG_KJH_LEVELLESS is off unless a test sets it.
#include "global.h"
#include "event_data.h"
#include "kjh_bond.h"
#include "kjh_evolution.h"
#include "kjh_training.h"
#include "string_util.h"
#include "test/battle.h"
#include "constants/items.h"

static void SetTrainingBank(struct Pokemon *mon, u32 bank)
{
    SetMonData(mon, MON_DATA_TRAINING_BANK, &bank);
}

static void SetBond(struct Pokemon *mon, u32 bond)
{
    u32 friendship = KJH_BondToFriendship(bond);
    SetMonData(mon, MON_DATA_FRIENDSHIP, &friendship);
}

static enum Species EvolutionByItem(struct Pokemon *mon, enum Item item)
{
    return GetEvolutionTargetSpecies(mon, EVO_MODE_ITEM_USE, item, NULL, NULL, CHECK_EVO);
}

TEST("KJH: evolution, by level it needs the level and 100 Training points")
{
    struct Pokemon mon;

    FlagSet(FLAG_KJH_LEVELLESS);
    CreateMon(&mon, SPECIES_CHARMANDER, 16, 0, OTID_STRUCT_PRESET(0));
    SetTrainingBank(&mon, 99);
    EXPECT_EQ(KJH_ReadyEvolution(&mon), SPECIES_NONE);
    SetTrainingBank(&mon, 100);
    EXPECT_EQ(KJH_ReadyEvolution(&mon), SPECIES_CHARMELEON);

    CreateMon(&mon, SPECIES_CHARMANDER, 15, 0, OTID_STRUCT_PRESET(0));
    SetTrainingBank(&mon, 100);
    EXPECT_EQ(KJH_ReadyEvolution(&mon), SPECIES_NONE);
}

TEST("KJH: evolution, placed points count as earned")
{
    struct Pokemon mon;

    FlagSet(FLAG_KJH_LEVELLESS);
    CreateMon(&mon, SPECIES_CHARMANDER, 16, 0, OTID_STRUCT_PRESET(0));
    SetTrainingBank(&mon, 100);
    EXPECT_EQ(KJH_PlaceTrainingPoints(&mon, STAT_ATK, 60), 60);
    EXPECT_EQ(KJH_ReadyEvolution(&mon), SPECIES_CHARMELEON);
}

TEST("KJH: evolution, the third form needs 200 points and a pseudo-legendary's last form 300")
{
    struct Pokemon mon;

    FlagSet(FLAG_KJH_LEVELLESS);
    CreateMon(&mon, SPECIES_CHARMELEON, 36, 0, OTID_STRUCT_PRESET(0));
    SetTrainingBank(&mon, 199);
    EXPECT_EQ(KJH_ReadyEvolution(&mon), SPECIES_NONE);
    SetTrainingBank(&mon, 200);
    EXPECT_EQ(KJH_ReadyEvolution(&mon), SPECIES_CHARIZARD);

    CreateMon(&mon, SPECIES_DRAGONAIR, 55, 0, OTID_STRUCT_PRESET(0));
    SetTrainingBank(&mon, 299);
    EXPECT_EQ(KJH_ReadyEvolution(&mon), SPECIES_NONE);
    SetTrainingBank(&mon, 300);
    EXPECT_EQ(KJH_ReadyEvolution(&mon), SPECIES_DRAGONITE);
}

TEST("KJH: evolution, a veteran past the level in another region stays ready")
{
    struct Pokemon mon;
    u32 peak = 20;

    FlagSet(FLAG_KJH_LEVELLESS);
    CreateMon(&mon, SPECIES_CHARMANDER, 10, 0, OTID_STRUCT_PRESET(0)); // a new region's team level
    SetMonData(&mon, MON_DATA_PEAK_LEVEL, &peak);
    SetTrainingBank(&mon, 100);
    EXPECT_EQ(KJH_ReadyEvolution(&mon), SPECIES_CHARMELEON);
}

TEST("KJH: evolution, outside the levels-free game the level is enough")
{
    struct Pokemon mon;

    CreateMon(&mon, SPECIES_CHARMANDER, 16, 0, OTID_STRUCT_PRESET(0));
    EXPECT_EQ(KJH_ReadyEvolution(&mon), SPECIES_CHARMELEON);
}

TEST("KJH: evolution, a trade's item needs its stage's points, a stone none")
{
    struct Pokemon mon;

    FlagSet(FLAG_KJH_LEVELLESS);
    CreateMon(&mon, SPECIES_KADABRA, 20, 0, OTID_STRUCT_PRESET(0));
    SetTrainingBank(&mon, 199);
    EXPECT_EQ(EvolutionByItem(&mon, ITEM_LINKING_CORD), SPECIES_NONE);
    SetTrainingBank(&mon, 200);
    EXPECT_EQ(EvolutionByItem(&mon, ITEM_LINKING_CORD), SPECIES_ALAKAZAM);

    CreateMon(&mon, SPECIES_ONIX, 20, 0, OTID_STRUCT_PRESET(0));
    SetTrainingBank(&mon, 99);
    EXPECT_EQ(EvolutionByItem(&mon, ITEM_METAL_COAT), SPECIES_NONE);
    SetTrainingBank(&mon, 100);
    EXPECT_EQ(EvolutionByItem(&mon, ITEM_METAL_COAT), SPECIES_STEELIX);

    CreateMon(&mon, SPECIES_VULPIX, 10, 0, OTID_STRUCT_PRESET(0));
    EXPECT_EQ(EvolutionByItem(&mon, ITEM_FIRE_STONE), SPECIES_NINETALES);
}

TEST("KJH: evolution, by friendship at the peak Bond 18, with no points")
{
    struct Pokemon mon;

    FlagSet(FLAG_KJH_LEVELLESS);
    CreateMon(&mon, SPECIES_GOLBAT, 30, 0, OTID_STRUCT_PRESET(0));
    SetBond(&mon, 17);
    EXPECT_EQ(KJH_ReadyEvolution(&mon), SPECIES_NONE);
    SetBond(&mon, KJH_EVOLUTION_BOND);
    EXPECT_EQ(KJH_ReadyEvolution(&mon), SPECIES_CROBAT);
    SetBond(&mon, 10); // the peak stays at 18
    EXPECT_EQ(KJH_ReadyEvolution(&mon), SPECIES_CROBAT);
}

TEST("KJH: evolution, the Summary's goal is the stage's")
{
    EXPECT_EQ(KJH_TrainingEvolutionGoal(SPECIES_CHARMANDER), 100);
    EXPECT_EQ(KJH_TrainingEvolutionGoal(SPECIES_ONIX), 100);
    EXPECT_EQ(KJH_TrainingEvolutionGoal(SPECIES_KADABRA), 200);
    EXPECT_EQ(KJH_TrainingEvolutionGoal(SPECIES_DRAGONAIR), 300);
    EXPECT_EQ(KJH_TrainingEvolutionGoal(SPECIES_GOLBAT), 0);
    EXPECT_EQ(KJH_TrainingEvolutionGoal(SPECIES_VULPIX), 0);
    EXPECT_EQ(KJH_TrainingEvolutionGoal(SPECIES_CHARIZARD), 0);
}

// gLeveledUpInBattle: the Pokemon the battle's end offers the evolution (TryEvolvePokemon, outside test battles)
WILD_BATTLE_TEST("KJH: evolution, a Pokemon that becomes ready in a battle is offered it after the battle")
{
    u32 bank, level;
    bool32 offered;

    PARAMETRIZE { bank = 99;  level = 16; offered = TRUE; }  // the KO's point makes 100
    PARAMETRIZE { bank = 100; level = 16; offered = FALSE; } // ready before and put off: the party menu's
    PARAMETRIZE { bank = 99;  level = 15; offered = FALSE; } // not ready by level
    GIVEN {
        FLAG_SET(FLAG_KJH_LEVELLESS);
        PLAYER(SPECIES_CHARMANDER) { Level(level); SetTrainingBank(gBattleTestRunnerState->data.currentMon, bank); }
        OPPONENT(SPECIES_CATERPIE) { Level(5); HP(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } THEN {
        EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_TRAINING_BANK), bank + 1);
        EXPECT_EQ((gLeveledUpInBattle & 1) != 0, offered);
    }
}

TEST("KJH: evolution, a rise of the team's level offers the Pokemon it made ready")
{
    u32 peak = 40;

    FlagSet(FLAG_KJH_LEVELLESS);
    ZeroPlayerPartyMons();
    CreateMon(&gParties[B_TRAINER_PLAYER][0], SPECIES_CHARMANDER, 16, 0, OTID_STRUCT_PRESET(0));
    SetTrainingBank(&gParties[B_TRAINER_PLAYER][0], 100);
    CreateMon(&gParties[B_TRAINER_PLAYER][1], SPECIES_BULBASAUR, 16, 0, OTID_STRUCT_PRESET(0)); // no points
    CreateMon(&gParties[B_TRAINER_PLAYER][2], SPECIES_SQUIRTLE, 16, 0, OTID_STRUCT_PRESET(0));
    SetTrainingBank(&gParties[B_TRAINER_PLAYER][2], 100);
    CreateMon(&gParties[B_TRAINER_PLAYER][3], SPECIES_GOLBAT, 16, 0, OTID_STRUCT_PRESET(0)); // ready by Bond
    SetBond(&gParties[B_TRAINER_PLAYER][3], KJH_EVOLUTION_BOND);
    CreateMon(&gParties[B_TRAINER_PLAYER][4], SPECIES_CHARMANDER, 16, 0, OTID_STRUCT_PRESET(0)); // a veteran
    SetTrainingBank(&gParties[B_TRAINER_PLAYER][4], 100);
    SetMonData(&gParties[B_TRAINER_PLAYER][4], MON_DATA_PEAK_LEVEL, &peak);

    gSpecialVar_0x8004 = 0;
    gSpecialVar_0x8005 = 14; // the team went from 14 to 16
    gSpecialVar_0x8006 = 16;
    EXPECT(KJH_BufferNextRiseEvolution());
    EXPECT_EQ(gSpecialVar_0x8004, 0);
    EXPECT_EQ(StringCompare(gStringVar1, GetSpeciesName(SPECIES_CHARMANDER)), 0);
    gSpecialVar_0x8004++;
    EXPECT(KJH_BufferNextRiseEvolution());
    EXPECT_EQ(gSpecialVar_0x8004, 2);
    gSpecialVar_0x8004++;
    EXPECT(!KJH_BufferNextRiseEvolution());

    // already ready at the old level: put off before, so not offered again
    gSpecialVar_0x8004 = 0;
    gSpecialVar_0x8005 = 16;
    EXPECT(!KJH_BufferNextRiseEvolution());
}
