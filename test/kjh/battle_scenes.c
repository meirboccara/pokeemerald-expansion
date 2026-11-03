// KJH: every boss opens its battle with a mugshot (ENG-7, src/kjh_battle_scenes.c). The test build has its own
// trainer table, so the trainers are made here, with the trainer numbers of src/data/trainers_frlg.party.
#include "global.h"
#include "battle_transition.h"
#include "data.h"
#include "kjh_battle_scenes.h"
#include "test/test.h"
#include "constants/opponents.h"
#include "constants/trainers.h"

static const struct Trainer sBrock = {.trainerClass = TRAINER_CLASS_LEADER_FRLG};
static const struct Trainer sLorelei = {.trainerClass = TRAINER_CLASS_ELITE_FOUR_FRLG, .mugshotColor = MUGSHOT_COLOR_PURPLE};
static const struct Trainer sGiovanni = {.trainerClass = TRAINER_CLASS_BOSS_FRLG};
static const struct Trainer sRival = {.trainerClass = TRAINER_CLASS_RIVAL_EARLY_FRLG};
static const struct Trainer sYoungster = {.trainerClass = TRAINER_CLASS_YOUNGSTER};

TEST("KJH: a gym leader's mugshot is green (Bruno's), a team boss's pink (Agatha's)")
{
    EXPECT_EQ(KJH_BossMugshotColor(&sBrock, TRAINER_LEADER_BROCK), MUGSHOT_COLOR_GREEN);
    EXPECT_EQ(KJH_BossMugshotColor(&sGiovanni, TRAINER_BOSS_GIOVANNI), MUGSHOT_COLOR_PINK);
}

TEST("KJH: a rival's mugshot is yellow (Blue's), but the first battle in Oak's lab has none")
{
    EXPECT_EQ(KJH_BossMugshotColor(&sRival, TRAINER_RIVAL_ROUTE22_EARLY_SQUIRTLE), MUGSHOT_COLOR_YELLOW);
    EXPECT_EQ(KJH_BossMugshotColor(&sRival, TRAINER_RIVAL_OAKS_LAB_SQUIRTLE), MUGSHOT_COLOR_NONE);
}

TEST("KJH: a trainer with its own mugshot keeps it, other trainers have none")
{
    EXPECT_EQ(KJH_BossMugshotColor(&sLorelei, TRAINER_ELITE_FOUR_LORELEI), MUGSHOT_COLOR_PURPLE);
    EXPECT_EQ(KJH_BossMugshotColor(&sYoungster, TRAINER_YOUNGSTER_BEN), MUGSHOT_COLOR_NONE);
}
