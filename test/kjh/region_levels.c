// KJH: Johto joins the levels-free system (LV-18, src/kjh_team_level.c, src/data/kjh_johto_zones.h): Johto's zones
// on the shared curve, its own team level and badge count, and the power cap starting again at 50% on arrival.
#include "global.h"
#include "event_data.h"
#include "kjh_field.h"
#include "kjh_move_library.h"
#include "kjh_power_cap.h"
#include "kjh_team_level.h"
#include "pokemon.h"
#include "test/test.h"
#include "constants/battle.h"
#include "constants/johto_flags.h"
#include "constants/map_groups.h"
#include "constants/region_map_sections.h"

static void SetRegionBadges(u32 firstBadgeFlag, u32 count)
{
    for (u32 i = 0; i < NUM_BADGES; i++)
    {
        if (i < count)
        {
            FlagSet(firstBadgeFlag + i);
        }
        else
        {
            FlagClear(firstBadgeFlag + i);
        }
    }
}

static void StandOn(u32 mapsec, u32 map)
{
    gMapHeader.regionMapSectionId = mapsec;
    gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(map);
    gSaveBlock1Ptr->location.mapNum = MAP_NUM(map);
}

static struct WarpData sSavedLocation;
static u16 sSavedMapsec;

// A veteran: Kanto's League beaten with 8 badges, no Johto badge, no Johto zone reached yet. Cleanup puts the player
// back where the other tests expect them.
static void StartVeteran(void)
{
    sSavedLocation = gSaveBlock1Ptr->location;
    sSavedMapsec = gMapHeader.regionMapSectionId;
    FlagSet(FLAG_KJH_LEVELLESS);
    FlagSet(FLAG_SYS_GAME_CLEAR);
    SetRegionBadges(FLAG_BADGE01_GET, NUM_BADGES);
    SetRegionBadges(FLAG_JOHTO_BADGE01_GET, 0);
    SetRegionBadges(FLAG_HOENN_BADGE01_GET, 0);
    VarSet(VAR_KJH_KANTO_ZONE_TOP, 100);
    VarSet(VAR_KJH_JOHTO_ZONE_TOP, 0);
    VarSet(VAR_KJH_TEAM_LEVEL, 100);
    VarSet(VAR_KJH_JOHTO_TEAM_LEVEL, 0);
    ZeroPlayerPartyMons();
}

static void Cleanup(void)
{
    gSaveBlock1Ptr->location = sSavedLocation;
    gMapHeader.regionMapSectionId = sSavedMapsec;
    FlagClear(FLAG_SYS_GAME_CLEAR);
    SetRegionBadges(FLAG_BADGE01_GET, 0);
    SetRegionBadges(FLAG_JOHTO_BADGE01_GET, 0);
    VarSet(VAR_KJH_JOHTO_ZONE_TOP, 0);
    VarSet(VAR_KJH_JOHTO_TEAM_LEVEL, 0);
}

TEST("KJH: Johto's zones sit on the shared curve, Kanto's place for place")
{
    EXPECT_EQ(KJH_ZoneTop(MAPSEC_J_NEW_BARK_TOWN, MAP_JOHTO_NEW_BARK_TOWN), 8);
    EXPECT_EQ(KJH_ZoneTop(MAPSEC_J_ROUTE_29, MAP_JOHTO_ROUTE_29), 8);
    EXPECT_EQ(KJH_ZoneTop(MAPSEC_J_ROUTE_30, MAP_JOHTO_ROUTE_30), 12);
    EXPECT_EQ(KJH_ZoneTop(MAPSEC_J_VIOLET_CITY, MAP_JOHTO_VIOLET_CITY), 14);
    EXPECT_EQ(KJH_ZoneTop(MAPSEC_J_UNION_CAVE, MAP_JOHTO_UNION_CAVE_1F), 18);
    EXPECT_EQ(KJH_ZoneTop(MAPSEC_J_RADIO_TOWER, MAP_JOHTO_RADIO_TOWER_1F), 74);
    EXPECT_EQ(KJH_ZoneTop(MAPSEC_J_ICE_PATH, MAP_JOHTO_ICE_PATH_1F), 78);
    EXPECT_EQ(KJH_ZoneTop(MAPSEC_J_SILVER_CAVE, MAP_JOHTO_SILVER_CAVE_ROOM_1), 100);
    // Dark Cave's two ends: by Violet City, and by Blackthorn City
    EXPECT_EQ(KJH_ZoneTop(MAPSEC_J_DARK_CAVE, MAP_JOHTO_DARK_CAVE_VIOLET_ENTRANCE), 12);
    EXPECT_EQ(KJH_ZoneTop(MAPSEC_J_DARK_CAVE, MAP_JOHTO_DARK_CAVE_BLACKTHORN_ENTRANCE), 78);
}

