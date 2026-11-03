// KJH: wild packs, the rules (include/kjh_pack.h).
#include "global.h"
#include "kjh_pack.h"
#include "pokemon.h"

bool32 KJH_PackSpeciesAllowed(enum Species species)
{
    const struct SpeciesInfo *info = &gSpeciesInfo[species];

    if (species == SPECIES_NONE || species == SPECIES_UNOWN)
        return FALSE;
    return !(info->isRestrictedLegendary || info->isSubLegendary || info->isMythical || info->isUltraBeast);
}

u32 KJH_PackLeaderLevel(u32 level)
{
    return min(level + KJH_PACK_LEADER_LEVEL_BONUS, MAX_LEVEL);
}

u32 KJH_PackCatchRate(u32 catchRate, bool32 leader)
{
    if (!leader)
        return catchRate;
    return max(catchRate / 2, 1);
}

u32 KJH_PackExp(u32 exp, enum KjhPackRole role)
{
    switch (role)
    {
    case KJH_PACK_ROLE_LEADER:
        return exp * KJH_PACK_LEADER_EXP_MULTIPLIER;
    case KJH_PACK_ROLE_LEADER_HELPER:
        return exp * KJH_PACK_HELPER_EXP_MULTIPLIER;
    default:
        return exp;
    }
}
