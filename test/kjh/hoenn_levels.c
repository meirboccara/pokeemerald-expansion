// KJH: Hoenn joins the levels-free system (LV-18's Hoenn half, src/kjh_team_level.c, src/data/kjh_hoenn_zones.h):
// Hoenn's zones on the shared curve in Emerald's story order, its own team level, badges, Gyms and League rooms, the
// power cap starting again at 50% on arrival, and no cap once the three Leagues are beaten.
#include "global.h"
#include "event_data.h"
#include "kjh_field.h"
#include "kjh_power_cap.h"
#include "kjh_team_level.h"
#include "pokemon.h"
#include "test/test.h"
#include "constants/battle.h"
#include "constants/hoenn_flags.h"
#include "constants/hoenn_vars.h"
#include "constants/johto_flags.h"
#include "constants/map_groups.h"
#include "constants/region_map_sections.h"

static void SetRegionBadges(u32 firstBadgeFlag, u32 count)
{
    for (u32 i = 0; i < NUM_BADGES; i++)
    {
        if (i < count)
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

static EWRAM_DATA struct WarpData sSavedLocation = {0};
static EWRAM_DATA u16 sSavedMapsec = 0;

// A veteran of Kanto and Johto: both Leagues beaten with their 8 badges, no Hoenn badge, no Hoenn zone reached yet.
// Cleanup puts the player back where the other tests expect them.
static void StartVeteran(void)
{
    sSavedLocation = gSaveBlock1Ptr->location;
    sSavedMapsec = gMapHeader.regionMapSectionId;
    FlagSet(FLAG_KJH_LEVELLESS);
    FlagSet(FLAG_SYS_GAME_CLEAR);
    FlagSet(FLAG_KJH_JOHTO_CHAMPION);
    FlagClear(FLAG_HOENN_GAME_CLEAR);
    SetRegionBadges(FLAG_BADGE01_GET, NUM_BADGES);
    SetRegionBadges(FLAG_JOHTO_BADGE01_GET, NUM_BADGES);
    SetRegionBadges(FLAG_HOENN_BADGE01_GET, 0);
    VarSet(VAR_KJH_KANTO_ZONE_TOP, 100);
    VarSet(VAR_KJH_TEAM_LEVEL, 100);
    VarSet(VAR_KJH_JOHTO_ZONE_TOP, 100);
    VarSet(VAR_KJH_JOHTO_TEAM_LEVEL, 100);
    VarSet(VAR_KJH_HOENN_ZONE_TOP, 0);
    VarSet(VAR_KJH_HOENN_TEAM_LEVEL, 0);
    ZeroPlayerPartyMons();
}

static void Cleanup(void)
{
    gSaveBlock1Ptr->location = sSavedLocation;
    gMapHeader.regionMapSectionId = sSavedMapsec;
    FlagClear(FLAG_SYS_GAME_CLEAR);
    FlagClear(FLAG_KJH_JOHTO_CHAMPION);
    FlagClear(FLAG_HOENN_GAME_CLEAR);
    SetRegionBadges(FLAG_BADGE01_GET, 0);
    SetRegionBadges(FLAG_JOHTO_BADGE01_GET, 0);
    SetRegionBadges(FLAG_HOENN_BADGE01_GET, 0);
    VarSet(VAR_KJH_JOHTO_ZONE_TOP, 0);
    VarSet(VAR_KJH_JOHTO_TEAM_LEVEL, 0);
    VarSet(VAR_KJH_HOENN_ZONE_TOP, 0);
    VarSet(VAR_KJH_HOENN_TEAM_LEVEL, 0);
}

TEST("KJH: Hoenn's zones sit on the shared curve, in Emerald's story order")
{
    EXPECT_EQ(KJH_ZoneTop(MAPSEC_LITTLEROOT_TOWN, MAP_LITTLEROOT_TOWN), 8);
    EXPECT_EQ(KJH_ZoneTop(MAPSEC_ROUTE_101, MAP_ROUTE101), 8);
    EXPECT_EQ(KJH_ZoneTop(MAPSEC_PETALBURG_WOODS, MAP_PETALBURG_WOODS), 12);
    EXPECT_EQ(KJH_ZoneTop(MAPSEC_RUSTBORO_CITY, MAP_RUSTBORO_CITY), 14);
    EXPECT_EQ(KJH_ZoneTop(MAPSEC_GRANITE_CAVE, MAP_GRANITE_CAVE_1F), 21);
    EXPECT_EQ(KJH_ZoneTop(MAPSEC_SLATEPORT_CITY, MAP_SLATEPORT_CITY), 26);
    EXPECT_EQ(KJH_ZoneTop(MAPSEC_MAUVILLE_CITY, MAP_MAUVILLE_CITY), 28);
    EXPECT_EQ(KJH_ZoneTop(MAPSEC_MT_CHIMNEY, MAP_MT_CHIMNEY), 38);
    EXPECT_EQ(KJH_ZoneTop(MAPSEC_MIRAGE_TOWER, MAP_MIRAGE_TOWER_1F), 48);
    EXPECT_EQ(KJH_ZoneTop(MAPSEC_FORTREE_CITY, MAP_FORTREE_CITY), 56);
    EXPECT_EQ(KJH_ZoneTop(MAPSEC_AQUA_HIDEOUT, MAP_AQUA_HIDEOUT_B1F), 68);
    EXPECT_EQ(KJH_ZoneTop(MAPSEC_SEAFLOOR_CAVERN, MAP_SEAFLOOR_CAVERN_ROOM1), 74);
    EXPECT_EQ(KJH_ZoneTop(MAPSEC_SKY_PILLAR, MAP_SKY_PILLAR_1F), 78);
    EXPECT_EQ(KJH_ZoneTop(MAPSEC_VICTORY_ROAD, MAP_VICTORY_ROAD_1F), 83);
    // Mossdeep's Space Center is taken after Tate and Liza; the Trick House's puzzles open with the badges
    EXPECT_EQ(KJH_ZoneTop(MAPSEC_MOSSDEEP_CITY, MAP_MOSSDEEP_CITY), 68);
    EXPECT_EQ(KJH_ZoneTop(MAPSEC_MOSSDEEP_CITY, MAP_MOSSDEEP_CITY_SPACE_CENTER_1F), 74);
    EXPECT_EQ(KJH_ZoneTop(MAPSEC_ROUTE_110, MAP_ROUTE110), 26);
    EXPECT_EQ(KJH_ZoneTop(MAPSEC_ROUTE_110, MAP_ROUTE110_TRICK_HOUSE_PUZZLE3), 48);
    // The League: one step per room, the Champion at 100
    EXPECT_EQ(KJH_ZoneTop(MAPSEC_EVER_GRANDE_CITY, MAP_EVER_GRANDE_CITY_SIDNEYS_ROOM), 84);
    EXPECT_EQ(KJH_ZoneTop(MAPSEC_EVER_GRANDE_CITY, MAP_EVER_GRANDE_CITY_PHOEBES_ROOM), 88);
    EXPECT_EQ(KJH_ZoneTop(MAPSEC_EVER_GRANDE_CITY, MAP_EVER_GRANDE_CITY_GLACIAS_ROOM), 92);
    EXPECT_EQ(KJH_ZoneTop(MAPSEC_EVER_GRANDE_CITY, MAP_EVER_GRANDE_CITY_DRAKES_ROOM), 96);
    EXPECT_EQ(KJH_ZoneTop(MAPSEC_EVER_GRANDE_CITY, MAP_EVER_GRANDE_CITY_CHAMPIONS_ROOM), 100);
    // No zone: the Battle Frontier, and the legendaries' own places
    EXPECT_EQ(KJH_ZoneTop(MAPSEC_BATTLE_FRONTIER, MAP_BATTLE_FRONTIER_OUTSIDE_WEST), 0);
    EXPECT_EQ(KJH_ZoneTop(MAPSEC_SOUTHERN_ISLAND, MAP_SOUTHERN_ISLAND_EXTERIOR), 0);
}

TEST("KJH: Hoenn's tables are for Hoenn's maps only")
{
    EXPECT_EQ(KJH_RegionOf(MAPSEC_SLATEPORT_CITY, MAP_SLATEPORT_CITY), KJH_REGION_HOENN);
    EXPECT_EQ(KJH_RegionOf(MAPSEC_BATTLE_FRONTIER, MAP_BATTLE_FRONTIER_OUTSIDE_WEST), KJH_REGION_HOENN);
    EXPECT_EQ(KJH_RegionOf(MAPSEC_SLATEPORT_CITY, MAP_PALLET_TOWN), KJH_REGION_NONE);
    EXPECT_EQ(KJH_ZoneTop(MAPSEC_SLATEPORT_CITY, MAP_PALLET_TOWN), 0);
    EXPECT_EQ(KJH_ZoneTop(MAPSEC_PALLET_TOWN, MAP_SLATEPORT_CITY), 0);
}

TEST("KJH: a veteran arrives in Slateport at Roxanne's ceiling, with the power cap at 50%")
{
    StartVeteran();
    CreateMon(&gParties[B_TRAINER_PLAYER][0], SPECIES_CHARIZARD, 100, 0, OTID_STRUCT_PRESET(0));
    KJH_SetMonLevel(&gParties[B_TRAINER_PLAYER][0], 100);
    StandOn(MAPSEC_SLATEPORT_CITY, MAP_SLATEPORT_CITY_HARBOR);
    EXPECT(!KJH_TryTeamLevelStep()); // the level went down: no "Your team feels stronger!"
    EXPECT_EQ(VarGet(VAR_KJH_HOENN_ZONE_TOP), 26);
    EXPECT_EQ(KJH_TeamLevel(), 14);
    EXPECT_EQ(VarGet(VAR_KJH_HOENN_TEAM_LEVEL), 14);
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_LEVEL), 14);
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_PEAK_LEVEL), 100);
    EXPECT_EQ(KJH_CountBadgesHere(), 0);
    EXPECT_EQ(KJH_PowerCapPercentHere(), 50);
    EXPECT(KJH_IsOhkoLockedHere());
    // Kanto and Johto keep their own levels
    StandOn(MAPSEC_VERMILION_CITY, MAP_VERMILION_CITY);
    EXPECT_EQ(KJH_TeamLevel(), 100);
    EXPECT_EQ(KJH_PowerCapPercentHere(), 100);
    StandOn(MAPSEC_J_GOLDENROD_CITY, MAP_JOHTO_GOLDENROD_CITY);
    EXPECT_EQ(KJH_TeamLevel(), 100);
    Cleanup();
}

