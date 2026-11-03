// KJH (LV-18): Hoenn's zones on the shared level curve (docs/LEVELLESS_DESIGN.md §1, variant C), place for place
// with Kanto's and Johto's (src/data/kjh_kanto_zones.h, src/data/kjh_johto_zones.h): the same ranges, the same Gym
// aces 14 · 22 · 30 · 40 · 50 · 60 · 70 · 80 and the same ceilings (sTeamLevelCaps). Hoenn is Emerald's own story on
// expansion's native maps (ENG-9), so the zones follow Emerald's road and Gym order (Roxanne, Brawly, Wattson,
// Flannery, Norman, Winona, Tate and Liza, Juan), and the teams' places sit where Emerald's story puts them.
// kjh_tools/zone_levels.py puts Hoenn's wild Pokémon and trainers on them. A first draft, to tune.
// Places left out on purpose (no zone, so no team level there): the Battle Frontier, Trainer Hill, secret bases, the
// S.S. Tidal, and the legendaries' own places (Sealed Chamber, the Regis' caves, Southern Island, Birth Island,
// Faraway Island, Navel Rock, Marine and Terra Caves): a postgame zone reached early would lift the team to its
// badges' ceiling for good.

enum KjhHoennZone
{
    KJH_HOENN_ZONE_NONE,
    // 0 badges, Roxanne's ace 14
    KJH_HOENN_ZONE_LITTLEROOT,
    KJH_HOENN_ZONE_PETALBURG,
    KJH_HOENN_ZONE_RUSTBORO,
    // 1 badge, Brawly's ace 22
    KJH_HOENN_ZONE_RUSTURF,
    KJH_HOENN_ZONE_DEWFORD,
    // 2 badges, Wattson's ace 30
    KJH_HOENN_ZONE_SLATEPORT,
    KJH_HOENN_ZONE_MAUVILLE,
    // 3 badges, Flannery's ace 40
    KJH_HOENN_ZONE_FALLARBOR,
    KJH_HOENN_ZONE_LAVARIDGE,
    // 4 badges, Norman's ace 50: Emerald has little between them, the desert's Mirage Tower (Go-Goggles) and the
    // Trick House's third puzzle (4 badges)
    KJH_HOENN_ZONE_DESERT,
    // 5 badges, Winona's ace 60: Surf from Norman opens the sea
    KJH_HOENN_ZONE_SEA,
    KJH_HOENN_ZONE_FORTREE,
    // 6 badges, Tate and Liza's ace 70: Lilycove, Mt. Pyre, the two hideouts, Mossdeep
    KJH_HOENN_ZONE_LILYCOVE,
    KJH_HOENN_ZONE_HIDEOUTS,
    // 7 badges, Juan's ace 80: the Space Center, the Seafloor Cavern, Sootopolis and Sky Pillar
    KJH_HOENN_ZONE_SEAFLOOR,
    KJH_HOENN_ZONE_SOOTOPOLIS,
    // 8 badges: Ever Grande, then one step per room
    KJH_HOENN_ZONE_VICTORY_ROAD,
    KJH_HOENN_ZONE_POKEMON_LEAGUE,
    KJH_HOENN_ZONE_SIDNEY,
    KJH_HOENN_ZONE_PHOEBE,
    KJH_HOENN_ZONE_GLACIA,
    KJH_HOENN_ZONE_DRAKE,
    KJH_HOENN_ZONE_CHAMPION,
    // After the League
    KJH_HOENN_ZONE_POSTGAME,
    KJH_HOENN_ZONE_COUNT,
};

