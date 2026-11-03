// KJH (LV-12): move stars and the training notebook (include/kjh_move_stars.h).
#include "global.h"
#include "battle.h"
#include "battle_controllers.h"
#include "battle_message.h"
#include "battle_scripts.h"
#include "battle_setup.h"
#include "data.h"
#include "kjh_progression.h"
#include "config_changes.h"
#include "kjh_levelless.h"
#include "kjh_move_stars.h"
#include "kjh_power_cap.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "string_util.h"
#include "constants/characters.h"

// docs/LEVELLESS_DESIGN.md §12: the points each star needs, counted from 1 star, and the share of power it gives
static const u8 sPointsForStars[KJH_STARS_MAX + 1] = {[1] = 0, [2] = 10, [3] = 30, [4] = 60, [5] = 100};
static const u8 sStarsPercent[KJH_STARS_MAX + 1] = {[1] = 60, [2] = 70, [3] = 80, [4] = 90, [5] = 100};
#define LATE_MOVE_POINTS 30
#define MAX_STAR_MESSAGES (PARTY_SIZE * MAX_MON_MOVES)

// This battle's moves used by each of the player's Pokemon, and the messages left to show after a win
static EWRAM_DATA u16 sUsedMoves[PARTY_SIZE][MAX_MON_MOVES] = {0};
static EWRAM_DATA struct { u8 partyId; u8 stars; u16 move; } sStarMessages[MAX_STAR_MESSAGES] = {0};
static EWRAM_DATA u8 sStarMessageCount = 0;
static EWRAM_DATA u8 sStarMessageNext = 0; // a level-up move learned while with the team starts at 3 stars

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

u32 KJH_BattleMovePercent(u32 battler, enum Move move)
{
    u32 percent = KJH_PowerCapPercentNow();

    if (!GetConfig(B_KJH_MOVE_STARS) || (gBattleTypeFlags & BATTLE_TYPE_LINK)
     || GetBattlerTrainer(battler) != B_TRAINER_PLAYER)
        return percent;
    for (u32 i = 0; i < MAX_MON_MOVES; i++)
    {
        if (gBattleMons[battler].moves[i] == move) // not a move it calls (Metronome) or copies
            return KJH_StarsAndCapPercent(KJH_GetMoveStars(&GetBattlerMon(battler)->box, move), percent);
    }
    return percent;
}

void KJH_MoveStarsStartBattle(void)
{
    memset(sUsedMoves, 0, sizeof(sUsedMoves));
    sStarMessageCount = sStarMessageNext = 0;
}

void KJH_NoteMoveUsed(u32 battler, enum Move move)
{
    u16 *used;
    u32 i;

    if (!GetConfig(B_KJH_MOVE_STARS) || GetBattlerTrainer(battler) != B_TRAINER_PLAYER
     || gBattlerPartyIndexes[battler] >= PARTY_SIZE)
        return;
    for (i = 0; i < MAX_MON_MOVES && gBattleMons[battler].moves[i] != move; i++)
        ;
    if (i == MAX_MON_MOVES) // a move it calls (Metronome) or copies
        return;
    used = sUsedMoves[gBattlerPartyIndexes[battler]];
    for (i = 0; i < MAX_MON_MOVES && used[i] != MOVE_NONE; i++)
    {
        if (used[i] == move)
            return;
    }
    if (i < MAX_MON_MOVES)
        used[i] = move;
}

static bool32 KnowsMove(struct BoxPokemon *boxMon, enum Move move)
{
    for (u32 i = 0; i < MAX_MON_MOVES; i++)
    {
        if (GetBoxMonData(boxMon, MON_DATA_MOVE1 + i) == move)
            return TRUE;
    }
    return FALSE;
}

static enum KjhWinKind BattleWinKind(void)
{
    if (!(gBattleTypeFlags & BATTLE_TYPE_TRAINER))
        return KJH_WIN_WILD;
    if (TRAINER_BATTLE_PARAM.opponentA < TRAINERS_COUNT // not a special one (secret bases, tests)
     && KJH_IsBossTrainer(GetTrainerStructFromId(TRAINER_BATTLE_PARAM.opponentA), TRAINER_BATTLE_PARAM.opponentA))
        return KJH_WIN_BOSS;
    return KJH_WIN_TRAINER;
}

