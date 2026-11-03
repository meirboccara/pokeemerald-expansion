// KJH: the team's level follows Kanto's zones (LV-2, src/kjh_team_level.c), and wild Pokemon sit in their zone's
// range (LV-3, kjh_tools/zone_levels.py). The zone table's tops, the badge
// ceiling, a catch, a gift and a Day Care pickup joining at the team's level, the party levelled on a step, nothing
// outside Kanto, and no Exp. or Rare Candy level-ups in the levels-free game.
#include "global.h"
#include "battle.h"
#include "battle_controllers.h"
#include "battle_util.h"
#include "daycare.h"
#include "event_data.h"
#include "kjh_team_level.h"
#include "pokemon.h"
#include "script_pokemon_util.h"
#include "string_util.h"
#include "wild_encounter.h"
#include "test/battle.h"
#include "test/test.h"
#include "constants/items.h"
#include "constants/map_groups.h"
#include "constants/region_map_sections.h"

// The test save stands on map 0, Hoenn's Petalburg City: these tests stand on a Kanto map, the section deciding the zone.
static void StandInKanto(void)
{
    gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(MAP_PALLET_TOWN);
    gSaveBlock1Ptr->location.mapNum = MAP_NUM(MAP_PALLET_TOWN);
}

static void SetBadges(u32 count)
{
    u32 i;
    FlagClear(FLAG_SYS_GAME_CLEAR);
    for (i = 0; i < NUM_BADGES; i++)
    {
        if (i < count)
            FlagSet(FLAG_BADGE01_GET + i);
        else
            FlagClear(FLAG_BADGE01_GET + i);
    }
}

// The levels-free game, standing in a Kanto section, with that zone top reached and no badge.
static void StartLevelsFree(u32 mapsec, u32 zoneTop)
{
    FlagSet(FLAG_KJH_LEVELLESS);
    StandInKanto();
    gMapHeader.regionMapSectionId = mapsec;
    VarSet(VAR_KJH_KANTO_ZONE_TOP, zoneTop);
    VarSet(VAR_KJH_TEAM_LEVEL, 0);
    SetBadges(0);
    ZeroPlayerPartyMons();
}

TEST("KJH: Kanto's zones give their top level, the League one step per room")
{
    EXPECT_EQ(KJH_ZoneTop(MAPSEC_PALLET_TOWN, MAP_PALLET_TOWN), 8);
    EXPECT_EQ(KJH_ZoneTop(MAPSEC_ROUTE_1, MAP_ROUTE1), 8);
    EXPECT_EQ(KJH_ZoneTop(MAPSEC_ROUTE_2, MAP_ROUTE2), 12);
    EXPECT_EQ(KJH_ZoneTop(MAPSEC_VIRIDIAN_FOREST, MAP_VIRIDIAN_FOREST), 12);
    EXPECT_EQ(KJH_ZoneTop(MAPSEC_PEWTER_CITY, MAP_PEWTER_CITY), 14);
    EXPECT_EQ(KJH_ZoneTop(MAPSEC_ROUTE_3, MAP_ROUTE3), 18);
    EXPECT_EQ(KJH_ZoneTop(MAPSEC_POKEMON_LEAGUE, MAP_POKEMON_LEAGUE_LORELEIS_ROOM), 84);
    EXPECT_EQ(KJH_ZoneTop(MAPSEC_POKEMON_LEAGUE, MAP_POKEMON_LEAGUE_BRUNOS_ROOM), 88);
    EXPECT_EQ(KJH_ZoneTop(MAPSEC_POKEMON_LEAGUE, MAP_POKEMON_LEAGUE_AGATHAS_ROOM), 92);
    EXPECT_EQ(KJH_ZoneTop(MAPSEC_POKEMON_LEAGUE, MAP_POKEMON_LEAGUE_LANCES_ROOM), 96);
    EXPECT_EQ(KJH_ZoneTop(MAPSEC_POKEMON_LEAGUE, MAP_POKEMON_LEAGUE_CHAMPIONS_ROOM), 100);
    EXPECT_EQ(KJH_ZoneTop(MAPSEC_LITTLEROOT_TOWN, MAP_LITTLEROOT_TOWN), 0);
}

