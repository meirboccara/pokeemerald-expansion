// KJH: wild packs (ENG-6, src/kjh_pack_rules.c and src/kjh_pack.c), after docs/PACKS.md in the KJH repo.
#include "global.h"
#include "battle.h"
#include "kjh_pack.h"
#include "pokemon.h"
#include "test/battle.h"

TEST("KJH: a wild Pokemon that wins the 1 in 20 roll leads a pack, 3 levels up")
{
    EXPECT_EQ(KJH_PackWildEncounterLevel(SPECIES_PIDGEY, 10), 10);
    SET_RNG(RNG_KJH_PACK_LEADER, 0); // outcome 0: it leads a pack
    EXPECT_EQ(KJH_PackWildEncounterLevel(SPECIES_PIDGEY, 10), 10 + KJH_PACK_LEADER_LEVEL_BONUS);
    EXPECT_EQ(KJH_PackWildEncounterLevel(SPECIES_ARTICUNO, 50), 50); // never a legendary
    KJH_PackSetNextEncounter(FALSE);
}

TEST("KJH: legendaries, mythicals, Ultra Beasts and Unown never lead a pack")
{
    EXPECT(KJH_PackSpeciesAllowed(SPECIES_PIDGEY));
    EXPECT(KJH_PackSpeciesAllowed(SPECIES_DRATINI));
    EXPECT(!KJH_PackSpeciesAllowed(SPECIES_NONE));
    EXPECT(!KJH_PackSpeciesAllowed(SPECIES_UNOWN));
    EXPECT(!KJH_PackSpeciesAllowed(SPECIES_ARTICUNO));
    EXPECT(!KJH_PackSpeciesAllowed(SPECIES_MEWTWO));
    EXPECT(!KJH_PackSpeciesAllowed(SPECIES_MEW));
    EXPECT(!KJH_PackSpeciesAllowed(SPECIES_RAIKOU));
    EXPECT(!KJH_PackSpeciesAllowed(SPECIES_LATIAS));
    EXPECT(!KJH_PackSpeciesAllowed(SPECIES_DEOXYS));
}

TEST("KJH: a pack leader is 3 levels up, never above 100")
{
    EXPECT_EQ(KJH_PackLeaderLevel(10), 13);
    EXPECT_EQ(KJH_PackLeaderLevel(98), MAX_LEVEL);
    EXPECT_EQ(KJH_PackLeaderLevel(MAX_LEVEL), MAX_LEVEL);
}

TEST("KJH: a pack leader has half its species' catch rate, never below 1")
{
    EXPECT_EQ(KJH_PackCatchRate(255, TRUE), 127);
    EXPECT_EQ(KJH_PackCatchRate(45, TRUE), 22);
    EXPECT_EQ(KJH_PackCatchRate(1, TRUE), 1);
    EXPECT_EQ(KJH_PackCatchRate(45, FALSE), 45);
}

TEST("KJH: a pack leader gives 4 times the Exp., a helper it called 2 times")
{
    EXPECT_EQ(KJH_PackExp(100, KJH_PACK_ROLE_LEADER), 400);
    EXPECT_EQ(KJH_PackExp(100, KJH_PACK_ROLE_LEADER_HELPER), 200);
    EXPECT_EQ(KJH_PackExp(100, KJH_PACK_ROLE_NONE), 100);
}

TEST("KJH: a pack leader has perfect IVs, another wild Pokemon keeps its own")
{
    struct Pokemon mon;

    CreateMonWithIVs(&mon, SPECIES_PIDGEY, 10, 0, OTID_STRUCT_PLAYER_ID, 0);
    KJH_PackSetNextEncounter(FALSE);
    KJH_PackFinishWildMon(&mon);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_SPEED_IV), 0);

    KJH_PackSetNextEncounter(TRUE);
    KJH_PackFinishWildMon(&mon);
    for (enum Stat stat = STAT_HP; stat < NUM_STATS; stat++)
        EXPECT_EQ(GetMonData(&mon, MON_DATA_HP_IV + stat), KJH_PACK_LEADER_IV);
    KJH_PackSetNextEncounter(FALSE);
}

WILD_BATTLE_TEST("KJH: a pack leader's battle opens with \"It leads a pack!\"")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_PIDGEY);
        KJH_PackSetNextEncounter(TRUE);
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); }
    } SCENE {
        MESSAGE("You encountered a wild Pidgey! It leads a pack!");
    } THEN {
        EXPECT(KJH_PackIsLeaderBattle());
        EXPECT(KJH_PackIsLeader(B_BATTLER_1));
    }
}

WILD_BATTLE_TEST("KJH: an ordinary wild Pokemon doesn't lead a pack")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_PIDGEY);
        KJH_PackSetNextEncounter(FALSE);
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); }
    } SCENE {
        NONE_OF { MESSAGE("You encountered a wild Pidgey! It leads a pack!"); }
        MESSAGE("You encountered a wild Pidgey!");
    } THEN {
        EXPECT(!KJH_PackIsLeaderBattle());
    }
}

SINGLE_BATTLE_TEST("KJH: a trainer's Pokemon never leads a pack")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_PIDGEY);
        KJH_PackSetNextEncounter(TRUE);
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); }
    } THEN {
        EXPECT(!KJH_PackIsLeaderBattle());
        EXPECT(!KJH_PackIsLeader(B_BATTLER_1));
    }
}

