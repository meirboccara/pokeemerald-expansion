// KJH (LV-18): Johto's zones on the shared level curve (docs/LEVELLESS_DESIGN.md §1, variant C), place for place
// with Kanto's (src/data/kjh_kanto_zones.h): the same ranges, the same Gym aces 14 · 22 · 30 · 40 · 50 · 60 · 70 · 80
// and the same ceilings (sTeamLevelCaps). The zones follow Crystal's usual road (Falkner, Bugsy, Whitney, Morty,
// Chuck, Jasmine, Pryce, Clair). kjh_tools/zone_levels.py puts Johto's wild Pokémon and trainers on them. A first
// draft, to tune. Johto's League is Indigo Plateau's rooms (STORY.md), ported with ENG-10.

enum KjhJohtoZone
{
    KJH_JOHTO_ZONE_NONE,
    // 0 badges, Falkner's ace 14
    KJH_JOHTO_ZONE_NEW_BARK,
    KJH_JOHTO_ZONE_CHERRYGROVE,
    KJH_JOHTO_ZONE_VIOLET,
    // 1 badge, Bugsy's ace 22
    KJH_JOHTO_ZONE_UNION_CAVE,
    KJH_JOHTO_ZONE_AZALEA,
    // 2 badges, Whitney's ace 30
    KJH_JOHTO_ZONE_ILEX_FOREST,
    KJH_JOHTO_ZONE_GOLDENROD,
    // 3 badges, Morty's ace 40
    KJH_JOHTO_ZONE_NATIONAL_PARK,
    KJH_JOHTO_ZONE_ECRUTEAK,
    // 4 badges, Chuck's ace 50
    KJH_JOHTO_ZONE_ROUTE_38,
    KJH_JOHTO_ZONE_OLIVINE,
    KJH_JOHTO_ZONE_CIANWOOD,
    // 5 badges, Jasmine's ace 60
    KJH_JOHTO_ZONE_MT_MORTAR,
    // 6 badges, Pryce's ace 70
    KJH_JOHTO_ZONE_MAHOGANY,
    // 7 badges, Clair's ace 80: in Crystal, Team Rocket takes the Radio Tower once Pryce is beaten
    KJH_JOHTO_ZONE_RADIO_TOWER,
    KJH_JOHTO_ZONE_ICE_PATH,
    // 8 badges: the road to the League
    KJH_JOHTO_ZONE_VICTORY_ROAD,
    // After the League
    KJH_JOHTO_ZONE_POSTGAME,
    KJH_JOHTO_ZONE_COUNT,
};

static const struct KjhZoneRange sJohtoZones[KJH_JOHTO_ZONE_COUNT] =
{
    [KJH_JOHTO_ZONE_NEW_BARK]        = {  5,   8 },
    [KJH_JOHTO_ZONE_CHERRYGROVE]     = {  9,  12 },
    [KJH_JOHTO_ZONE_VIOLET]          = { 12,  14 },
    [KJH_JOHTO_ZONE_UNION_CAVE]      = { 14,  18 },
    [KJH_JOHTO_ZONE_AZALEA]          = { 18,  21 },
    [KJH_JOHTO_ZONE_ILEX_FOREST]     = { 22,  26 },
    [KJH_JOHTO_ZONE_GOLDENROD]       = { 26,  28 },
    [KJH_JOHTO_ZONE_NATIONAL_PARK]   = { 30,  34 },
    [KJH_JOHTO_ZONE_ECRUTEAK]        = { 34,  38 },
    [KJH_JOHTO_ZONE_ROUTE_38]        = { 40,  43 },
    [KJH_JOHTO_ZONE_OLIVINE]         = { 43,  46 },
    [KJH_JOHTO_ZONE_CIANWOOD]        = { 46,  48 },
    [KJH_JOHTO_ZONE_MT_MORTAR]       = { 50,  56 },
    [KJH_JOHTO_ZONE_MAHOGANY]        = { 60,  66 },
    [KJH_JOHTO_ZONE_RADIO_TOWER]     = { 70,  74 },
    [KJH_JOHTO_ZONE_ICE_PATH]        = { 74,  78 },
    [KJH_JOHTO_ZONE_VICTORY_ROAD]    = { 80,  83 },
    [KJH_JOHTO_ZONE_POSTGAME]        = { 90, 100 },
};