TEST("KJH: the team's ceiling is the next Gym ace, then the Champion")
{
    static const u8 caps[] = {14, 22, 30, 40, 50, 60, 70, 80, 100};
    u32 badges;
    for (badges = 0; badges <= NUM_BADGES; badges++)
        EXPECT_EQ(KJH_TeamLevelCap(badges), caps[badges]);
}

TEST("KJH: the team stops at 14 until Brock is beaten, and Gyms count in any order")
{
    StandInKanto();
    VarSet(VAR_KJH_KANTO_ZONE_TOP, 12);
    SetBadges(0);
    EXPECT_EQ(KJH_TeamLevel(), 12);
    VarSet(VAR_KJH_KANTO_ZONE_TOP, 18);
    EXPECT_EQ(KJH_TeamLevel(), 14);
    SetBadges(1);
    EXPECT_EQ(KJH_TeamLevel(), 18);
    SetBadges(0);
    FlagSet(FLAG_BADGE05_GET); // Koga first: one badge, so Misty's ceiling.
    VarSet(VAR_KJH_KANTO_ZONE_TOP, 48);
    EXPECT_EQ(KJH_TeamLevel(), 22);
}

TEST("KJH: once the League is beaten, the team is at the Champion's level")
{
    VarSet(VAR_KJH_KANTO_ZONE_TOP, 8);
    SetBadges(NUM_BADGES);
    FlagSet(FLAG_SYS_GAME_CLEAR);
    EXPECT_EQ(KJH_TeamLevel(), 100);
    FlagClear(FLAG_SYS_GAME_CLEAR);
    EXPECT_EQ(KJH_TeamLevel(), 8);
}

TEST("KJH: a Pokémon set to a level gets that level's stats and a new peak level")
{
    struct Pokemon mon;
    CreateMon(&mon, SPECIES_CHARMANDER, 5, 0, OTID_STRUCT_PRESET(0));
    KJH_SetMonLevel(&mon, 14);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_LEVEL), 14);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_PEAK_LEVEL), 14);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_HP), GetMonData(&mon, MON_DATA_MAX_HP));
    EXPECT_GT(GetMonData(&mon, MON_DATA_ATK), 10);
    KJH_SetMonLevel(&mon, 12); // A lower team level (a new region, later) keeps the peak.
    EXPECT_EQ(GetMonData(&mon, MON_DATA_LEVEL), 12);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_PEAK_LEVEL), 14);
}

TEST("KJH: a catch joins at the team's level, with that met level")
{
    struct Pokemon mon;
    StartLevelsFree(MAPSEC_VIRIDIAN_FOREST, 12);
    CreateMon(&mon, SPECIES_PIDGEY, 3, 0, OTID_STRUCT_PRESET(0));
    ASSUME(GiveCapturedMonToPlayer(&mon) == MON_GIVEN_TO_PARTY);
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_LEVEL), 12);
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_MET_LEVEL), 12);
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_PEAK_LEVEL), 12);
}

TEST("KJH: outside the levels-free game, or outside Kanto, a catch keeps its own level")
{
    struct Pokemon mon;
    StartLevelsFree(MAPSEC_VIRIDIAN_FOREST, 12);
    FlagClear(FLAG_KJH_LEVELLESS);
    CreateMon(&mon, SPECIES_PIDGEY, 3, 0, OTID_STRUCT_PRESET(0));
    ASSUME(GiveCapturedMonToPlayer(&mon) == MON_GIVEN_TO_PARTY);
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_LEVEL), 3);
    StartLevelsFree(MAPSEC_LITTLEROOT_TOWN, 12);
    CreateMon(&mon, SPECIES_PIDGEY, 3, 0, OTID_STRUCT_PRESET(0));
    ASSUME(GiveCapturedMonToPlayer(&mon) == MON_GIVEN_TO_PARTY);
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_LEVEL), 3);
    EXPECT(!KJH_TryTeamLevelStep());
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_LEVEL), 3);
}

