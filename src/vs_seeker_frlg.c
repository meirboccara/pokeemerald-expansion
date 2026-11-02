// KJH: the VS Seeker's rematches in Kanto. The table and the rules are FireRed's (pokefirered's src/vs_seeker.c):
// a trainer brings the next party they haven't lost with, but no further than the player's progress allows.
#include "global.h"
#include "battle_setup.h"
#include "event_data.h"
#include "vs_seeker_frlg.h"
#include "constants/opponents.h"

#define SKIP 0xFFFF
#define FRLG_REMATCH_PARTIES 6

struct FrlgRematch
{
    u16 trainerIds[FRLG_REMATCH_PARTIES]; // the first battle, then tiers 1 to 5; 0 ends the row
};

#include "data/vs_seeker_frlg.h"

// The progress that unlocks each tier's party (tier 0 is the first battle).
static const u16 sTierUnlockFlags[FRLG_REMATCH_PARTIES] =
{
    [1] = FLAG_GOT_VS_SEEKER,
    [2] = FLAG_WORLD_MAP_CELADON_CITY,
    [3] = FLAG_WORLD_MAP_FUCHSIA_CITY,
    [4] = FLAG_SYS_GAME_CLEAR,
    [5] = FLAG_IS_CHAMPION, // FireRed's FLAG_SYS_CAN_LINK_WITH_RS (linked with Hoenn at One Island)
};

// The "wants a rematch" state is one bit per row in the save's trainerRematches: Kanto's 221 rows don't fit
// expansion's one byte per row.
STATIC_ASSERT(ARRAY_COUNT(sFrlgRematches) <= 8 * MAX_REMATCH_ENTRIES, FrlgRematchesFitInSave);

static s32 FindRow(u16 trainerId)
{
    u32 i, j;

    if (trainerId == TRAINER_NONE || trainerId == SKIP)
        return -1;
    for (i = 0; i < ARRAY_COUNT(sFrlgRematches); i++)
    {
        for (j = 0; j < FRLG_REMATCH_PARTIES && sFrlgRematches[i].trainerIds[j] != TRAINER_NONE; j++)
        {
            if (sFrlgRematches[i].trainerIds[j] == trainerId)
                return i;
        }
    }
    return -1;
}

// FireRed's GetNextAvailableRematchTrainer: the first tier not yet beaten, or the last tier once all are.
static u32 GetNextTier(const u16 *trainerIds)
{
    u32 tier;

    for (tier = 1; tier < FRLG_REMATCH_PARTIES; tier++)
    {
        if (trainerIds[tier] == TRAINER_NONE)
            return tier - 1;
        if (trainerIds[tier] == SKIP || HasTrainerBeenFought(trainerIds[tier]))
            continue;
        return tier;
    }
    return tier - 1;
}

// FireRed's TryGetRematchTrainerIdGivenGameState: a tier the player hasn't unlocked falls back to the highest
// lower tier that has a party (only that one step is checked, as in FireRed).
static u32 HoldBackToProgress(const u16 *trainerIds, u32 tier)
{
    if (tier == 0 || FlagGet(sTierUnlockFlags[tier]))
        return tier;
    while (--tier != 0)
    {
        if (trainerIds[tier] != SKIP)
            return tier;
    }
    return 0;
}

s32 FrlgRematch_GetRow(u16 trainerId)
{
    return FindRow(trainerId);
}

u16 FrlgRematch_GetOpponent(u16 trainerId)
{
    s32 row = FindRow(trainerId);
    const u16 *trainerIds;

    if (row < 0)
        return 0;
    trainerIds = sFrlgRematches[row].trainerIds;
    return trainerIds[HoldBackToProgress(trainerIds, GetNextTier(trainerIds))];
}

void FrlgRematch_SetWaiting(u16 trainerId)
{
    s32 row = FindRow(trainerId);

    if (row >= 0)
        gSaveBlock1Ptr->trainerRematches[row / 8] |= 1 << (row % 8);
}

bool32 FrlgRematch_IsWaiting(u16 trainerId)
{
    s32 row = FindRow(trainerId);

    if (row < 0)
        return FALSE;
    return (gSaveBlock1Ptr->trainerRematches[row / 8] >> (row % 8)) & 1;
}

void FrlgRematch_ClearWaiting(u16 trainerId)
{
    s32 row = FindRow(trainerId);

    if (row >= 0)
        gSaveBlock1Ptr->trainerRematches[row / 8] &= ~(1 << (row % 8));
}
