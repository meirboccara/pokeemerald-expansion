// KJH: the power cap for strong moves (LV-11, src/kjh_power_cap.c), with the numbers of docs/LEVELLESS_DESIGN.md
// §7 in the KJH repo: a move above 60 power hits at max(60, power x %), % by the region's badges (0-1: 50 ... 6+:
// 100). The cap is off in the test build (B_KJH_POWER_CAP); these tests turn it on.
#include "global.h"
#include "event_data.h"
#include "kjh_power_cap.h"
#include "test/battle.h"
#include "constants/map_groups.h"

static void SetBadges(u32 count)
{
    // The test save stands on map 0, Hoenn's Petalburg City (ENG-9): stand on a Kanto map
    gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(MAP_PALLET_TOWN);
    gSaveBlock1Ptr->location.mapNum = MAP_NUM(MAP_PALLET_TOWN);
    for (u32 i = 0; i < NUM_BADGES; i++)
    {
        if (i < count)
            FlagSet(FLAG_BADGE01_GET + i);
        else
            FlagClear(FLAG_BADGE01_GET + i);
    }
}

TEST("KJH: power cap, the percentage by the region's badges")
{
    EXPECT_EQ(KJH_PowerCapPercent(0), 50);
    EXPECT_EQ(KJH_PowerCapPercent(1), 50);
    EXPECT_EQ(KJH_PowerCapPercent(2), 60);
    EXPECT_EQ(KJH_PowerCapPercent(3), 70);
    EXPECT_EQ(KJH_PowerCapPercent(4), 80);
    EXPECT_EQ(KJH_PowerCapPercent(5), 90);
    EXPECT_EQ(KJH_PowerCapPercent(6), 100);
    EXPECT_EQ(KJH_PowerCapPercent(8), 100);
}

TEST("KJH: power cap, Overheat (140) at each badge count, the design's table")
{
    EXPECT_EQ(KJH_CappedPower(140, KJH_PowerCapPercent(0)), 70);
    EXPECT_EQ(KJH_CappedPower(140, KJH_PowerCapPercent(2)), 84);
    EXPECT_EQ(KJH_CappedPower(140, KJH_PowerCapPercent(3)), 98);
    EXPECT_EQ(KJH_CappedPower(140, KJH_PowerCapPercent(4)), 112);
    EXPECT_EQ(KJH_CappedPower(140, KJH_PowerCapPercent(5)), 126);
    EXPECT_EQ(KJH_CappedPower(140, KJH_PowerCapPercent(6)), 140);
}

TEST("KJH: power cap, never below 60, and moves of 60 or less are never limited")
{
    EXPECT_EQ(KJH_CappedPower(90, 50), 60);
    EXPECT_EQ(KJH_CappedPower(61, 50), 60);
    EXPECT_EQ(KJH_CappedPower(60, 50), 60);
    EXPECT_EQ(KJH_CappedPower(40, 50), 40);
    EXPECT_EQ(KJH_CappedPower(0, 50), 0);
}

TEST("KJH: power cap, one-hit KO moves are locked until the 6th badge")
{
    EXPECT(KJH_IsOhkoLocked(0));
    EXPECT(KJH_IsOhkoLocked(5));
    EXPECT(!KJH_IsOhkoLocked(6));
    EXPECT(!KJH_IsOhkoLocked(8));
}

TEST("KJH: power cap, the region's badges are Kanto's")
{
    SetBadges(3);
    EXPECT_EQ(KJH_RegionBadges(), 3);
    SetBadges(0);
    EXPECT_EQ(KJH_RegionBadges(), 0);
}

// Eruption at full HP is 150: with 2 badges (60%) it hits as hard as Flamethrower (90) with 6
SINGLE_BATTLE_TEST("KJH: power cap, with 2 badges a 150-power move hits at 90", s16 damage)
{
    enum Move move;
    u32 badges;
    PARAMETRIZE { move = MOVE_ERUPTION; badges = 2; }
    PARAMETRIZE { move = MOVE_FLAMETHROWER; badges = 6; }
    GIVEN {
        ASSUME(GetMovePower(MOVE_ERUPTION) == 150);
        ASSUME(GetMovePower(MOVE_FLAMETHROWER) == 90);
        ASSUME(GetMoveCategory(MOVE_ERUPTION) == GetMoveCategory(MOVE_FLAMETHROWER));
        WITH_CONFIG(B_KJH_POWER_CAP, TRUE);
        SetBadges(badges);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_EQ(results[0].damage, results[1].damage);
    }
}

// Flamethrower (90) at 0 badges would be 45: it stays at 60, as hard as Incinerate (60)
SINGLE_BATTLE_TEST("KJH: power cap, a held-back move never drops below 60", s16 damage)
{
    enum Move move;
    PARAMETRIZE { move = MOVE_FLAMETHROWER; }
    PARAMETRIZE { move = MOVE_INCINERATE; }
    GIVEN {
        ASSUME(GetMovePower(MOVE_INCINERATE) == 60);
        ASSUME(GetMoveCategory(MOVE_INCINERATE) == GetMoveCategory(MOVE_FLAMETHROWER));
        WITH_CONFIG(B_KJH_POWER_CAP, TRUE);
        SetBadges(0);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_EQ(results[0].damage, results[1].damage);
    }
}

SINGLE_BATTLE_TEST("KJH: power cap, with 6 badges Overheat hits at full power", s16 damage)
{
    bool32 cap;
    PARAMETRIZE { cap = FALSE; }
    PARAMETRIZE { cap = TRUE; }
    GIVEN {
        WITH_CONFIG(B_KJH_POWER_CAP, cap);
        SetBadges(6);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_OVERHEAT); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_EQ(results[0].damage, results[1].damage);
    }
}

