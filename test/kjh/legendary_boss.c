// KJH: a legendary fights as a boss (CF-12, src/kjh_legendary.c): a totem aura with +1 to its two highest stats
// (HP not counted), and the boss AI for that one battle.
#include "global.h"
#include "battle_main.h"
#include "battle_util2.h"
#include "kjh_legendary.h"
#include "kjh_progression.h"
#include "test/battle.h"

TEST("KJH: Articuno's aura raises its two highest stats, Defense and Sp. Def")
{
    ASSUME(GetSpeciesBaseSpDefense(SPECIES_ARTICUNO) == 125);
    ASSUME(GetSpeciesBaseDefense(SPECIES_ARTICUNO) == 100);
    ASSUME(GetSpeciesBaseSpAttack(SPECIES_ARTICUNO) == 95);
    EXPECT_EQ(KJH_LegendaryBoostedStats(SPECIES_ARTICUNO), (1 << STAT_DEF) | (1 << STAT_SPDEF));
}

TEST("KJH: HP is never one of the aura's stats")
{
    // Snorlax: HP 160 is its highest, then Sp. Def 110 and Attack 110
    ASSUME(GetSpeciesBaseHP(SPECIES_SNORLAX) == 160);
    ASSUME(GetSpeciesBaseAttack(SPECIES_SNORLAX) == 110);
    ASSUME(GetSpeciesBaseSpDefense(SPECIES_SNORLAX) == 110);
    EXPECT_EQ(KJH_LegendaryBoostedStats(SPECIES_SNORLAX), (1 << STAT_ATK) | (1 << STAT_SPDEF));
}

TEST("KJH: a tie for the aura's second stat goes to the stat that comes first")
{
    // Regice: Sp. Def 200, then Defense and Sp. Atk tied at 100: Defense comes first (Attack, Defense, Speed, Sp. Atk)
    ASSUME(GetSpeciesBaseSpDefense(SPECIES_REGICE) == 200);
    ASSUME(GetSpeciesBaseDefense(SPECIES_REGICE) == 100);
    ASSUME(GetSpeciesBaseSpAttack(SPECIES_REGICE) == 100);
    EXPECT_EQ(KJH_LegendaryBoostedStats(SPECIES_REGICE), (1 << STAT_DEF) | (1 << STAT_SPDEF));
}

TEST("KJH: a legendary boss battle has the smart wild AI, and it ends with the battle")
{
    KJH_SetupLegendaryBoss(SPECIES_ARTICUNO);
    EXPECT(KJH_IsLegendaryBossBattle());
    EXPECT(IsWildMonSmart());
    FreeBattleResources();
    EXPECT(!KJH_IsLegendaryBossBattle());
    EXPECT(!IsWildMonSmart());
    memset(gQueuedStatBoosts, 0, sizeof(gQueuedStatBoosts));
}

TEST("KJH: a legendary boss gets the boss trainers' AI on top of the wild AI, other wild Pokemon don't")
{
    u64 wildFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_CHECK_VIABILITY;

    EXPECT_EQ(KJH_LegendaryWildAiFlags(wildFlags), wildFlags);
    KJH_SetupLegendaryBoss(SPECIES_ARTICUNO);
    EXPECT_EQ(KJH_LegendaryWildAiFlags(wildFlags), wildFlags | KJH_BOSS_AI_FLAGS);
    FreeBattleResources();
    EXPECT_EQ(KJH_LegendaryWildAiFlags(wildFlags), wildFlags);
    memset(gQueuedStatBoosts, 0, sizeof(gQueuedStatBoosts));
}

WILD_BATTLE_TEST("KJH: a legendary boss starts its battle with the aura and +1 to its two highest stats")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_ARTICUNO) { Level(50); Moves(MOVE_CELEBRATE); }
        KJH_SetupLegendaryBoss(SPECIES_ARTICUNO);
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_TOTEM_FLARE, opponent);
        MESSAGE("The wild Articuno's aura flared to life!");
    } THEN {
        EXPECT_EQ(opponent->statStages[STAT_DEF], DEFAULT_STAT_STAGE + 1);
        EXPECT_EQ(opponent->statStages[STAT_SPDEF], DEFAULT_STAT_STAGE + 1);
        EXPECT_EQ(opponent->statStages[STAT_ATK], DEFAULT_STAT_STAGE);
        EXPECT_EQ(opponent->statStages[STAT_SPATK], DEFAULT_STAT_STAGE);
        EXPECT_EQ(opponent->statStages[STAT_SPEED], DEFAULT_STAT_STAGE);
    }
}

WILD_BATTLE_TEST("KJH: a wild Pokemon that isn't a legendary boss has no aura")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_ARTICUNO) { Level(50); Moves(MOVE_CELEBRATE); }
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); }
    } SCENE {
        NONE_OF { MESSAGE("The wild Articuno's aura flared to life!"); }
    } THEN {
        EXPECT_EQ(opponent->statStages[STAT_DEF], DEFAULT_STAT_STAGE);
        EXPECT_EQ(opponent->statStages[STAT_SPDEF], DEFAULT_STAT_STAGE);
    }
}

// The test runner sets the AI flags itself, so this checks what the boss flags do; the test above checks that a
// legendary boss gets them (KJH_LegendaryWildAiFlags, which GetWildAiFlags in battle_ai_main.c returns).
AI_SINGLE_BATTLE_TEST("KJH: Articuno as a boss picks the move that knocks out")
{
    GIVEN {
        ASSUME(GetMoveType(MOVE_ICE_BEAM) == TYPE_ICE);
        ASSUME(GetMoveType(MOVE_GUST) == TYPE_FLYING);
        AI_FLAGS(KJH_BOSS_AI_FLAGS);
        PLAYER(SPECIES_RHYDON) { Level(45); HP(60); }
        PLAYER(SPECIES_RHYDON) { Level(45); }
        OPPONENT(SPECIES_ARTICUNO) { Level(50); Moves(MOVE_GUST, MOVE_MIST, MOVE_ICE_BEAM, MOVE_AGILITY); }
    } WHEN {
        TURN { EXPECT_MOVE(opponent, MOVE_ICE_BEAM); SEND_OUT(player, 1); }
    } SCENE {
        MESSAGE("Rhydon fainted!");
    }
}
