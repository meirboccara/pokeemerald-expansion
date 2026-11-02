// KJH: the party Exp. Share (ENG-4). KJH's Gen 6+ Exp. Share is expansion's I_EXP_SHARE_FLAG, a FireRed flag that a
// new game sets: the Pokemon that battled get full Exp., the rest of the party half.
#include "global.h"
#include "test/battle.h"

WILD_BATTLE_TEST("KJH: with the Exp. Share flag, a Pokemon that didn't battle gets Exp.")
{
    GIVEN {
        FLAG_SET(I_EXP_SHARE_FLAG);
        PLAYER(SPECIES_WOBBUFFET) { Level(99); }
        PLAYER(SPECIES_DITTO) { Level(1); }
        OPPONENT(SPECIES_CATERPIE) { Level(20); HP(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_TACKLE); }
    } THEN {
        EXPECT_GT(GetMonData(&gParties[B_TRAINER_PLAYER][1], MON_DATA_LEVEL), 1);
    }
}
