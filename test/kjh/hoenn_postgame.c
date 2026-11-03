// KJH (ENG-9/ENG-10 follow-ups, Hoenn): Emerald's C code that asks "is the game cleared?" for Hoenn things reads
// Hoenn's League (FLAG_HOENN_GAME_CLEAR), not Kanto's (FireRed's FLAG_SYS_GAME_CLEAR, always set first in KJH).
// And Hoenn's rematch state: in the FireRed build the save's trainerRematches holds Kanto's VS Seeker bits
// (src/vs_seeker_frlg.c), so Hoenn's trainers neither read nor write it: they never offer a rematch.
#include "global.h"
#include "battle_setup.h"
#include "event_data.h"
#include "gym_leader_rematch.h"
#include "match_call.h"
#include "pokenav.h"
#include "string_util.h"
#include "strings.h"
#include "vs_seeker_frlg.h"
#include "test/test.h"
#include "constants/opponents.h"
#include "constants/rematches.h"

#if IS_FRLG

static EWRAM_DATA u8 sGot[1000] = {0};
static EWRAM_DATA u8 sWant[1000] = {0};

static void KantoClearOnly(void)
{
    FlagSet(FLAG_SYS_GAME_CLEAR);
    FlagClear(FLAG_HOENN_GAME_CLEAR);
}

static void ClearRematchState(void)
{
    memset(gSaveBlock1Ptr->trainerRematches, 0, sizeof(gSaveBlock1Ptr->trainerRematches));
}

TEST("KJH Hoenn post-game: Mom's Match Call waits for Hoenn's League, not Kanto's")
{
    FlagSet(FLAG_DEFEATED_PETALBURG_GYM);
    KantoClearOnly();
    MatchCall_GetMessage(MC_HEADER_MOM, sGot);
    StringExpandPlaceholders(sWant, MatchCall_Text_Mom3);
    EXPECT_NE(StringCompare(sGot, sWant), 0);

    FlagSet(FLAG_HOENN_GAME_CLEAR);
    MatchCall_GetMessage(MC_HEADER_MOM, sGot);
    EXPECT_EQ(StringCompare(sGot, sWant), 0);

    FlagClear(FLAG_HOENN_GAME_CLEAR);
    FlagClear(FLAG_DEFEATED_PETALBURG_GYM);
}

TEST("KJH Hoenn post-game: Hoenn's Gym Leader rematches wait for Hoenn's League, not Kanto's")
{
    KantoClearOnly();
    EXPECT_EQ(GetCurrentGymLeaderRematchLevel(), 0);
    FlagSet(FLAG_HOENN_GAME_CLEAR);
    EXPECT_NE(GetCurrentGymLeaderRematchLevel(), 0);
    FlagClear(FLAG_HOENN_GAME_CLEAR);
}

TEST("KJH Hoenn rematches: a Hoenn Match Call rematch request leaves Kanto's VS Seeker state alone")
{
    u32 i;

    ClearRematchState();
    SetTrainerFlag(TRAINER_ROSE_1); // Rose is gRematchTable's row 0: her byte is Kanto's rows 0-7
    UpdateRematchIfDefeated(REMATCH_ROSE);
    for (i = 0; i < ARRAY_COUNT(gSaveBlock1Ptr->trainerRematches); i++)
        EXPECT_EQ(gSaveBlock1Ptr->trainerRematches[i], 0);
    ClearTrainerFlag(TRAINER_ROSE_1);
}

TEST("KJH Hoenn rematches: Kanto's VS Seeker state never makes a Hoenn trainer want a rematch")
{
    ClearRematchState();
    memset(gSaveBlock1Ptr->trainerRematches, 0xFF, 28); // every Kanto row waits (221 rows, one bit each)
    SetTrainerFlag(TRAINER_ROSE_1);
    EXPECT_EQ(GetActiveTrainerRematches(REMATCH_ROSE), 0);
    EXPECT_EQ(GetHoennRematchState(REMATCH_ROSE), 0);
    EXPECT_EQ(ShouldTryRematchBattleForTrainerId(TRAINER_ROSE_1), FALSE);
    EXPECT_EQ(ShouldTryRematchBattleForTrainerId(TRAINER_ROXANNE_1), FALSE);
    ClearTrainerFlag(TRAINER_ROSE_1);
    ClearRematchState();
}

TEST("KJH Hoenn rematches: Kanto's VS Seeker still marks Kanto's trainers")
{
    ClearRematchState();
    FrlgRematch_SetWaiting(TRAINER_YOUNGSTER_BEN);
    EXPECT(FrlgRematch_IsWaiting(TRAINER_YOUNGSTER_BEN));
    EXPECT(ShouldTryRematchBattleForTrainerId(TRAINER_YOUNGSTER_BEN));
    ClearRematchState();
}

#endif // IS_FRLG