static const struct KjhZoneRange sHoennZones[KJH_HOENN_ZONE_COUNT] =
{
    [KJH_HOENN_ZONE_LITTLEROOT]      = {  5,   8 },
    [KJH_HOENN_ZONE_PETALBURG]       = {  9,  12 },
    [KJH_HOENN_ZONE_RUSTBORO]        = { 12,  14 },
    [KJH_HOENN_ZONE_RUSTURF]         = { 14,  18 },
    [KJH_HOENN_ZONE_DEWFORD]         = { 18,  21 },
    [KJH_HOENN_ZONE_SLATEPORT]       = { 22,  26 },
    [KJH_HOENN_ZONE_MAUVILLE]        = { 26,  28 },
    [KJH_HOENN_ZONE_FALLARBOR]       = { 30,  34 },
    [KJH_HOENN_ZONE_LAVARIDGE]       = { 34,  38 },
    [KJH_HOENN_ZONE_DESERT]          = { 40,  48 },
    [KJH_HOENN_ZONE_SEA]             = { 50,  53 },
    [KJH_HOENN_ZONE_FORTREE]         = { 53,  56 },
    [KJH_HOENN_ZONE_LILYCOVE]        = { 60,  64 },
    [KJH_HOENN_ZONE_HIDEOUTS]        = { 64,  68 },
    [KJH_HOENN_ZONE_SEAFLOOR]        = { 70,  74 },
    [KJH_HOENN_ZONE_SOOTOPOLIS]      = { 74,  78 },
    [KJH_HOENN_ZONE_VICTORY_ROAD]    = { 80,  83 },
    [KJH_HOENN_ZONE_POKEMON_LEAGUE]  = { 83,  84 },
    [KJH_HOENN_ZONE_SIDNEY]          = { 84,  84 },
    [KJH_HOENN_ZONE_PHOEBE]          = { 88,  88 },
    [KJH_HOENN_ZONE_GLACIA]          = { 92,  92 },
    [KJH_HOENN_ZONE_DRAKE]           = { 96,  96 },
    [KJH_HOENN_ZONE_CHAMPION]        = {100, 100 },
    [KJH_HOENN_ZONE_POSTGAME]        = { 90, 100 },
};

// Hoenn's Gyms and their ace in Emerald's Gym order (the ceiling of the badges before them).
static const struct KjhGymAce sHoennGyms[] =
{
    { MAP_RUSTBORO_CITY_GYM,     14 },
    { MAP_DEWFORD_TOWN_GYM,      22 },
    { MAP_MAUVILLE_CITY_GYM,     30 },
    { MAP_LAVARIDGE_TOWN_GYM_1F, 40 },
    { MAP_LAVARIDGE_TOWN_GYM_B1F, 40 },
    { MAP_PETALBURG_CITY_GYM,    50 },
    { MAP_FORTREE_CITY_GYM,      60 },
    { MAP_MOSSDEEP_CITY_GYM,     70 },
    { MAP_SOOTOPOLIS_CITY_GYM_1F, 80 },
    { MAP_SOOTOPOLIS_CITY_GYM_B1F, 80 },
};

