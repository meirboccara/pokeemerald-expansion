// KJH (LV-5): Bond 1-20, gains, losses and the floor (src/kjh_bond.c, docs/LEVELLESS_DESIGN.md §3).
#include "global.h"
#include "clock.h"
#include "event_data.h"
#include "fake_rtc.h"
#include "kjh_bond.h"
#include "kjh_clock.h"
#include "kjh_levelless.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "test/battle.h"
#include "test/overworld_script.h"

static void SetFriendship(struct Pokemon *mon, u32 friendship)
{
    SetMonData(mon, MON_DATA_FRIENDSHIP, &friendship);
}

static struct Pokemon *GiveWobbuffet(u32 friendship)
{
    ZeroPlayerPartyMons();
    RUN_OVERWORLD_SCRIPT(givemon SPECIES_WOBBUFFET, 20;);
    SetFriendship(&gPlayerParty[0], friendship);
    return &gPlayerParty[0];
}

TEST("KJH: Bond runs from 1 at friendship 70 to 20 at 255, about 10 points a step")
{
    EXPECT_EQ(KJH_FriendshipToBond(0), 1);
    EXPECT_EQ(KJH_FriendshipToBond(70), 1);
    EXPECT_EQ(KJH_FriendshipToBond(79), 1);
    EXPECT_EQ(KJH_FriendshipToBond(80), 2);
    EXPECT_EQ(KJH_FriendshipToBond(254), 19);
    EXPECT_EQ(KJH_FriendshipToBond(255), 20);
    for (u32 bond = 1; bond <= KJH_BOND_MAX; bond++)
    {
        EXPECT_EQ(KJH_FriendshipToBond(KJH_BondToFriendship(bond)), bond);
        if (bond > 1)
            EXPECT_EQ(KJH_FriendshipToBond(KJH_BondToFriendship(bond) - 1), bond - 1);
    }
}

TEST("KJH: gains add friendship points, x1.5 with a Soothe Bell; the peak Bond follows")
{
    struct Pokemon *mon = GiveWobbuffet(100);

    KJH_GainBond(mon, KJH_BOND_GAIN_FOE);
    EXPECT_EQ(GetMonData(mon, MON_DATA_FRIENDSHIP), 102);
    SetMonData(mon, MON_DATA_HELD_ITEM, &(u16){ITEM_SOOTHE_BELL});
    KJH_GainBond(mon, KJH_BOND_GAIN_FOE);
    EXPECT_EQ(GetMonData(mon, MON_DATA_FRIENDSHIP), 105);
    KJH_GainBond(mon, 255);
    EXPECT_EQ(GetMonData(mon, MON_DATA_FRIENDSHIP), MAX_FRIENDSHIP);
    EXPECT_EQ(GetMonData(mon, MON_DATA_PEAK_BOND), KJH_BOND_MAX);
    KJH_LoseBond(mon, KJH_BOND_LOSS_WHITEOUT);
    EXPECT_EQ(GetMonData(mon, MON_DATA_PEAK_BOND), KJH_BOND_MAX); // kept for good
    EXPECT_EQ(KJH_GetPeakBond(mon), KJH_BOND_MAX);
}

TEST("KJH: faints and whiteouts go down to Bond 1, no lower")
{
    struct Pokemon *mon = GiveWobbuffet(100);

    AdjustFriendship(mon, FRIENDSHIP_EVENT_FAINT_SMALL);
    EXPECT_EQ(GetMonData(mon, MON_DATA_FRIENDSHIP), 80);
    AdjustFriendship(mon, FRIENDSHIP_EVENT_FAINT_FIELD_PSN);
    EXPECT_EQ(GetMonData(mon, MON_DATA_FRIENDSHIP), KJH_BOND_MIN_FRIENDSHIP);
    SetFriendship(mon, 150);
    KJH_BondOnWhiteOut();
    EXPECT_EQ(GetMonData(mon, MON_DATA_FRIENDSHIP), 100);
    KJH_BondOnWhiteOut();
    EXPECT_EQ(GetMonData(mon, MON_DATA_FRIENDSHIP), KJH_BOND_MIN_FRIENDSHIP);
}