TEST("KJH: a gift joins at the team's level and keeps its met level, an egg stays an egg")
{
    struct Pokemon mon;
    StartLevelsFree(MAPSEC_PALLET_TOWN, 8);
    CreateMon(&mon, SPECIES_BULBASAUR, 5, 0, OTID_STRUCT_PRESET(0));
    GiveScriptedMonToPlayer(&mon, PARTY_SIZE);
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_LEVEL), 8);
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_MET_LEVEL), 5);
    ASSUME(ScriptGiveEgg(SPECIES_PICHU) == MON_GIVEN_TO_PARTY);
    EXPECT(GetMonData(&gParties[B_TRAINER_PLAYER][1], MON_DATA_IS_EGG));
    KJH_ApplyTeamLevelToParty();
    EXPECT_NE(GetMonData(&gParties[B_TRAINER_PLAYER][1], MON_DATA_LEVEL), 8);
}

TEST("KJH: a Pokémon doesn't grow at the Day Care and comes back at the team's level, for the base fee")
{
    StartLevelsFree(MAPSEC_FOUR_ISLAND, 100);
    SetBadges(NUM_BADGES);
    memset(&gSaveBlock1Ptr->daycare, 0, sizeof(gSaveBlock1Ptr->daycare));
    CreateMon(&gParties[B_TRAINER_PLAYER][0], SPECIES_CHARMANDER, 50, 0, OTID_STRUCT_PRESET(0));
    CreateMon(&gParties[B_TRAINER_PLAYER][1], SPECIES_PIDGEY, 50, 0, OTID_STRUCT_PRESET(0));
    CalculatePlayerPartyCount();
    gSpecialVar_0x8004 = 1;
    StoreSelectedPokemonInDaycare();
    gSaveBlock1Ptr->daycare.mons[0].steps = 20000;
    gSpecialVar_0x8004 = 0;
    EXPECT_EQ(GetNumLevelsGainedFromDaycare(), 0);
    TakePokemonFromDaycare();
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][1], MON_DATA_SPECIES), SPECIES_PIDGEY);
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][1], MON_DATA_LEVEL), 100);
}

TEST("KJH: a step levels the whole party, and says so when the team's level went up")
{
    StartLevelsFree(MAPSEC_PEWTER_CITY, 14);
    SetBadges(1);
    CreateMon(&gParties[B_TRAINER_PLAYER][0], SPECIES_CHARMANDER, 14, 0, OTID_STRUCT_PRESET(0));
    CreateMon(&gParties[B_TRAINER_PLAYER][1], SPECIES_PIDGEY, 30, 0, OTID_STRUCT_PRESET(0));
    VarSet(VAR_KJH_TEAM_LEVEL, 14);
    gMapHeader.regionMapSectionId = MAPSEC_ROUTE_3;
    EXPECT(KJH_TryTeamLevelStep());
    EXPECT_EQ(VarGet(VAR_KJH_KANTO_ZONE_TOP), 18);
    EXPECT_EQ(VarGet(VAR_KJH_TEAM_LEVEL), 18);
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_LEVEL), 18);
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][1], MON_DATA_LEVEL), 18);
    gMapHeader.regionMapSectionId = MAPSEC_PALLET_TOWN; // Going back stays at 18, with no message.
    EXPECT(!KJH_TryTeamLevelStep());
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_LEVEL), 18);
}

TEST("KJH: a Rare Candy has no effect in the levels-free game")
{
    struct Pokemon mon;
    FlagSet(FLAG_KJH_LEVELLESS);
    CreateMon(&mon, SPECIES_CHARMANDER, 14, 0, OTID_STRUCT_PRESET(0));
    EXPECT(PokemonUseItemEffects(&mon, ITEM_RARE_CANDY, 0, 0, FALSE));
    EXPECT_EQ(GetMonData(&mon, MON_DATA_LEVEL), 14);
    FlagClear(FLAG_KJH_LEVELLESS);
    EXPECT(!PokemonUseItemEffects(&mon, ITEM_RARE_CANDY, 0, 0, FALSE));
    EXPECT_EQ(GetMonData(&mon, MON_DATA_LEVEL), 15);
}

