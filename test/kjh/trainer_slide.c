// KJH (ENG-9): Johto's and Hoenn's trainer ids are past expansion's trainer slide tables (sTrainerSlides is
// TRAINER_PARTNER(PARTNER_COUNT) rows), so src/trainer_slide.c's GetTrainerSlideArray gives NULL for them, and the
// test build's table (sTestTrainerSlides) is shorter still. Such a trainer has no slide: nothing may be read through
// that NULL or past the table (on the GBA, NULL[slide] reads the BIOS's open bus, a non-zero word, so a Johto or Hoenn
// battle would show a "slide" of garbage text before the first turn).
#include "global.h"
#include "difficulty.h"
#include "event_data.h"
#include "trainer_slide.h"
#include "test/test.h"
#include "constants/opponents.h"
#include "constants/trainer_slide.h"

#define TRAINER_LEAF_TEST 2 // test/battle/trainer_slides.h's Trainer A

TEST("KJH: a Johto or Hoenn trainer has no trainer slide")
{
    u32 slide = TRAINER_SLIDE_BEFORE_FIRST_TURN;

    VarSet(TESTING_VAR_TRAINER_SLIDES, slide);
    FlagClear(TESTING_FLAG_TRAINER_SLIDES); // as in the game: GetTrainerSlideArray is NULL for these ids
    EXPECT(GetTrainerSlideMessage(DIFFICULTY_NORMAL, TRAINER_ROXANNE_1, slide) == NULL);
    EXPECT(GetTrainerSlideMessage(DIFFICULTY_NORMAL, JOHTO_TRAINERS_START, slide) == NULL);
    EXPECT(GetTrainerSlideMessage(DIFFICULTY_HARD, TRAINERS_COUNT - 1, slide) == NULL);
    FlagSet(TESTING_FLAG_TRAINER_SLIDES); // the test table: Trainer A has one, the ids past it have none
    EXPECT(GetTrainerSlideMessage(DIFFICULTY_NORMAL, TRAINER_LEAF_TEST, slide) != NULL);
    EXPECT(GetTrainerSlideMessage(DIFFICULTY_NORMAL, TRAINER_ROXANNE_1, slide) == NULL);
    EXPECT(GetTrainerSlideMessage(DIFFICULTY_NORMAL, TRAINERS_COUNT - 1, slide) == NULL);
    FlagClear(TESTING_FLAG_TRAINER_SLIDES);
    VarSet(TESTING_VAR_TRAINER_SLIDES, 0);
}