TEST("KJH: levels, the League and TMs give no Bond; steps do")
{
    struct Pokemon *mon = GiveWobbuffet(100);

    AdjustFriendship(mon, FRIENDSHIP_EVENT_GROW_LEVEL);
    AdjustFriendship(mon, FRIENDSHIP_EVENT_LEARN_TMHM);
    EXPECT_EQ(GetMonData(mon, MON_DATA_FRIENDSHIP), 100);
    AdjustFriendship(mon, FRIENDSHIP_EVENT_WALKING); // called every KJH_BOND_WALK_STEPS steps
    EXPECT_EQ(GetMonData(mon, MON_DATA_FRIENDSHIP), 101);
}

TEST("KJH: the Day Care and the PC never take a Pokemon below half its peak Bond")
{
    struct Pokemon *mon = GiveWobbuffet(MAX_FRIENDSHIP); // peak 20: the floor is Bond 10
    u32 floor = KJH_BondToFriendship(10);

    EXPECT_EQ(KJH_BondFloorFriendship(20), floor);
    EXPECT_EQ(KJH_BondFloorFriendship(19), floor);  // half of 19, rounded up
    KJH_BondOnDaycarePickup(mon);
    EXPECT_EQ(GetMonData(mon, MON_DATA_FRIENDSHIP), MAX_FRIENDSHIP - KJH_BOND_LOSS_DAYCARE);
    for (u32 i = 0; i < 20; i++)
        KJH_BondOnDaycarePickup(mon);
    EXPECT_EQ(GetMonData(mon, MON_DATA_FRIENDSHIP), floor);
}

TEST("KJH: each in-game week in the PC loses 20 friendship, down to half the peak Bond")
{
    struct BoxPokemon *boxed = GetBoxedMonPtr(0, 0);
    struct Pokemon *mon = GiveWobbuffet(MAX_FRIENDSHIP);

    *boxed = mon->box;
    KJH_StartClock();
    FakeRtc_AdvanceTimeBy(6, 0, 0, 0); // 6 days: not a week yet
    DoTimeBasedEvents();
    EXPECT_EQ(GetBoxMonData(boxed, MON_DATA_FRIENDSHIP), MAX_FRIENDSHIP);
    FakeRtc_AdvanceTimeBy(1, 0, 0, 0); // day 7: a new week
    DoTimeBasedEvents();
    EXPECT_EQ(GetBoxMonData(boxed, MON_DATA_FRIENDSHIP), MAX_FRIENDSHIP - KJH_BOND_LOSS_PC_WEEK);
    FakeRtc_AdvanceTimeBy(70, 0, 0, 0); // ten more weeks
    DoTimeBasedEvents();
    EXPECT_EQ(GetBoxMonData(boxed, MON_DATA_FRIENDSHIP), KJH_BondToFriendship(10));
    EXPECT_EQ(GetBoxMonData(boxed, MON_DATA_PEAK_BOND), KJH_BOND_MAX);
    ZeroBoxMonData(boxed);
}

TEST("KJH: the starter begins at Bond 5")
{
    GiveWobbuffet(70);
    KJH_SetStarterBond();
    EXPECT_EQ(KJH_GetBond(&gPlayerParty[0]), KJH_STARTER_BOND);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_PEAK_BOND), KJH_STARTER_BOND);
}

SINGLE_BATTLE_TEST("KJH: a won battle gives each Pokemon that fought +2 per foe down and +1 for the win")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Friendship(100); }
        PLAYER(SPECIES_WYNAUT) { Friendship(100); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_TACKLE); }
    } SCENE {
        MESSAGE("The opposing Wobbuffet fainted!");
    } THEN {
        EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_FRIENDSHIP), 100 + KJH_BOND_GAIN_FOE + KJH_BOND_GAIN_WIN);
        EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][1], MON_DATA_FRIENDSHIP), 100); // never sent out
    }
}

SINGLE_BATTLE_TEST("KJH: a Pokemon that faints in battle loses 20 friendship")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Friendship(150); HP(1); }
        PLAYER(SPECIES_WYNAUT) { Friendship(100); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(1); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_TACKLE); SEND_OUT(player, 1); }
        TURN { MOVE(player, MOVE_TACKLE); }
    } SCENE {
        MESSAGE("Wobbuffet fainted!");
        MESSAGE("The opposing Wobbuffet fainted!");
    } THEN {
        // fainted: -20; it had faced the foe, which fell later: +2; it was sent out in a won battle: +1
        EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_FRIENDSHIP),
                  150 - KJH_BOND_LOSS_FAINT + KJH_BOND_GAIN_FOE + KJH_BOND_GAIN_WIN);
        EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][1], MON_DATA_FRIENDSHIP), 100 + KJH_BOND_GAIN_FOE + KJH_BOND_GAIN_WIN);
    }
}
