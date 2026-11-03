#include "global.h"
#include "clock.h"
#include "new_game.h"
#include "random.h"
#include "clock.h"
#include "pokemon.h"
#include "roamer.h"
#include "pokemon_size_record.h"
#include "script.h"
#include "lottery_corner.h"
#include "play_time.h"
#include "mauville_old_man.h"
#include "match_call.h"
#include "lilycove_lady.h"
#include "load_save.h"
#include "pokeblock.h"
#include "dewford_trend.h"
#include "berry.h"
#include "rtc.h"
#include "easy_chat.h"
#include "event_data.h"
#include "money.h"
#include "trainer_hill.h"
#include "trainer_tower.h"
#include "tv.h"
#include "coins.h"
#include "text.h"
#include "overworld.h"
#include "mail.h"
#include "battle_records.h"
#include "item.h"
#include "pokedex.h"
#include "apprentice.h"
#include "frontier_util.h"
#include "pokedex.h"
#include "save.h"
#include "link_rfu.h"
#include "main.h"
#include "contest.h"
#include "item_menu.h"
#include "pokemon_storage_system.h"
#include "pokemon_jump.h"
#include "decoration_inventory.h"
#include "secret_base.h"
#include "string_util.h"
#include "player_pc.h"
#include "field_specials.h"
#include "berry_powder.h"
#include "mystery_gift.h"
#include "union_room_chat.h"
#include "constants/map_groups.h"
#include "constants/items.h"
#include "script_pokemon_util.h"
#include "difficulty.h"
#include "kjh_clock.h"
#include "kjh_move_stars.h"
#include "kjh_swarms.h"
#include "constants/heal_locations.h"
#include "follower_npc.h"

extern const u8 EventScript_ResetAllMapFlags[];
extern const u8 EventScript_ResetAllMapFlagsFrlg[];

static void ClearFrontierRecord(void);
static void WarpToTruck(void);
static void ResetMiniGamesRecords(void);
static void ResetItemFlags(void);
static void ResetDexNav(void);

EWRAM_DATA bool8 gDifferentSaveFile = FALSE;
EWRAM_DATA bool8 gEnableContestDebugging = FALSE;

static const struct ContestWinner sContestWinnerPicDummy =
{
    .monName = _(""),
    .trainerName = _("")
};

void SetTrainerId(u32 trainerId, u8 *dst)
{
    dst[0] = trainerId;
    dst[1] = trainerId >> 8;
    dst[2] = trainerId >> 16;
    dst[3] = trainerId >> 24;
}

u32 GetTrainerId(u8 *trainerId)
{
    return (trainerId[3] << 24) | (trainerId[2] << 16) | (trainerId[1] << 8) | (trainerId[0]);
}

void CopyTrainerId(u8 *dst, u8 *src)
{
    s32 i;
    for (i = 0; i < TRAINER_ID_LENGTH; i++)
        dst[i] = src[i];
}

static void InitPlayerTrainerId(void)
{
    u32 trainerId = (Random() << 16) | GetGeneratedTrainerIdLower();
    SetTrainerId(trainerId, gSaveBlock2Ptr->playerTrainerId);
}

// L=A isnt set here for some reason.
static void SetDefaultOptions(void)
{
    gSaveBlock2Ptr->optionsTextSpeed = OPTIONS_TEXT_SPEED_MID;
    gSaveBlock2Ptr->optionsWindowFrameType = 0;
    gSaveBlock2Ptr->optionsSound = OPTIONS_SOUND_MONO;
    gSaveBlock2Ptr->optionsBattleStyle = OPTIONS_BATTLE_STYLE_SHIFT;
    gSaveBlock2Ptr->optionsBattleSceneOff = FALSE;
    gSaveBlock2Ptr->regionMapZoom = FALSE;
}

static void ClearPokedexFlags(void)
{
    memset(&gSaveBlock1Ptr->dexCaught, 0, sizeof(gSaveBlock1Ptr->dexCaught));
    memset(&gSaveBlock1Ptr->dexSeen, 0, sizeof(gSaveBlock1Ptr->dexSeen));
}

void ClearAllContestWinnerPics(void)
{
    s32 i;

    ClearContestWinnerPicsInContestHall();

    // Clear Museum paintings
    for (i = MUSEUM_CONTEST_WINNERS_START; i < NUM_CONTEST_WINNERS; i++)
        gSaveBlock1Ptr->contestWinners[i] = sContestWinnerPicDummy;
}

static void ClearFrontierRecord(void)
{
    CpuFill32(0, &gSaveBlock2Ptr->frontier, sizeof(gSaveBlock2Ptr->frontier));

    gSaveBlock2Ptr->frontier.opponentNames[0][0] = EOS;
    gSaveBlock2Ptr->frontier.opponentNames[1][0] = EOS;
}