// Johto's Gyms and their ace in Crystal's Gym order (the ceiling of the badges before them).
static const struct KjhGymAce sJohtoGyms[] =
{
    { MAP_JOHTO_VIOLET_GYM,        14 },
    { MAP_JOHTO_AZALEA_GYM,        22 },
    { MAP_JOHTO_GOLDENROD_GYM,     30 },
    { MAP_JOHTO_ECRUTEAK_GYM,      40 },
    { MAP_JOHTO_CIANWOOD_GYM,      50 },
    { MAP_JOHTO_OLIVINE_GYM,       60 },
    { MAP_JOHTO_MAHOGANY_GYM,      70 },
    { MAP_JOHTO_BLACKTHORN_GYM_1F, 80 },
    { MAP_JOHTO_BLACKTHORN_GYM_2F, 80 },
};

// Maps that have a zone of their own, before their section's: Dark Cave's Blackthorn end, and the Rocket warehouse
// under Goldenrod, taken with the Radio Tower.
static const struct KjhMapZone sJohtoMapZones[] =
{
    { MAP_JOHTO_DARK_CAVE_BLACKTHORN_ENTRANCE,               KJH_JOHTO_ZONE_ICE_PATH },
    { MAP_JOHTO_GOLDENROD_UNDERGROUND_SWITCH_ROOM_ENTRANCES, KJH_JOHTO_ZONE_RADIO_TOWER },
    { MAP_JOHTO_GOLDENROD_UNDERGROUND_WAREHOUSE,             KJH_JOHTO_ZONE_RADIO_TOWER },
};

