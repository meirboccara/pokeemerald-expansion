// KJH: a legendary fights as a boss (CF-12, include/kjh_legendary.h).
#include "global.h"
#include "battle.h"
#include "kjh_legendary.h"
#include "kjh_progression.h"
#include "pokemon.h"
#include "script.h"

EWRAM_DATA static bool8 sLegendaryBossBattle = FALSE;

u32 KJH_LegendaryBoostedStats(enum Species species)
{
    enum Stat best = STAT_HP, second = STAT_HP;

    for (enum Stat stat = STAT_ATK; stat < NUM_STATS; stat++)
    {
        u32 base = GetSpeciesBaseStat(species, stat);

        // Strictly higher, so a tie keeps the stat that came first.
        if (best == STAT_HP || base > GetSpeciesBaseStat(species, best))
        {
            second = best;
            best = stat;
        }
        else if (second == STAT_HP || base > GetSpeciesBaseStat(species, second))
        {
            second = stat;
        }
    }

    return (1 << best) | (1 << second);
}

void KJH_SetupLegendaryBoss(enum Species species)
{
    u32 stats = KJH_LegendaryBoostedStats(species);
    struct QueuedStatBoost *boost = &gQueuedStatBoosts[B_POSITION_OPPONENT_LEFT];

    for (enum Stat stat = STAT_ATK; stat < NUM_STATS; stat++)
    {
        if (stats & (1 << stat))
        {
            boost->stats |= 1 << stat;
            boost->statChanges[stat] = 1;
        }
    }

    sLegendaryBossBattle = TRUE;
}

// The wild Pokemon is the one setwildbattle put in the enemy party.
void KJH_ScriptSetupLegendaryBoss(struct ScriptContext *ctx)
{
    Script_RequestEffects(SCREFF_V1);
    KJH_SetupLegendaryBoss(GetMonData(&gParties[B_TRAINER_OPPONENT_A][0], MON_DATA_SPECIES));
}

bool32 KJH_IsLegendaryBossBattle(void)
{
    return sLegendaryBossBattle;
}

void KJH_EndLegendaryBossBattle(void)
{
    sLegendaryBossBattle = FALSE;
}

u64 KJH_LegendaryWildAiFlags(u64 wildFlags)
{
    if (sLegendaryBossBattle)
        return wildFlags | KJH_BOSS_AI_FLAGS;
    return wildFlags;
}