TEST("KJH: Hoenn's badges lift the team to the furthest zone, the cap with them")
{
    StartVeteran();
    StandOn(MAPSEC_SLATEPORT_CITY, MAP_SLATEPORT_CITY);
    KJH_RecordZone();
    SetRegionBadges(FLAG_HOENN_BADGE01_GET, 1);
    EXPECT_EQ(KJH_TeamLevel(), 22);
    EXPECT_EQ(KJH_PowerCapPercentHere(), 50);
    SetRegionBadges(FLAG_HOENN_BADGE01_GET, 2);
    EXPECT_EQ(KJH_TeamLevel(), 26);
    EXPECT_EQ(KJH_PowerCapPercentHere(), 60);
    // Going back west to Littleroot isn't a fall: the furthest zone stays
    StandOn(MAPSEC_LITTLEROOT_TOWN, MAP_LITTLEROOT_TOWN);
    KJH_RecordZone();
    EXPECT_EQ(VarGet(VAR_KJH_HOENN_ZONE_TOP), 26);
    EXPECT_EQ(KJH_TeamLevel(), 26);
    // A rise is news
    VarSet(VAR_KJH_HOENN_TEAM_LEVEL, 26);
    StandOn(MAPSEC_MAUVILLE_CITY, MAP_MAUVILLE_CITY);
    EXPECT(KJH_TryTeamLevelStep());
    EXPECT_EQ(VarGet(VAR_KJH_HOENN_TEAM_LEVEL), 28);
    Cleanup();
}

