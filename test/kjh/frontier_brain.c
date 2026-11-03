// KJH: expansion's special trainer number TRAINER_FRONTIER_BRAIN (300 frontier trainers + 5 records + 4 apprentices
// + 1) is 310, which in FireRed is a real trainer, TRAINER_ELITE_FOUR_LORELEI. The battle's opponent pic, class and
// name took Lorelei for the Frontier Brain: a "?" pic and "PKMN TRAINER" with no name (emu_story.py in the KJH repo).
// They ask IsFrontierBrainOpponent (src/frontier_util.c), which only answers yes in the Battle Frontier.
#include "global.h"
#include "battle.h"
#include "frontier_util.h"
#include "test/test.h"
#include "constants/battle.h"
#include "constants/opponents.h"
#include "constants/trainers.h"

TEST("KJH: Lorelei's trainer number is TRAINER_FRONTIER_BRAIN's in the FireRed build")
{
    EXPECT_EQ(TRAINER_ELITE_FOUR_LORELEI, TRAINER_FRONTIER_BRAIN);
}

TEST("KJH: outside the Battle Frontier, Lorelei is not the Frontier Brain")
{
    gBattleTypeFlags = BATTLE_TYPE_TRAINER | BATTLE_TYPE_IS_MASTER;
    EXPECT(!IsFrontierBrainOpponent(TRAINER_ELITE_FOUR_LORELEI));
}

TEST("KJH: in a Battle Frontier facility, the Frontier Brain is still the Frontier Brain")
{
    gBattleTypeFlags = BATTLE_TYPE_TRAINER | BATTLE_TYPE_DOME;
    EXPECT(IsFrontierBrainOpponent(TRAINER_FRONTIER_BRAIN));
    gBattleTypeFlags = BATTLE_TYPE_TRAINER | BATTLE_TYPE_DOME;
    EXPECT(!IsFrontierBrainOpponent(TRAINER_FRONTIER_BRAIN + 1));
}
