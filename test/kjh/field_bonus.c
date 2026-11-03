// KJH: the field bonus (LV-14, src/kjh_field.c), with the rules of docs/LEVELLESS_DESIGN.md §8 in the KJH repo: on a
// field of type X, X-type moves deal x1.2 and the types X is super effective against x0.8, for both sides.
#include "global.h"
#include "kjh_field.h"
#include "test/battle.h"

static struct KjhField Field(enum Type type, bool32 boostOnly)
{
    struct KjhField field = {.type = type, .boostOnly = boostOnly};
    return field;
}

TEST("KJH: field, water is Water, caves and mountains Rock, sand Ground, long grass Grass")
{
    EXPECT_EQ(KJH_FieldTypeFromEnvironment(BATTLE_ENVIRONMENT_WATER), TYPE_WATER);
    EXPECT_EQ(KJH_FieldTypeFromEnvironment(BATTLE_ENVIRONMENT_POND), TYPE_WATER);
    EXPECT_EQ(KJH_FieldTypeFromEnvironment(BATTLE_ENVIRONMENT_UNDERWATER), TYPE_WATER);
    EXPECT_EQ(KJH_FieldTypeFromEnvironment(BATTLE_ENVIRONMENT_CAVE), TYPE_ROCK);
    EXPECT_EQ(KJH_FieldTypeFromEnvironment(BATTLE_ENVIRONMENT_MOUNTAIN), TYPE_ROCK);
    EXPECT_EQ(KJH_FieldTypeFromEnvironment(BATTLE_ENVIRONMENT_SAND), TYPE_GROUND);
    EXPECT_EQ(KJH_FieldTypeFromEnvironment(BATTLE_ENVIRONMENT_LONG_GRASS), TYPE_GRASS);
}

TEST("KJH: field, buildings, plain ground and short grass have no field")
{
    EXPECT_EQ(KJH_FieldTypeFromEnvironment(BATTLE_ENVIRONMENT_BUILDING), TYPE_NONE);
    EXPECT_EQ(KJH_FieldTypeFromEnvironment(BATTLE_ENVIRONMENT_PLAIN), TYPE_NONE);
    EXPECT_EQ(KJH_FieldTypeFromEnvironment(BATTLE_ENVIRONMENT_GRASS), TYPE_NONE);
}

TEST("KJH: field, a Gym uses its leader's type, and Kanto's first 2 Gyms only boost")
{
    struct KjhField field;

    field = KJH_FieldForMap(MAP_PEWTER_CITY_GYM, BATTLE_ENVIRONMENT_BUILDING);
    EXPECT_EQ(field.type, TYPE_ROCK);
    EXPECT(field.boostOnly);
    field = KJH_FieldForMap(MAP_CERULEAN_CITY_GYM, BATTLE_ENVIRONMENT_BUILDING);
    EXPECT_EQ(field.type, TYPE_WATER);
    EXPECT(field.boostOnly);
    field = KJH_FieldForMap(MAP_VERMILION_CITY_GYM, BATTLE_ENVIRONMENT_BUILDING);
    EXPECT_EQ(field.type, TYPE_ELECTRIC);
    EXPECT(!field.boostOnly);
    field = KJH_FieldForMap(MAP_VIRIDIAN_CITY_GYM, BATTLE_ENVIRONMENT_BUILDING);
    EXPECT_EQ(field.type, TYPE_GROUND);
    EXPECT(!field.boostOnly);
}

