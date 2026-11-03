#ifndef GUARD_KJH_DEX_RADAR_H
#define GUARD_KJH_DEX_RADAR_H

// KJH (ENG-8): the route radar, a screen of the Pokedex (R on the Pokedex list). For each route of the regions
// reached so far it lists the wild Pokemon by encounter method with their chance: grass, surfing, the three rods,
// Rock Smash and the headbutt trees (CF-10: Johto's rare trees apart). Species never seen show as ?????; caught ones
// get a Poke Ball. CF-7: today's swarms are marked on the route list, and the route page shows the swarm species
// with its chance (the other species of that method lose that share). Ported from KJH's pokefirered tree
// (src/kjh_dex_radar*.c), where it was a page of FireRed's Pokedex. Expansion's DexNav (start menu) searches the map
// the player stands on; the radar covers every route.
//
// The regions are rows of a table (src/kjh_dex_radar.c, sRadarRegions): a region lists its routes once it is
// reached; its wild tables are found by map group. A new region (Hoenn) is one more row.

enum
{
    KJH_RADAR_SWARM_LAND,     // CF-7: today's swarm, in the grass
    KJH_RADAR_SWARM_FISHING,  // CF-7: today's swarm, by any rod
    KJH_RADAR_GRASS,
    KJH_RADAR_SURF,
    KJH_RADAR_OLD_ROD,
    KJH_RADAR_GOOD_ROD,
    KJH_RADAR_SUPER_ROD,
    KJH_RADAR_ROCK_SMASH,
    KJH_RADAR_HEADBUTT,       // a tree's Pokemon (Kanto's trees, Johto's common trees)
    KJH_RADAR_HEADBUTT_RARE,  // Johto's rare trees (Crystal's rare table, CF-10)
    KJH_RADAR_METHOD_COUNT
};

// The encounter tables a map can have (struct WildEncounterTypes)
enum
{
    KJH_RADAR_TABLE_LAND,
    KJH_RADAR_TABLE_WATER,
    KJH_RADAR_TABLE_ROCK_SMASH,
    KJH_RADAR_TABLE_FISHING,
    KJH_RADAR_TABLE_HEADBUTT,
    KJH_RADAR_TABLE_HEADBUTT_RARE,
    KJH_RADAR_TABLE_COUNT
};

struct KjhRadarEntry
{
    u16 species;
    u8 method; // KJH_RADAR_*
    u8 rate;   // percent, for this method
};

// --- The rules (src/kjh_dex_radar_rules.c): no game state ---

// The method a slot of an encounter table belongs to: the fishing table holds the three rods
u8 KJH_RadarSlotMethod(u8 table, u8 slot);
// Percent chance of that slot, among the encounters of its method (headbutt: among a tree's Pokemon)
u8 KJH_RadarSlotRate(u8 table, u8 slot);
// How many slots a table has
u8 KJH_RadarTableSlots(u8 table);
// Adds one slot of one map's table to that map's entries. A species in several slots of the same method adds up.
// Returns the new count (unchanged when full).
u8 KJH_RadarAddSlot(struct KjhRadarEntry *entries, u8 count, u8 max, u16 species, u8 table, u8 slot);
// Merges one map's entries into its route's (a route can have several maps: cave floors, Safari Zone areas). A
// species found on several maps keeps its best chance. Returns the new count.
u8 KJH_RadarMergeMap(struct KjhRadarEntry *route, u8 count, u8 max, const struct KjhRadarEntry *map, u8 mapCount);
// Sorts by method (swarms first), then highest chance first, then species
void KJH_RadarSort(struct KjhRadarEntry *entries, u8 count);
// Adds a species to a route's species, each once (a Pokemon can be met on grass and by fishing). Returns the new
// count (unchanged for SPECIES_NONE, a species already there or a full list).
u8 KJH_RadarAddSpecies(u16 *species, u8 count, u8 max, u16 newSpecies);
// CF-7: today's swarm on one map's entries. swarmMethod is KJH_RADAR_SWARM_LAND or KJH_RADAR_SWARM_FISHING; the
// swarm species takes chance % of that method's encounters (each rod's, for fishing), as the game rolls it, so the
// map's other entries of that method keep (100 - chance) % of theirs, rounded. Adds the swarm's own entry. Returns
// the new count.
u8 KJH_RadarApplySwarm(struct KjhRadarEntry *entries, u8 count, u8 max, u16 species, u8 swarmMethod, u8 chance);

// --- The game side (src/kjh_dex_radar.c): the wild tables, the regions reached, the Pokedex flags ---

#define KJH_RADAR_MAX_ROUTES  200
#define KJH_RADAR_MAX_ENTRIES 64

struct KjhRadarRoute
{
    u16 mapSec;
    u8 region;       // index in the radar's region table (KJH_RadarRegionName)
    u8 speciesCount;
    u8 caughtCount;
    bool8 swarm;     // CF-7: one of today's swarms is on this route
};

// The routes of the regions reached so far (Sevii Islands: once unlocked), by region in the table's order, then the
// region's own order (Kanto: map sections, Johto: the way the player travels). Returns how many.
u16 KJH_RadarBuildRoutes(struct KjhRadarRoute *routes, u16 max);
// One route's encounters with today's swarm on it, sorted (KJH_RadarSort). Returns how many.
u8 KJH_RadarBuildRoute(u16 mapSec, struct KjhRadarEntry *entries, u8 max);
// The name the radar shows for a species: its name once seen, else ?????
const u8 *KJH_RadarSpeciesName(u16 species);
// A region row's name (KANTO, JOHTO)
const u8 *KJH_RadarRegionName(u8 region);

// The screen (src/kjh_dex_radar_screen.c): opens the radar; B on the route list goes to returnCallback
void KJH_OpenRouteRadar(void (*returnCallback)(void));

#endif // GUARD_KJH_DEX_RADAR_H