SINGLE_BATTLE_TEST("KJH: power cap, Overheat with no badges deals less", s16 damage)
{
    bool32 cap;
    PARAMETRIZE { cap = FALSE; }
    PARAMETRIZE { cap = TRUE; }
    GIVEN {
        WITH_CONFIG(B_KJH_POWER_CAP, cap);
        SetBadges(0);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_OVERHEAT); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_LT(results[1].damage, results[0].damage);
    }
}

SINGLE_BATTLE_TEST("KJH: power cap, the opponent's moves are held back too", s16 damage)
{
    enum Move move;
    u32 badges;
    PARAMETRIZE { move = MOVE_ERUPTION; badges = 2; }
    PARAMETRIZE { move = MOVE_FLAMETHROWER; badges = 6; }
    GIVEN {
        WITH_CONFIG(B_KJH_POWER_CAP, TRUE);
        SetBadges(badges);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, move); }
    } SCENE {
        HP_BAR(player, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_EQ(results[0].damage, results[1].damage);
    }
}

SINGLE_BATTLE_TEST("KJH: power cap, the battle says a move is held back, once")
{
    GIVEN {
        WITH_CONFIG(B_KJH_POWER_CAP, TRUE);
        SetBadges(0);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_EMBER); }
        TURN { MOVE(player, MOVE_OVERHEAT); }
        TURN { MOVE(player, MOVE_OVERHEAT); }
    } SCENE {
        MESSAGE("Wobbuffet used Ember!");
        NOT MESSAGE("Ember is held back… (50%)");
        MESSAGE("Wobbuffet used Overheat!");
        MESSAGE("Overheat is held back… (50%)");
        MESSAGE("Wobbuffet used Overheat!");
        NOT MESSAGE("Overheat is held back… (50%)");
    }
}

SINGLE_BATTLE_TEST("KJH: power cap, no message with 6 badges")
{
    GIVEN {
        WITH_CONFIG(B_KJH_POWER_CAP, TRUE);
        SetBadges(6);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_OVERHEAT); }
    } SCENE {
        MESSAGE("Wobbuffet used Overheat!");
        NOT MESSAGE("Overheat is held back… (100%)");
    }
}

SINGLE_BATTLE_TEST("KJH: power cap, a one-hit KO move can't be chosen before the 6th badge")
{
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_FISSURE) == EFFECT_OHKO);
        WITH_CONFIG(B_KJH_POWER_CAP, TRUE);
        SetBadges(5);
        PLAYER(SPECIES_WOBBUFFET) { Moves(MOVE_FISSURE, MOVE_CELEBRATE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_FISSURE, allowed: FALSE); MOVE(player, MOVE_CELEBRATE); }
    } SCENE {
        MESSAGE("Wobbuffet used Celebrate!");
    }
}

SINGLE_BATTLE_TEST("KJH: power cap, a one-hit KO move can be chosen from the 6th badge")
{
    GIVEN {
        WITH_CONFIG(B_KJH_POWER_CAP, TRUE);
        SetBadges(6);
        PLAYER(SPECIES_WOBBUFFET) { Moves(MOVE_FISSURE, MOVE_CELEBRATE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_FISSURE); }
    } SCENE {
        MESSAGE("Wobbuffet used Fissure!");
    }
}

SINGLE_BATTLE_TEST("KJH: power cap, Seismic Toss still deals the user's level")
{
    GIVEN {
        WITH_CONFIG(B_KJH_POWER_CAP, TRUE);
        SetBadges(0);
        PLAYER(SPECIES_WOBBUFFET) { Level(50); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SEISMIC_TOSS); }
    } SCENE {
        HP_BAR(opponent, damage: 50);
    }
}

SINGLE_BATTLE_TEST("KJH: power cap, Night Shade still deals the user's level")
{
    GIVEN {
        WITH_CONFIG(B_KJH_POWER_CAP, TRUE);
        SetBadges(0);
        PLAYER(SPECIES_WOBBUFFET) { Level(50); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_NIGHT_SHADE); }
    } SCENE {
        HP_BAR(opponent, damage: 50);
    }
}

AI_SINGLE_BATTLE_TEST("KJH: power cap, the AI doesn't choose a locked one-hit KO move")
{
    GIVEN {
        WITH_CONFIG(B_KJH_POWER_CAP, TRUE);
        SetBadges(0);
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY | AI_FLAG_RISKY);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { Moves(MOVE_FISSURE, MOVE_CELEBRATE); }
    } WHEN {
        TURN { EXPECT_MOVE(opponent, MOVE_CELEBRATE); }
        TURN { EXPECT_MOVE(opponent, MOVE_CELEBRATE); }
    }
}

// X-Scissor (80) held back to 60 must not get Technician's x1.5 for moves of 60 or less
SINGLE_BATTLE_TEST("KJH: power cap, Technician doesn't boost a held-back move", s16 damage)
{
    enum Ability ability;
    PARAMETRIZE { ability = ABILITY_SWARM; }
    PARAMETRIZE { ability = ABILITY_TECHNICIAN; }
    GIVEN {
        ASSUME(GetMovePower(MOVE_X_SCISSOR) == 80);
        WITH_CONFIG(B_KJH_POWER_CAP, TRUE);
        SetBadges(0);
        PLAYER(SPECIES_SCYTHER) { Ability(ability); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_X_SCISSOR); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_EQ(results[0].damage, results[1].damage);
    }
}