// Maps that have a zone of their own, before their section's.
static const struct KjhMapZone sHoennMapZones[] =
{
    // The Trick House's puzzles open one by one with the badges (Route110_TrickHouseEntrance): 3 badges for the
    // second ... the Hall of Fame for the eighth
    { MAP_ROUTE110_TRICK_HOUSE_PUZZLE2,     KJH_HOENN_ZONE_FALLARBOR },
    { MAP_ROUTE110_TRICK_HOUSE_PUZZLE3,     KJH_HOENN_ZONE_DESERT },
    { MAP_ROUTE110_TRICK_HOUSE_PUZZLE4,     KJH_HOENN_ZONE_SEA },
    { MAP_ROUTE110_TRICK_HOUSE_PUZZLE5,     KJH_HOENN_ZONE_LILYCOVE },
    { MAP_ROUTE110_TRICK_HOUSE_PUZZLE6,     KJH_HOENN_ZONE_SEAFLOOR },
    { MAP_ROUTE110_TRICK_HOUSE_PUZZLE7,     KJH_HOENN_ZONE_VICTORY_ROAD },
    { MAP_ROUTE110_TRICK_HOUSE_PUZZLE8,     KJH_HOENN_ZONE_POSTGAME },
    // The desert, with the Go-Goggles from Flannery's town
    { MAP_MIRAGE_TOWER_1F,                  KJH_HOENN_ZONE_DESERT },
    { MAP_MIRAGE_TOWER_2F,                  KJH_HOENN_ZONE_DESERT },
    { MAP_MIRAGE_TOWER_3F,                  KJH_HOENN_ZONE_DESERT },
    { MAP_MIRAGE_TOWER_4F,                  KJH_HOENN_ZONE_DESERT },
    // Meteor Falls' inner rooms need Waterfall (Juan's badge); Steven waits there after the League
    { MAP_METEOR_FALLS_1F_2R,               KJH_HOENN_ZONE_VICTORY_ROAD },
    { MAP_METEOR_FALLS_B1F_1R,              KJH_HOENN_ZONE_VICTORY_ROAD },
    { MAP_METEOR_FALLS_B1F_2R,              KJH_HOENN_ZONE_VICTORY_ROAD },
    { MAP_METEOR_FALLS_STEVENS_CAVE,        KJH_HOENN_ZONE_POSTGAME },
    // Team Magma takes the Space Center once Tate and Liza are beaten
    { MAP_MOSSDEEP_CITY_SPACE_CENTER_1F,    KJH_HOENN_ZONE_SEAFLOOR },
    { MAP_MOSSDEEP_CITY_SPACE_CENTER_2F,    KJH_HOENN_ZONE_SEAFLOOR },
    // Ever Grande's League: the building, then one step per room (each hall goes with the room before it)
    { MAP_EVER_GRANDE_CITY_POKEMON_LEAGUE_1F, KJH_HOENN_ZONE_POKEMON_LEAGUE },
    { MAP_EVER_GRANDE_CITY_POKEMON_LEAGUE_2F, KJH_HOENN_ZONE_POKEMON_LEAGUE },
    { MAP_EVER_GRANDE_CITY_SIDNEYS_ROOM,    KJH_HOENN_ZONE_SIDNEY },
    { MAP_EVER_GRANDE_CITY_HALL1,           KJH_HOENN_ZONE_SIDNEY },
    { MAP_EVER_GRANDE_CITY_PHOEBES_ROOM,    KJH_HOENN_ZONE_PHOEBE },
    { MAP_EVER_GRANDE_CITY_HALL2,           KJH_HOENN_ZONE_PHOEBE },
    { MAP_EVER_GRANDE_CITY_GLACIAS_ROOM,    KJH_HOENN_ZONE_GLACIA },
    { MAP_EVER_GRANDE_CITY_HALL3,           KJH_HOENN_ZONE_GLACIA },
    { MAP_EVER_GRANDE_CITY_DRAKES_ROOM,     KJH_HOENN_ZONE_DRAKE },
    { MAP_EVER_GRANDE_CITY_HALL4,           KJH_HOENN_ZONE_DRAKE },
    { MAP_EVER_GRANDE_CITY_HALL5,           KJH_HOENN_ZONE_DRAKE },
    { MAP_EVER_GRANDE_CITY_CHAMPIONS_ROOM,  KJH_HOENN_ZONE_CHAMPION },
    { MAP_EVER_GRANDE_CITY_HALL_OF_FAME,    KJH_HOENN_ZONE_CHAMPION },
};

