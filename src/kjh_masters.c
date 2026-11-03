// KJH (LV-13): training masters (include/kjh_masters.h).
#include "global.h"
#include "battle.h"
#include "battle_setup.h"
#include "event_data.h"
#include "kjh_masters.h"
#include "kjh_team_level.h"
#include "pokemon.h"
#include "constants/opponents.h"

#define MASTER(t, flag) {TRAINER_KJH_MASTER_##t, TYPE_##t, FLAG_KJH_MASTER_##t##_ONCE, FLAG_KJH_MASTER_##t##_TWICE}

static const struct KjhMaster sMasters[KJH_MASTERS_COUNT] =
{
    MASTER(WATER, 0), MASTER(FIRE, 0), MASTER(ELECTRIC, 0), MASTER(GHOST, 0), MASTER(ICE, 0), MASTER(BUG, 0),
    MASTER(ROCK, 0), MASTER(FIGHTING, 0), MASTER(POISON, 0), MASTER(GROUND, 0), MASTER(NORMAL, 0),
};

const struct KjhMaster *KJH_GetMaster(u32 trainerId)
{
    for (u32 i = 0; i < ARRAY_COUNT(sMasters); i++)
    {
        if (sMasters[i].trainerId == trainerId)
            return &sMasters[i];
    }
    return NULL;
}

u32 KJH_MasterFightsLeftToday(u32 trainerId)
{
    const struct KjhMaster *master = KJH_GetMaster(trainerId);

    if (master == NULL || FlagGet(master->flagTwice))
        return 0;
    return FlagGet(master->flagOnce) ? 1 : 2;
}

void KJH_NoteMasterFought(u32 trainerId)
{
    const struct KjhMaster *master = KJH_GetMaster(trainerId);

    if (master == NULL)
        return;
    if (FlagGet(master->flagOnce))
        FlagSet(master->flagTwice);
    else
        FlagSet(master->flagOnce);
}

u32 KJH_MasterLevel(void)
{
    u32 level = 1;

    if (KJH_IsLevelsFree() && KJH_TeamLevel() > 0) // 0: no zone reached yet
        return KJH_TeamLevel();
    for (u32 i = 0; i < PARTY_SIZE; i++)
    {
        if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES) != SPECIES_NONE)
            level = max(level, GetMonData(&gPlayerParty[i], MON_DATA_LEVEL));
    }
    return level;
}

enum Type KJH_MasterBattleType(void)
{
    const struct KjhMaster *master;

    if (!(gBattleTypeFlags & BATTLE_TYPE_TRAINER) || TRAINER_BATTLE_PARAM.opponentA >= TRAINERS_COUNT)
        return TYPE_NONE;
    master = KJH_GetMaster(TRAINER_BATTLE_PARAM.opponentA);
    return master != NULL ? master->type : TYPE_NONE;
}

void KJH_SpecialMasterFightsLeft(void)
{
    gSpecialVar_Result = KJH_MasterFightsLeftToday(gSpecialVar_0x8004);
}

void KJH_SpecialMasterFought(void)
{
    KJH_NoteMasterFought(gSpecialVar_0x8004);
}
