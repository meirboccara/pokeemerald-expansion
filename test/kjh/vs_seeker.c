// KJH: the VS Seeker's rematches in Kanto (src/vs_seeker_frlg.c), with FireRed's table: Youngster Ben on Route 3
// has parties at tiers 1, 3 and 4 (tier 2 is skipped); tiers unlock with the VS Seeker, Celadon, Fuchsia, the
// League and the Hoenn link.
#include "global.h"
#include "battle_setup.h"
#include "event_data.h"
#include "vs_seeker_frlg.h"
#include "test/test.h"
#include "constants/opponents.h"

static const u16 sTierFlags[] =
{
    FLAG_GOT_VS_SEEKER,
    FLAG_WORLD_MAP_CELADON_CITY,
    FLAG_WORLD_MAP_FUCHSIA_CITY,
    FLAG_SYS_GAME_CLEAR,
    FLAG_IS_CHAMPION,
};

static const u16 sBenParties[] =
{
    TRAINER_YOUNGSTER_BEN,
    TRAINER_YOUNGSTER_BEN_2,
    TRAINER_YOUNGSTER_BEN_3,
    TRAINER_YOUNGSTER_BEN_4,
};

// Progress: how many tier flags are set, in order. Beaten: how many of Ben's parties the player has beaten.
static void SetUpBen(u32 progress, u32 beaten)
{
    for (u32 i = 0; i < ARRAY_COUNT(sTierFlags); i++)
    {
        if (i < progress)
        {
            FlagSet(sTierFlags[i]);
        }
        else
        {
            FlagClear(sTierFlags[i]);
        }
    }

    for (u32 i = 0; i < ARRAY_COUNT(sBenParties); i++)
    {
        if (i < beaten)
        {
            FlagSet(TRAINER_FLAGS_START + sBenParties[i]);
        }
        else
        {
            FlagClear(TRAINER_FLAGS_START + sBenParties[i]);
        }
    }

    memset(gSaveBlock1Ptr->trainerRematches, 0, sizeof(gSaveBlock1Ptr->trainerRematches));
}

TEST("KJH VS Seeker: Ben brings his second party once the player has the VS Seeker")
{
    SetUpBen(1, 1);
    EXPECT_EQ(FrlgRematch_GetOpponent(TRAINER_YOUNGSTER_BEN), TRAINER_YOUNGSTER_BEN_2);
}

TEST("KJH VS Seeker: Ben has no tier 2 party, so his third waits for Fuchsia")
{
    SetUpBen(2, 2);
    EXPECT_EQ(FrlgRematch_GetOpponent(TRAINER_YOUNGSTER_BEN), TRAINER_YOUNGSTER_BEN_2);
    SetUpBen(3, 2);
    EXPECT_EQ(FrlgRematch_GetOpponent(TRAINER_YOUNGSTER_BEN), TRAINER_YOUNGSTER_BEN_3);
}

TEST("KJH VS Seeker: Ben skips no party he hasn't beaten, even with all tiers unlocked")
{
    SetUpBen(5, 1);
    EXPECT_EQ(FrlgRematch_GetOpponent(TRAINER_YOUNGSTER_BEN), TRAINER_YOUNGSTER_BEN_2);
}

TEST("KJH VS Seeker: once all his parties are beaten, Ben keeps his last one")
{
    SetUpBen(5, 4);
    EXPECT_EQ(FrlgRematch_GetOpponent(TRAINER_YOUNGSTER_BEN), TRAINER_YOUNGSTER_BEN_4);
}

TEST("KJH VS Seeker: before the VS Seeker, Ben brings his first party back")
{
    SetUpBen(0, 1);
    EXPECT_EQ(FrlgRematch_GetOpponent(TRAINER_YOUNGSTER_BEN), TRAINER_YOUNGSTER_BEN);
}

TEST("KJH VS Seeker: a trainer with one party fights with it again")
{
    SetUpBen(5, 0);
    FlagSet(TRAINER_FLAGS_START + TRAINER_YOUNGSTER_CALVIN);
    EXPECT_EQ(FrlgRematch_GetOpponent(TRAINER_YOUNGSTER_CALVIN), TRAINER_YOUNGSTER_CALVIN);
}

TEST("KJH VS Seeker: gym leaders and others outside the table have no rematch")
{
    SetUpBen(5, 0);
    EXPECT_EQ(FrlgRematch_GetOpponent(TRAINER_LEADER_BROCK), 0);
    EXPECT_EQ(FrlgRematch_GetOpponent(TRAINER_NONE), 0);
}

TEST("KJH VS Seeker: a trainer waiting for a rematch is found by any of their parties")
{
    SetUpBen(1, 1);
    FrlgRematch_SetWaiting(TRAINER_YOUNGSTER_BEN);
    EXPECT(FrlgRematch_IsWaiting(TRAINER_YOUNGSTER_BEN));
    EXPECT(FrlgRematch_IsWaiting(TRAINER_YOUNGSTER_BEN_2));
    EXPECT(!FrlgRematch_IsWaiting(TRAINER_YOUNGSTER_CALVIN));
}

TEST("KJH VS Seeker: beating a rematch party clears only that trainer's wait")
{
    SetUpBen(1, 1);
    FrlgRematch_SetWaiting(TRAINER_YOUNGSTER_BEN);
    FrlgRematch_SetWaiting(TRAINER_YOUNGSTER_CALVIN);
    FrlgRematch_ClearWaiting(TRAINER_YOUNGSTER_BEN_2);
    EXPECT(!FrlgRematch_IsWaiting(TRAINER_YOUNGSTER_BEN));
    EXPECT(FrlgRematch_IsWaiting(TRAINER_YOUNGSTER_CALVIN));
}

TEST("KJH VS Seeker: the last trainer of Kanto's table has a wait of their own")
{
    SetUpBen(1, 0);
    FrlgRematch_SetWaiting(TRAINER_GENTLEMAN_CLIFFORD);
    EXPECT(FrlgRematch_IsWaiting(TRAINER_GENTLEMAN_CLIFFORD));
    EXPECT(!FrlgRematch_IsWaiting(TRAINER_PAINTER_EDNA));
    EXPECT(!FrlgRematch_IsWaiting(TRAINER_YOUNGSTER_BEN));
}
