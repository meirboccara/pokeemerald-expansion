// KJH: the team's level follows Kanto's zones (LV-2, include/kjh_team_level.h).
#include "global.h"
#include "event_data.h"
#include "kjh_team_level.h"
#include "overworld.h"
#include "pokemon.h"
#include "script.h"
#include "constants/map_groups.h"
#include "constants/region_map_sections.h"
#include "data/kjh_kanto_zones.h"

extern const u8 EventScript_KjhTeamFeelsStronger[];

bool32 KJH_IsLevelsFree(void)
{
    return FlagGet(FLAG_KJH_LEVELLESS);
}

u32 KJH_ZoneTop(u32 mapsec, u32 map)
{
    u32 i;

    for (i = 0; i < ARRAY_COUNT(sKantoMapZones); i++)
    {
        if (sKantoMapZones[i].map == map)
            return sKantoZones[sKantoMapZones[i].zone].max;
    }

    for (i = 0; i < ARRAY_COUNT(sKantoMapsecZones); i++)
    {
        if (sKantoMapsecZones[i].mapsec == mapsec)
            return sKantoZones[sKantoMapsecZones[i].zone].max;
    }

    return 0;
}

u32 KJH_TeamLevelCap(u32 badges)
{
    return sKantoTeamLevelCaps[min(badges, NUM_BADGES)];
}

static u32 CountKantoBadges(void)
{
    u32 i, count = 0;

    for (i = 0; i < NUM_BADGES; i++)
    {
        if (FlagGet(FLAG_BADGE01_GET + i))
            count++;
    }

    return count;
}

u32 KJH_TeamLevel(void)
{
    return min(VarGet(VAR_KJH_KANTO_ZONE_TOP), KJH_TeamLevelCap(CountKantoBadges()));
}

// The top of the zone the player stands in, 0 outside Kanto's table.
static u32 CurrentZoneTop(void)
{
    u32 map = (gSaveBlock1Ptr->location.mapGroup << 8) | gSaveBlock1Ptr->location.mapNum;

    return KJH_ZoneTop(gMapHeader.regionMapSectionId, map);
}

void KJH_RecordZone(void)
{
    u32 top = CurrentZoneTop();

    if (top > VarGet(VAR_KJH_KANTO_ZONE_TOP))
        VarSet(VAR_KJH_KANTO_ZONE_TOP, top);
}

// Kanto's team level applies only on Kanto's maps (Johto and Hoenn get their own with LV-18).
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

    if (!TeamLevelApplies())
        return FALSE;

    KJH_RecordZone();
    level = KJH_TeamLevel();
    KJH_ApplyTeamLevelToParty();
    before = VarGet(VAR_KJH_TEAM_LEVEL);
    if (level == before)
        return FALSE;

    VarSet(VAR_KJH_TEAM_LEVEL, level);
    if (before == 0 || level < before)
        return FALSE;

    gSpecialVar_0x8005 = before; // LV-10: the moves this rise unlocked (EventScript_KjhLibraryNewMoves)
    gSpecialVar_0x8006 = level;
    ScriptContext_SetupScript(EventScript_KjhTeamFeelsStronger);
    return TRUE;
}
