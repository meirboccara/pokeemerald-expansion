// KJH: a hit too big for the battle's damage slots (s16 moveDamage) saturates instead of wrapping.
// Found while porting emu_story.py: a Lv 100 Pokemon with 999 Sp. Atk used Dark Pulse on a foe with 1 Sp. Def, the
// foe flinched and lost no HP. CalculateMoveDamage returns s32; stored into gBattleStruct->moveDamage (s16), a damage
// of 32768..65535 (mod 65536) turned negative, and negative damage heals.
#include "global.h"
#include "test/battle.h"

// Wobbuffet's Dark Pulse on a Wobbuffet is super effective (x2): with 999 Sp. Atk against 1 Sp. Def the hit is
// 114126..134268 by the roll, with 250 Sp. Atk 28562..33604: both wrap for some rolls.
SINGLE_BATTLE_TEST("KJH: damage, a huge special hit knocks the foe out at every roll")
{
    u32 spAtk = 0, roll = 0;
    for (u32 j = 0; j < 16; j++)
    {
        PARAMETRIZE { spAtk = 250; roll = j; }
        PARAMETRIZE { spAtk = 999; roll = j; }
    }
    GIVEN {
        ASSUME(GetMoveCategory(MOVE_DARK_PULSE) == DAMAGE_CATEGORY_SPECIAL);
        PLAYER(SPECIES_WOBBUFFET) { Level(100); SpAttack(spAtk); }
        OPPONENT(SPECIES_WOBBUFFET) { Level(100); SpDefense(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_DARK_PULSE, WITH_RNG(RNG_DAMAGE_MODIFIER, roll)); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_DARK_PULSE, player);
        HP_BAR(opponent, hp: 0);
        MESSAGE("The opposing Wobbuffet fainted!");
    }
}

// The same through the physical side and a crit: 999 Attack, Close Combat (120) on a Normal-type with 1 Defense
SINGLE_BATTLE_TEST("KJH: damage, a huge physical crit knocks the foe out")
{
    GIVEN {
        ASSUME(GetMoveCategory(MOVE_CLOSE_COMBAT) == DAMAGE_CATEGORY_PHYSICAL);
        PLAYER(SPECIES_WOBBUFFET) { Level(100); Attack(999); }
        OPPONENT(SPECIES_SNORLAX) { Level(100); Defense(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_CLOSE_COMBAT, criticalHit: TRUE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CLOSE_COMBAT, player);
        HP_BAR(opponent, hp: 0);
        MESSAGE("The opposing Snorlax fainted!");
    }
}
