// KJH (LV-10): the move library (src/kjh_move_library.c) and expansion's relearner reading it.
#include "global.h"
#include "event_data.h"
#include "item.h"
#include "kjh_bond.h"
#include "kjh_levelless.h"
#include "kjh_move_library.h"
#include "pokemon.h"
#include "party_menu.h"
#include "test/test.h"
#include "constants/items.h"

static void Create(struct Pokemon *mon, u32 species, u32 level)
{
    CreateMon(mon, species, level, 0, OTID_STRUCT_PRESET(0));
}

// Cascaded hardware timers avoid the 16-bit BENCHMARK timer wrapping on the old scan.
static void StartLibraryTimer(void)
{
    VBlankIntrWait();
    REG_TM2CNT = 0;
    REG_TM3CNT = 0;
    REG_TM3CNT_H = TIMER_ENABLE | TIMER_COUNTUP;
    REG_TM2CNT_H = TIMER_ENABLE | TIMER_64CLK;
}

static u32 StopLibraryTimer(void)
{
    REG_TM2CNT_H = 0;
    REG_TM3CNT_H = 0;
    return ((u32)REG_TM3CNT_L << 16) | REG_TM2CNT_L;
}

TEST("KJH: growth empty-slot review latency stays below four frames")
{
    u32 ticks;
    ZeroPlayerPartyMons();
    Create(&gPlayerParty[0], SPECIES_RAICHU, 5);
    for (u32 slot = 0; slot < MAX_MON_MOVES; slot++)
        SetMonMoveSlot(&gPlayerParty[0], MOVE_NONE, slot);
    FlagClear(FLAG_SYS_GAME_CLEAR);
    gSpecialVar_0x8004 = 0;
    gSpecialVar_0x8005 = 5;
    gSpecialVar_0x8006 = 5;
    StartLibraryTimer();
    bool32 result = KJH_BufferNextNewLibraryMoves();
    ticks = StopLibraryTimer();
    Test_MgbaPrintf("growth review: %d ticks (64 GBA cycles/tick)", ticks);
    EXPECT(result);
    EXPECT_LT(ticks, 17556); // four 280896-cycle GBA frames
}

// The per-move scan KJH_GetUnknownLibraryMoves replaced: the reference for its result.
static u32 ScanLibraryMoves(struct BoxPokemon *boxMon, u16 *moves, u32 maxMoves)
{
    u32 count = 0;
    for (u32 move = 1; move < MOVES_COUNT && count < maxMoves; move++)
    {
        bool32 known = FALSE;
        for (u32 slot = 0; slot < MAX_MON_MOVES; slot++)
            if (GetBoxMonData(boxMon, MON_DATA_MOVE1 + slot) == move)
                known = TRUE;
        if (!known && KJH_IsMoveInLibrary(boxMon, move))
            moves[count++] = move;
    }
    return count;
}

static void ExpectSameMoves(const u16 *a, u32 aCount, const u16 *b, u32 bCount)
{
    EXPECT_EQ(aCount, bCount);
    for (u32 i = 0; i < aCount && i < bCount; i++)
        EXPECT_EQ(a[i], b[i]);
}

TEST("KJH: unknown library moves match the per-move scan: pre-evolution level-up moves, known moves left out")
{
    struct Pokemon mon;
    u16 expected[100], actual[100];
    u32 expectedCount, actualCount, scanTicks, collectTicks;

    Create(&mon, SPECIES_RAICHU, 50);
    FlagClear(FLAG_SYS_GAME_CLEAR);
    SetMonMoveSlot(&mon, MOVE_THUNDER_SHOCK, 0);
    StartLibraryTimer();
    expectedCount = ScanLibraryMoves(&mon.box, expected, ARRAY_COUNT(expected));
    scanTicks = StopLibraryTimer();
    StartLibraryTimer();
    actualCount = KJH_GetUnknownLibraryMoves(&mon.box, actual, ARRAY_COUNT(actual));
    collectTicks = StopLibraryTimer();
    Test_MgbaPrintf("per-move scan: %d ticks, learnset collection: %d ticks", scanTicks, collectTicks);
    EXPECT_GT(expectedCount, 0);
    ExpectSameMoves(expected, expectedCount, actual, actualCount);
    EXPECT_LT(collectTicks * 100, scanTicks);
}

