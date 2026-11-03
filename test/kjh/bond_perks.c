// KJH (LV-6): Bond perks (src/kjh_bond.c): +2% stats at Bond 5, +5% at 15 (at least +1), snapping out of confusion
// or infatuation at 10 and shaking off a status at 19, for the player's and trainers' Pokemon; none in hard mode.
#include "global.h"
#include "difficulty.h"
#include "kjh_bond.h"
#include "pokemon.h"
#include "test/battle.h"

static void StatsAt(struct Pokemon *mon, u32 bond, u32 *stats)
{
    u32 friendship = KJH_BondToFriendship(bond);
    SetMonData(mon, MON_DATA_FRIENDSHIP, &friendship);
    CalculateMonStats(mon);
    for (u32 i = 0; i < NUM_STATS; i++)
        stats[i] = GetMonData(mon, MON_DATA_MAX_HP + i);
}

TEST("KJH: Bond 5 gives +2% to every stat, HP too, Bond 15 +5% instead, at least +1; Bond 4 nothing")
{
    struct Pokemon mon;
    u32 base[NUM_STATS], small[NUM_STATS], big[NUM_STATS], below[NUM_STATS];

    CreateMon(&mon, SPECIES_MEWTWO, 100, 0, OTID_STRUCT_PRESET(0));
    StatsAt(&mon, 1, base);
    StatsAt(&mon, 5, small);
    StatsAt(&mon, 15, big);
    StatsAt(&mon, 4, below); // Bond went down: the ongoing perk is gone
    for (u32 i = 0; i < NUM_STATS; i++)
    {
        EXPECT_EQ(small[i], base[i] + max(base[i] * 2 / 100, 1));
        EXPECT_EQ(big[i], base[i] + max(base[i] * 5 / 100, 1));
        EXPECT_EQ(below[i], base[i]);
    }
}

TEST("KJH: a small stat gets at least +1 at Bond 5")
{
    struct Pokemon mon;
    u32 base[NUM_STATS], small[NUM_STATS];

    CreateMon(&mon, SPECIES_MAGIKARP, 5, 0, OTID_STRUCT_PRESET(0));
    StatsAt(&mon, 1, base);
    StatsAt(&mon, 5, small);
    for (u32 i = 0; i < NUM_STATS; i++)
        EXPECT_EQ(small[i], base[i] + 1);
}

TEST("KJH: hard mode turns the Bond perks off")
{
    struct Pokemon mon;
    u32 base[NUM_STATS], big[NUM_STATS];
    enum DifficultyLevel level = GetCurrentDifficultyLevel();

    CreateMon(&mon, SPECIES_MEWTWO, 100, 0, OTID_STRUCT_PRESET(0));
    SetCurrentDifficultyLevel(DIFFICULTY_HARD);
    EXPECT(!KJH_BondPerksOn());
    StatsAt(&mon, 1, base);
    StatsAt(&mon, 20, big);
    SetCurrentDifficultyLevel(level);
    for (u32 i = 0; i < NUM_STATS; i++)
        EXPECT_EQ(big[i], base[i]);
}

SINGLE_BATTLE_TEST("KJH: at Bond 19 a Pokemon shakes off a status at the end of a turn; at 18 it doesn't")
{
    u32 bond;
    PARAMETRIZE { bond = 19; }
    PARAMETRIZE { bond = 18; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Friendship(KJH_BondToFriendship(bond)); Status1(STATUS1_BURN); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { }
    } SCENE {
        if (bond == 19)
            MESSAGE("Wobbuffet cured its burn through sheer determination so you wouldn't worry!");
        else
            NOT MESSAGE("Wobbuffet cured its burn through sheer determination so you wouldn't worry!");
    } THEN {
        EXPECT_EQ(player->status1, bond == 19 ? 0 : STATUS1_BURN);
    }
}

SINGLE_BATTLE_TEST("KJH: at Bond 10 a Pokemon snaps out of confusion at the end of a turn; at 9 it doesn't")
{
    u32 bond;
    PARAMETRIZE { bond = 10; }
    PARAMETRIZE { bond = 9; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Friendship(KJH_BondToFriendship(bond)); Speed(1); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(2); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_CONFUSE_RAY); MOVE(player, MOVE_CELEBRATE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CONFUSE_RAY, opponent);
        if (bond == 10)
            MESSAGE("Wobbuffet snapped out of its confusion!");
        else
            NOT MESSAGE("Wobbuffet snapped out of its confusion!");
    }
}

SINGLE_BATTLE_TEST("KJH: a trainer's Pokemon gets the Bond perks too")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { Friendship(MAX_FRIENDSHIP); Status1(STATUS1_BURN); }
    } WHEN {
        TURN { }
    } SCENE {
        MESSAGE("The opposing Wobbuffet cured its burn through sheer determination so you wouldn't worry!");
    }
}

WILD_BATTLE_TEST("KJH: a wild Pokemon gets no Bond perks")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { Friendship(MAX_FRIENDSHIP); Status1(STATUS1_BURN); }
    } WHEN {
        TURN { }
    } SCENE {
        NOT MESSAGE("The wild Wobbuffet cured its burn through sheer determination so you wouldn't worry!");
    } THEN {
        EXPECT_EQ(opponent->status1, STATUS1_BURN);
    }
}
