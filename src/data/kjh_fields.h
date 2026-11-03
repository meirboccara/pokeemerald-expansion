// KJH: maps whose field is set by hand (LV-14, docs/LEVELLESS_DESIGN.md §8 in the KJH repo). Everywhere else the
// field comes from the battle environment (KJH_FieldTypeFromEnvironment). Johto and Hoenn join with LV-18.
// - Gyms use the leader's type; the first 2 Gyms of each region only boost (no x0.8).
// - Each Elite Four room uses its member's type; the Champion's room is neutral.
// - Special places. The training masters' spots (§12: "only where the master stands") come with the masters, LV-13.

struct KjhFieldMap
{
    u16 mapId;
    struct KjhField field;
};

#define FIELD(map, fieldType)      { map, { fieldType, FALSE } }
#define EARLY_GYM(map, fieldType)  { map, { fieldType, TRUE } }   // the region's 1st or 2nd Gym: boost only

static const struct KjhFieldMap sKjhFieldMaps[] =
{
    // Kanto's Gyms
    EARLY_GYM(MAP_PEWTER_CITY_GYM, TYPE_ROCK),          // Brock
    EARLY_GYM(MAP_CERULEAN_CITY_GYM, TYPE_WATER),       // Misty
    FIELD(MAP_VERMILION_CITY_GYM, TYPE_ELECTRIC),       // Lt. Surge
    FIELD(MAP_CELADON_CITY_GYM, TYPE_GRASS),            // Erika
    FIELD(MAP_FUCHSIA_CITY_GYM, TYPE_POISON),           // Koga
    FIELD(MAP_SAFFRON_CITY_GYM, TYPE_PSYCHIC),          // Sabrina
    FIELD(MAP_CINNABAR_ISLAND_GYM, TYPE_FIRE),          // Blaine
    FIELD(MAP_VIRIDIAN_CITY_GYM, TYPE_GROUND),          // Giovanni

    // Kanto's Elite Four
    FIELD(MAP_POKEMON_LEAGUE_LORELEIS_ROOM, TYPE_ICE),
    FIELD(MAP_POKEMON_LEAGUE_BRUNOS_ROOM, TYPE_FIGHTING),
    FIELD(MAP_POKEMON_LEAGUE_AGATHAS_ROOM, TYPE_GHOST),
    FIELD(MAP_POKEMON_LEAGUE_LANCES_ROOM, TYPE_DRAGON),
    FIELD(MAP_POKEMON_LEAGUE_CHAMPIONS_ROOM, TYPE_NONE),

    // Kanto's special places
    FIELD(MAP_POWER_PLANT, TYPE_ELECTRIC),
    FIELD(MAP_POKEMON_TOWER_1F, TYPE_GHOST),
    FIELD(MAP_POKEMON_TOWER_2F, TYPE_GHOST),
    FIELD(MAP_POKEMON_TOWER_3F, TYPE_GHOST),
    FIELD(MAP_POKEMON_TOWER_4F, TYPE_GHOST),
    FIELD(MAP_POKEMON_TOWER_5F, TYPE_GHOST),
    FIELD(MAP_POKEMON_TOWER_6F, TYPE_GHOST),
    FIELD(MAP_POKEMON_TOWER_7F, TYPE_GHOST),
    FIELD(MAP_SEAFOAM_ISLANDS_1F, TYPE_ICE),
    FIELD(MAP_SEAFOAM_ISLANDS_B1F, TYPE_ICE),
    FIELD(MAP_SEAFOAM_ISLANDS_B2F, TYPE_ICE),
    FIELD(MAP_SEAFOAM_ISLANDS_B3F, TYPE_ICE),
    FIELD(MAP_SEAFOAM_ISLANDS_B4F, TYPE_ICE),
    FIELD(MAP_MT_EMBER_EXTERIOR, TYPE_FIRE),
    FIELD(MAP_MT_EMBER_SUMMIT_PATH_1F, TYPE_FIRE),
    FIELD(MAP_MT_EMBER_SUMMIT_PATH_2F, TYPE_FIRE),
    FIELD(MAP_MT_EMBER_SUMMIT_PATH_3F, TYPE_FIRE),
    FIELD(MAP_MT_EMBER_SUMMIT, TYPE_FIRE),
    FIELD(MAP_MT_EMBER_RUBY_PATH_1F, TYPE_FIRE),
    FIELD(MAP_MT_EMBER_RUBY_PATH_B1F, TYPE_FIRE),
    FIELD(MAP_MT_EMBER_RUBY_PATH_B1F_STAIRS, TYPE_FIRE),
    FIELD(MAP_MT_EMBER_RUBY_PATH_B2F, TYPE_FIRE),
    FIELD(MAP_MT_EMBER_RUBY_PATH_B2F_STAIRS, TYPE_FIRE),
    FIELD(MAP_MT_EMBER_RUBY_PATH_B3F, TYPE_FIRE),
    FIELD(MAP_MT_EMBER_RUBY_PATH_B4F, TYPE_FIRE),
    FIELD(MAP_MT_EMBER_RUBY_PATH_B5F, TYPE_FIRE),
    FIELD(MAP_VIRIDIAN_FOREST, TYPE_BUG),
};

#undef FIELD
#undef EARLY_GYM
