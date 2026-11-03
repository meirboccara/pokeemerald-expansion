// KJH (ENG-9): Johto's flags, variables and trainers in a FireRed build. FireRed's flags and variables fill
// SaveBlock1; Johto's are in SaveBlock3 (src/event_data.c), and Johto's trainer ids start where
// TRAINER_FLAGS_START + id is a Johto flag.
#include "global.h"
#include "battle_setup.h"
#include "data.h"
#include "event_data.h"
#include "string_util.h"
#include "test/test.h"
#include "constants/opponents.h"

#if IS_FRLG

TEST("KJH: Johto's flags are kept in SaveBlock3, apart from FireRed's")
{
    u8 kanto[NUM_FLAG_BYTES];

    memcpy(kanto, gSaveBlock1Ptr->flags, sizeof(kanto));
    FlagClear(JOHTO_FLAGS_START);
    FlagClear(KJH_SAVE3_FLAGS_END - 1);
    EXPECT(!FlagGet(JOHTO_FLAGS_START));

    FlagSet(JOHTO_FLAGS_START);
    FlagSet(KJH_SAVE3_FLAGS_END - 1);
    EXPECT(FlagGet(JOHTO_FLAGS_START));
    EXPECT(FlagGet(KJH_SAVE3_FLAGS_END - 1));
    EXPECT(!FlagGet(JOHTO_FLAGS_START + 1));
    EXPECT_EQ(memcmp(kanto, gSaveBlock1Ptr->flags, sizeof(kanto)), 0);
    EXPECT_EQ(gSaveBlock3Ptr->kjhFlags[(JOHTO_FLAGS_START - KJH_SAVE3_FLAGS_START) / 8] & 1, 1);

    FlagClear(JOHTO_FLAGS_START);
    EXPECT(!FlagGet(JOHTO_FLAGS_START));
}

TEST("KJH: Johto's variables are kept in SaveBlock3")
{
    u16 kanto[VARS_COUNT];

    memcpy(kanto, gSaveBlock1Ptr->vars, sizeof(kanto));
    VarSet(JOHTO_VARS_START, 1234);
    VarSet(KJH_SAVE3_VARS_END - 1, 5678);
    EXPECT_EQ(VarGet(JOHTO_VARS_START), 1234);
    EXPECT_EQ(VarGet(KJH_SAVE3_VARS_END - 1), 5678);
    EXPECT_EQ(gSaveBlock3Ptr->kjhVars[0], 1234);
    EXPECT_EQ(memcmp(kanto, gSaveBlock1Ptr->vars, sizeof(kanto)), 0);
}

TEST("KJH: a Johto trainer's flag is a Johto flag")
{
    EXPECT_EQ(TRAINER_FLAGS_START + JOHTO_TRAINERS_START, JOHTO_TRAINER_FLAGS_START);
    EXPECT_GE(JOHTO_TRAINER_FLAGS_START, FLAGS_COUNT);
    EXPECT_LE(JOHTO_TRAINERS_COUNT, JOHTO_TRAINER_FLAGS_COUNT);
    EXPECT_LE(JOHTO_TRAINERS_START + JOHTO_TRAINERS_COUNT, TRAINERS_COUNT); // Hoenn's come after (hoenn_state.c)

    ClearTrainerFlag(JOHTO_TRAINERS_START);
    EXPECT(!HasTrainerBeenFought(JOHTO_TRAINERS_START));
    SetTrainerFlag(JOHTO_TRAINERS_START);
    EXPECT(HasTrainerBeenFought(JOHTO_TRAINERS_START));
    EXPECT(FlagGet(JOHTO_TRAINER_FLAGS_START));
    ClearTrainerFlag(JOHTO_TRAINERS_START);
}

// Tests have their own gTrainers; Johto's parties are checked in the emulator (emu_expansion_eng9.py).
TEST("KJH: Johto's trainer classes and pics are in the fork's tables")
{
    EXPECT_EQ(StringCompare(gTrainerClasses[TRAINER_CLASS_J_SAGE].name, COMPOUND_STRING("SAGE")), 0);
    EXPECT_EQ(gTrainerClasses[TRAINER_CLASS_J_KIMONO_GIRL].money, 15);
    EXPECT_EQ(StringCompare(gTrainerClasses[TRAINER_CLASS_J_BOARDER].name, COMPOUND_STRING("BOARDER")), 0);
    EXPECT(gTrainerPicInfo[TRAINER_PIC_J_FALKNER].frontPic != NULL);
    EXPECT(gTrainerPicInfo[TRAINER_PIC_J_WHITNEY].frontPic->imageData != NULL);
}

#endif
