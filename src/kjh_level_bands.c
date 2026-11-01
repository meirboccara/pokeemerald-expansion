// KJH: level bands (include/kjh_level_bands.h). No GBA dependencies, so it is unit-tested on the host
// (kjh_tools/test/test_level_bands.c).
#include "kjh_level_bands.h"
#include "constants/global.h"
#include "constants/pokemon.h"

u8 KJH_BandLevel(u8 band, u8 level)
{
    s32 l = level;
    switch (band)
    {
    case KJH_BAND_JOHTO:
        l = 58 + ((l - 2) * 9) / 20;
        break;
    case KJH_BAND_JOHTO_LEAGUE:
        l = 80 + ((l - 63) * 2) / 3;
        break;
    case KJH_BAND_HOENN:
        l = 80 + ((l - 5) * 9) / 25;
        break;
    default:
        break;
    }
    if (l < 1)
        l = 1;
    if (l > MAX_LEVEL)
        l = MAX_LEVEL;
    return l;
}

u8 KJH_PartyLevel(const u8 *levels, u8 count, u8 topN)
{
    u8 sorted[PARTY_SIZE];
    u16 sum = 0;
    u8 i, j;

    if (count > PARTY_SIZE)
        count = PARTY_SIZE;
    if (topN == 0 || topN > count)
        topN = count;
    if (topN == 0)
        return 1;
    for (i = 0; i < count; i++)
        sorted[i] = levels[i];
    // the topN best levels, highest first (6 Pokemon at most: a selection sort is plenty)
    for (i = 0; i < topN; i++)
    {
        for (j = i + 1; j < count; j++)
        {
            if (sorted[j] > sorted[i])
            {
                u8 t = sorted[i];
                sorted[i] = sorted[j];
                sorted[j] = t;
            }
        }
        sum += sorted[i];
    }
    return sum / topN;
}

// How far the catch-up target sits from the party's level, by badges (all regions together), after Pokemon
// Unbound's badge-based level scales: gentle while the party is small, a boss's ace above the party only late.
static const struct
{
    u8 minBadges;
    s8 normal; // a normal trainer's best Pokemon
    s8 boss;   // a boss's ace
} sCatchUp[] = {
    {6, -2, +1},
    {3, -2,  0},
    {0, -3, -1},
};

u8 KJH_TrainerLevelBoost(u8 teamTop, u8 partyLevel, u8 badges, bool8 boss)
{
    s16 target;
    u8 i = 0;

    while (badges < sCatchUp[i].minBadges)
        i++;
    target = partyLevel + (boss ? sCatchUp[i].boss : sCatchUp[i].normal);
    if (target > MAX_LEVEL)
        target = MAX_LEVEL;
    return target > teamTop ? target - teamTop : 0;
}