TEST("KJH: unknown library moves match the per-move scan: egg moves, a TM in the bag, a tutor that has taught")
{
    struct Pokemon mon;
    u16 expected[100], actual[100];
    u32 expectedCount, friendship = KJH_BondToFriendship(KJH_LIBRARY_EGG_MOVES_BOND);

    Create(&mon, SPECIES_SNORLAX, 30);
    SetMonData(&mon, MON_DATA_FRIENDSHIP, &friendship);
    FlagClear(FLAG_SYS_GAME_CLEAR);
    ASSUME(CanLearnTeachableMove(SPECIES_SNORLAX, MOVE_EARTHQUAKE));
    ASSUME(CanLearnTeachableMove(SPECIES_SNORLAX, MOVE_BODY_SLAM));
    AddBagItem(GetTMHMItemIdFromMoveId(MOVE_EARTHQUAKE), 1);
    FlagSet(FLAG_TUTOR_BODY_SLAM);
    expectedCount = ScanLibraryMoves(&mon.box, expected, ARRAY_COUNT(expected));
    ExpectSameMoves(expected, expectedCount, actual, KJH_GetUnknownLibraryMoves(&mon.box, actual, ARRAY_COUNT(actual)));
    RemoveBagItem(GetTMHMItemIdFromMoveId(MOVE_EARTHQUAKE), 1);
    FlagClear(FLAG_TUTOR_BODY_SLAM);
}

TEST("KJH: unknown library moves keep the per-move scan's lowest move IDs when the list is full")
{
    struct Pokemon mon;
    u16 expected[100], actual[100];
    u32 expectedCount;

    Create(&mon, SPECIES_RAICHU, 50);
    FlagSet(FLAG_SYS_GAME_CLEAR);
    expectedCount = ScanLibraryMoves(&mon.box, expected, ARRAY_COUNT(expected));
    ASSUME(expectedCount > 3);
    ExpectSameMoves(expected, 3, actual, KJH_GetUnknownLibraryMoves(&mon.box, actual, 3));
    ExpectSameMoves(expected, expectedCount, actual, KJH_GetUnknownLibraryMoves(&mon.box, actual, ARRAY_COUNT(actual)));
    FlagClear(FLAG_SYS_GAME_CLEAR);
}

static u32 FirstLevelUpMoveAbove(u32 species, u32 level, u32 *learnedAt)
{
    const struct LevelUpMove *learnset = GetSpeciesLevelUpLearnset(species);
    for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
    {
        if (learnset[i].level > level)
        {
            *learnedAt = learnset[i].level;
            return learnset[i].move;
        }
    }
    return MOVE_NONE;
}

TEST("KJH: the library uses the peak level, so a lower level takes no move away; all moves after the League")
{
    struct Pokemon mon;
    u32 learnedAt = 0, move, peak;

    Create(&mon, SPECIES_CHARMANDER, 10);
    move = FirstLevelUpMoveAbove(SPECIES_CHARMANDER, 10, &learnedAt);
    ASSUME(move != MOVE_NONE);
    FlagClear(FLAG_SYS_GAME_CLEAR);
    EXPECT_EQ(KJH_LibraryLevel(&mon.box), 10);
    EXPECT(!KJH_IsMoveInLibrary(&mon.box, move));
    peak = learnedAt;
    SetMonData(&mon, MON_DATA_PEAK_LEVEL, &peak);
    EXPECT_EQ(KJH_LibraryLevel(&mon.box), learnedAt);
    EXPECT(KJH_IsMoveInLibrary(&mon.box, move));
    FlagSet(FLAG_SYS_GAME_CLEAR);
    EXPECT_EQ(KJH_LibraryLevel(&mon.box), MAX_LEVEL);
    FlagClear(FLAG_SYS_GAME_CLEAR);
}

TEST("KJH: an evolved Pokemon keeps its pre-evolutions' level-up moves")
{
    struct Pokemon mon;
    const struct LevelUpMove *pre = GetSpeciesLevelUpLearnset(SPECIES_PICHU);

    Create(&mon, SPECIES_RAICHU, 50);
    FlagClear(FLAG_SYS_GAME_CLEAR);
    for (u32 i = 0; pre[i].move != LEVEL_UP_MOVE_END && pre[i].level <= 50; i++)
        EXPECT(KJH_IsMoveInLibrary(&mon.box, pre[i].move));
}