static void WarpToTruck(void)
{
#if defined(KJH_DEBUG_WARP) && KJH_DEBUG_WARP == 4
    // KJH emulator harness (source/kjh_tools/test in the KJH repo): the test writes the map group, map number, x
    // and y at 0x0203FF00 before "New Game"; KJH_DebugHarnessStart gives the party and flags
    vu8 *p = (vu8 *)0x0203FF00;
    SetWarpDestination(p[0], p[1], WARP_ID_NONE, p[2], p[3]);
#else
    if (IS_FRLG)
        SetWarpDestination(MAP_GROUP(MAP_PALLET_TOWN_PLAYERS_HOUSE_2F), MAP_NUM(MAP_PALLET_TOWN_PLAYERS_HOUSE_2F), WARP_ID_NONE, 6, 6);
    else
        SetWarpDestination(MAP_GROUP(MAP_INSIDE_OF_TRUCK), MAP_NUM(MAP_INSIDE_OF_TRUCK), WARP_ID_NONE, -1, -1);
#endif
    WarpIntoMap();
}

#if defined(KJH_DEBUG_WARP) && KJH_DEBUG_WARP == 4
// KJH emulator harness, same layout as the KJH pokefirered tree: 0x0203FF04 up to 16 flags to set
// (0x8000 | flag clears it);
// 0x0203FF24 species, held item and level of the first Pokemon (0: Pikachu Lv 20), 0x0203FF2A a bag item,
// 0x0203FF2C species and level of a second Pokemon (0: none),
// 0x0203FF34 the VS Seeker's charge in steps (100: ready), 0x0203FF36 an item registered to SELECT
// (0x0203FF30-33 are the KJH tree's pack and journey switches),
// 0x0203FF38 a variable and its value (0: none), 0x0203FF3C a game stat and its value (0: none),
// 0x0203FF40 National Pokedex numbers 1 to N seen and caught, with the National Pokedex on (0: none),
// 0x0203FF44 a swarm of src/kjh_swarms.c to start, its index + 1 (0: the day's random one),
// 0x0203FF48 species and level of a third Pokemon (0: none)
static void KJH_DebugHarnessStart(void)
{
    vu16 *thirdMon = (vu16 *)0x0203FF48;
    vu16 *swarm = (vu16 *)0x0203FF44;
    vu16 *stat = (vu16 *)0x0203FF3C;
    vu16 *caughtUpTo = (vu16 *)0x0203FF40;
    vu16 *flags = (vu16 *)0x0203FF04;
    vu16 *dbgMon = (vu16 *)0x0203FF24;
    vu16 *vsSeeker = (vu16 *)0x0203FF34; // charge, registered item
    vu16 *var = (vu16 *)0x0203FF38;

    // A real game sets this in the player's house (setrespawn), which the harness skips: without it, losing a battle
    // warps to nowhere
    SetLastHealLocationWarp(HEAL_LOCATION_PALLET_TOWN);
    // Flags first: clearing FLAG_KJH_LEVELLESS (LV-2) keeps the given Pokemon at their own levels.
    for (u32 i = 0; i < 16 && flags[i] != 0; i++)
    {
        if (flags[i] & 0x8000) // a flag to clear, such as an object's hide flag set by the new game's reset
            FlagClear(flags[i] & 0x7FFF);
        else
            FlagSet(flags[i]);
    }
    if (dbgMon[0] != SPECIES_NONE)
        ScriptGiveMon(dbgMon[0], dbgMon[2], dbgMon[1]);
    else
        ScriptGiveMon(SPECIES_PIKACHU, 20, ITEM_NONE);
    if (dbgMon[4] != SPECIES_NONE)
        ScriptGiveMon(dbgMon[4], dbgMon[5], ITEM_NONE);
    if (thirdMon[0] != SPECIES_NONE)
        ScriptGiveMon(thirdMon[0], thirdMon[1], ITEM_NONE);
    if (dbgMon[3] != ITEM_NONE)
        AddBagItem(dbgMon[3], 1);
    FlagSet(FLAG_SYS_POKEMON_GET);
    FlagSet(FLAG_SYS_POKEDEX_GET);
    FlagSet(FLAG_SYS_B_DASH);
    AddBagItem(ITEM_POKE_BALL, 20);
    AddBagItem(ITEM_POTION, 10);
    gSaveBlock1Ptr->trainerRematchStepCounter = vsSeeker[0];
    gSaveBlock1Ptr->registeredItem = vsSeeker[1];
    if (var[0] >= VARS_START && var[0] <= VARS_END)
        VarSet(var[0], var[1]);
    if (stat[0] != 0 && stat[0] < NUM_GAME_STATS)
        SetGameStat(stat[0], stat[1]);
    if (swarm[0] != 0 && swarm[0] <= KJH_SwarmCount())
        KJH_StartSwarm(swarm[0] - 1);
    if (caughtUpTo[0] != 0)
    {
        EnableNationalPokedex();
        for (u32 dexNum = 1; dexNum <= caughtUpTo[0] && dexNum < NATIONAL_DEX_COUNT + 1; dexNum++)
        {
            GetSetPokedexFlag(dexNum, FLAG_SET_SEEN);
            GetSetPokedexFlag(dexNum, FLAG_SET_CAUGHT);
        }
    }
}
#endif

void Sav2_ClearSetDefault(void)
{
    ClearSav2();
    SetDefaultOptions();
}