TEST("KJH: field, each Elite Four room uses its member's type, the Champion's room has none")
{
    EXPECT_EQ(KJH_FieldForMap(MAP_POKEMON_LEAGUE_LORELEIS_ROOM, BATTLE_ENVIRONMENT_BUILDING).type, TYPE_ICE);
    EXPECT_EQ(KJH_FieldForMap(MAP_POKEMON_LEAGUE_BRUNOS_ROOM, BATTLE_ENVIRONMENT_BUILDING).type, TYPE_FIGHTING);
    EXPECT_EQ(KJH_FieldForMap(MAP_POKEMON_LEAGUE_AGATHAS_ROOM, BATTLE_ENVIRONMENT_BUILDING).type, TYPE_GHOST);
    EXPECT_EQ(KJH_FieldForMap(MAP_POKEMON_LEAGUE_LANCES_ROOM, BATTLE_ENVIRONMENT_BUILDING).type, TYPE_DRAGON);
    EXPECT_EQ(KJH_FieldForMap(MAP_POKEMON_LEAGUE_CHAMPIONS_ROOM, BATTLE_ENVIRONMENT_BUILDING).type, TYPE_NONE);
}

TEST("KJH: field, Kanto's special places are set by hand, wherever the battle is fought on them")
{
    EXPECT_EQ(KJH_FieldForMap(MAP_POWER_PLANT, BATTLE_ENVIRONMENT_BUILDING).type, TYPE_ELECTRIC);
    EXPECT_EQ(KJH_FieldForMap(MAP_POKEMON_TOWER_3F, BATTLE_ENVIRONMENT_BUILDING).type, TYPE_GHOST);
    EXPECT_EQ(KJH_FieldForMap(MAP_SEAFOAM_ISLANDS_B3F, BATTLE_ENVIRONMENT_POND).type, TYPE_ICE);
    EXPECT_EQ(KJH_FieldForMap(MAP_MT_EMBER_EXTERIOR, BATTLE_ENVIRONMENT_PLAIN).type, TYPE_FIRE);
    EXPECT_EQ(KJH_FieldForMap(MAP_MT_EMBER_RUBY_PATH_B5F, BATTLE_ENVIRONMENT_CAVE).type, TYPE_FIRE);
    EXPECT_EQ(KJH_FieldForMap(MAP_VIRIDIAN_FOREST, BATTLE_ENVIRONMENT_GRASS).type, TYPE_BUG);
    EXPECT(!KJH_FieldForMap(MAP_POWER_PLANT, BATTLE_ENVIRONMENT_BUILDING).boostOnly);
}

// The training masters' spots (LV-13) are set in the table: wild battles there count too (LEVELLESS_DESIGN.md §12)
TEST("KJH: field, other maps take the environment's field; the masters' spots have theirs")
{
    EXPECT_EQ(KJH_FieldForMap(MAP_MT_MOON_1F, BATTLE_ENVIRONMENT_CAVE).type, TYPE_ROCK);
    EXPECT_EQ(KJH_FieldForMap(MAP_DIGLETTS_CAVE_B1F, BATTLE_ENVIRONMENT_CAVE).type, TYPE_GROUND);
    EXPECT_EQ(KJH_FieldForMap(MAP_SAFFRON_CITY_DOJO, BATTLE_ENVIRONMENT_BUILDING).type, TYPE_FIGHTING);
    EXPECT_EQ(KJH_FieldForMap(MAP_ROUTE19, BATTLE_ENVIRONMENT_SAND).type, TYPE_WATER);
    EXPECT_EQ(KJH_FieldForMap(MAP_ROUTE1, BATTLE_ENVIRONMENT_GRASS).type, TYPE_NONE);
    EXPECT_EQ(KJH_FieldForMap(MAP_ROUTE1, BATTLE_ENVIRONMENT_POND).type, TYPE_WATER);
    EXPECT(!KJH_FieldForMap(MAP_ROUTE1, BATTLE_ENVIRONMENT_POND).boostOnly);
}

