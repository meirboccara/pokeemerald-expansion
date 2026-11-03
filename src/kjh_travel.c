// KJH: faster travel (CF-11, include/kjh_travel.h).
#include "global.h"
#include "event_data.h"
#include "kjh_travel.h"
#include "sound.h"
#include "constants/songs.h"

bool32 KJH_CanToggleAutoRun(void)
{
    return FlagGet(FLAG_SYS_B_DASH) && gSaveBlock2Ptr->optionsButtonMode != OPTIONS_BUTTON_MODE_L_EQUALS_A;
}

void KJH_ToggleAutoRun(void)
{
    if (!KJH_CanToggleAutoRun())
        return;
    FlagToggle(FLAG_KJH_AUTO_RUN);
    PlaySE(SE_SELECT);
}

// Whether a step on foot is a running one (the caller still checks the Running Shoes and where running is allowed)
bool32 KJH_IsRunning(u16 heldKeys)
{
    bool32 holdingB = (heldKeys & B_BUTTON) != 0;

    if (FlagGet(FLAG_KJH_AUTO_RUN))
        return !holdingB;
    return holdingB;
}

bool32 KJH_IsFastTravelHeld(u16 heldKeys)
{
    return (heldKeys & B_BUTTON) != 0;
}