// Every Hoenn section with a place in the story (towns take in their houses, Pokémon Centers and Gyms). A route of
// land and sea goes by its land, where the player first walks it; its trainers out on the water are placed in the
// sea's zone by kjh_tools/zone_levels_overrides.json.
static const struct KjhMapsecZone sHoennMapsecZones[] =
{
    { MAPSEC_LITTLEROOT_TOWN,          KJH_HOENN_ZONE_LITTLEROOT },
    { MAPSEC_ROUTE_101,                KJH_HOENN_ZONE_LITTLEROOT },
    { MAPSEC_OLDALE_TOWN,              KJH_HOENN_ZONE_LITTLEROOT },
    { MAPSEC_ROUTE_103,                KJH_HOENN_ZONE_LITTLEROOT },
    { MAPSEC_ROUTE_102,                KJH_HOENN_ZONE_PETALBURG },
    { MAPSEC_PETALBURG_CITY,           KJH_HOENN_ZONE_PETALBURG },
    { MAPSEC_ROUTE_104,                KJH_HOENN_ZONE_PETALBURG },
    { MAPSEC_PETALBURG_WOODS,          KJH_HOENN_ZONE_PETALBURG },
    { MAPSEC_RUSTBORO_CITY,            KJH_HOENN_ZONE_RUSTBORO },
    { MAPSEC_ROUTE_116,                KJH_HOENN_ZONE_RUSTURF },
    { MAPSEC_RUSTURF_TUNNEL,           KJH_HOENN_ZONE_RUSTURF },
    { MAPSEC_DEWFORD_TOWN,             KJH_HOENN_ZONE_DEWFORD },
    { MAPSEC_ROUTE_106,                KJH_HOENN_ZONE_DEWFORD },
    { MAPSEC_GRANITE_CAVE,             KJH_HOENN_ZONE_DEWFORD },
    { MAPSEC_SLATEPORT_CITY,           KJH_HOENN_ZONE_SLATEPORT },
    { MAPSEC_ROUTE_109,                KJH_HOENN_ZONE_SLATEPORT },
    { MAPSEC_ROUTE_110,                KJH_HOENN_ZONE_SLATEPORT },
    { MAPSEC_MAUVILLE_CITY,            KJH_HOENN_ZONE_MAUVILLE },
    { MAPSEC_ROUTE_117,                KJH_HOENN_ZONE_MAUVILLE },
    { MAPSEC_VERDANTURF_TOWN,          KJH_HOENN_ZONE_MAUVILLE },
    { MAPSEC_ROUTE_118,                KJH_HOENN_ZONE_MAUVILLE },
    { MAPSEC_ROUTE_111,                KJH_HOENN_ZONE_FALLARBOR },
    { MAPSEC_ROUTE_112,                KJH_HOENN_ZONE_FALLARBOR },
    { MAPSEC_FIERY_PATH,               KJH_HOENN_ZONE_FALLARBOR },
    { MAPSEC_ROUTE_113,                KJH_HOENN_ZONE_FALLARBOR },
    { MAPSEC_FALLARBOR_TOWN,           KJH_HOENN_ZONE_FALLARBOR },
    { MAPSEC_ROUTE_114,                KJH_HOENN_ZONE_FALLARBOR },
    { MAPSEC_ROUTE_115,                KJH_HOENN_ZONE_FALLARBOR },
    { MAPSEC_METEOR_FALLS,             KJH_HOENN_ZONE_FALLARBOR },
    { MAPSEC_MT_CHIMNEY,               KJH_HOENN_ZONE_LAVARIDGE },
    { MAPSEC_JAGGED_PASS,              KJH_HOENN_ZONE_LAVARIDGE },
    { MAPSEC_LAVARIDGE_TOWN,           KJH_HOENN_ZONE_LAVARIDGE },
    { MAPSEC_MIRAGE_TOWER,             KJH_HOENN_ZONE_DESERT },
    { MAPSEC_ROUTE_105,                KJH_HOENN_ZONE_SEA },
    { MAPSEC_UNDERWATER_105,           KJH_HOENN_ZONE_SEA },
    { MAPSEC_ROUTE_107,                KJH_HOENN_ZONE_SEA },
    { MAPSEC_ROUTE_108,                KJH_HOENN_ZONE_SEA },
    { MAPSEC_ABANDONED_SHIP,           KJH_HOENN_ZONE_SEA },
    { MAPSEC_NEW_MAUVILLE,             KJH_HOENN_ZONE_SEA },
    { MAPSEC_ALTERING_CAVE,            KJH_HOENN_ZONE_SEA },   // across Route 103's water
    { MAPSEC_ROUTE_119,                KJH_HOENN_ZONE_FORTREE },
    { MAPSEC_FORTREE_CITY,             KJH_HOENN_ZONE_FORTREE },
    { MAPSEC_ROUTE_120,                KJH_HOENN_ZONE_LILYCOVE },
    { MAPSEC_SCORCHED_SLAB,            KJH_HOENN_ZONE_LILYCOVE },
    { MAPSEC_ROUTE_121,                KJH_HOENN_ZONE_LILYCOVE },
    { MAPSEC_SAFARI_ZONE,              KJH_HOENN_ZONE_LILYCOVE },
    { MAPSEC_LILYCOVE_CITY,            KJH_HOENN_ZONE_LILYCOVE },
    { MAPSEC_ROUTE_122,                KJH_HOENN_ZONE_LILYCOVE },
    { MAPSEC_MT_PYRE,                  KJH_HOENN_ZONE_LILYCOVE },
    { MAPSEC_ROUTE_123,                KJH_HOENN_ZONE_LILYCOVE },
    { MAPSEC_MAGMA_HIDEOUT,            KJH_HOENN_ZONE_HIDEOUTS },
    { MAPSEC_AQUA_HIDEOUT,             KJH_HOENN_ZONE_HIDEOUTS },
    { MAPSEC_ROUTE_124,                KJH_HOENN_ZONE_HIDEOUTS },
    { MAPSEC_UNDERWATER_124,           KJH_HOENN_ZONE_HIDEOUTS },
    { MAPSEC_MOSSDEEP_CITY,            KJH_HOENN_ZONE_HIDEOUTS },
    { MAPSEC_ROUTE_125,                KJH_HOENN_ZONE_HIDEOUTS },
    { MAPSEC_UNDERWATER_125,           KJH_HOENN_ZONE_HIDEOUTS },
    { MAPSEC_SHOAL_CAVE,               KJH_HOENN_ZONE_HIDEOUTS },
    { MAPSEC_ROUTE_126,                KJH_HOENN_ZONE_SEAFLOOR },
    { MAPSEC_UNDERWATER_126,           KJH_HOENN_ZONE_SEAFLOOR },
    { MAPSEC_ROUTE_127,                KJH_HOENN_ZONE_SEAFLOOR },
    { MAPSEC_UNDERWATER_127,           KJH_HOENN_ZONE_SEAFLOOR },
    { MAPSEC_ROUTE_128,                KJH_HOENN_ZONE_SEAFLOOR },
    { MAPSEC_UNDERWATER_128,           KJH_HOENN_ZONE_SEAFLOOR },
    { MAPSEC_SEAFLOOR_CAVERN,          KJH_HOENN_ZONE_SEAFLOOR },
    { MAPSEC_UNDERWATER_SEAFLOOR_CAVERN, KJH_HOENN_ZONE_SEAFLOOR },
    { MAPSEC_SOOTOPOLIS_CITY,          KJH_HOENN_ZONE_SOOTOPOLIS },
    { MAPSEC_UNDERWATER_SOOTOPOLIS,    KJH_HOENN_ZONE_SOOTOPOLIS },
    { MAPSEC_CAVE_OF_ORIGIN,           KJH_HOENN_ZONE_SOOTOPOLIS },
    { MAPSEC_SKY_PILLAR,               KJH_HOENN_ZONE_SOOTOPOLIS },
    { MAPSEC_ROUTE_129,                KJH_HOENN_ZONE_SOOTOPOLIS },
    { MAPSEC_UNDERWATER_129,           KJH_HOENN_ZONE_SOOTOPOLIS },
    { MAPSEC_ROUTE_130,                KJH_HOENN_ZONE_SOOTOPOLIS },
    { MAPSEC_ROUTE_131,                KJH_HOENN_ZONE_SOOTOPOLIS },
    { MAPSEC_PACIFIDLOG_TOWN,          KJH_HOENN_ZONE_SOOTOPOLIS },
    { MAPSEC_ROUTE_132,                KJH_HOENN_ZONE_SOOTOPOLIS },
    { MAPSEC_ROUTE_133,                KJH_HOENN_ZONE_SOOTOPOLIS },
    { MAPSEC_ROUTE_134,                KJH_HOENN_ZONE_SOOTOPOLIS },
    { MAPSEC_EVER_GRANDE_CITY,         KJH_HOENN_ZONE_VICTORY_ROAD },
    { MAPSEC_VICTORY_ROAD,             KJH_HOENN_ZONE_VICTORY_ROAD },
    { MAPSEC_DESERT_UNDERPASS,         KJH_HOENN_ZONE_POSTGAME },   // the Fossil Maniac's tunnel, after the League
    { MAPSEC_ARTISAN_CAVE,             KJH_HOENN_ZONE_POSTGAME },   // by the Battle Frontier
};
