// KJH: rules for boss trainers (include/kjh_boss_rules.h). No GBA dependencies, so they are unit-tested on
// the host (kjh_tools/test/test_boss_rules.c).
#include "kjh_boss_rules.h"
#include "constants/pokemon.h"

#define MAX_BOSS_EV 252

// STAT_ATK or STAT_SPATK
static u8 AttackStat(const u8 *baseStats, u16 physicalPower, u16 specialPower)
{
    if (physicalPower != specialPower)
        return physicalPower > specialPower ? STAT_ATK : STAT_SPATK;
    return baseStats[STAT_SPATK] > baseStats[STAT_ATK] ? STAT_SPATK : STAT_ATK;
}

// The best of HP, Defense, Speed and Sp. Def (Speed first on a tie)
static u8 BestOtherStat(const u8 *baseStats)
{
    static const u8 sOrder[] = {STAT_SPEED, STAT_HP, STAT_DEF, STAT_SPDEF};
    u8 best = sOrder[0], i;

    for (i = 1; i < sizeof(sOrder); i++)
    {
        if (baseStats[sOrder[i]] > baseStats[best])
            best = sOrder[i];
    }
    return best;
}

void KJH_BossEvs(const u8 *baseStats, u16 physicalPower, u16 specialPower, u8 badges, u8 *evs)
{
    u8 amount, i;

    if (badges > KJH_BOSS_FULL_EV_BADGES)
        badges = KJH_BOSS_FULL_EV_BADGES;
    // a little at the first gym already, full from KJH_BOSS_FULL_EV_BADGES on; EVs count in steps of 4
    amount = (MAX_BOSS_EV * (badges + 1) / (KJH_BOSS_FULL_EV_BADGES + 1)) & ~3;
    for (i = 0; i < NUM_STATS; i++)
        evs[i] = 0;
    evs[AttackStat(baseStats, physicalPower, specialPower)] = amount;
    evs[BestOtherStat(baseStats)] = amount;
}

u8 KJH_BossNature(const u8 *baseStats, u16 physicalPower, u16 specialPower)
{
    u8 raised = AttackStat(baseStats, physicalPower, specialPower);
    u8 other = raised == STAT_ATK ? STAT_SPATK : STAT_ATK;
    u16 otherPower = raised == STAT_ATK ? specialPower : physicalPower;
    u8 lowered = other;

    if (otherPower != 0)
        lowered = baseStats[STAT_DEF] <= baseStats[STAT_SPDEF] ? STAT_DEF : STAT_SPDEF;
    // Gen 3 natures: 5 per raised stat, in the order Attack, Defense, Speed, Sp. Atk, Sp. Def
    return (raised - STAT_ATK) * 5 + (lowered - STAT_ATK);
}

u8 KJH_SlideToShow(u8 monsLeft, u16 hp, u16 maxHp, u8 shown)
{
    if (monsLeft != 1 || hp == 0)
        return KJH_SLIDE_NONE;
    if (!(shown & (1 << KJH_SLIDE_LAST_MON)))
        return KJH_SLIDE_LAST_MON;
    if (!(shown & (1 << KJH_SLIDE_LAST_LOW_HP)) && hp * 4 <= maxHp)
        return KJH_SLIDE_LAST_LOW_HP;
    return KJH_SLIDE_NONE;
}
