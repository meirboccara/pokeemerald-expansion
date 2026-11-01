// KJH: Brock's AI (src/kjh_progression.c, KJH_AiFlags) in a real battle. The test runner sets the flags itself,
// so this checks the flags KJH gives Brock, not the hook in battle_ai_main.c that applies them in the game.
#include "global.h"
#include "kjh_progression.h"
#include "test/battle.h"
#include "constants/opponents.h"

// Brock's flags in src/data/trainers_frlg.party, with KJH's boss flags on top
#define BROCK_AI KJH_AiFlags(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY, \
                             TRAINER_CLASS_LEADER_FRLG, TRAINER_LEADER_BROCK)

AI_SINGLE_BATTLE_TEST("KJH: Brock's Onix picks the move that knocks out")
{
    GIVEN {
        ASSUME(GetMoveType(MOVE_ROCK_TOMB) == TYPE_ROCK);
        AI_FLAGS(BROCK_AI);
        PLAYER(SPECIES_CHARMANDER) { Level(14); HP(15); }
        PLAYER(SPECIES_CHARMANDER) { Level(14); }
        OPPONENT(SPECIES_ONIX) { Level(14); Moves(MOVE_TACKLE, MOVE_BIND, MOVE_ROCK_TOMB); }
    } WHEN {
        TURN { EXPECT_MOVE(opponent, MOVE_ROCK_TOMB); SEND_OUT(player, 1); }
    } SCENE {
        MESSAGE("Charmander fainted!");
    }
}
