// KJH (ENG-9, Hoenn): Hoenn's flags, variables and trainers in a FireRed build. Expansion's native Hoenn maps run
// Emerald's own scripts; their flags and variables get their own ranges in SaveBlock3 (src/event_data.c), apart from
// FireRed's (SaveBlock1) and Johto's, and Emerald's trainers their own ids after Johto's.
#include "global.h"
#include "battle_setup.h"
#include "data.h"
#include "event_data.h"
#include "field_move.h"
#include "kjh_team_level.h"
#include "string_util.h"
#include "test/test.h"
#include "constants/field_move.h"
#include "constants/map_groups.h"
#include "constants/opponents.h"
#include "constants/region_map_sections.h"
#include "constants/trainers.h"

#if IS_FRLG

struct KjhSaveSnapshot
{
    u8 kantoFlags[NUM_FLAG_BYTES];
    u16 kantoVars[VARS_COUNT];
    u8 johtoFlags[sizeof(gSaveBlock3Ptr->kjhFlags)];
    u16 johtoVars[ARRAY_COUNT(gSaveBlock3Ptr->kjhVars)];
};

static EWRAM_DATA struct KjhSaveSnapshot sSnapshot = {0}; // not in IWRAM: the test build's IWRAM is tight

static void TakeSnapshot(void)
{
    memcpy(sSnapshot.kantoFlags, gSaveBlock1Ptr->flags, sizeof(sSnapshot.kantoFlags));
    memcpy(sSnapshot.kantoVars, gSaveBlock1Ptr->vars, sizeof(sSnapshot.kantoVars));
    memcpy(sSnapshot.johtoFlags, gSaveBlock3Ptr->kjhFlags, sizeof(sSnapshot.johtoFlags));
    memcpy(sSnapshot.johtoVars, gSaveBlock3Ptr->kjhVars, sizeof(sSnapshot.johtoVars));
}

// Kanto's (SaveBlock1) and Johto's (SaveBlock3) flags and variables are as they were at the snapshot.
static bool32 KantoAndJohtoUnchanged(void)
{
    return memcmp(sSnapshot.kantoFlags, gSaveBlock1Ptr->flags, sizeof(sSnapshot.kantoFlags)) == 0
        && memcmp(sSnapshot.kantoVars, gSaveBlock1Ptr->vars, sizeof(sSnapshot.kantoVars)) == 0
        && memcmp(sSnapshot.johtoFlags, gSaveBlock3Ptr->kjhFlags, sizeof(sSnapshot.johtoFlags)) == 0
        && memcmp(sSnapshot.johtoVars, gSaveBlock3Ptr->kjhVars, sizeof(sSnapshot.johtoVars)) == 0;
}

static bool32 IsHoennFlag(u32 flag)
{
    return flag >= HOENN_FLAGS_START && flag < HOENN_FLAGS_END;
}

// The emulator test reads them there (kjh_tools/test/emu_expansion_hoenn.py, SAVE3_HOENN_VARS / _FLAGS): change both.
TEST("KJH: Hoenn's variables and flags sit at the end of SaveBlock3")
{
    EXPECT_EQ(offsetof(struct SaveBlock3, hoennVars), 524);
    EXPECT_EQ(offsetof(struct SaveBlock3, hoennFlags), 834);
}

TEST("KJH: Hoenn's story flags are real flags in SaveBlock3, apart from Kanto's and Johto's")
{
    // Emerald-only flags were 0 (no flag) in a FireRed build
    EXPECT(IsHoennFlag(FLAG_RESCUED_BIRCH));
    EXPECT(IsHoennFlag(FLAG_HIDE_LITTLEROOT_TOWN_FAT_MAN));
    EXPECT(IsHoennFlag(FLAG_DEFEATED_RUSTBORO_GYM));
    EXPECT(IsHoennFlag(FLAG_HIDDEN_ITEM_ROUTE_104_POTION));
    EXPECT(IsHoennFlag(FLAG_ITEM_ROUTE_102_POTION));
    EXPECT_GE(HOENN_FLAGS_START, KJH_SAVE3_FLAGS_END);

    FlagClear(FLAG_RESCUED_BIRCH);
    FlagClear(HOENN_FLAGS_END - 1);
    TakeSnapshot();
    FlagSet(FLAG_RESCUED_BIRCH);
    FlagSet(HOENN_FLAGS_END - 1);
    EXPECT(FlagGet(FLAG_RESCUED_BIRCH));
    EXPECT(FlagGet(HOENN_FLAGS_END - 1));
    EXPECT(!FlagGet(FLAG_HIDE_LITTLEROOT_TOWN_FAT_MAN));
    EXPECT(KantoAndJohtoUnchanged());
    FlagClear(FLAG_RESCUED_BIRCH);
    FlagClear(HOENN_FLAGS_END - 1);
    EXPECT(!FlagGet(FLAG_RESCUED_BIRCH));
}

