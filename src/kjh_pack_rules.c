// KJH: wild packs, the rules (include/kjh_pack.h).
#include "global.h"
#include "kjh_pack.h"
#include "pokemon.h"

bool32 KJH_PackSpeciesAllowed(enum Species species)
{
    const struct SpeciesInfo *info = &gSpeciesInfo[species];

    if (species == SPECIES_NONE || species == SPECIES_UNOWN) return FALSE;
    return !KJH_IsLegendarySpecies(species) && !info->isUltraBeast;
}

u32 KJH_PackLeaderLevel(u32 level)
{
    return min(level + KJH_PACK_LEADER_LEVEL_BONUS, MAX_LEVEL);
}

u32 KJH_AlphaLevel(u32 level)
{
    return min(level + KJH_ALPHA_LEVEL_BONUS, MAX_LEVEL);
}

void KJH_LeaderIvs(u8 *ivs, enum Stat perfect1, enum Stat perfect2)
{
    for (enum Stat stat = STAT_HP; stat < NUM_STATS; stat++)
    {
        if (ivs[stat] < KJH_LEADER_MIN_IV)
        {
            ivs[stat] = KJH_LEADER_MIN_IV;
        }
    }

    ivs[perfect1] = MAX_PER_STAT_IVS;
    ivs[perfect2] = MAX_PER_STAT_IVS;
}

bool32 KJH_IsStarterSpecies(enum Species species)
{
    static const u16 sStarters[] =
    {
        SPECIES_BULBASAUR, SPECIES_CHARMANDER, SPECIES_SQUIRTLE,
        SPECIES_CHIKORITA, SPECIES_CYNDAQUIL, SPECIES_TOTODILE,
        SPECIES_TREECKO, SPECIES_TORCHIC, SPECIES_MUDKIP,
    };

    for (u32 i = 0; i < ARRAY_COUNT(sStarters); i++)
    {
        if (sStarters[i] == species) return TRUE;
    }

    return FALSE;
}

bool32 KJH_IsLegendarySpecies(enum Species species)
{
    const struct SpeciesInfo *info = &gSpeciesInfo[species];

    return species != SPECIES_NONE && (info->isRestrictedLegendary || info->isSubLegendary || info->isMythical);
}

u32 KJH_PackCatchRate(u32 catchRate, bool32 leader)
{
    if (!leader) return catchRate;
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

u32 KJH_PackHelperLevel(u32 callerLevel, bool32 callerIsLeader, u32 levelDrop)
{
    s32 level = callerLevel;

    if (callerIsLeader)
    {
        level -= KJH_PACK_LEADER_LEVEL_BONUS;
    }
    level -= levelDrop;
    return max(level, 1);
}

u32 KJH_PackCallChance(bool32 leader, u32 helpersCalled, bool32 freeSlot, bool32 firstTurn, u32 hp, u32 maxHp)
{
    u32 chance;

    if (helpersCalled >= KJH_PACK_MAX_HELPERS) return 0;
    if (!leader) return KJH_PACK_CALL_ORDINARY;
    if (firstTurn) return 0;

    if (hp * 4 <= maxHp)
    {
        chance = KJH_PACK_CALL_LEADER_DESPERATE;
    }
    else if (hp * 2 <= maxHp)
    {
        chance = KJH_PACK_CALL_LEADER_HURT;
    }
    else
    {
        chance = KJH_PACK_CALL_LEADER_HEALTHY;
    }
    return freeSlot ? chance : chance / 2;
}

u32 KJH_PackAnswerChance(bool32 leader)
{
    return leader ? KJH_PACK_ANSWER_LEADER : KJH_PACK_ANSWER_ORDINARY;
}

u32 KJH_PackPartnerSlot(const bool8 *usable, u32 fighting)
{
    for (u32 i = 0; i < PARTY_SIZE; i++)
    {
        if (i != fighting && usable[i]) return i;
    }
    return KJH_PACK_NO_PARTNER;
}

u32 KJH_PackEmptySlot(const bool8 *usable, u32 fighting)
{
    for (u32 i = 0; i < PARTY_SIZE; i++)
    {
        if (i != fighting && !usable[i]) return i;
    }
    return fighting == 0 ? 1 : 0; // unreachable when there is no partner
}

void KJH_PackPutPartnerSecond(u8 *order, u32 partnerSlot)
{
    u8 slots[PARTY_SIZE];

    for (u32 i = 0; i < PARTY_SIZE / 2; i++)
    {
        slots[i * 2] = order[i] >> 4;
        slots[i * 2 + 1] = order[i] & 0xF;
    }
    for (u32 i = 0; i < PARTY_SIZE; i++)
    {
        if (slots[i] == partnerSlot)
        {
            slots[i] = slots[1];
            slots[1] = partnerSlot;
            break;
        }
    }
    for (u32 i = 0; i < PARTY_SIZE / 2; i++)
    {
        order[i] = (slots[i * 2] << 4) | slots[i * 2 + 1];
    }
}