TEST("KJH: each map belongs to its region, by its zone table")
{
    EXPECT_EQ(KJH_RegionOf(MAPSEC_PALLET_TOWN, MAP_PALLET_TOWN), KJH_REGION_KANTO);
    EXPECT_EQ(KJH_RegionOf(MAPSEC_POKEMON_LEAGUE, MAP_POKEMON_LEAGUE_LANCES_ROOM), KJH_REGION_KANTO);
    EXPECT_EQ(KJH_RegionOf(MAPSEC_J_GOLDENROD_CITY, MAP_JOHTO_GOLDENROD_CITY), KJH_REGION_JOHTO);
    EXPECT_EQ(KJH_RegionOf(MAPSEC_LITTLEROOT_TOWN, MAP_LITTLEROOT_TOWN), KJH_REGION_HOENN); // its map groups (ENG-9)
    EXPECT_EQ(KJH_RegionOf(MAPSEC_LITTLEROOT_TOWN, MAP_PALLET_TOWN), KJH_REGION_NONE);
}

TEST("KJH: the badges that count are the region's: Johto's in Johto, Hoenn's in Hoenn, Kanto's elsewhere")
{
    StartVeteran();
    SetRegionBadges(FLAG_JOHTO_BADGE01_GET, 2);
    StandOn(MAPSEC_J_AZALEA_TOWN, MAP_JOHTO_AZALEA_TOWN);
    EXPECT_EQ(KJH_CountBadgesHere(), 2);
    EXPECT_EQ(KJH_RegionBadges(), 2);
    StandOn(MAPSEC_CELADON_CITY, MAP_CELADON_CITY);
    EXPECT_EQ(KJH_CountBadgesHere(), NUM_BADGES);
    StandOn(MAPSEC_LITTLEROOT_TOWN, MAP_LITTLEROOT_TOWN);
    EXPECT_EQ(KJH_CountBadgesHere(), 0); // Hoenn's (ENG-9)
    StandOn(MAPSEC_LITTLEROOT_TOWN, MAP_PALLET_TOWN);
    EXPECT_EQ(KJH_CountBadgesHere(), NUM_BADGES);
    Cleanup();
}

TEST("KJH: a veteran's team arrives in Johto low, at New Bark Town's level, and keeps its peak")
{
    StartVeteran();
    CreateMon(&gParties[B_TRAINER_PLAYER][0], SPECIES_CHARIZARD, 100, 0, OTID_STRUCT_PRESET(0));
    KJH_SetMonLevel(&gParties[B_TRAINER_PLAYER][0], 100);
    StandOn(MAPSEC_J_NEW_BARK_TOWN, MAP_JOHTO_NEW_BARK_TOWN);
    EXPECT(!KJH_TryTeamLevelStep()); // the level went down: no "Your team feels stronger!"
    EXPECT_EQ(VarGet(VAR_KJH_JOHTO_ZONE_TOP), 8);
    EXPECT_EQ(VarGet(VAR_KJH_KANTO_ZONE_TOP), 100);
    EXPECT_EQ(KJH_TeamLevel(), 8);
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_LEVEL), 8);
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_PEAK_LEVEL), 100);
    // Back in Kanto, the team is at Kanto's Champion level again, and that isn't news
    StandOn(MAPSEC_VERMILION_CITY, MAP_VERMILION_CITY);
    EXPECT_EQ(KJH_TeamLevel(), 100);
    EXPECT(!KJH_TryTeamLevelStep());
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_LEVEL), 100);
    // Nor is Johto again: its level is still 8
    StandOn(MAPSEC_J_ROUTE_29, MAP_JOHTO_ROUTE_29);
    EXPECT(!KJH_TryTeamLevelStep());
    // A real rise in Johto is: Cherrygrove's 12
    StandOn(MAPSEC_J_CHERRYGROVE_CITY, MAP_JOHTO_CHERRYGROVE_CITY);
    EXPECT(KJH_TryTeamLevelStep());
    EXPECT_EQ(VarGet(VAR_KJH_JOHTO_TEAM_LEVEL), 12);
    EXPECT_EQ(VarGet(VAR_KJH_TEAM_LEVEL), 100);
    Cleanup();
}

TEST("KJH: in Johto the team stops at Falkner's ace until his badge, as in Kanto at Brock's")
{
    StartVeteran();
    StandOn(MAPSEC_J_UNION_CAVE, MAP_JOHTO_UNION_CAVE_1F);
    KJH_RecordZone();
    EXPECT_EQ(VarGet(VAR_KJH_JOHTO_ZONE_TOP), 18);
    EXPECT_EQ(KJH_TeamLevel(), 14);
    SetRegionBadges(FLAG_JOHTO_BADGE01_GET, 1);
    EXPECT_EQ(KJH_TeamLevel(), 18);
    Cleanup();
}