// LV-7: no EVs either; Training points replace them (test/kjh/training.c)
WILD_BATTLE_TEST("KJH: in the levels-free game, a knockout gives no Exp. and no EVs, but Training points")
{
    GIVEN {
        FLAG_SET(FLAG_KJH_LEVELLESS);
        PLAYER(SPECIES_WOBBUFFET) { Level(20); }
        OPPONENT(SPECIES_CATERPIE) { Level(10); HP(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        MESSAGE("The wild Caterpie fainted!");
        NOT EXPERIENCE_BAR(player);
    } THEN {
        EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_LEVEL), 20);
        EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_HP_EV), 0);
        EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_TRAINING_BANK), 1);
    }
}

TEST("KJH: Route 1's grass is still Lv 5-8 with 6 badges")
{
    const struct WildPokemonInfo *grass;
    u32 lo = MAX_LEVEL, hi = 0, headerId;
    SetBadges(6);
    gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(MAP_ROUTE1);
    gSaveBlock1Ptr->location.mapNum = MAP_NUM(MAP_ROUTE1);
    headerId = GetCurrentMapWildMonHeaderId();
    ASSUME(headerId != HEADER_NONE);
    grass = gWildMonHeaders[headerId].encounterTypes[TIME_OF_DAY_DEFAULT].landMonsInfo;
    for (u32 i = 0; i < NUM_LAND_MONS_ENCOUNTER_SLOTS; i++)
    {
        lo = min(lo, grass->wildPokemon[i].minLevel);
        hi = max(hi, grass->wildPokemon[i].maxLevel);
    }

    EXPECT_EQ(lo, 5);
    EXPECT_EQ(hi, 8);
}

TEST("KJH: a Gym's trainers move with the badges, only in their Gym and in the levels-free game")
{
    StartLevelsFree(MAPSEC_PEWTER_CITY, 14);
    gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(MAP_PEWTER_CITY_GYM);
    gSaveBlock1Ptr->location.mapNum = MAP_NUM(MAP_PEWTER_CITY_GYM);
    EXPECT_EQ(KJH_GymLevelShift(), 0);
    SetBadges(2);
    EXPECT_EQ(KJH_GymLevelShift(), 16);
    FlagClear(FLAG_KJH_LEVELLESS);
    EXPECT_EQ(KJH_GymLevelShift(), 0);
    FlagSet(FLAG_KJH_LEVELLESS);
    gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(MAP_ROUTE3);
    gSaveBlock1Ptr->location.mapNum = MAP_NUM(MAP_ROUTE3);
    EXPECT_EQ(KJH_GymLevelShift(), 0);
}

// A player's own Pokemon caught at the team's level (met level 14 here) with no badge: Gen 8 obedience compares the
// met level with 10.
static void SetUpOwnBattler(u32 metLevel)
{
    gBattleTypeFlags = 0;
    gBattlerAttacker = 0;
    gBattlerBattleController[0] = BATTLE_CONTROLLER_PLAYER;
    gBattleMons[0].level = metLevel;
    gBattleMons[0].metLevel = metLevel;
    gBattleMons[0].otId = READ_OTID_FROM_SAVE;
    StringCopy(gBattleMons[0].otName, gSaveBlock2Ptr->playerName);
}

TEST("KJH: in the levels-free game, the player's Pokemon always obey, whatever their level")
{
    u32 disobeyed = 0;
    SetBadges(0);
    SetUpOwnBattler(14);
    FlagSet(FLAG_KJH_LEVELLESS);
    for (u32 i = 0; i < 64; i++)
        EXPECT_EQ(GetAttackerObedienceForAction(), OBEYS);
    FlagClear(FLAG_KJH_LEVELLESS);
    SetUpOwnBattler(60);
    for (u32 i = 0; i < 64; i++)
    {
        if (GetAttackerObedienceForAction() != OBEYS)
            disobeyed++;
    }

    EXPECT_GT(disobeyed, 0); // Without the levels-free game, Gen 8 obedience still applies.
}