bool32 KJH_MoveStarsBattleWon(void)
{
    enum KjhWinKind kind;
    u32 points;

    if (!GetConfig(B_KJH_MOVE_STARS) || (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_FRONTIER)))
        return FALSE;
    kind = BattleWinKind();
    points = KJH_MovePointsForWin(kind, GetMonData(&gParties[B_TRAINER_OPPONENT_A][0], MON_DATA_TIER_MARK));
    sStarMessageCount = sStarMessageNext = 0;
    for (u32 partyId = 0; partyId < PARTY_SIZE; partyId++)
    {
        struct BoxPokemon *boxMon = &gParties[B_TRAINER_PLAYER][partyId].box;

        for (u32 i = 0; i < MAX_MON_MOVES && sUsedMoves[partyId][i] != MOVE_NONE; i++)
        {
            enum Move move = sUsedMoves[partyId][i];
            u32 before, after;

            if (!KnowsMove(boxMon, move)) // forgotten during the battle
                continue;
            before = KJH_GetMoveStars(boxMon, move);
            after = KJH_AddMovePoints(boxMon, move, points);
            if (after > before && sStarMessageCount < MAX_STAR_MESSAGES)
            {
                sStarMessages[sStarMessageCount].partyId = partyId;
                sStarMessages[sStarMessageCount].move = move;
                sStarMessages[sStarMessageCount].stars = after;
                sStarMessageCount++;
            }
        }
    }
    memset(sUsedMoves, 0, sizeof(sUsedMoves));
    return sStarMessageCount > 0;
}

void BS_KjhTryMoveGrewStronger(void)
{
    // battle_script_commands.c's NATIVE_ARGS(const u8 *doneInstr), which is local to it
    const struct __attribute__((packed)) { u8 opcode; void (*func)(void); const u8 *doneInstr; const u8 nextInstr[0]; }
        *const cmd = (const void *)gBattlescriptCurrInstr;
    u8 *stars = gBattleTextBuff3;

    if (sStarMessageNext >= sStarMessageCount)
    {
        gBattlescriptCurrInstr = cmd->doneInstr;
        return;
    }
    PREPARE_MON_NICK_BUFFER(gBattleTextBuff1, B_POSITION_PLAYER_LEFT, sStarMessages[sStarMessageNext].partyId);
    PREPARE_MOVE_BUFFER(gBattleTextBuff2, sStarMessages[sStarMessageNext].move);
    for (u32 i = 0; i < sStarMessages[sStarMessageNext].stars; i++)
        stars = StringCopy(stars, COMPOUND_STRING("{STAR}"));
    sStarMessageNext++;
    gBattlescriptCurrInstr = cmd->nextInstr;
}

u32 KJH_SummaryHeldBackMovePower(struct BoxPokemon *boxMon, enum Move move, u32 power)
{
    u32 percent = KJH_PowerCapPercentNow();
    u32 heldBackPower;

    if (GetConfig(B_KJH_MOVE_STARS))
        percent = KJH_StarsAndCapPercent(KJH_GetMoveStars(boxMon, move), percent);
    heldBackPower = KJH_CappedPower(power, percent);
    return heldBackPower < power ? heldBackPower : 0;
}

u8 *KJH_StringMoveStars(u8 *dest, struct BoxPokemon *boxMon, enum Move move)
{
    u32 points = KJH_GetMovePoints(boxMon, move);
    u32 stars = KJH_StarsFromPoints(points);

    for (u32 i = 0; i < stars; i++)
        dest = StringCopy(dest, COMPOUND_STRING("{STAR}"));
    if (stars == KJH_STARS_MAX)
        return dest;
    *dest++ = CHAR_SPACE;
    dest = ConvertIntToDecimalStringN(dest, points, STR_CONV_MODE_LEFT_ALIGN, 3);
    *dest++ = CHAR_SLASH;
    return ConvertIntToDecimalStringN(dest, KJH_PointsForStars(stars + 1), STR_CONV_MODE_LEFT_ALIGN, 3);
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
