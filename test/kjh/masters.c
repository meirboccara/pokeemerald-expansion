// KJH (LV-13, LV-18): matching spots, Kanto's and Johto's training masters (src/kjh_masters.c, src/kjh_move_stars.c).
#include "global.h"
#include "event_data.h"
#include "kjh_field.h"
#include "kjh_masters.h"
#include "kjh_move_stars.h"
#include "kjh_team_level.h"
#include "test/battle.h"
#include "constants/johto_flags.h"
#include "constants/map_groups.h"
#include "constants/region_map_sections.h"
#include "constants/opponents.h"

TEST("KJH: Kanto has 11 training masters, one per type, with their daily flags")
{
    static const enum Type sTypes[] = {TYPE_WATER, TYPE_FIRE, TYPE_ELECTRIC, TYPE_GHOST, TYPE_ICE, TYPE_BUG, TYPE_ROCK,
                                       TYPE_FIGHTING, TYPE_POISON, TYPE_GROUND, TYPE_NORMAL};

    for (u32 i = 0; i < KJH_KANTO_MASTERS_COUNT; i++)
    {
        const struct KjhMaster *master = KJH_GetMaster(TRAINER_KJH_MASTER_WATER + i);

        EXPECT(master != NULL);
        if (master == NULL)
            continue;
        EXPECT_EQ(master->type, sTypes[i]);
        EXPECT_GE(master->flagOnce, DAILY_FLAGS_START);
        EXPECT_LE(master->flagTwice, DAILY_FLAGS_END);
    }
    EXPECT(KJH_GetMaster(TRAINER_LEADER_BROCK) == NULL);
}

TEST("KJH: Johto has 12 training masters, one per type, with daily flags of their own (LV-18)")
{
    static const enum Type sTypes[] = {TYPE_WATER, TYPE_FIRE, TYPE_ICE, TYPE_DRAGON, TYPE_BUG, TYPE_ROCK, TYPE_FIGHTING,
                                       TYPE_DARK, TYPE_PSYCHIC, TYPE_FLYING, TYPE_STEEL, TYPE_NORMAL};
    u16 flags[2 * (KJH_KANTO_MASTERS_COUNT + KJH_JOHTO_MASTERS_COUNT)];
    u32 n = 0;

    EXPECT_EQ(KJH_JOHTO_MASTERS_COUNT, 12);
    EXPECT_EQ(KJH_MASTERS_COUNT, 23);
    for (u32 i = 0; i < KJH_KANTO_MASTERS_COUNT; i++)
    {
        const struct KjhMaster *master = KJH_GetMaster(TRAINER_KJH_MASTER_WATER + i);

        if (master == NULL)
            continue;
        flags[n++] = master->flagOnce;
        flags[n++] = master->flagTwice;
    }
    for (u32 i = 0; i < KJH_JOHTO_MASTERS_COUNT; i++)
    {
        const struct KjhMaster *master = KJH_GetMaster(TRAINER_KJH_JOHTO_MASTER_WATER + i);

        EXPECT(master != NULL);
        if (master == NULL)
            continue;
        EXPECT_EQ(master->type, sTypes[i]);
        EXPECT_GE(master->trainerId, TRAINERS_COUNT_FRLG);       // FireRed's free ids, with a trainer flag
        EXPECT_LT(master->trainerId, MAX_TRAINERS_COUNT_FRLG);
        EXPECT_GE(master->flagOnce, DAILY_FLAGS_START);
        EXPECT_LE(master->flagTwice, DAILY_FLAGS_END);
        flags[n++] = master->flagOnce;
        flags[n++] = master->flagTwice;
    }
    for (u32 i = 0; i < n; i++)     // no two masters share a flag
    {
        for (u32 j = i + 1; j < n; j++)
            EXPECT_NE(flags[i], flags[j]);
    }
}

TEST("KJH: a Johto master's day is reset by the daily events too")
{
    FlagClear(FLAG_KJH_JOHTO_MASTER_STEEL_ONCE);
    FlagClear(FLAG_KJH_JOHTO_MASTER_STEEL_TWICE);
    KJH_NoteMasterFought(TRAINER_KJH_JOHTO_MASTER_STEEL);
    KJH_NoteMasterFought(TRAINER_KJH_JOHTO_MASTER_STEEL);
    EXPECT_EQ(KJH_MasterFightsLeftToday(TRAINER_KJH_JOHTO_MASTER_STEEL), 0);
    EXPECT_EQ(KJH_MasterFightsLeftToday(TRAINER_KJH_MASTER_WATER), 2);   // its own flags, not a Kanto master's
    ClearDailyFlags();
    EXPECT_EQ(KJH_MasterFightsLeftToday(TRAINER_KJH_JOHTO_MASTER_STEEL), 2);
}

