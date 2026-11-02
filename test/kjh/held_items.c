// KJH: held items come back after battle (CF-2). Expansion's Gen 9 rule (B_RESTORE_HELD_BATTLE_ITEMS): an item a
// Pokemon used up, or lost to Knock Off or Thief, is held again once the battle is over; a Berry is gone for good.
#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("KJH: a White Herb used in a trainer battle is back after it")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Item(ITEM_WHITE_HERB); Speed(1); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(1); Speed(2); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_LEER); MOVE(player, MOVE_TACKLE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_LEER, opponent);
        MESSAGE("Wobbuffet returned its stats to normal using its White Herb!");
        MESSAGE("The opposing Wobbuffet fainted!");
    } THEN {
        EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_HELD_ITEM), ITEM_WHITE_HERB);
    }
}

SINGLE_BATTLE_TEST("KJH: a Sitrus Berry eaten in a trainer battle stays eaten")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { MaxHP(100); HP(60); Item(ITEM_SITRUS_BERRY); Speed(1); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(1); Speed(2); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_SUPER_FANG); MOVE(player, MOVE_TACKLE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SUPER_FANG, opponent);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_HELD_ITEM_BERRY, player);
        MESSAGE("The opposing Wobbuffet fainted!");
    } THEN {
        EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_HELD_ITEM), ITEM_NONE);
    }
}

SINGLE_BATTLE_TEST("KJH: an item knocked off by a trainer's Pokemon is back after the battle")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Item(ITEM_LEFTOVERS); Speed(1); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(1); Speed(2); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_KNOCK_OFF); MOVE(player, MOVE_TACKLE); }
    } SCENE {
        MESSAGE("The opposing Wobbuffet knocked off Wobbuffet's Leftovers!");
        MESSAGE("The opposing Wobbuffet fainted!");
    } THEN {
        EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_HELD_ITEM), ITEM_LEFTOVERS);
    }
}

SINGLE_BATTLE_TEST("KJH: an item a trainer's Pokemon steals with Thief is back after the battle")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Item(ITEM_LEFTOVERS); Speed(1); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(1); Speed(2); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_THIEF); MOVE(player, MOVE_TACKLE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_THIEF, opponent);
        MESSAGE("The opposing Wobbuffet fainted!");
    } THEN {
        EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_HELD_ITEM), ITEM_LEFTOVERS);
    }
}

SINGLE_BATTLE_TEST("KJH: an item the player steals from a trainer's Pokemon with Thief is kept")
{
    GIVEN {
        // a Lv 1 thief does 1-3 damage, then Dragon Rage's 40 knocks the opponent out
        PLAYER(SPECIES_WOBBUFFET) { Level(1); Speed(2); }
        OPPONENT(SPECIES_WOBBUFFET) { Item(ITEM_LEFTOVERS); HP(41); Speed(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_THIEF); }
        TURN { MOVE(player, MOVE_DRAGON_RAGE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_ITEM_STEAL, opponent);
    } THEN {
        EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_HELD_ITEM), ITEM_LEFTOVERS);
    }
}

SINGLE_BATTLE_TEST("KJH: an opponent's White Herb still works in battle")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Speed(2); }
        OPPONENT(SPECIES_WOBBUFFET) { Item(ITEM_WHITE_HERB); Speed(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_LEER); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_LEER, player);
        MESSAGE("The opposing Wobbuffet returned its stats to normal using its White Herb!");
    } THEN {
        EXPECT_EQ(opponent->statStages[STAT_DEF], DEFAULT_STAT_STAGE);
        EXPECT_EQ(opponent->item, ITEM_NONE);
    }
}