TEST("KJH: Hoenn's badges and Champion flag are Hoenn's own")
{
    EXPECT(IsHoennFlag(FLAG_HOENN_BADGE01_GET));
    EXPECT(IsHoennFlag(FLAG_HOENN_BADGE08_GET));
    EXPECT_EQ(FLAG_HOENN_BADGE08_GET, FLAG_HOENN_BADGE01_GET + 7);
    EXPECT(IsHoennFlag(FLAG_HOENN_GAME_CLEAR));

    FlagClear(FLAG_HOENN_BADGE05_GET);
    FlagClear(FLAG_HOENN_GAME_CLEAR);
    TakeSnapshot();
    FlagSet(FLAG_HOENN_BADGE05_GET);
    FlagSet(FLAG_HOENN_GAME_CLEAR);
    EXPECT(FlagGet(FLAG_HOENN_BADGE05_GET));
    EXPECT(KantoAndJohtoUnchanged());
    FlagClear(FLAG_HOENN_BADGE05_GET);
    FlagClear(FLAG_HOENN_GAME_CLEAR);
}

TEST("KJH: Hoenn's story variables are kept in SaveBlock3; the engine's stay where they were")
{
    EXPECT_GE(VAR_LITTLEROOT_INTRO_STATE, HOENN_VARS_START);
    EXPECT_LT(VAR_LITTLEROOT_INTRO_STATE, HOENN_VARS_END);
    EXPECT_GE(VAR_BIRCH_LAB_STATE, HOENN_VARS_START);
    EXPECT_GE(HOENN_VARS_START, KJH_SAVE3_VARS_END);
    EXPECT_LT(VAR_REPEL_STEP_COUNT, VARS_END + 1); // the repel's steps are the whole game's

    TakeSnapshot();
    VarSet(VAR_LITTLEROOT_INTRO_STATE, 1234);
    VarSet(HOENN_VARS_END - 1, 5678);
    EXPECT_EQ(VarGet(VAR_LITTLEROOT_INTRO_STATE), 1234);
    EXPECT_EQ(VarGet(HOENN_VARS_END - 1), 5678);
    EXPECT_EQ(gSaveBlock3Ptr->hoennVars[VAR_LITTLEROOT_INTRO_STATE - HOENN_VARS_START], 1234);
    EXPECT(KantoAndJohtoUnchanged());
    VarSet(VAR_LITTLEROOT_INTRO_STATE, 0);
    VarSet(HOENN_VARS_END - 1, 0);
}

TEST("KJH: Hoenn's trainers come after Johto's, and their flags are Hoenn flags")
{
    EXPECT_GE(TRAINER_SAWYER_1, HOENN_TRAINERS_START);
    EXPECT_GE(HOENN_TRAINERS_START, JOHTO_TRAINERS_START + JOHTO_TRAINERS_COUNT);
    EXPECT_EQ(TRAINERS_COUNT, HOENN_TRAINERS_START + HOENN_TRAINERS_COUNT);
    EXPECT_LT(TRAINER_MAY_PLACEHOLDER, TRAINERS_COUNT);
    EXPECT(IsHoennFlag(GetTrainerFlagFromId(TRAINER_SAWYER_1)));
    EXPECT(IsHoennFlag(GetTrainerFlagFromId(TRAINER_MAY_PLACEHOLDER)));
    EXPECT_EQ(GetTrainerFlagFromId(JOHTO_TRAINERS_START), JOHTO_TRAINER_FLAGS_START); // Johto's are unchanged

    ClearTrainerFlag(TRAINER_ROXANNE_1);
    TakeSnapshot();
    EXPECT(!HasTrainerBeenFought(TRAINER_ROXANNE_1));
    SetTrainerFlag(TRAINER_ROXANNE_1);
    EXPECT(HasTrainerBeenFought(TRAINER_ROXANNE_1));
    EXPECT(!HasTrainerBeenFought(TRAINER_ROXANNE_2));
    EXPECT(KantoAndJohtoUnchanged());
    ClearTrainerFlag(TRAINER_ROXANNE_1);
}