TEST("KJH: Hoenn's Gyms move to the player's Hoenn badges, in Emerald's order")
{
    StartVeteran();
    StandOn(MAPSEC_RUSTBORO_CITY, MAP_RUSTBORO_CITY_GYM);
    EXPECT(KJH_IsInGym());
    EXPECT_EQ(KJH_GymLevelShift(), 0);
    StandOn(MAPSEC_DEWFORD_TOWN, MAP_DEWFORD_TOWN_GYM);
    EXPECT_EQ(KJH_GymLevelShift(), 14 - 22); // Brawly with no Hoenn badge: his ace at Roxanne's 14
    StandOn(MAPSEC_PETALBURG_CITY, MAP_PETALBURG_CITY_GYM);
    SetRegionBadges(FLAG_HOENN_BADGE01_GET, 4);
    EXPECT_EQ(KJH_GymLevelShift(), 0);       // Norman, the 5th
    StandOn(MAPSEC_SOOTOPOLIS_CITY, MAP_SOOTOPOLIS_CITY_GYM_1F);
    SetRegionBadges(FLAG_HOENN_BADGE01_GET, 7);
    EXPECT_EQ(KJH_GymLevelShift(), 0);
    StandOn(MAPSEC_PETALBURG_CITY, MAP_PETALBURG_CITY);
    EXPECT(!KJH_IsInGym());
    Cleanup();
}

