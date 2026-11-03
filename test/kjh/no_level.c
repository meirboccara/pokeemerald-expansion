// KJH (LV-4): no level shown; Bond in its place (src/kjh_bond.c).
#include "global.h"
#include "event_data.h"
#include "kjh_bond.h"
#include "string_util.h"
#include "test/test.h"

TEST("KJH: levels are hidden while the levels-free design is on")
{
    FlagSet(FLAG_KJH_LEVELLESS);
    EXPECT(KJH_HideLevels());
    FlagClear(FLAG_KJH_LEVELLESS);
    EXPECT(!KJH_HideLevels());
}

TEST("KJH: the Bond label replaces the level")
{
    u8 label[16];

    KJH_BufferBondLabel(label, KJH_BondToFriendship(12));
    EXPECT_EQ(StringCompare(label, COMPOUND_STRING("BOND 12")), 0);
    KJH_BufferBondLabel(label, 0);
    EXPECT_EQ(StringCompare(label, COMPOUND_STRING("BOND 1")), 0);
}

// LV-4, second pass (2026-11-03): the screens the first pass missed.
#include "daycare.h"
#include "dexnav.h"
#include "frontier_util.h"
#include "hall_of_fame.h"
#include "menu_specialized.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "constants/battle_frontier.h"
#include "constants/frontier_util.h"

static EWRAM_DATA struct DaycareMon sNoLevelDaycareMon = {0};

static bool32 HasLevelSymbol(const u8 *str)
{
    for (; *str != EOS; str++)
    {
        if (str[0] == CHAR_EXTRA_SYMBOL && str[1] == CHAR_LV_2)
            return TRUE;
    }
    return FALSE;
}

TEST("KJH: the DexNav search window shows no level while levels are hidden")
{
    u8 text[16];

    FlagClear(FLAG_KJH_LEVELLESS);
    DexNavBufferMonLevel(text, 12);
    EXPECT_EQ(StringCompare(text, COMPOUND_STRING("{LV}. 12")), 0);
    FlagSet(FLAG_KJH_LEVELLESS);
    DexNavBufferMonLevel(text, 12);
    EXPECT_EQ(text[0], EOS);
}

TEST("KJH: the Day Care list shows the Bond, not the level, while levels are hidden")
{
    u8 text[16];
    struct Pokemon mon;

    CreateMon(&mon, SPECIES_PIDGEY, 12, 0, OTID_STRUCT_PRESET(0));
    SetMonData(&mon, MON_DATA_FRIENDSHIP, &(u8){KJH_BondToFriendship(7)});
    sNoLevelDaycareMon.mon = mon.box;
    sNoLevelDaycareMon.steps = 0;
    FlagClear(FLAG_KJH_LEVELLESS);
    DaycareBufferMonLevel(text, &sNoLevelDaycareMon);
    EXPECT_EQ(StringCompare(text, COMPOUND_STRING("{LV}12")), 0);
    FlagSet(FLAG_KJH_LEVELLESS);
    DaycareBufferMonLevel(text, &sNoLevelDaycareMon);
    EXPECT_EQ(StringCompare(text, COMPOUND_STRING("BOND 7")), 0);
}

TEST("KJH: a Hall of Fame card shows no level while levels are hidden")
{
    u8 text[16];

    FlagClear(FLAG_KJH_LEVELLESS);
    HallOfFameBufferMonLevel(text, 45);
    EXPECT_EQ(StringCompare(text, COMPOUND_STRING("Lv. 45")), 0);
    FlagSet(FLAG_KJH_LEVELLESS);
    HallOfFameBufferMonLevel(text, 45);
    EXPECT_EQ(text[0], EOS);
}

TEST("KJH: the condition menu's name line shows no level while levels are hidden")
{
    u8 name[64], location[64];

    ZeroPlayerPartyMons();
    CreateMon(&gParties[B_TRAINER_PLAYER][0], SPECIES_PIDGEY, 12, 0, OTID_STRUCT_PRESET(0));
    FlagClear(FLAG_KJH_LEVELLESS);
    GetConditionMenuMonNameAndLocString(location, name, TOTAL_BOXES_COUNT, 0, 0, 2, FALSE);
    EXPECT(HasLevelSymbol(name));
    FlagSet(FLAG_KJH_LEVELLESS);
    GetConditionMenuMonNameAndLocString(location, name, TOTAL_BOXES_COUNT, 0, 0, 2, FALSE);
    EXPECT(!HasLevelSymbol(name));
}

TEST("KJH: the Battle Frontier's level mode is always the Open Level in the levels-free game")
{
    FlagSet(FLAG_KJH_LEVELLESS);
    gSpecialVar_0x8004 = FRONTIER_UTIL_FUNC_SET_DATA;
    gSpecialVar_0x8005 = FRONTIER_DATA_LVL_MODE;
    gSpecialVar_0x8006 = FRONTIER_LVL_50;
    CallFrontierUtilFunc();
    EXPECT_EQ((u32)gSaveBlock2Ptr->frontier.lvlMode, FRONTIER_LVL_OPEN);
    gSpecialVar_0x8006 = FRONTIER_LVL_TENT; // the Battle Tents keep their own mode
    CallFrontierUtilFunc();
    EXPECT_EQ((u32)gSaveBlock2Ptr->frontier.lvlMode, FRONTIER_LVL_TENT);
}

TEST("KJH: Frontier opponents take the team's level, with no Open Level floor, in the levels-free game")
{
    ZeroPlayerPartyMons();
    CreateMon(&gParties[B_TRAINER_PLAYER][0], SPECIES_PIDGEY, 34, 0, OTID_STRUCT_PRESET(0));
    FlagSet(FLAG_KJH_LEVELLESS);
    EXPECT_EQ(GetFrontierEnemyMonLevel(FRONTIER_LVL_OPEN), 34);
    FlagClear(FLAG_KJH_LEVELLESS);
    EXPECT_EQ(GetFrontierEnemyMonLevel(FRONTIER_LVL_OPEN), 60); // expansion: Open Level opponents are at least 60
}
