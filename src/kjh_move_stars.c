// KJH (LV-12): move stars and the training notebook (include/kjh_move_stars.h).
#include "global.h"
#include "kjh_levelless.h"
#include "kjh_move_stars.h"
#include "kjh_power_cap.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"

// docs/LEVELLESS_DESIGN.md §12: the points each star needs, counted from 1 star, and the share of power it gives
static const u8 sPointsForStars[KJH_STARS_MAX + 1] = {[1] = 0, [2] = 10, [3] = 30, [4] = 60, [5] = 100};
static const u8 sStarsPercent[KJH_STARS_MAX + 1] = {[1] = 60, [2] = 70, [3] = 80, [4] = 90, [5] = 100};
#define LATE_MOVE_POINTS 30 // a level-up move learned while with the team starts at 3 stars

u32 KJH_StarsFromPoints(u32 points)
{
    u32 stars = 1;

    while (stars < KJH_STARS_MAX && points >= sPointsForStars[stars + 1])
        stars++;
    return stars;
}

u32 KJH_PointsForStars(u32 stars)
{
    return sPointsForStars[min(max(stars, 1), KJH_STARS_MAX)];
}

u32 KJH_StarsPercent(u32 stars)
{
    return sStarsPercent[min(max(stars, 1), KJH_STARS_MAX)];
}

u32 KJH_StarsAndCapPercent(u32 stars, u32 capPercent)
{
    return min(KJH_StarsPercent(stars), capPercent);
}

u32 KJH_StarredPower(u32 power, u32 stars)
{
    return KJH_CappedPower(power, KJH_StarsPercent(stars));
}

u32 KJH_MovePointsForWin(enum KjhWinKind kind, u32 tierMark)
{
    switch (kind)
    {
    case KJH_WIN_BOSS:
        return 5;
    case KJH_WIN_TRAINER:
        return 2;
    case KJH_WIN_WILD:
    default:
        if (tierMark == KJH_TIER_ALPHA)
            return 6;
        if (tierMark == KJH_TIER_LEADER)
            return 3;
        return 1;
    }
}

// A level-up move above the met level was unlocked while the Pokemon travelled with the team (a catch's met level is
// the team's level then); everything else (older level-up moves, TM, tutor and egg moves) starts at 1 star
u32 KJH_StartingMovePoints(struct BoxPokemon *boxMon, enum Move move)
{
    const struct LevelUpMove *learnset = GetSpeciesLevelUpLearnset(GetBoxMonData(boxMon, MON_DATA_SPECIES));
    u32 metLevel = GetBoxMonData(boxMon, MON_DATA_MET_LEVEL);

    for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
    {
        if (learnset[i].move == move && learnset[i].level > metLevel)
            return LATE_MOVE_POINTS;
    }
    return 0;
}

static struct KjhNotebookEntry *Notebook(void)
{
    return gPokemonStoragePtr->kjhNotebook;
}

static s32 FindEntry(u32 personality, enum Move move)
{
    struct KjhNotebookEntry *notebook = Notebook();

    for (u32 i = 0; i < KJH_NOTEBOOK_SIZE; i++)
    {
        if (notebook[i].move == MOVE_NONE)
            break;
        if (notebook[i].personality == personality && notebook[i].move == move)
            return i;
    }
    return -1;
}

u32 KJH_GetMovePoints(struct BoxPokemon *boxMon, enum Move move)
{
    s32 i = FindEntry(GetBoxMonData(boxMon, MON_DATA_PERSONALITY), move);

    if (i >= 0)
        return Notebook()[i].points;
    return KJH_StartingMovePoints(boxMon, move);
}

u32 KJH_GetMoveStars(struct BoxPokemon *boxMon, enum Move move)
{
    return KJH_StarsFromPoints(KJH_GetMovePoints(boxMon, move));
}

// The notebook is kept in order of use, the latest first: an entry that trains moves to the front, a new one pushes
// the last (unused the longest) out when the notebook is full
u32 KJH_AddMovePoints(struct BoxPokemon *boxMon, enum Move move, u32 points)
{
    struct KjhNotebookEntry *notebook = Notebook();
    struct KjhNotebookEntry entry;
    u32 personality = GetBoxMonData(boxMon, MON_DATA_PERSONALITY);
    s32 i = FindEntry(personality, move);

    if (i >= 0)
    {
        entry = notebook[i];
    }
    else
    {
        entry.personality = personality;
        entry.move = move;
        entry.points = KJH_StartingMovePoints(boxMon, move);
        entry.unused = 0;
        i = KJH_NOTEBOOK_SIZE - 1;  // the slot that frees up: the last one, empty or the oldest
    }
    entry.points = min(entry.points + points, KJH_MOVE_POINTS_MAX);
    memmove(&notebook[1], &notebook[0], i * sizeof(*notebook));
    notebook[0] = entry;
    return KJH_StarsFromPoints(entry.points);
}

void KJH_ClearNotebook(void)
{
    memset(Notebook(), 0, KJH_NOTEBOOK_SIZE * sizeof(struct KjhNotebookEntry));
}

u32 KJH_NotebookCount(void)
{
    u32 count = 0;

    while (count < KJH_NOTEBOOK_SIZE && Notebook()[count].move != MOVE_NONE)
        count++;
    return count;
}