TEST("KJH: the Hoenn League beaten, Hoenn uses its Champion's level")
{
    StartVeteran();
    StandOn(MAPSEC_LITTLEROOT_TOWN, MAP_LITTLEROOT_TOWN);
    KJH_RecordZone();
    SetRegionBadges(FLAG_HOENN_BADGE01_GET, NUM_BADGES);
    EXPECT_EQ(KJH_TeamLevel(), 8);
    FlagSet(FLAG_HOENN_GAME_CLEAR);
    EXPECT_EQ(KJH_TeamLevel(), 100);
    Cleanup();
}

TEST("KJH: after the three Leagues there is no power cap anywhere")
{
    StartVeteran();
    StandOn(MAPSEC_SLATEPORT_CITY, MAP_SLATEPORT_CITY);
    FlagSet(FLAG_HOENN_GAME_CLEAR); // the Hoenn League beaten, still with no Hoenn badge
    EXPECT_EQ(KJH_PowerCapPercentHere(), 100);
    EXPECT(!KJH_IsOhkoLockedHere());
    EXPECT_EQ(KJH_TeamLevel(), 100);
    // One League missing: the cap is back, by the region's badges
    FlagClear(FLAG_KJH_JOHTO_CHAMPION);
    EXPECT_EQ(KJH_PowerCapPercentHere(), 50);
    EXPECT(KJH_IsOhkoLockedHere());
    FlagSet(FLAG_KJH_JOHTO_CHAMPION);
    FlagClear(FLAG_SYS_GAME_CLEAR);
    StandOn(MAPSEC_J_NEW_BARK_TOWN, MAP_JOHTO_NEW_BARK_TOWN);
    SetRegionBadges(FLAG_JOHTO_BADGE01_GET, 0);
    EXPECT_EQ(KJH_PowerCapPercentHere(), 50);
    FlagSet(FLAG_SYS_GAME_CLEAR);
    EXPECT_EQ(KJH_PowerCapPercentHere(), 100);
    Cleanup();
}