TEST("KJH: egg moves join the library at Bond 8 (peak)")
{
    struct Pokemon mon;
    const u16 *eggMoves = GetSpeciesEggMoves(SPECIES_CHARMANDER);
    u32 friendship;

    ASSUME(eggMoves[0] != MOVE_UNAVAILABLE);
    Create(&mon, SPECIES_CHARMANDER, 5);
    friendship = KJH_BondToFriendship(KJH_LIBRARY_EGG_MOVES_BOND - 1);
    SetMonData(&mon, MON_DATA_FRIENDSHIP, &friendship);
    EXPECT(!KJH_HasEggMovesInLibrary(&mon.box));
    EXPECT(!KJH_IsMoveInLibrary(&mon.box, eggMoves[0]));
    friendship = KJH_BondToFriendship(KJH_LIBRARY_EGG_MOVES_BOND);
    SetMonData(&mon, MON_DATA_FRIENDSHIP, &friendship);
    friendship = KJH_BOND_MIN_FRIENDSHIP; // the peak keeps it
    SetMonData(&mon, MON_DATA_FRIENDSHIP, &friendship);
    EXPECT(KJH_HasEggMovesInLibrary(&mon.box));
    EXPECT(KJH_IsMoveInLibrary(&mon.box, eggMoves[0]));
}

TEST("KJH: a TM in the bag and a tutor that has taught put their move in the library")
{
    struct Pokemon mon;

    Create(&mon, SPECIES_SNORLAX, 30);
    ASSUME(GetTMHMItemIdFromMoveId(MOVE_EARTHQUAKE) != ITEM_NONE);
    ASSUME(CanLearnTeachableMove(SPECIES_SNORLAX, MOVE_EARTHQUAKE));
    ASSUME(CanLearnTeachableMove(SPECIES_SNORLAX, MOVE_BODY_SLAM));
    RemoveBagItem(GetTMHMItemIdFromMoveId(MOVE_EARTHQUAKE), 1);
    EXPECT(!KJH_IsMoveInLibrary(&mon.box, MOVE_EARTHQUAKE));
    AddBagItem(GetTMHMItemIdFromMoveId(MOVE_EARTHQUAKE), 1);
    EXPECT(KJH_IsMoveInLibrary(&mon.box, MOVE_EARTHQUAKE));
    RemoveBagItem(GetTMHMItemIdFromMoveId(MOVE_EARTHQUAKE), 1);

    FlagClear(FLAG_TUTOR_BODY_SLAM);
    EXPECT(!KJH_IsTutorMoveInLibrary(MOVE_BODY_SLAM));
    FlagSet(FLAG_TUTOR_BODY_SLAM);
    EXPECT(KJH_IsMoveInLibrary(&mon.box, MOVE_BODY_SLAM));
    FlagClear(FLAG_TUTOR_BODY_SLAM);
    EXPECT(!KJH_IsTutorMoveInLibrary(MOVE_HEADBUTT)); // no Kanto tutor teaches it
}

TEST("KJH: a level rise lists the level-up moves it unlocked, pre-evolutions' too, each once")
{
    u16 moves[16];
    u32 count = KJH_GetNewLevelUpMoves(SPECIES_CHARMELEON, 1, 100, moves, ARRAY_COUNT(moves));
    const struct LevelUpMove *learnset = GetSpeciesLevelUpLearnset(SPECIES_CHARMELEON);

    EXPECT_GT(count, 0);
    for (u32 i = 0; i < count; i++)
    {
        for (u32 j = i + 1; j < count; j++)
            EXPECT_NE(moves[i], moves[j]);
    }
    EXPECT_EQ(KJH_GetNewLevelUpMoves(SPECIES_CHARMELEON, 100, 100, moves, ARRAY_COUNT(moves)), 0);
    for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
    {
        if (learnset[i].level > 1)
        {
            u32 n = KJH_GetNewLevelUpMoves(SPECIES_CHARMELEON, learnset[i].level - 1, learnset[i].level, moves, ARRAY_COUNT(moves));
            bool32 found = FALSE;
            for (u32 j = 0; j < n; j++)
                found |= moves[j] == learnset[i].move;
            EXPECT(found || KJH_GetNewLevelUpMoves(SPECIES_CHARMANDER, 0, learnset[i].level - 1, moves, ARRAY_COUNT(moves)) > 0);
            break;
        }
    }
}

TEST("KJH: a move swapped in keeps the PP percentage of the move it replaces")
{
    EXPECT_EQ(KJH_PpAfterSwap(10, 35, 35), 10); // full stays full
    EXPECT_EQ(KJH_PpAfterSwap(10, 0, 35), 0);
    EXPECT_EQ(KJH_PpAfterSwap(20, 5, 10), 10);  // half
    EXPECT_EQ(KJH_PpAfterSwap(5, 1, 3), 1);     // rounded down
}

TEST("KJH: moves are locked from the League's first room until the run ends")
{
    KJH_UnlockMoves();
    EXPECT(!KJH_AreMovesLocked());
    KJH_LockMoves();
    EXPECT(KJH_AreMovesLocked());
    KJH_UnlockMoves();
    EXPECT(!KJH_AreMovesLocked());
}
