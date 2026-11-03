// KJH: wild Leaders and Alphas in the levels-free game (LV-15, src/kjh_pack.c): the Alpha's level and IVs, a
// Leader's IVs, the tier marks, the Alpha's intro and that it never calls for help. ENG-6's own rules stay without
// the levels-free flag (test/kjh/packs.c).
#include "global.h"
#include "event_data.h"
#include "kjh_levelless.h"
#include "kjh_pack.h"
#include "pokemon.h"
#include "test/battle.h"
#include "test/test.h"

static u32 CountIvsAtLeast(struct Pokemon *mon, u32 iv)
{
    u32 count = 0;
    for (enum Stat stat = STAT_HP; stat < NUM_STATS; stat++)
    {
        if (GetMonData(mon, MON_DATA_HP_IV + stat) >= iv)
        {
            count++;
        }
    }

    return count;
}

TEST("KJH: an Alpha is 5 levels up, a Leader's IVs are at least 20 with two at 31")
{
    u8 ivs[NUM_STATS] = {0, 25, 3, 12, 19, 31}; // HP, Atk, Def, Speed, Sp. Atk, Sp. Def
    EXPECT_EQ(KJH_AlphaLevel(10), 15);
    EXPECT_EQ(KJH_AlphaLevel(98), 100);
    KJH_LeaderIvs(ivs, STAT_HP, STAT_SPEED);
    EXPECT_EQ(ivs[STAT_HP], 31);
    EXPECT_EQ(ivs[STAT_SPEED], 31);
    EXPECT_EQ(ivs[STAT_ATK], 25);
    EXPECT_EQ(ivs[STAT_DEF], 20);
    EXPECT_EQ(ivs[STAT_SPATK], 20);
    EXPECT_EQ(ivs[STAT_SPDEF], 31); // a 31 it already had stays
}

TEST("KJH: in the levels-free game an Alpha has all IVs 31 and keeps its mark")
{
    struct Pokemon mon;
    FlagSet(FLAG_KJH_LEVELLESS);
    CreateMonWithIVs(&mon, SPECIES_ONIX, 15, 0, OTID_STRUCT_PLAYER_ID, 0);
    KJH_PackSetNextEncounterAlpha();
    KJH_PackFinishWildMon(&mon);
    EXPECT_EQ(CountIvsAtLeast(&mon, 31), NUM_STATS);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_TIER_MARK), KJH_TIER_ALPHA);
    KJH_PackSetNextEncounter(FALSE);
}

TEST("KJH: in the levels-free game a Leader's IVs are its own, raised, and it keeps its mark")
{
    struct Pokemon mon;
    FlagSet(FLAG_KJH_LEVELLESS);
    CreateMonWithIVs(&mon, SPECIES_PIDGEY, 10, 0, OTID_STRUCT_PLAYER_ID, 0);
    KJH_PackSetNextEncounter(TRUE);
    KJH_PackFinishWildMon(&mon);
    EXPECT_EQ(CountIvsAtLeast(&mon, KJH_LEADER_MIN_IV), NUM_STATS);
    EXPECT_EQ(CountIvsAtLeast(&mon, 31), 2);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_TIER_MARK), KJH_TIER_LEADER);
    // Without the levels-free game, ENG-6's leader: perfect IVs, no mark
    FlagClear(FLAG_KJH_LEVELLESS);
    CreateMonWithIVs(&mon, SPECIES_PIDGEY, 10, 0, OTID_STRUCT_PLAYER_ID, 0);
    KJH_PackSetNextEncounter(TRUE);
    KJH_PackFinishWildMon(&mon);
    EXPECT_EQ(CountIvsAtLeast(&mon, 31), NUM_STATS);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_TIER_MARK), KJH_TIER_REGULAR);
    KJH_PackSetNextEncounter(FALSE);
}

TEST("KJH: a wild Pokemon that may lead a pack is an Alpha 1 time in 100 in the levels-free game")
{
    FlagSet(FLAG_KJH_LEVELLESS);
    SET_RNG(RNG_KJH_ALPHA, 0); // outcome 0: an Alpha
    EXPECT_EQ(KJH_PackWildEncounterLevel(SPECIES_PIDGEY, 10), 15);
    KJH_PackSetNextEncounter(FALSE);
    SET_RNG(RNG_KJH_ALPHA, 1);
    SET_RNG(RNG_KJH_PACK_LEADER, 0); // not an Alpha, a Leader
    EXPECT_EQ(KJH_PackWildEncounterLevel(SPECIES_PIDGEY, 10), 13);
    KJH_PackSetNextEncounter(FALSE);
    SET_RNG(RNG_KJH_ALPHA, 0);
    EXPECT_EQ(KJH_PackWildEncounterLevel(SPECIES_MEWTWO, 70), 70); // legendaries are never Alphas in the wild
    KJH_PackSetNextEncounter(FALSE);
}

