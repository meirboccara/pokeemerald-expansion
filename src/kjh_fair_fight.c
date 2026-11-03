// KJH (LV-17): fair fights (include/kjh_fair_fight.h).
#include "global.h"
#include "battle_setup.h"
#include "data.h"
#include "event_data.h"
#include "kjh_fair_fight.h"
#include "kjh_progression.h"
#include "main.h"
#include "overworld.h"
#include "party_menu.h"
#include "pokemon.h"
#include "string_util.h"

// The whole party while the chosen Pokemon fight, and where each fighter came from (gSelectedOrderFromParty: slot + 1)
static EWRAM_DATA struct Pokemon sWaitingParty[PARTY_SIZE] = {0};
static EWRAM_DATA u8 sFighterSlots[PARTY_SIZE] = {0};
static EWRAM_DATA bool8 sFairFightActive = FALSE;

static u32 CountHealthyMons(void)
{
    u32 count = 0;
    for (u32 i = 0; i < PARTY_SIZE; i++)
    {
        if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES) != SPECIES_NONE
         && !GetMonData(&gPlayerParty[i], MON_DATA_IS_EGG)
         && GetMonData(&gPlayerParty[i], MON_DATA_HP) != 0)
            count++;
    }
    return count;
}

u16 KJH_FairFightCount(void)
{
    u32 trainer = gSpecialVar_0x8004, count;

    if (!IS_FRLG || trainer == TRAINER_NONE || HasTrainerBeenFought(trainer))
        return 0;
    if (KJH_BossKind(GetTrainerClassFromId(trainer)) != KJH_BOSS_LEADER)
        return 0;
    count = GetTrainerPartySizeFromId(trainer);
    if (count == 0 || CountHealthyMons() <= count)
        return 0; // fewer healthy Pokemon than needed: fight with what you have
    if (count > ARRAY_COUNT(gSelectedOrderFromParty))
        return 0; // the party menu picks at most MAX_FRONTIER_PARTY_SIZE: a bigger team faces the whole party
    StringCopy(gStringVar1, GetTrainerNameFromId(trainer));
    ConvertIntToDecimalStringN(gStringVar2, count, STR_CONV_MODE_LEFT_ALIGN, 1);
    return count;
}

static void CB2_ReturnFromChooseFairFightParty(void)
{
    gSpecialVar_Result = gSelectedOrderFromParty[0] != 0;
    VarSet(VAR_FRONTIER_FACILITY, 0);
    SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
}

void KJH_ChooseFairFightParty(void)
{
    VarSet(VAR_FRONTIER_FACILITY, KJH_FACILITY_FAIR_FIGHT);
    gMain.savedCallback = CB2_ReturnFromChooseFairFightParty;
    InitChooseHalfPartyForBattle(0);
}

void KJH_ApplyFairFightParty(void)
{
    u32 count = 0;

    for (u32 i = 0; i < PARTY_SIZE; i++)
        sWaitingParty[i] = gPlayerParty[i];
    for (u32 i = 0; i < PARTY_SIZE; i++)
    {
        sFighterSlots[i] = i < ARRAY_COUNT(gSelectedOrderFromParty) ? gSelectedOrderFromParty[i] : 0; // 0: none
        if (sFighterSlots[i] != 0)
            gPlayerParty[count++] = sWaitingParty[sFighterSlots[i] - 1];
    }
    for (u32 i = count; i < PARTY_SIZE; i++)
        ZeroMonData(&gPlayerParty[i]);
    CalculatePlayerPartyCount();
    sFairFightActive = TRUE;
}

bool32 KJH_IsFairFightActive(void)
{
    return sFairFightActive;
}

void KJH_RestoreFairFightParty(void)
{
    u32 fighter = 0;

    if (!sFairFightActive)
        return;
    for (u32 i = 0; i < PARTY_SIZE; i++)
    {
        if (sFighterSlots[i] != 0)
            sWaitingParty[sFighterSlots[i] - 1] = gPlayerParty[fighter++];
    }
    for (u32 i = 0; i < PARTY_SIZE; i++)
        gPlayerParty[i] = sWaitingParty[i];
    CalculatePlayerPartyCount();
    sFairFightActive = FALSE;
}