TEST("KJH: field, on a Water field, Water moves x1.2, Fire, Ground and Rock moves x0.8, the rest x1")
{
    struct KjhField water = Field(TYPE_WATER, FALSE);

    EXPECT_EQ(KJH_FieldMoveModifier(water, TYPE_WATER), UQ_4_12(1.2));
    EXPECT_EQ(KJH_FieldMoveModifier(water, TYPE_FIRE), UQ_4_12(0.8));
    EXPECT_EQ(KJH_FieldMoveModifier(water, TYPE_GROUND), UQ_4_12(0.8));
    EXPECT_EQ(KJH_FieldMoveModifier(water, TYPE_ROCK), UQ_4_12(0.8));
    EXPECT_EQ(KJH_FieldMoveModifier(water, TYPE_GRASS), UQ_4_12(1.0));
    EXPECT_EQ(KJH_FieldMoveModifier(water, TYPE_ELECTRIC), UQ_4_12(1.0));
    EXPECT_EQ(KJH_FieldMoveModifier(water, TYPE_NORMAL), UQ_4_12(1.0));
}

TEST("KJH: field, a field's own type is always x1.2, never x0.8 (Ghost and Dragon)")
{
    EXPECT_EQ(KJH_FieldMoveModifier(Field(TYPE_GHOST, FALSE), TYPE_GHOST), UQ_4_12(1.2));
    EXPECT_EQ(KJH_FieldMoveModifier(Field(TYPE_GHOST, FALSE), TYPE_PSYCHIC), UQ_4_12(0.8));
    EXPECT_EQ(KJH_FieldMoveModifier(Field(TYPE_DRAGON, FALSE), TYPE_DRAGON), UQ_4_12(1.2));
}

TEST("KJH: field, a boost-only field (Kanto's first 2 Gyms) has no x0.8")
{
    struct KjhField brock = Field(TYPE_ROCK, TRUE);

    EXPECT_EQ(KJH_FieldMoveModifier(brock, TYPE_ROCK), UQ_4_12(1.2));
    EXPECT_EQ(KJH_FieldMoveModifier(brock, TYPE_FIRE), UQ_4_12(1.0));
    EXPECT_EQ(KJH_FieldMoveModifier(brock, TYPE_FLYING), UQ_4_12(1.0));
    EXPECT_EQ(KJH_FieldMoveModifier(Field(TYPE_ROCK, FALSE), TYPE_FIRE), UQ_4_12(0.8));
}

TEST("KJH: field, no field changes no move")
{
    for (enum Type type = TYPE_NONE; type < NUMBER_OF_MON_TYPES; type++)
        EXPECT_EQ(KJH_FieldMoveModifier(Field(TYPE_NONE, FALSE), type), UQ_4_12(1.0));
}

TEST("KJH: field, weather and field together are capped at x1.5")
{
    EXPECT_EQ(KJH_CapWeatherAndField(UQ_4_12(1.5), UQ_4_12(1.2)), UQ_4_12(1.5));
    EXPECT_EQ(KJH_CapWeatherAndField(UQ_4_12(1.5), UQ_4_12(1.0)), UQ_4_12(1.5));
    EXPECT_EQ(KJH_CapWeatherAndField(UQ_4_12(1.0), UQ_4_12(1.2)), UQ_4_12(1.2));
    EXPECT_EQ(KJH_CapWeatherAndField(UQ_4_12(0.5), UQ_4_12(1.0)), UQ_4_12(0.5));
    EXPECT_EQ(KJH_CapWeatherAndField(UQ_4_12(1.0), UQ_4_12(0.8)), UQ_4_12(0.8));
}

TEST("KJH: field, every field type has a battle-start message")
{
    for (enum Type type = TYPE_NORMAL; type < NUMBER_OF_MON_TYPES; type++)
    {
        if (type == TYPE_MYSTERY || type == TYPE_STELLAR)
            continue;
        EXPECT(KJH_FieldStartMessage(type) != NULL);
    }
    EXPECT(KJH_FieldStartMessage(TYPE_NONE) == NULL);
}

SINGLE_BATTLE_TEST("KJH: field, on water, a Water move deals x1.2", s16 damage)
{
    u32 environment;
    PARAMETRIZE { environment = BATTLE_ENVIRONMENT_BUILDING; }
    PARAMETRIZE { environment = BATTLE_ENVIRONMENT_WATER; }
    GIVEN {
        ASSUME(GetMoveType(MOVE_WATER_GUN) == TYPE_WATER);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
        Environment(environment);
    } WHEN {
        TURN { MOVE(player, MOVE_WATER_GUN); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.2), results[1].damage);
    }
}