WILD_BATTLE_TEST("KJH: an Alpha's battle opens with \"It looks enormous!\" and it never calls for help")
{
    GIVEN {
        FLAG_SET(FLAG_KJH_LEVELLESS);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_PIDGEY) { Moves(MOVE_TACKLE); }
        KJH_PackSetNextEncounterAlpha();
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE, WITH_RNG(RNG_KJH_PACK_CALL, 0)); MOVE(opponent, MOVE_TACKLE, WITH_RNG(RNG_KJH_PACK_CALL, 0)); }
        TURN { MOVE(player, MOVE_CELEBRATE, WITH_RNG(RNG_KJH_PACK_CALL, 0)); MOVE(opponent, MOVE_TACKLE, WITH_RNG(RNG_KJH_PACK_CALL, 0)); }
    } SCENE {
        MESSAGE("You encountered an ALPHA Pidgey! It looks enormous!");
        NONE_OF { MESSAGE("The wild Pidgey called for help!"); }
    } THEN {
        EXPECT(KJH_PackIsAlphaBattle());
        EXPECT(KJH_PackIsAlpha(B_BATTLER_1));
        EXPECT(!KJH_PackIsLeaderBattle());
        EXPECT_EQ(KJH_PackHelpers(), 0);
    }
}

TEST("KJH: a starter given and a legendary caught are Alphas, other Pokemon aren't")
{
    struct Pokemon mon;
    FlagSet(FLAG_KJH_LEVELLESS);
    ZeroPlayerPartyMons();
    CreateMonWithIVs(&mon, SPECIES_BULBASAUR, 5, 0, OTID_STRUCT_PLAYER_ID, 0);
    GiveScriptedMonToPlayer(&mon, PARTY_SIZE);
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_TIER_MARK), KJH_TIER_ALPHA);
    EXPECT_EQ(CountIvsAtLeast(&gParties[B_TRAINER_PLAYER][0], 31), NUM_STATS);
    CreateMonWithIVs(&mon, SPECIES_EEVEE, 25, 0, OTID_STRUCT_PLAYER_ID, 0);
    GiveScriptedMonToPlayer(&mon, PARTY_SIZE);
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][1], MON_DATA_TIER_MARK), KJH_TIER_REGULAR);
    CreateMonWithIVs(&mon, SPECIES_MEWTWO, 70, 0, OTID_STRUCT_PLAYER_ID, 0);
    ASSUME(GiveCapturedMonToPlayer(&mon) == MON_GIVEN_TO_PARTY);
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][2], MON_DATA_TIER_MARK), KJH_TIER_ALPHA);
    CreateMonWithIVs(&mon, SPECIES_PIDGEY, 5, 0, OTID_STRUCT_PLAYER_ID, 0);
    ASSUME(GiveCapturedMonToPlayer(&mon) == MON_GIVEN_TO_PARTY);
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][3], MON_DATA_TIER_MARK), KJH_TIER_REGULAR);
    // Without the levels-free game, nobody is an Alpha
    FlagClear(FLAG_KJH_LEVELLESS);
    CreateMonWithIVs(&mon, SPECIES_CHARMANDER, 5, 0, OTID_STRUCT_PLAYER_ID, 0);
    GiveScriptedMonToPlayer(&mon, PARTY_SIZE);
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][4], MON_DATA_TIER_MARK), KJH_TIER_REGULAR);
}

WILD_BATTLE_TEST("KJH: higher tiers are harder to catch: a Leader half the catch rate, an Alpha a third")
{
    u32 tier = 0;
    PARAMETRIZE { tier = 0; }
    PARAMETRIZE { tier = 1; }
    PARAMETRIZE { tier = 2; }
    GIVEN {
        FLAG_SET(FLAG_KJH_LEVELLESS);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_PIDGEY);
        if (tier == 2)
            KJH_PackSetNextEncounterAlpha();
        else
            KJH_PackSetNextEncounter(tier == 1);
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); }
    } THEN {
        // Pidgey's catch rate is 255
        if (tier == 2)
            EXPECT_EQ(KJH_PackBattlerCatchRate(255, B_BATTLER_1), 85);
        else if (tier == 1)
            EXPECT_EQ(KJH_PackBattlerCatchRate(255, B_BATTLER_1), 127);
        else
            EXPECT_EQ(KJH_PackBattlerCatchRate(255, B_BATTLER_1), 255);
    }
}
