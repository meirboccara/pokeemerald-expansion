// KJH: the team's level follows Kanto's zones (LV-2), and Johto's (LV-18) (include/kjh_team_level.h).
#include "global.h"
#include "event_data.h"
#include "kjh_team_level.h"
#include "overworld.h"
#include "pokemon.h"
#include "script.h"
#include "constants/map_groups.h"
#include "constants/region_map_sections.h"
#include "constants/johto_flags.h"
#include "data/kjh_kanto_zones.h"
#include "data/kjh_johto_zones.h"

extern const u8 EventScript_KjhTeamFeelsStronger[];

#define NO_LEAGUE_FLAG 0 // a region whose League isn't in the game yet

// A region's zone tables, the variables that keep its furthest zone's top and the team level last applied there (for
// "Your team feels stronger!": crossing back to a region whose level is higher isn't a rise), its first badge's flag
// and the flag of its League beaten (NO_LEAGUE_FLAG: its League isn't in the game yet).
struct KjhRegionZones
{
    const struct KjhZoneRange *zones;
    const struct KjhMapZone *mapZones;
    const struct KjhMapsecZone *mapsecZones;
    const struct KjhGymAce *gyms;
    u8 mapZoneCount;
    u8 mapsecZoneCount;
    u8 gymCount;
    u16 zoneTopVar;
    u16 teamLevelVar;
    u16 firstBadgeFlag;
    u16 leagueFlag;
};

static const struct KjhRegionZones sRegions[KJH_REGION_COUNT] =
{
    [KJH_REGION_KANTO] =
    {
        .zones = sKantoZones,
        .mapZones = sKantoMapZones,
        .mapsecZones = sKantoMapsecZones,
        .gyms = sKantoGyms,
        .mapZoneCount = ARRAY_COUNT(sKantoMapZones),
        .mapsecZoneCount = ARRAY_COUNT(sKantoMapsecZones),
        .gymCount = ARRAY_COUNT(sKantoGyms),
        .zoneTopVar = VAR_KJH_KANTO_ZONE_TOP,
        .teamLevelVar = VAR_KJH_TEAM_LEVEL,
        .firstBadgeFlag = FLAG_BADGE01_GET,
        .leagueFlag = FLAG_SYS_GAME_CLEAR,
    },
    [KJH_REGION_JOHTO] =
    {
        .zones = sJohtoZones,
        .mapZones = sJohtoMapZones,
        .mapsecZones = sJohtoMapsecZones,
        .gyms = sJohtoGyms,
        .mapZoneCount = ARRAY_COUNT(sJohtoMapZones),
        .mapsecZoneCount = ARRAY_COUNT(sJohtoMapsecZones),
        .gymCount = ARRAY_COUNT(sJohtoGyms),
        .zoneTopVar = VAR_KJH_JOHTO_ZONE_TOP,
        .teamLevelVar = VAR_KJH_JOHTO_TEAM_LEVEL,
        .firstBadgeFlag = FLAG_JOHTO_BADGE01_GET,
        .leagueFlag = NO_LEAGUE_FLAG, // Johto's League comes with ENG-10
    },
};

// Johto's generated variables (constants/johto_vars.h) end well before these two
STATIC_ASSERT(VAR_KJH_JOHTO_TEAM_LEVEL >= VAR_J_SCENE_ROUTE_34_ILEX_FOREST_GATE + 1
              && VAR_KJH_JOHTO_ZONE_TOP < JOHTO_VARS_START + JOHTO_VARS_COUNT, KjhJohtoLevelVarsInJohtoVarSpace);

bool32 KJH_IsLevelsFree(void)
{
    return FlagGet(FLAG_KJH_LEVELLESS);
}

// The zone of a place in a region's tables, 0 (its NONE) if it isn't in them.
static u32 ZoneIn(const struct KjhRegionZones *region, u32 mapsec, u32 map)
{
    for (u32 i = 0; i < region->mapZoneCount; i++)
    {
        if (region->mapZones[i].map == map)
            return region->mapZones[i].zone;
    }

    for (u32 i = 0; i < region->mapsecZoneCount; i++)
    {
        if (region->mapsecZones[i].mapsec == mapsec)
            return region->mapsecZones[i].zone;
    }

    return 0;
}

// Kanto's tables are looked at first: a map in two regions' tables (Indigo Plateau's rooms, when ENG-10 gives them a
// Johto season) is Kanto's until then.
enum KjhRegion KJH_RegionOf(u32 mapsec, u32 map)
{
    for (enum KjhRegion region = KJH_REGION_KANTO; region < KJH_REGION_COUNT; region++)
    {
        if (ZoneIn(&sRegions[region], mapsec, map))
            return region;
    }

    return KJH_REGION_NONE;
}

u32 KJH_ZoneTop(u32 mapsec, u32 map)
{
    for (enum KjhRegion region = KJH_REGION_KANTO; region < KJH_REGION_COUNT; region++)
    {
        u32 zone = ZoneIn(&sRegions[region], mapsec, map);

        if (zone)
            return sRegions[region].zones[zone].max;
    }

    return 0;
}

u32 KJH_TeamLevelCap(u32 badges)
{
    return sTeamLevelCaps[min(badges, NUM_BADGES)];
}