// Every Johto section (towns take in their houses, Pokémon Centers and Gyms).
static const struct KjhMapsecZone sJohtoMapsecZones[] =
{
    { MAPSEC_J_NEW_BARK_TOWN,    KJH_JOHTO_ZONE_NEW_BARK },
    { MAPSEC_J_ROUTE_29,         KJH_JOHTO_ZONE_NEW_BARK },
    { MAPSEC_J_ROUTE_46,         KJH_JOHTO_ZONE_NEW_BARK },
    { MAPSEC_J_CHERRYGROVE_CITY, KJH_JOHTO_ZONE_CHERRYGROVE },
    { MAPSEC_J_ROUTE_30,         KJH_JOHTO_ZONE_CHERRYGROVE },
    { MAPSEC_J_ROUTE_31,         KJH_JOHTO_ZONE_CHERRYGROVE },
    { MAPSEC_J_DARK_CAVE,        KJH_JOHTO_ZONE_CHERRYGROVE },
    { MAPSEC_J_VIOLET_CITY,      KJH_JOHTO_ZONE_VIOLET },
    { MAPSEC_J_SPROUT_TOWER,     KJH_JOHTO_ZONE_VIOLET },
    { MAPSEC_J_ROUTE_32,         KJH_JOHTO_ZONE_UNION_CAVE },
    { MAPSEC_J_RUINS_OF_ALPH,    KJH_JOHTO_ZONE_UNION_CAVE },
    { MAPSEC_J_UNION_CAVE,       KJH_JOHTO_ZONE_UNION_CAVE },
    { MAPSEC_J_ROUTE_33,         KJH_JOHTO_ZONE_UNION_CAVE },
    { MAPSEC_J_AZALEA_TOWN,      KJH_JOHTO_ZONE_AZALEA },
    { MAPSEC_J_SLOWPOKE_WELL,    KJH_JOHTO_ZONE_AZALEA },
    { MAPSEC_J_ILEX_FOREST,      KJH_JOHTO_ZONE_ILEX_FOREST },
    { MAPSEC_J_ROUTE_34,         KJH_JOHTO_ZONE_ILEX_FOREST },
    { MAPSEC_J_GOLDENROD_CITY,   KJH_JOHTO_ZONE_GOLDENROD },
    { MAPSEC_J_ROUTE_35,         KJH_JOHTO_ZONE_NATIONAL_PARK },
    { MAPSEC_J_NATIONAL_PARK,    KJH_JOHTO_ZONE_NATIONAL_PARK },
    { MAPSEC_J_ROUTE_36,         KJH_JOHTO_ZONE_NATIONAL_PARK },
    { MAPSEC_J_ROUTE_37,         KJH_JOHTO_ZONE_NATIONAL_PARK },
    { MAPSEC_J_ECRUTEAK_CITY,    KJH_JOHTO_ZONE_ECRUTEAK },
    { MAPSEC_J_BURNED_TOWER,     KJH_JOHTO_ZONE_ECRUTEAK },
    { MAPSEC_J_ROUTE_38,         KJH_JOHTO_ZONE_ROUTE_38 },
    { MAPSEC_J_ROUTE_39,         KJH_JOHTO_ZONE_ROUTE_38 },
    { MAPSEC_J_OLIVINE_CITY,     KJH_JOHTO_ZONE_OLIVINE },
    { MAPSEC_J_LIGHTHOUSE,       KJH_JOHTO_ZONE_OLIVINE },
    { MAPSEC_J_ROUTE_40,         KJH_JOHTO_ZONE_CIANWOOD },
    { MAPSEC_J_ROUTE_41,         KJH_JOHTO_ZONE_CIANWOOD },
    { MAPSEC_J_WHIRL_ISLANDS,    KJH_JOHTO_ZONE_CIANWOOD },
    { MAPSEC_J_CIANWOOD_CITY,    KJH_JOHTO_ZONE_CIANWOOD },
    { MAPSEC_J_ROUTE_42,         KJH_JOHTO_ZONE_MT_MORTAR },
    { MAPSEC_J_MT_MORTAR,        KJH_JOHTO_ZONE_MT_MORTAR },
    { MAPSEC_J_MAHOGANY_TOWN,    KJH_JOHTO_ZONE_MAHOGANY },
    { MAPSEC_J_ROUTE_43,         KJH_JOHTO_ZONE_MAHOGANY },
    { MAPSEC_J_LAKE_OF_RAGE,     KJH_JOHTO_ZONE_MAHOGANY },
    { MAPSEC_J_RADIO_TOWER,      KJH_JOHTO_ZONE_RADIO_TOWER },
    { MAPSEC_J_TIN_TOWER,        KJH_JOHTO_ZONE_RADIO_TOWER },
    { MAPSEC_J_ROUTE_44,         KJH_JOHTO_ZONE_ICE_PATH },
    { MAPSEC_J_ICE_PATH,         KJH_JOHTO_ZONE_ICE_PATH },
    { MAPSEC_J_BLACKTHORN_CITY,  KJH_JOHTO_ZONE_ICE_PATH },
    { MAPSEC_J_DRAGONS_DEN,      KJH_JOHTO_ZONE_ICE_PATH },
    { MAPSEC_J_ROUTE_45,         KJH_JOHTO_ZONE_ICE_PATH },
    { MAPSEC_J_ROUTE_27,         KJH_JOHTO_ZONE_VICTORY_ROAD },
    { MAPSEC_J_TOHJO_FALLS,      KJH_JOHTO_ZONE_VICTORY_ROAD },
    { MAPSEC_J_ROUTE_26,         KJH_JOHTO_ZONE_VICTORY_ROAD },
    { MAPSEC_J_ROUTE_28,         KJH_JOHTO_ZONE_POSTGAME },
    { MAPSEC_J_SILVER_CAVE,      KJH_JOHTO_ZONE_POSTGAME },
};
