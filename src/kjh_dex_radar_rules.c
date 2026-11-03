// KJH (ENG-8, CF-7): the route radar, the rules (include/kjh_dex_radar.h). No game state: tested in
// test/kjh/dex_radar.c. Ported from KJH's pokefirered tree, with the headbutt tables and the swarm added.
#include "global.h"
#include "kjh_dex_radar.h"

// Slot chances, as in src/data/wild_encounters.json's "fields". Fishing: slots 0-1 old rod, 2-4 good rod, 5-9 super
// rod. Headbutt (both tables): kjh_headbutt.c's sHeadbuttSlotRates.
static const u8 sLandRates[] = {20, 20, 10, 10, 10, 10, 5, 5, 4, 4, 1, 1};
static const u8 sWaterRockRates[] = {60, 30, 5, 4, 1};
static const u8 sFishingRates[] = {70, 30, 60, 20, 20, 40, 40, 15, 4, 1};
static const u8 sHeadbuttRates[] = {50, 15, 15, 10, 5, 5};

static const u8 *const sTableRates[KJH_RADAR_TABLE_COUNT] =
{
    [KJH_RADAR_TABLE_LAND]          = sLandRates,
    [KJH_RADAR_TABLE_WATER]         = sWaterRockRates,
    [KJH_RADAR_TABLE_ROCK_SMASH]    = sWaterRockRates,
    [KJH_RADAR_TABLE_FISHING]       = sFishingRates,
    [KJH_RADAR_TABLE_HEADBUTT]      = sHeadbuttRates,
    [KJH_RADAR_TABLE_HEADBUTT_RARE] = sHeadbuttRates,
};

static const u8 sTableSlots[KJH_RADAR_TABLE_COUNT] =
{
    [KJH_RADAR_TABLE_LAND]          = ARRAY_COUNT(sLandRates),
    [KJH_RADAR_TABLE_WATER]         = ARRAY_COUNT(sWaterRockRates),
    [KJH_RADAR_TABLE_ROCK_SMASH]    = ARRAY_COUNT(sWaterRockRates),
    [KJH_RADAR_TABLE_FISHING]       = ARRAY_COUNT(sFishingRates),
    [KJH_RADAR_TABLE_HEADBUTT]      = ARRAY_COUNT(sHeadbuttRates),
    [KJH_RADAR_TABLE_HEADBUTT_RARE] = ARRAY_COUNT(sHeadbuttRates),
};

u8 KJH_RadarSlotMethod(u8 table, u8 slot)
{
    switch (table)
    {
    case KJH_RADAR_TABLE_WATER:
        return KJH_RADAR_SURF;
    case KJH_RADAR_TABLE_ROCK_SMASH:
        return KJH_RADAR_ROCK_SMASH;
    case KJH_RADAR_TABLE_FISHING:
        if (slot < 2)
            return KJH_RADAR_OLD_ROD;
        if (slot < 5)
            return KJH_RADAR_GOOD_ROD;
        return KJH_RADAR_SUPER_ROD;
    case KJH_RADAR_TABLE_HEADBUTT:
        return KJH_RADAR_HEADBUTT;
    case KJH_RADAR_TABLE_HEADBUTT_RARE:
        return KJH_RADAR_HEADBUTT_RARE;
    default:
        return KJH_RADAR_GRASS;
    }
}

u8 KJH_RadarTableSlots(u8 table)
{
    return table < KJH_RADAR_TABLE_COUNT ? sTableSlots[table] : 0;
}

u8 KJH_RadarSlotRate(u8 table, u8 slot)
{
    if (slot >= KJH_RadarTableSlots(table))
        return 0;
    return sTableRates[table][slot];
}

static struct KjhRadarEntry *FindEntry(struct KjhRadarEntry *entries, u8 count, u16 species, u8 method)
{
    for (u32 i = 0; i < count; i++)
    {
        if (entries[i].species == species && entries[i].method == method)
            return &entries[i];
    }
    return NULL;
}

static u8 AddEntry(struct KjhRadarEntry *entries, u8 count, u8 max, u16 species, u8 method, u8 rate)
{
    struct KjhRadarEntry *entry;

    if (species == SPECIES_NONE)
        return count;
    entry = FindEntry(entries, count, species, method);
    if (entry != NULL)
    {
        entry->rate += rate;
        return count;
    }
    if (count >= max)
        return count;
    entries[count].species = species;
    entries[count].method = method;
    entries[count].rate = rate;
    return count + 1;
}

u8 KJH_RadarAddSlot(struct KjhRadarEntry *entries, u8 count, u8 max, u16 species, u8 table, u8 slot)
{
    return AddEntry(entries, count, max, species, KJH_RadarSlotMethod(table, slot), KJH_RadarSlotRate(table, slot));
}

u8 KJH_RadarMergeMap(struct KjhRadarEntry *route, u8 count, u8 max, const struct KjhRadarEntry *map, u8 mapCount)
{
    struct KjhRadarEntry *entry;

    for (u32 i = 0; i < mapCount; i++)
    {
        entry = FindEntry(route, count, map[i].species, map[i].method);
        if (entry != NULL)
        {
            if (map[i].rate > entry->rate)
                entry->rate = map[i].rate;
        }
        else if (count < max)
        {
            route[count++] = map[i];
        }
    }
    return count;
}

static bool32 ComesBefore(const struct KjhRadarEntry *a, const struct KjhRadarEntry *b)
{
    if (a->method != b->method)
        return a->method < b->method;
    if (a->rate != b->rate)
        return a->rate > b->rate;
    return a->species < b->species;
}

void KJH_RadarSort(struct KjhRadarEntry *entries, u8 count)
{
    struct KjhRadarEntry entry;
    u32 j;

    // insertion sort: a route has a few dozen entries at most
    for (u32 i = 1; i < count; i++)
    {
        entry = entries[i];
        for (j = i; j > 0 && ComesBefore(&entry, &entries[j - 1]); j--)
            entries[j] = entries[j - 1];
        entries[j] = entry;
    }
}

u8 KJH_RadarAddSpecies(u16 *species, u8 count, u8 max, u16 newSpecies)
{
    if (newSpecies == SPECIES_NONE || count >= max)
        return count;
    for (u32 i = 0; i < count; i++)
    {
        if (species[i] == newSpecies)
            return count;
    }
    species[count] = newSpecies;
    return count + 1;
}

static bool32 IsSwarmedMethod(u8 method, u8 swarmMethod)
{
    if (swarmMethod == KJH_RADAR_SWARM_LAND)
        return method == KJH_RADAR_GRASS;
    return method == KJH_RADAR_OLD_ROD || method == KJH_RADAR_GOOD_ROD || method == KJH_RADAR_SUPER_ROD;
}

u8 KJH_RadarApplySwarm(struct KjhRadarEntry *entries, u8 count, u8 max, u16 species, u8 swarmMethod, u8 chance)
{
    bool32 found = FALSE;

    if (species == SPECIES_NONE || chance == 0)
        return count;
    if (chance > 100)
        chance = 100;
    for (u32 i = 0; i < count; i++)
    {
        if (IsSwarmedMethod(entries[i].method, swarmMethod))
        {
            // rounded, but a Pokemon still there never shows 0%
            entries[i].rate = max((entries[i].rate * (100 - chance) + 50) / 100, chance < 100 ? 1 : 0);
            found = TRUE;
        }
    }
    // a swarm on a map without that method's table (no grass, no water) never shows up
    if (!found)
        return count;
    return AddEntry(entries, count, max, species, swarmMethod, chance);
}
