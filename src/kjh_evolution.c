// KJH: evolution by Training points (LV-9, include/kjh_evolution.h).
#include "global.h"
#include "battle.h"
#include "event_data.h"
#include "evolution_scene.h"
#include "kjh_bond.h"
#include "kjh_evolution.h"
#include "kjh_team_level.h"
#include "kjh_training.h"
#include "overworld.h"
#include "party_menu.h"
#include "pokemon.h"
#include "string_util.h"

// The Pokemon not ready to evolve when the battle started, by personality: a fair fight (LV-17) changes the party's
// order between the start and the end
static EWRAM_DATA u32 sNotReadyAtStart[PARTY_SIZE] = {0};
static EWRAM_DATA u8 sNotReadyCount = 0;

bool32 KJH_EvolutionTrainingKeyMet(struct Pokemon *mon, u32 index)
{
    if (!KJH_IsLevelsFree())
        return TRUE;
    return KJH_TrainingEarned(mon) >= KJH_TrainingGoalOfEvolution(GetMonData(mon, MON_DATA_SPECIES), index);
}

bool32 KJH_FriendshipEvolutionKeyMet(struct Pokemon *mon, u32 friendship, u32 threshold)
{
    if (!KJH_IsLevelsFree())
        return friendship >= threshold;
    return KJH_GetPeakBond(mon) >= KJH_EVOLUTION_BOND;
}

u32 KJH_LevelForEvolution(struct Pokemon *mon)
{
    u32 level = GetMonData(mon, MON_DATA_LEVEL);

    if (KJH_IsLevelsFree())
        level = max(level, GetMonData(mon, MON_DATA_PEAK_LEVEL));
    return level;
}

enum Species KJH_ReadyEvolution(struct Pokemon *mon)
{
    if (GetMonData(mon, MON_DATA_SPECIES) == SPECIES_NONE || GetMonData(mon, MON_DATA_IS_EGG))
        return SPECIES_NONE;
    return GetEvolutionTargetSpecies(mon, EVO_MODE_NORMAL, ITEM_NONE, NULL, NULL, CHECK_EVO);
}

void KJH_EvolutionBattleStart(void)
{
    sNotReadyCount = 0;
    if (!KJH_IsLevelsFree())
        return;
    for (u32 i = 0; i < PARTY_SIZE; i++)
    {
        struct Pokemon *mon = &gParties[B_TRAINER_PLAYER][i];

        if (GetMonData(mon, MON_DATA_SPECIES) != SPECIES_NONE && KJH_ReadyEvolution(mon) == SPECIES_NONE)
            sNotReadyAtStart[sNotReadyCount++] = GetMonData(mon, MON_DATA_PERSONALITY);
    }
}

static bool32 WasNotReadyAtStart(u32 personality)
{
    for (u32 i = 0; i < sNotReadyCount; i++)
    {
        if (sNotReadyAtStart[i] == personality)
            return TRUE;
    }
    return FALSE;
}

void KJH_EvolutionBattleEnd(void)
{
    if (KJH_IsLevelsFree())
    {
        for (u32 i = 0; i < PARTY_SIZE; i++)
        {
            struct Pokemon *mon = &gParties[B_TRAINER_PLAYER][i];

            if (KJH_ReadyEvolution(mon) != SPECIES_NONE && WasNotReadyAtStart(GetMonData(mon, MON_DATA_PERSONALITY)))
                gLeveledUpInBattle |= 1u << i;
        }
    }
    sNotReadyCount = 0;
}

// The level of the species' evolution into this target (0: not by level)
static u32 EvolutionLevelInto(enum Species species, enum Species target)
{
    const struct Evolution *evolutions = GetSpeciesEvolutions(species);

    for (u32 i = 0; evolutions != NULL && evolutions[i].method != EVOLUTIONS_END; i++)
    {
        if (evolutions[i].method == EVO_LEVEL && evolutions[i].targetSpecies == target)
            return evolutions[i].param;
    }
    return 0;
}

u16 KJH_BufferNextRiseEvolution(void)
{
    for (; gSpecialVar_0x8004 < PARTY_SIZE; gSpecialVar_0x8004++)
    {
        struct Pokemon *mon = &gParties[B_TRAINER_PLAYER][gSpecialVar_0x8004];
        enum Species target = KJH_ReadyEvolution(mon);

        // ready by the new level, not by the old one: one put off before is left for the party menu, and so is a
        // veteran whose peak level is past the new one (it was ready before)
        if (target != SPECIES_NONE && GetMonData(mon, MON_DATA_PEAK_LEVEL) <= gSpecialVar_0x8006
         && EvolutionLevelInto(GetMonData(mon, MON_DATA_SPECIES), target) > gSpecialVar_0x8005)
        {
            GetMonNickname(mon, gStringVar1);
            return TRUE;
        }
    }
    return FALSE;
}

bool32 KJH_BeginReadyEvolution(u32 partyId, MainCallback afterwards)
{
    struct Pokemon *mon = &gParties[B_TRAINER_PLAYER][partyId];
    bool32 canStopEvo = TRUE;
    enum Species target = GetEvolutionTargetSpecies(mon, EVO_MODE_NORMAL, ITEM_NONE, NULL, &canStopEvo, CHECK_EVO);

    if (target == SPECIES_NONE)
        return FALSE;
    GetEvolutionTargetSpecies(mon, EVO_MODE_NORMAL, ITEM_NONE, NULL, &canStopEvo, DO_EVO);
    gCB2_AfterEvolution = afterwards;
    BeginEvolutionScene(mon, target, canStopEvo, partyId);
    return TRUE;
}

u16 KJH_EvolveFromScript(void)
{
    return KJH_BeginReadyEvolution(gSpecialVar_0x8004, CB2_ReturnToFieldContinueScript);
}
