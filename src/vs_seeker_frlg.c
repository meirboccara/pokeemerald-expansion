// KJH: the VS Seeker's rematches in Kanto. The table and the rules are FireRed's (pokefirered's src/vs_seeker.c):
// a trainer brings the next party they haven't lost with, but no further than the player's progress allows.
#include "global.h"
#include "battle_setup.h"
#include "event_data.h"
#include "vs_seeker_frlg.h"
#include "constants/opponents.h"

#define NO_PARTY_AT_TIER 0xFFFF // FireRed's SKIP: the trainer has no new party at that tier
#define FRLG_REMATCH_PARTIES 6
#define BITS_PER_BYTE 8

struct FrlgRematch
{
    u16 trainerIds[FRLG_REMATCH_PARTIES]; // The first battle, then tiers 1 to 5; 0 ends the row.
};

#include "data/vs_seeker_frlg.h"

enum FrlgRematchTier
{
    TIER_FIRST_BATTLE,
    TIER_VS_SEEKER,
    TIER_CELADON,
    TIER_FUCHSIA,
    TIER_LEAGUE,
    TIER_HOENN_LINK,
};

// The progress that unlocks each tier's party.
static const u16 sTierUnlockFlags[FRLG_REMATCH_PARTIES] =
{
    [TIER_VS_SEEKER]  = FLAG_GOT_VS_SEEKER,
    [TIER_CELADON]    = FLAG_WORLD_MAP_CELADON_CITY,
    [TIER_FUCHSIA]    = FLAG_WORLD_MAP_FUCHSIA_CITY,
    [TIER_LEAGUE]     = FLAG_SYS_GAME_CLEAR,
    [TIER_HOENN_LINK] = FLAG_IS_CHAMPION, // FireRed's FLAG_SYS_CAN_LINK_WITH_RS (linked with Hoenn at One Island).
};

// The "wants a rematch" state is one bit per row in the save's trainerRematches: Kanto's 221 rows don't fit
// expansion's one byte per row.
STATIC_ASSERT(ARRAY_COUNT(sFrlgRematches) <= BITS_PER_BYTE * MAX_REMATCH_ENTRIES, FrlgRematchesFitInSave);

s32 FrlgRematch_GetRow(u16 trainerId)
{
    if (trainerId == TRAINER_NONE || trainerId == NO_PARTY_AT_TIER)
        return -1;

    for (u32 row = 0; row < ARRAY_COUNT(sFrlgRematches); row++)
    {
        for (u32 tier = 0; tier < FRLG_REMATCH_PARTIES && sFrlgRematches[row].trainerIds[tier] != TRAINER_NONE; tier++)
        {
            if (sFrlgRematches[row].trainerIds[tier] == trainerId)
                return row;
        }
    }

    return -1;
}

// FireRed's GetNextAvailableRematchTrainer: the first tier not yet beaten, or the last tier once all are.
static u32 GetNextTier(const u16 *trainerIds)
{
    u32 tier;

    for (tier = TIER_VS_SEEKER; tier < FRLG_REMATCH_PARTIES; tier++)
    {
        if (trainerIds[tier] == TRAINER_NONE)
            return tier - 1;
        if (trainerIds[tier] != NO_PARTY_AT_TIER && !HasTrainerBeenFought(trainerIds[tier]))
            return tier;
    }

    return tier - 1;
}

// FireRed's TryGetRematchTrainerIdGivenGameState: a tier the player hasn't unlocked falls back to the highest
// lower tier that has a party (only that one step is checked, as in FireRed).
static u32 HoldBackToProgress(const u16 *trainerIds, u32 tier)
{
    if (tier == TIER_FIRST_BATTLE || FlagGet(sTierUnlockFlags[tier]))
        return tier;

    while (--tier != TIER_FIRST_BATTLE)
    {
        if (trainerIds[tier] != NO_PARTY_AT_TIER)
            return tier;
    }

    return TIER_FIRST_BATTLE;
}

u16 FrlgRematch_GetOpponent(u16 trainerId)
{
    s32 row = FrlgRematch_GetRow(trainerId);
    const u16 *trainerIds;

    if (row < 0)
        return 0;

    trainerIds = sFrlgRematches[row].trainerIds;
    return trainerIds[HoldBackToProgress(trainerIds, GetNextTier(trainerIds))];
}

// The byte of trainerRematches that holds a row's bit, and the bit.
static u8 *GetWaitByte(s32 row, u8 *bit)
{
    *bit = 1 << (row % BITS_PER_BYTE);
    return &gSaveBlock1Ptr->trainerRematches[row / BITS_PER_BYTE];
}

void FrlgRematch_SetWaiting(u16 trainerId)
{
    s32 row = FrlgRematch_GetRow(trainerId);
    u8 bit;

    if (row >= 0)
    {
        u8 *byte = GetWaitByte(row, &bit);
        *byte |= bit;
    }
}

bool32 FrlgRematch_IsWaiting(u16 trainerId)
{
    s32 row = FrlgRematch_GetRow(trainerId);
    u8 bit;

    if (row < 0)
        return FALSE;

    return (*GetWaitByte(row, &bit) & bit) != 0;
}

void FrlgRematch_ClearWaiting(u16 trainerId)
{
    s32 row = FrlgRematch_GetRow(trainerId);
    u8 bit;

    if (row >= 0)
    {
        u8 *byte = GetWaitByte(row, &bit);
        *byte &= ~bit;
    }
}
