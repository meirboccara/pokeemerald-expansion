// KJH: faster travel (CF-11, src/kjh_travel.c): auto-run on L, B for a faster bike and Surf.
#include "global.h"
#include "event_data.h"
#include "kjh_travel.h"
#include "test/test.h"
#include "constants/global.h"

TEST("KJH: B runs; with auto-run on, the player runs without B and B walks")
{
    FlagClear(FLAG_KJH_AUTO_RUN);
    EXPECT(!KJH_IsRunning(0));
    EXPECT(KJH_IsRunning(B_BUTTON));
    FlagSet(FLAG_KJH_AUTO_RUN);
    EXPECT(KJH_IsRunning(0));
    EXPECT(KJH_IsRunning(DPAD_RIGHT));
    EXPECT(!KJH_IsRunning(B_BUTTON | DPAD_RIGHT));
    FlagClear(FLAG_KJH_AUTO_RUN);
}

TEST("KJH: L toggles auto-run once the player has the Running Shoes, not in the L=A button mode")
{
    u8 mode = gSaveBlock2Ptr->optionsButtonMode;

    FlagClear(FLAG_KJH_AUTO_RUN);
    gSaveBlock2Ptr->optionsButtonMode = OPTIONS_BUTTON_MODE_NORMAL;
    FlagClear(FLAG_SYS_B_DASH);
    KJH_ToggleAutoRun();
    EXPECT(!FlagGet(FLAG_KJH_AUTO_RUN));

    FlagSet(FLAG_SYS_B_DASH);
    KJH_ToggleAutoRun();
    EXPECT(FlagGet(FLAG_KJH_AUTO_RUN));
    KJH_ToggleAutoRun();
    EXPECT(!FlagGet(FLAG_KJH_AUTO_RUN));

    gSaveBlock2Ptr->optionsButtonMode = OPTIONS_BUTTON_MODE_L_EQUALS_A;
    KJH_ToggleAutoRun();
    EXPECT(!FlagGet(FLAG_KJH_AUTO_RUN));
    gSaveBlock2Ptr->optionsButtonMode = mode;
}

TEST("KJH: the auto-run setting is a saved flag")
{
    // a save flag (not a temporary or special one), so it survives save and load
    EXPECT_GT(FLAG_KJH_AUTO_RUN, TEMP_FLAGS_END);
    EXPECT_LT(FLAG_KJH_AUTO_RUN, FLAGS_COUNT);
}

TEST("KJH: B is the fast key on the bike and while surfing")
{
    EXPECT(KJH_IsFastTravelHeld(B_BUTTON | DPAD_UP));
    EXPECT(!KJH_IsFastTravelHeld(DPAD_UP));
}