void ResetMenuAndMonGlobals(void)
{
    gDifferentSaveFile = FALSE;
    ResetPokedexScrollPositions();
    ZeroPlayerPartyMons();
    ZeroEnemyPartyMons();
    ResetBagScrollPositions();
    ResetPokeblockScrollPositions();
}

void NewGameInitData(void)
{
#if IS_FRLG
    u8 rivalName[PLAYER_NAME_LENGTH + 1];
#endif
    if (gSaveFileStatus == SAVE_STATUS_EMPTY || gSaveFileStatus == SAVE_STATUS_CORRUPT)
        RtcReset();

#if IS_FRLG
    StringCopy(rivalName, gSaveBlock1Ptr->rivalName);
#endif
    gDifferentSaveFile = TRUE;
    gSaveBlock2Ptr->encryptionKey = 0;
    ZeroPlayerPartyMons();
    ZeroEnemyPartyMons();
    ResetPokedex();
    ClearFrontierRecord();
    ClearSav1();
    ClearSav3();
    ClearAllMail();
    gSaveBlock2Ptr->specialSaveWarpFlags = 0;
    gSaveBlock2Ptr->gcnLinkFlags = 0;
    InitPlayerTrainerId();
    PlayTimeCounter_Reset();
    ClearPokedexFlags();
    InitEventData();
    ClearTVShowData();
    ResetGabbyAndTy();
    ClearSecretBases();
    ClearBerryTrees();
    SetMoney(&gSaveBlock1Ptr->money, 3000);
    SetCoins(0);
    ResetLinkContestBoolean();
    ResetGameStats();
    ClearAllContestWinnerPics();
    ClearPlayerLinkBattleRecords();
    InitSeedotSizeRecord();
    InitLotadSizeRecord();
    gPartiesCount[B_TRAINER_PLAYER] = 0;
    ZeroPlayerPartyMons();
    ResetPokemonStorageSystem();
    DeactivateAllRoamers();
    gSaveBlock1Ptr->registeredItem = ITEM_NONE;
    ClearBag();
    NewGameInitPCItems();
    ClearPokeblocks();
    ClearDecorationInventories();
    InitEasyChatPhrases();
    SetMauvilleOldMan();
    InitDewfordTrend();
    ResetFanClub();
    ResetLotteryCorner();
    UpdateDailySeed();
    WarpToTruck();
    if (IS_FRLG)
        RunScriptImmediately(EventScript_ResetAllMapFlagsFrlg);
    else
        RunScriptImmediately(EventScript_ResetAllMapFlags);
#if IS_FRLG
        StringCopy(gSaveBlock1Ptr->rivalName, rivalName);
#endif
    ResetMiniGamesRecords();
    InitUnionRoomChatRegisteredTexts();
    InitLilycoveLady();
    ResetAllApprenticeData();
    ClearRankingHallRecords();
    InitMatchCallCounters();
    ClearMysteryGift();
    WipeTrainerNameRecords();
    ResetTrainerHillResults();
    ResetTrainerTowerResults();
    ResetContestLinkResults();
    SetCurrentDifficultyLevel(DIFFICULTY_NORMAL);
    ResetItemFlags();
    ResetDexNav();
    ClearFollowerNPCData();
    if (I_EXP_SHARE_FLAG != 0)
        FlagSet(I_EXP_SHARE_FLAG); // KJH: the party Exp. Share is on from the start.
    FlagSet(FLAG_KJH_LEVELLESS); // KJH (LV-2): the team's level follows the zones.
#if IS_FRLG
    FlagSet(FLAG_J_ALWAYS_SET); // KJH (ENG-9): Johto's objects that Crystal shows at night or in the morning stay hidden.
    KJH_ClearNotebook(); // KJH (LV-12): no trained moves yet
#endif
    if (OW_USE_FAKE_RTC)
        KJH_StartClock(); // KJH (CF-4): the in-game clock starts in the morning, with no question.
#if defined(KJH_DEBUG_WARP) && KJH_DEBUG_WARP == 4
    KJH_DebugHarnessStart();
#endif
}

static void ResetMiniGamesRecords(void)
{
    CpuFill16(0, &gSaveBlock2Ptr->berryCrush, sizeof(struct BerryCrush));
    SetBerryPowder(&gSaveBlock2Ptr->berryCrush.berryPowderAmount, 0);
    ResetPokemonJumpRecords();
    CpuFill16(0, &gSaveBlock2Ptr->berryPick, sizeof(struct BerryPickingResults));
}

static void ResetItemFlags(void)
{
#if OW_SHOW_ITEM_DESCRIPTIONS == OW_ITEM_DESCRIPTIONS_FIRST_TIME
    memset(&gSaveBlock3Ptr->itemFlags, 0, sizeof(gSaveBlock3Ptr->itemFlags));
#endif
}

static void ResetDexNav(void)
{
#if USE_DEXNAV_SEARCH_LEVELS == TRUE
    memset(gSaveBlock3Ptr->dexNavSearchLevels, 0, sizeof(gSaveBlock3Ptr->dexNavSearchLevels));
#endif
    gSaveBlock3Ptr->dexNavChain = 0;
}