WILD_BATTLE_TEST("KJH: knocking out a pack leader gives 4 times the Exp.", s32 exp)
{
    bool32 leader = FALSE;

    PARAMETRIZE { leader = TRUE; }
    PARAMETRIZE { leader = FALSE; }

    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Level(20); }
        OPPONENT(SPECIES_CATERPIE) { Level(10); HP(1); }
        KJH_PackSetNextEncounter(leader);
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        MESSAGE("The wild Caterpie fainted!");
        EXPERIENCE_BAR(player, captureGainedExp: &results[i].exp);
    } FINALLY {
        EXPECT_MUL_EQ(results[1].exp, Q_4_12(4.0), results[0].exp); // results[0]: the leader
    }
}

TEST("KJH: a leader calls more the more it is hurt, never on the first turn, half as often with no free slot")
{
    EXPECT_EQ(KJH_PackCallChance(TRUE, 0, TRUE, TRUE, 100, 100), 0);
    EXPECT_EQ(KJH_PackCallChance(TRUE, 0, TRUE, FALSE, 100, 100), KJH_PACK_CALL_LEADER_HEALTHY);
    EXPECT_EQ(KJH_PackCallChance(TRUE, 0, TRUE, FALSE, 50, 100), KJH_PACK_CALL_LEADER_HURT);
    EXPECT_EQ(KJH_PackCallChance(TRUE, 0, TRUE, FALSE, 25, 100), KJH_PACK_CALL_LEADER_DESPERATE);
    EXPECT_EQ(KJH_PackCallChance(TRUE, 1, FALSE, FALSE, 25, 100), KJH_PACK_CALL_LEADER_DESPERATE / 2);
    EXPECT_EQ(KJH_PackCallChance(TRUE, KJH_PACK_MAX_HELPERS, TRUE, FALSE, 25, 100), 0);
}

TEST("KJH: another wild Pokemon calls now and then, from the first turn")
{
    EXPECT_EQ(KJH_PackCallChance(FALSE, 0, TRUE, TRUE, 100, 100), KJH_PACK_CALL_ORDINARY);
    EXPECT_EQ(KJH_PackCallChance(FALSE, 0, FALSE, FALSE, 10, 100), KJH_PACK_CALL_ORDINARY);
    EXPECT_EQ(KJH_PackCallChance(FALSE, KJH_PACK_MAX_HELPERS, TRUE, FALSE, 100, 100), 0);
    EXPECT_EQ(KJH_PackAnswerChance(TRUE), KJH_PACK_ANSWER_LEADER);
    EXPECT_EQ(KJH_PackAnswerChance(FALSE), KJH_PACK_ANSWER_ORDINARY);
}

TEST("KJH: a helper is at the pack's level or up to 2 below, never under 1")
{
    EXPECT_EQ(KJH_PackHelperLevel(13, TRUE, 0), 10);
    EXPECT_EQ(KJH_PackHelperLevel(13, TRUE, 2), 8);
    EXPECT_EQ(KJH_PackHelperLevel(10, FALSE, 1), 9);
    EXPECT_EQ(KJH_PackHelperLevel(2, FALSE, 2), 1);
}

TEST("KJH: the player's first healthy Pokemon that isn't fighting steps in, listed second")
{
    bool8 usable[PARTY_SIZE] = {TRUE, FALSE, TRUE, TRUE, FALSE, FALSE};
    bool8 alone[PARTY_SIZE] = {TRUE, FALSE, FALSE, FALSE, FALSE, FALSE};
    u8 order[PARTY_SIZE / 2] = {0x01, 0x23, 0x45};

    EXPECT_EQ(KJH_PackPartnerSlot(usable, 0), 2);
    EXPECT_EQ(KJH_PackPartnerSlot(usable, 2), 0);
    EXPECT_EQ(KJH_PackPartnerSlot(alone, 0), KJH_PACK_NO_PARTNER);
    EXPECT_EQ(KJH_PackEmptySlot(alone, 0), 1);

    KJH_PackPutPartnerSecond(order, 2);
    EXPECT_EQ(order[0], 0x02);
    EXPECT_EQ(order[1], 0x13);
    EXPECT_EQ(order[2], 0x45);
}

WILD_BATTLE_TEST("KJH: a wild Pokemon that calls for help spends its turn, even when no one answers")
{
    u32 speed = 0;

    PARAMETRIZE { speed = 1; }   // the player moves after the call
    PARAMETRIZE { speed = 200; } // the player moves first: the call comes before it all the same

    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Speed(speed); }
        OPPONENT(SPECIES_PIDGEY) { Speed(50); Moves(MOVE_TACKLE); }
        KJH_PackSetNextEncounter(FALSE);
    } WHEN {
        // The calls are rolled at the turn's first move, whoever's it is: a rigged roll applies to its own action
        TURN { MOVE(player, MOVE_SCRATCH, WITH_RNG(RNG_KJH_PACK_CALL, 0)); MOVE(opponent, MOVE_TACKLE, WITH_RNG(RNG_KJH_PACK_CALL, 0)); }
    } SCENE {
        MESSAGE("The wild Pidgey called for help!");
        MESSAGE("But no one answered!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        NOT ANIMATION(ANIM_TYPE_MOVE, MOVE_TACKLE, opponent);
    } THEN {
        EXPECT_EQ(KJH_PackHelpers(), 0);
    }
}

WILD_BATTLE_TEST("KJH: an ordinary wild Pokemon usually doesn't call for help")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_PIDGEY) { Moves(MOVE_TACKLE); }
        KJH_PackSetNextEncounter(FALSE);
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_TACKLE); }
    } SCENE {
        NONE_OF { MESSAGE("The wild Pidgey called for help!"); }
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TACKLE, opponent);
    }
}
