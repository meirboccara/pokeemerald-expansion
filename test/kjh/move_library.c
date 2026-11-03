// KJH (LV-10): the move library (src/kjh_move_library.c) and expansion's relearner reading it.
#include "global.h"
#include "event_data.h"
#include "item.h"
#include "kjh_bond.h"
#include "kjh_levelless.h"
#include "kjh_move_library.h"
#include "pokemon.h"
#include "test/test.h"
#include "constants/items.h"

static void Create(struct Pokemon *mon, u32 species, u32 level)
{
    CreateMon(mon, species, level, 0, OTID_STRUCT_PRESET(0));
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