TEST("KJH: a Johto Gym moves to the player's Johto badges")
{
    StartVeteran();
    StandOn(MAPSEC_J_VIOLET_CITY, MAP_JOHTO_VIOLET_GYM);
    EXPECT(KJH_IsInGym());
    EXPECT_EQ(KJH_GymLevelShift(), 0);
    StandOn(MAPSEC_J_AZALEA_TOWN, MAP_JOHTO_AZALEA_GYM);
    EXPECT_EQ(KJH_GymLevelShift(), 14 - 22); // Bugsy with no Johto badge: his ace at Falkner's 14
    StandOn(MAPSEC_J_BLACKTHORN_CITY, MAP_JOHTO_BLACKTHORN_GYM_2F);
    SetRegionBadges(FLAG_JOHTO_BADGE01_GET, 7);
    EXPECT_EQ(KJH_GymLevelShift(), 0);
    Cleanup();
}

TEST("KJH: the power cap starts again at 50% in Johto, with Kanto's 8 badges")
{
    StartVeteran();
    StandOn(MAPSEC_J_NEW_BARK_TOWN, MAP_JOHTO_NEW_BARK_TOWN);
    EXPECT_EQ(KJH_PowerCapPercent(KJH_RegionBadges()), 50);
    EXPECT(KJH_IsOhkoLocked(KJH_RegionBadges()));
    SetRegionBadges(FLAG_JOHTO_BADGE01_GET, 6);
    EXPECT_EQ(KJH_PowerCapPercent(KJH_RegionBadges()), 100);
    StandOn(MAPSEC_VERMILION_CITY, MAP_VERMILION_CITY);
    SetRegionBadges(FLAG_JOHTO_BADGE01_GET, 0);
    EXPECT_EQ(KJH_PowerCapPercent(KJH_RegionBadges()), 100);
    Cleanup();
}

TEST("KJH: field, Johto's Gyms use their Leader's type, the first two only boost")
{
    EXPECT_EQ(KJH_FieldForMap(MAP_JOHTO_VIOLET_GYM, BATTLE_ENVIRONMENT_BUILDING).type, TYPE_FLYING);
    EXPECT(KJH_FieldForMap(MAP_JOHTO_AZALEA_GYM, BATTLE_ENVIRONMENT_BUILDING).boostOnly);
    EXPECT_EQ(KJH_FieldForMap(MAP_JOHTO_ECRUTEAK_GYM, BATTLE_ENVIRONMENT_BUILDING).type, TYPE_GHOST);
    EXPECT(!KJH_FieldForMap(MAP_JOHTO_ECRUTEAK_GYM, BATTLE_ENVIRONMENT_BUILDING).boostOnly);
    EXPECT_EQ(KJH_FieldForMap(MAP_JOHTO_BLACKTHORN_GYM_2F, BATTLE_ENVIRONMENT_BUILDING).type, TYPE_DRAGON);
}

TEST("KJH: field, Johto's special places are set by hand, wherever the battle is fought on them")
{
    EXPECT_EQ(KJH_FieldForMap(MAP_JOHTO_ICE_PATH_B3F, BATTLE_ENVIRONMENT_CAVE).type, TYPE_ICE);
    EXPECT_EQ(KJH_FieldForMap(MAP_JOHTO_DRAGONS_DEN_B1F, BATTLE_ENVIRONMENT_POND).type, TYPE_DRAGON);
    EXPECT_EQ(KJH_FieldForMap(MAP_JOHTO_BURNED_TOWER_B1F, BATTLE_ENVIRONMENT_BUILDING).type, TYPE_FIRE);
    EXPECT_EQ(KJH_FieldForMap(MAP_JOHTO_ILEX_FOREST, BATTLE_ENVIRONMENT_GRASS).type, TYPE_BUG);
    EXPECT_EQ(KJH_FieldForMap(MAP_JOHTO_WHIRL_ISLAND_B2F, BATTLE_ENVIRONMENT_CAVE).type, TYPE_WATER);
    // a cave without a hand-set field (Dark Cave's Violet side is the Dark master's, LV-18)
    EXPECT_EQ(KJH_FieldForMap(MAP_JOHTO_DARK_CAVE_BLACKTHORN_ENTRANCE, BATTLE_ENVIRONMENT_CAVE).type, TYPE_ROCK);
}

TEST("KJH: a rise in Johto names no move as new to a veteran, only to a Pokemon that never was that strong")
{
    StartVeteran();
    CreateMon(&gParties[B_TRAINER_PLAYER][0], SPECIES_CHARMANDER, 100, 0, OTID_STRUCT_PRESET(0));
    KJH_SetMonLevel(&gParties[B_TRAINER_PLAYER][0], 100);
    KJH_SetMonLevel(&gParties[B_TRAINER_PLAYER][0], 12);
    gSpecialVar_0x8004 = 0;
    gSpecialVar_0x8005 = 1;
    gSpecialVar_0x8006 = 12; // Charmander learns Ember below 12
    EXPECT(!KJH_BufferNextNewLibraryMoves());
    CreateMon(&gParties[B_TRAINER_PLAYER][0], SPECIES_CHARMANDER, 12, 0, OTID_STRUCT_PRESET(0));
    KJH_SetMonLevel(&gParties[B_TRAINER_PLAYER][0], 12);
    gSpecialVar_0x8004 = 0;
    EXPECT(KJH_BufferNextNewLibraryMoves());
    Cleanup();
}