static u32 CountRegionBadges(enum KjhRegion region)
{
    u32 count = 0;

    for (u32 i = 0; i < NUM_BADGES; i++)
    {
        if (FlagGet(sRegions[region].firstBadgeFlag + i))
            count++;
    }

    return count;
}

u32 KJH_CountKantoBadges(void)
{
    return CountRegionBadges(KJH_REGION_KANTO);
}

static u32 CurrentMapId(void)
{
    return (gSaveBlock1Ptr->location.mapGroup << 8) | gSaveBlock1Ptr->location.mapNum;
}

// The region the player stands in; Kanto outside every region.
enum KjhRegion KJH_RegionHere(void)
{
    enum KjhRegion region = KJH_RegionOf(gMapHeader.regionMapSectionId, CurrentMapId());

    return region == KJH_REGION_NONE ? KJH_REGION_KANTO : region;
}

u32 KJH_CountBadgesHere(void)
{
    return CountRegionBadges(KJH_RegionHere());
}

u32 KJH_TeamLevel(void)
{
    enum KjhRegion region = KJH_RegionHere();

    // KJH (LV-3): the region's League beaten, the region uses its Champion's level.
    if (sRegions[region].leagueFlag != NO_LEAGUE_FLAG && FlagGet(sRegions[region].leagueFlag))
        return KJH_TeamLevelCap(NUM_BADGES);

    return min(VarGet(sRegions[region].zoneTopVar), KJH_TeamLevelCap(CountRegionBadges(region)));
}

// The top of the zone the player stands in, 0 outside every region.
static u32 CurrentZoneTop(void)
{
    return KJH_ZoneTop(gMapHeader.regionMapSectionId, CurrentMapId());
}

// The ace of the Gym the player stands in (its region's Gyms), 0 outside a Gym.
static u32 CurrentGymAce(void)
{
    const struct KjhRegionZones *region = &sRegions[KJH_RegionHere()];
    u32 map = CurrentMapId();

    for (u32 i = 0; i < region->gymCount; i++)
    {
        if (region->gyms[i].map == map)
            return region->gyms[i].ace;
    }

    return 0;
}

bool32 KJH_IsInGym(void)
{
    return CurrentGymAce() != 0;
}

s32 KJH_GymLevelShift(void)
{
    u32 ace = CurrentGymAce();

    if (!KJH_IsLevelsFree() || ace == 0)
        return 0;

    return (s32)KJH_TeamLevelCap(KJH_CountBadgesHere()) - (s32)ace;
}

void KJH_RecordZone(void)
{
    u32 top = CurrentZoneTop();
    u16 zoneTopVar = sRegions[KJH_RegionHere()].zoneTopVar;

    if (top > VarGet(zoneTopVar))
        VarSet(zoneTopVar, top);
}

// The team level applies only on a region's maps (Hoenn's come with ENG-9's step 2).
static bool32 TeamLevelApplies(void)
{
    return KJH_IsLevelsFree() && CurrentZoneTop() != 0;
}

void KJH_SetMonLevel(struct Pokemon *mon, u32 level)
{
    enum Species species = GetMonData(mon, MON_DATA_SPECIES);
    u32 exp;

    if (species == SPECIES_NONE || GetMonData(mon, MON_DATA_IS_EGG) || level == 0)
        return;

    if (GetMonData(mon, MON_DATA_LEVEL) != level)
    {
        exp = gExperienceTables[gSpeciesInfo[species].growthRate][level];
        SetMonData(mon, MON_DATA_EXP, &exp);
        CalculateMonStats(mon);
    }

    if (GetMonData(mon, MON_DATA_PEAK_LEVEL) < level)
        SetMonData(mon, MON_DATA_PEAK_LEVEL, &level);
}

void KJH_JoinTeam(struct Pokemon *mon, bool32 caught)
{
    u32 level;

    if (!TeamLevelApplies() || GetMonData(mon, MON_DATA_IS_EGG))
        return;

    KJH_RecordZone();
    level = KJH_TeamLevel();
    if (level == 0)
        return;

    KJH_SetMonLevel(mon, level);
    if (caught)
        SetMonData(mon, MON_DATA_MET_LEVEL, &level);
}

void KJH_ApplyTeamLevelToParty(void)
{
    u32 i, level = KJH_TeamLevel();

    for (i = 0; i < PARTY_SIZE; i++)
        KJH_SetMonLevel(&gParties[B_TRAINER_PLAYER][i], level);
}

bool32 KJH_TryTeamLevelStep(void)
{
    u32 level, before;
    u16 teamLevelVar;

    if (!TeamLevelApplies())
        return FALSE;

    KJH_RecordZone();
    level = KJH_TeamLevel();
    KJH_ApplyTeamLevelToParty();
    teamLevelVar = sRegions[KJH_RegionHere()].teamLevelVar;
    before = VarGet(teamLevelVar);
    if (level == before)
        return FALSE;

    VarSet(teamLevelVar, level);
    if (before == 0 || level < before)
        return FALSE;

    gSpecialVar_0x8005 = before; // LV-10: the moves this rise unlocked (EventScript_KjhLibraryNewMoves)
    gSpecialVar_0x8006 = level;
    ScriptContext_SetupScript(EventScript_KjhTeamFeelsStronger);
    return TRUE;
}