TEST("KJH: Johto's masters' spots that their place doesn't give have their field (LV-18)")
{
    EXPECT_EQ(KJH_FieldForMap(MAP_JOHTO_MOUNT_MORTAR_B1F, BATTLE_ENVIRONMENT_CAVE).type, TYPE_FIGHTING);   // Kiyo's floor
    EXPECT_EQ(KJH_FieldForMap(MAP_JOHTO_DARK_CAVE_VIOLET_ENTRANCE, BATTLE_ENVIRONMENT_CAVE).type, TYPE_DARK);
    EXPECT_EQ(KJH_FieldForMap(MAP_JOHTO_RUINS_OF_ALPH_OUTSIDE, BATTLE_ENVIRONMENT_GRASS).type, TYPE_PSYCHIC);
    EXPECT_EQ(KJH_FieldForMap(MAP_JOHTO_TIN_TOWER_2F, BATTLE_ENVIRONMENT_CAVE).type, TYPE_FLYING);
    EXPECT_EQ(KJH_FieldForMap(MAP_JOHTO_OLIVINE_LIGHTHOUSE_1F, BATTLE_ENVIRONMENT_CAVE).type, TYPE_STEEL);
    EXPECT_EQ(KJH_FieldForMap(MAP_JOHTO_NATIONAL_PARK, BATTLE_ENVIRONMENT_GRASS).type, TYPE_NORMAL);
    // the rest come from their place: Mt. Mortar's other floors are a cave (Rock)
    EXPECT_EQ(KJH_FieldForMap(MAP_JOHTO_MOUNT_MORTAR_1F_OUTSIDE, BATTLE_ENVIRONMENT_CAVE).type, TYPE_ROCK);
    EXPECT_EQ(KJH_FieldForMap(MAP_JOHTO_WHIRL_ISLAND_NE, BATTLE_ENVIRONMENT_CAVE).type, TYPE_WATER);
    EXPECT_EQ(KJH_FieldForMap(MAP_JOHTO_DRAGONS_DEN_B1F, BATTLE_ENVIRONMENT_CAVE).type, TYPE_DRAGON);
}

TEST("KJH: a master's team is at the team level of the region the player stands in (LV-18)")
{
    struct WarpData location = gSaveBlock1Ptr->location;
    u16 mapsec = gMapHeader.regionMapSectionId;

    // A veteran (Kanto's League, 8 badges, Kanto's team at 100) in Union Cave, no Johto badge: Johto's team is at
    // Falkner's ace, 14
    FlagSet(FLAG_KJH_LEVELLESS);
    FlagSet(FLAG_SYS_GAME_CLEAR);
    for (u32 i = 0; i < NUM_BADGES; i++)
    {
        FlagSet(FLAG_BADGE01_GET + i);
        FlagClear(FLAG_JOHTO_BADGE01_GET + i);
    }
    VarSet(VAR_KJH_KANTO_ZONE_TOP, 100);
    VarSet(VAR_KJH_TEAM_LEVEL, 100);
    VarSet(VAR_KJH_JOHTO_ZONE_TOP, 0);
    VarSet(VAR_KJH_JOHTO_TEAM_LEVEL, 0);
    gMapHeader.regionMapSectionId = MAPSEC_J_UNION_CAVE;
    gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(MAP_JOHTO_UNION_CAVE_1F);
    gSaveBlock1Ptr->location.mapNum = MAP_NUM(MAP_JOHTO_UNION_CAVE_1F);
    KJH_RecordZone();
    EXPECT_EQ(KJH_MasterLevel(), 14);
    // Back in Kanto, Kanto's masters are at Kanto's 100
    gMapHeader.regionMapSectionId = MAPSEC_VERMILION_CITY;
    gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(MAP_VERMILION_CITY);
    gSaveBlock1Ptr->location.mapNum = MAP_NUM(MAP_VERMILION_CITY);
    EXPECT_EQ(KJH_MasterLevel(), 100);

    gSaveBlock1Ptr->location = location;
    gMapHeader.regionMapSectionId = mapsec;
    FlagClear(FLAG_SYS_GAME_CLEAR);
    for (u32 i = 0; i < NUM_BADGES; i++)
        FlagClear(FLAG_BADGE01_GET + i);
    VarSet(VAR_KJH_JOHTO_ZONE_TOP, 0);
    VarSet(VAR_KJH_JOHTO_TEAM_LEVEL, 0);
}

TEST("KJH: a master can be fought twice per in-game day")
{
    FlagClear(FLAG_KJH_MASTER_FIRE_ONCE);
    FlagClear(FLAG_KJH_MASTER_FIRE_TWICE);
    EXPECT_EQ(KJH_MasterFightsLeftToday(TRAINER_KJH_MASTER_FIRE), 2);
    KJH_NoteMasterFought(TRAINER_KJH_MASTER_FIRE);
    EXPECT_EQ(KJH_MasterFightsLeftToday(TRAINER_KJH_MASTER_FIRE), 1);
    KJH_NoteMasterFought(TRAINER_KJH_MASTER_FIRE);
    EXPECT_EQ(KJH_MasterFightsLeftToday(TRAINER_KJH_MASTER_FIRE), 0);
    KJH_NoteMasterFought(TRAINER_KJH_MASTER_FIRE);
    EXPECT_EQ(KJH_MasterFightsLeftToday(TRAINER_KJH_MASTER_FIRE), 0);
    ClearDailyFlags();      // a new day (CF-4's daily events)
    EXPECT_EQ(KJH_MasterFightsLeftToday(TRAINER_KJH_MASTER_FIRE), 2);
}

TEST("KJH: a move of the field's type trains twice as fast; a master gives +20 to moves of its type, never doubled")
{
    // basic points, the move's type, the field, the master's type (TYPE_NONE: not a master)
    EXPECT_EQ(KJH_MovePointsForMove(1, TYPE_WATER, TYPE_WATER, TYPE_NONE), 2);     // a wild battle on water
    EXPECT_EQ(KJH_MovePointsForMove(1, TYPE_FIRE, TYPE_WATER, TYPE_NONE), 1);
    EXPECT_EQ(KJH_MovePointsForMove(5, TYPE_ROCK, TYPE_ROCK, TYPE_NONE), 10);      // Brock, Rock moves on his field
    EXPECT_EQ(KJH_MovePointsForMove(2, TYPE_GHOST, TYPE_GHOST, TYPE_GHOST), 20);   // the master's type: +20 flat
    EXPECT_EQ(KJH_MovePointsForMove(2, TYPE_DARK, TYPE_GHOST, TYPE_GHOST), 2);     // the rest: a trainer's
    EXPECT_EQ(KJH_MovePointsForMove(1, TYPE_NORMAL, TYPE_NONE, TYPE_NONE), 1);
}
