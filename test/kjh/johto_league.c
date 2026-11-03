// KJH: the Johto League season at Indigo Plateau (ENG-10, data/scripts/kjh_indigo.inc, src/kjh_team_level.c): once the
// season is open, Indigo Plateau and the League's rooms are Johto's, so the team is at Johto's level there; becoming
// Champion in that season makes the player Johto Champion.
#include "global.h"
#include "event_data.h"
#include "kjh_team_level.h"
#include "test/test.h"
#include "constants/johto_flags.h"
#include "constants/map_groups.h"
#include "constants/region_map_sections.h"

static struct WarpData sSavedLocation;
static u16 sSavedMapsec, sSavedKantoZoneTop;
static bool8 sSavedLevelsFree;

static void SetBadges(u32 firstBadgeFlag, bool32 all)
{
    for (u32 i = 0; i < NUM_BADGES; i++)
    {
        if (all)
            FlagSet(firstBadgeFlag + i);
        else
            FlagClear(firstBadgeFlag + i);
    }
}

static void StandOn(u32 mapsec, u32 map)
{
    gMapHeader.regionMapSectionId = mapsec;
    gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(map);
    gSaveBlock1Ptr->location.mapNum = MAP_NUM(map);
}

// Kanto Champion with Johto's 8 badges, Johto's furthest zone Victory Road (83)
static void StartJohtoSeason(void)
{
    sSavedLocation = gSaveBlock1Ptr->location;
    sSavedMapsec = gMapHeader.regionMapSectionId;
    sSavedKantoZoneTop = VarGet(VAR_KJH_KANTO_ZONE_TOP);
    sSavedLevelsFree = FlagGet(FLAG_KJH_LEVELLESS);
    FlagSet(FLAG_KJH_LEVELLESS);
    FlagSet(FLAG_SYS_GAME_CLEAR);
    SetBadges(FLAG_BADGE01_GET, TRUE);
    SetBadges(FLAG_JOHTO_BADGE01_GET, TRUE);
    VarSet(VAR_KJH_KANTO_ZONE_TOP, 100);
    VarSet(VAR_KJH_JOHTO_ZONE_TOP, 83);
    FlagSet(FLAG_KJH_JOHTO_LEAGUE_OPEN);
}

static void Cleanup(void)
{
    gSaveBlock1Ptr->location = sSavedLocation;
    gMapHeader.regionMapSectionId = sSavedMapsec;
    VarSet(VAR_KJH_KANTO_ZONE_TOP, sSavedKantoZoneTop);
    if (!sSavedLevelsFree)
        FlagClear(FLAG_KJH_LEVELLESS);
    FlagClear(FLAG_SYS_GAME_CLEAR);
    FlagClear(FLAG_KJH_JOHTO_LEAGUE_OPEN);
    FlagClear(FLAG_KJH_JOHTO_CHAMPION);
    SetBadges(FLAG_BADGE01_GET, FALSE);
    SetBadges(FLAG_JOHTO_BADGE01_GET, FALSE);
    VarSet(VAR_KJH_JOHTO_ZONE_TOP, 0);
    VarSet(VAR_KJH_JOHTO_TEAM_LEVEL, 0);
}

TEST("KJH: Indigo Plateau is Kanto's until the Johto League season, then Johto's")
{
    EXPECT_EQ(KJH_RegionOf(MAPSEC_POKEMON_LEAGUE, MAP_POKEMON_LEAGUE_LORELEIS_ROOM), KJH_REGION_KANTO);
    EXPECT_EQ(KJH_RegionOf(MAPSEC_INDIGO_PLATEAU, MAP_INDIGO_PLATEAU_POKEMON_CENTER_1F), KJH_REGION_KANTO);
    StartJohtoSeason();
    EXPECT_EQ(KJH_RegionOf(MAPSEC_POKEMON_LEAGUE, MAP_POKEMON_LEAGUE_LORELEIS_ROOM), KJH_REGION_JOHTO);
    EXPECT_EQ(KJH_RegionOf(MAPSEC_POKEMON_LEAGUE, MAP_POKEMON_LEAGUE_CHAMPIONS_ROOM), KJH_REGION_JOHTO);
    EXPECT_EQ(KJH_RegionOf(MAPSEC_INDIGO_PLATEAU, MAP_INDIGO_PLATEAU_POKEMON_CENTER_1F), KJH_REGION_JOHTO);
    // the rest of Kanto stays Kanto's
    EXPECT_EQ(KJH_RegionOf(MAPSEC_KANTO_VICTORY_ROAD, MAP_VICTORY_ROAD_1F_FRLG), KJH_REGION_KANTO);
    EXPECT_EQ(KJH_RegionOf(MAPSEC_PALLET_TOWN, MAP_PALLET_TOWN), KJH_REGION_KANTO);
    Cleanup();
}

TEST("KJH: the Johto League's rooms have the Kanto League's steps")
{
    StartJohtoSeason();
    EXPECT_EQ(KJH_ZoneTop(MAPSEC_INDIGO_PLATEAU, MAP_INDIGO_PLATEAU_POKEMON_CENTER_1F), 84);
    EXPECT_EQ(KJH_ZoneTop(MAPSEC_POKEMON_LEAGUE, MAP_POKEMON_LEAGUE_LORELEIS_ROOM), 84);
    EXPECT_EQ(KJH_ZoneTop(MAPSEC_POKEMON_LEAGUE, MAP_POKEMON_LEAGUE_BRUNOS_ROOM), 88);
    EXPECT_EQ(KJH_ZoneTop(MAPSEC_POKEMON_LEAGUE, MAP_POKEMON_LEAGUE_AGATHAS_ROOM), 92);
    EXPECT_EQ(KJH_ZoneTop(MAPSEC_POKEMON_LEAGUE, MAP_POKEMON_LEAGUE_LANCES_ROOM), 96);
    EXPECT_EQ(KJH_ZoneTop(MAPSEC_POKEMON_LEAGUE, MAP_POKEMON_LEAGUE_CHAMPIONS_ROOM), 100);
    Cleanup();
}

TEST("KJH: in the Johto League season, the team climbs Johto's level room by room")
{
    StartJohtoSeason();
    StandOn(MAPSEC_INDIGO_PLATEAU, MAP_INDIGO_PLATEAU_POKEMON_CENTER_1F);
    EXPECT_EQ(KJH_TeamLevel(), 83); // Johto's Victory Road, not Kanto's Champion level
    StandOn(MAPSEC_POKEMON_LEAGUE, MAP_POKEMON_LEAGUE_AGATHAS_ROOM);
    KJH_TryTeamLevelStep();
    EXPECT_EQ(VarGet(VAR_KJH_JOHTO_ZONE_TOP), 92);
    EXPECT_EQ(VarGet(VAR_KJH_KANTO_ZONE_TOP), 100);
    EXPECT_EQ(KJH_TeamLevel(), 92);
    Cleanup();
}

TEST("KJH: Johto Champion, the team is at the Champion's level in Johto")
{
    StartJohtoSeason();
    StandOn(MAPSEC_J_GOLDENROD_CITY, MAP_JOHTO_GOLDENROD_CITY);
    EXPECT_EQ(KJH_TeamLevel(), 83);
    FlagSet(FLAG_KJH_JOHTO_CHAMPION);
    EXPECT_EQ(KJH_TeamLevel(), 100);
    Cleanup();
}