SINGLE_BATTLE_TEST("KJH: field, on water, a Fire move deals x0.8", s16 damage)
{
    u32 environment;
    PARAMETRIZE { environment = BATTLE_ENVIRONMENT_BUILDING; }
    PARAMETRIZE { environment = BATTLE_ENVIRONMENT_WATER; }
    GIVEN {
        ASSUME(GetMoveType(MOVE_EMBER) == TYPE_FIRE);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
        Environment(environment);
    } WHEN {
        TURN { MOVE(player, MOVE_EMBER); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(0.8), results[1].damage);
    }
}

SINGLE_BATTLE_TEST("KJH: field, on water, a Normal move is unchanged", s16 damage)
{
    u32 environment;
    PARAMETRIZE { environment = BATTLE_ENVIRONMENT_BUILDING; }
    PARAMETRIZE { environment = BATTLE_ENVIRONMENT_WATER; }
    GIVEN {
        ASSUME(GetMoveType(MOVE_TACKLE) == TYPE_NORMAL);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
        Environment(environment);
    } WHEN {
        TURN { MOVE(player, MOVE_TACKLE); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_EQ(results[0].damage, results[1].damage);
    }
}

SINGLE_BATTLE_TEST("KJH: field, the opponent's moves get the field too", s16 damage)
{
    u32 environment;
    PARAMETRIZE { environment = BATTLE_ENVIRONMENT_BUILDING; }
    PARAMETRIZE { environment = BATTLE_ENVIRONMENT_WATER; }
    GIVEN {
        ASSUME(GetMoveType(MOVE_WATER_GUN) == TYPE_WATER);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
        Environment(environment);
    } WHEN {
        TURN { MOVE(opponent, MOVE_WATER_GUN); }
    } SCENE {
        HP_BAR(player, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.2), results[1].damage);
    }
}

SINGLE_BATTLE_TEST("KJH: field, rain on water gives a Water move x1.5, not x1.8", s16 damage)
{
    u32 environment;
    PARAMETRIZE { environment = BATTLE_ENVIRONMENT_BUILDING; }
    PARAMETRIZE { environment = BATTLE_ENVIRONMENT_WATER; }
    GIVEN {
        ASSUME(GetMoveType(MOVE_WATER_GUN) == TYPE_WATER);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
        Environment(environment);
    } WHEN {
        TURN { MOVE(player, MOVE_RAIN_DANCE); }
        TURN { MOVE(player, MOVE_WATER_GUN); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_WATER_GUN, player);
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_EQ(results[0].damage, results[1].damage);
    }
}

SINGLE_BATTLE_TEST("KJH: field, a battle on water starts with the field's message")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
        Environment(BATTLE_ENVIRONMENT_WATER);
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); }
    } SCENE {
        MESSAGE("Water is all around! Water moves are boosted here!");
        MESSAGE("Wobbuffet used Celebrate!");
    }
}

SINGLE_BATTLE_TEST("KJH: field, a battle in a building has no field message")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
        Environment(BATTLE_ENVIRONMENT_BUILDING);
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); }
    } SCENE {
        NONE_OF {
            MESSAGE("Water is all around! Water moves are boosted here!");
            MESSAGE("Rocks are all around! Rock moves are boosted here!");
        }
        MESSAGE("Wobbuffet used Celebrate!");
    }
}

// The test runner's battles are recorded link battles (BATTLE_TYPE_RECORDED_LINK), on map 0.0: not in the table
SINGLE_BATTLE_TEST("KJH: field, a battle on water is fought on a Water field")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
        Environment(BATTLE_ENVIRONMENT_WATER);
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); }
    } THEN {
        EXPECT_EQ(KJH_GetBattleField().type, TYPE_WATER);
        EXPECT(!KJH_GetBattleField().boostOnly);
    }
}