// Tests have their own gTrainers; Hoenn's parties are checked in the emulator (emu_expansion_hoenn.py).
TEST("KJH: Hoenn's trainer classes and pics are in the fork's tables")
{
    EXPECT_EQ(StringCompare(gTrainerClasses[TRAINER_CLASS_AQUA_ADMIN].name, COMPOUND_STRING("AQUA ADMIN")), 0);
    EXPECT_EQ(StringCompare(gTrainerClasses[TRAINER_CLASS_LEADER].name, COMPOUND_STRING("LEADER")), 0);
    EXPECT(gTrainerPicInfo[TRAINER_PIC_LEADER_ROXANNE].frontPic != NULL);
    EXPECT(gTrainerPicInfo[TRAINER_PIC_AQUA_ADMIN_M].frontPic != NULL);
}

TEST("KJH: Hoenn's maps are Hoenn's region, and count Hoenn's badges")
{
    struct WarpData saved = gSaveBlock1Ptr->location;
    u16 savedMapsec = gMapHeader.regionMapSectionId;

    EXPECT_EQ(KJH_RegionOf(MAPSEC_LITTLEROOT_TOWN, MAP_LITTLEROOT_TOWN), KJH_REGION_HOENN);
    EXPECT_EQ(KJH_RegionOf(MAPSEC_RUSTBORO_CITY, MAP_RUSTBORO_CITY_GYM), KJH_REGION_HOENN);
    EXPECT_EQ(KJH_RegionOf(MAPSEC_PALLET_TOWN, MAP_PALLET_TOWN), KJH_REGION_KANTO);

    for (u32 i = 0; i < NUM_BADGES; i++)
    {
        FlagSet(FLAG_BADGE01_GET + i);
        FlagClear(FLAG_HOENN_BADGE01_GET + i);
    }
    FlagSet(FLAG_HOENN_BADGE01_GET);
    FlagSet(FLAG_HOENN_BADGE02_GET);

    gMapHeader.regionMapSectionId = MAPSEC_RUSTBORO_CITY;
    gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(MAP_RUSTBORO_CITY);
    gSaveBlock1Ptr->location.mapNum = MAP_NUM(MAP_RUSTBORO_CITY);
    EXPECT_EQ(KJH_RegionHere(), KJH_REGION_HOENN);
    EXPECT_EQ(KJH_CountBadgesHere(), 2);

    gSaveBlock1Ptr->location = saved;
    gMapHeader.regionMapSectionId = savedMapsec;
    FlagClear(FLAG_HOENN_BADGE01_GET);
    FlagClear(FLAG_HOENN_BADGE02_GET);
    for (u32 i = 0; i < NUM_BADGES; i++)
        FlagClear(FLAG_BADGE01_GET + i);
}

TEST("KJH: in Hoenn, Hoenn's badges open the HMs in Emerald's order; Kanto's still do everywhere")
{
    struct WarpData saved = gSaveBlock1Ptr->location;

    for (u32 i = 0; i < NUM_BADGES; i++)
    {
        FlagClear(FLAG_BADGE01_GET + i);
        FlagClear(FLAG_HOENN_BADGE01_GET + i);
    }
    FlagSet(FLAG_HOENN_BADGE05_GET); // the Balance Badge: SURF

    gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(MAP_PETALBURG_CITY);
    gSaveBlock1Ptr->location.mapNum = MAP_NUM(MAP_PETALBURG_CITY);
    EXPECT(IsFieldMoveUnlocked(FIELD_MOVE_SURF));
    EXPECT(!IsFieldMoveUnlocked(FIELD_MOVE_WATERFALL));
    EXPECT(!IsFieldMoveUnlocked(FIELD_MOVE_CUT));

    gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(MAP_PALLET_TOWN);
    gSaveBlock1Ptr->location.mapNum = MAP_NUM(MAP_PALLET_TOWN);
    EXPECT(!IsFieldMoveUnlocked(FIELD_MOVE_SURF)); // Hoenn's badge, outside Hoenn
    FlagSet(FLAG_BADGE05_GET); // Kanto's Soul Badge: SURF everywhere
    EXPECT(IsFieldMoveUnlocked(FIELD_MOVE_SURF));
    gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(MAP_PETALBURG_CITY);
    gSaveBlock1Ptr->location.mapNum = MAP_NUM(MAP_PETALBURG_CITY);
    FlagClear(FLAG_HOENN_BADGE05_GET);
    EXPECT(IsFieldMoveUnlocked(FIELD_MOVE_SURF));

    FlagClear(FLAG_BADGE05_GET);
    gSaveBlock1Ptr->location = saved;
}

#endif