TEST("KJH: field, Hoenn's Gyms use their Leader's type, the first two only boost")
{
    EXPECT_EQ(KJH_FieldForMap(MAP_RUSTBORO_CITY_GYM, BATTLE_ENVIRONMENT_BUILDING).type, TYPE_ROCK);
    EXPECT(KJH_FieldForMap(MAP_RUSTBORO_CITY_GYM, BATTLE_ENVIRONMENT_BUILDING).boostOnly);
    EXPECT_EQ(KJH_FieldForMap(MAP_DEWFORD_TOWN_GYM, BATTLE_ENVIRONMENT_BUILDING).type, TYPE_FIGHTING);
    EXPECT(KJH_FieldForMap(MAP_DEWFORD_TOWN_GYM, BATTLE_ENVIRONMENT_BUILDING).boostOnly);
    EXPECT_EQ(KJH_FieldForMap(MAP_MAUVILLE_CITY_GYM, BATTLE_ENVIRONMENT_BUILDING).type, TYPE_ELECTRIC);
    EXPECT(!KJH_FieldForMap(MAP_MAUVILLE_CITY_GYM, BATTLE_ENVIRONMENT_BUILDING).boostOnly);
    EXPECT_EQ(KJH_FieldForMap(MAP_LAVARIDGE_TOWN_GYM_B1F, BATTLE_ENVIRONMENT_BUILDING).type, TYPE_FIRE);
    EXPECT_EQ(KJH_FieldForMap(MAP_PETALBURG_CITY_GYM, BATTLE_ENVIRONMENT_BUILDING).type, TYPE_NORMAL);
    EXPECT_EQ(KJH_FieldForMap(MAP_FORTREE_CITY_GYM, BATTLE_ENVIRONMENT_BUILDING).type, TYPE_FLYING);
    EXPECT_EQ(KJH_FieldForMap(MAP_MOSSDEEP_CITY_GYM, BATTLE_ENVIRONMENT_BUILDING).type, TYPE_PSYCHIC);
    EXPECT_EQ(KJH_FieldForMap(MAP_SOOTOPOLIS_CITY_GYM_1F, BATTLE_ENVIRONMENT_BUILDING).type, TYPE_WATER);
    // The Elite Four's rooms use their member's type; Wallace's room is neutral
    EXPECT_EQ(KJH_FieldForMap(MAP_EVER_GRANDE_CITY_SIDNEYS_ROOM, BATTLE_ENVIRONMENT_BUILDING).type, TYPE_DARK);
    EXPECT_EQ(KJH_FieldForMap(MAP_EVER_GRANDE_CITY_PHOEBES_ROOM, BATTLE_ENVIRONMENT_BUILDING).type, TYPE_GHOST);
    EXPECT_EQ(KJH_FieldForMap(MAP_EVER_GRANDE_CITY_GLACIAS_ROOM, BATTLE_ENVIRONMENT_BUILDING).type, TYPE_ICE);
    EXPECT_EQ(KJH_FieldForMap(MAP_EVER_GRANDE_CITY_DRAKES_ROOM, BATTLE_ENVIRONMENT_BUILDING).type, TYPE_DRAGON);
    EXPECT_EQ(KJH_FieldForMap(MAP_EVER_GRANDE_CITY_CHAMPIONS_ROOM, BATTLE_ENVIRONMENT_BUILDING).type, TYPE_NONE);
}

TEST("KJH: field, Hoenn's special places are set by hand, wherever the battle is fought on them")
{
    EXPECT_EQ(KJH_FieldForMap(MAP_FIERY_PATH, BATTLE_ENVIRONMENT_CAVE).type, TYPE_FIRE);
    EXPECT_EQ(KJH_FieldForMap(MAP_MT_CHIMNEY, BATTLE_ENVIRONMENT_MOUNTAIN).type, TYPE_FIRE);
    EXPECT_EQ(KJH_FieldForMap(MAP_MT_PYRE_4F, BATTLE_ENVIRONMENT_BUILDING).type, TYPE_GHOST);
    EXPECT_EQ(KJH_FieldForMap(MAP_SHOAL_CAVE_LOW_TIDE_ICE_ROOM, BATTLE_ENVIRONMENT_CAVE).type, TYPE_ICE);
    EXPECT_EQ(KJH_FieldForMap(MAP_NEW_MAUVILLE_INSIDE, BATTLE_ENVIRONMENT_BUILDING).type, TYPE_ELECTRIC);
    EXPECT_EQ(KJH_FieldForMap(MAP_PETALBURG_WOODS, BATTLE_ENVIRONMENT_GRASS).type, TYPE_BUG);
    EXPECT_EQ(KJH_FieldForMap(MAP_SKY_PILLAR_3F, BATTLE_ENVIRONMENT_CAVE).type, TYPE_DRAGON);
    EXPECT_EQ(KJH_FieldForMap(MAP_ABANDONED_SHIP_ROOMS_B1F, BATTLE_ENVIRONMENT_POND).type, TYPE_GHOST);
    // a cave without a hand-set field (Granite Cave's 1F has the Steel master's, test/kjh/masters.c)
    EXPECT_EQ(KJH_FieldForMap(MAP_GRANITE_CAVE_B1F, BATTLE_ENVIRONMENT_CAVE).type, TYPE_ROCK);
}
