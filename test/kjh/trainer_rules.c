// KJH: trainer levels and boss rules (src/kjh_progression.c) on Brock, Misty and the first rival. Their levels are
// the data's, which kjh_tools/zone_levels.py set from the zones (LV-3); a Gym Leader's team follows the badges in
// the levels-free game. The test build has its own trainer table, so they are copied here from
// src/data/trainers_frlg.party.
#include "global.h"
#include "battle.h"
#include "battle_setup.h"
#include "data.h"
#include "event_data.h"
#include "kjh_progression.h"
#include "kjh_team_level.h"
#include "malloc.h"
#include "move.h"
#include "pokemon.h"
#include "test/test.h"
#include "constants/battle_ai.h"
#include "constants/items.h"
#include "constants/map_groups.h"
#include "constants/opponents.h"
#include "constants/trainers.h"

#define BROCK_AI (AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY)

static const struct TrainerMon sBrockParty[] =
{
    {
        .species = SPECIES_GEODUDE,
        .gender = TRAINER_MON_RANDOM_GENDER,
        .iv = TRAINER_PARTY_IVS(0, 0, 0, 0, 0, 0),
        .lvl = 12,
        .ball = POKEBALL_COUNT,
        .nature = NATURE_HARDY,
        .dynamaxLevel = MAX_DYNAMAX_LEVEL,
        .moves = {MOVE_TACKLE, MOVE_DEFENSE_CURL},
    },
    {
        .species = SPECIES_ONIX,
        .gender = TRAINER_MON_RANDOM_GENDER,
        .iv = TRAINER_PARTY_IVS(0, 0, 0, 0, 0, 0),
        .lvl = 14,
        .ball = POKEBALL_COUNT,
        .nature = NATURE_HARDY,
        .dynamaxLevel = MAX_DYNAMAX_LEVEL,
        .moves = {MOVE_TACKLE, MOVE_BIND, MOVE_ROCK_TOMB},
    },
};

static const struct Trainer sBrock =
{
    .trainerName = _("BROCK"),
    .trainerClass = TRAINER_CLASS_LEADER_FRLG,
    .aiFlags = BROCK_AI,
    .party = sBrockParty,
    .partySize = ARRAY_COUNT(sBrockParty),
};

static const struct TrainerMon sMistyParty[] =
{
    {
        .species = SPECIES_STARYU,
        .gender = TRAINER_MON_RANDOM_GENDER,
        .iv = TRAINER_PARTY_IVS(0, 0, 0, 0, 0, 0),
        .lvl = 19,
        .ball = POKEBALL_COUNT,
        .nature = NATURE_HARDY,
        .dynamaxLevel = MAX_DYNAMAX_LEVEL,
    },
    {
        .species = SPECIES_STARMIE,
        .gender = TRAINER_MON_RANDOM_GENDER,
        .iv = TRAINER_PARTY_IVS(0, 0, 0, 0, 0, 0),
        .lvl = 22,
        .ball = POKEBALL_COUNT,
        .nature = NATURE_HARDY,
        .dynamaxLevel = MAX_DYNAMAX_LEVEL,
    },
};

static const struct Trainer sMisty =
{
    .trainerName = _("MISTY"),
    .trainerClass = TRAINER_CLASS_LEADER_FRLG,
    .aiFlags = BROCK_AI,
    .party = sMistyParty,
    .partySize = ARRAY_COUNT(sMistyParty),
};

static const struct TrainerMon sRivalParty[] =
{
    {
        .species = SPECIES_SQUIRTLE,
        .gender = TRAINER_MON_RANDOM_GENDER,
        .iv = TRAINER_PARTY_IVS(0, 0, 0, 0, 0, 0),
        .lvl = 8,
        .ball = POKEBALL_COUNT,
        .nature = NATURE_HARDY,
        .dynamaxLevel = MAX_DYNAMAX_LEVEL,
        .moves = {MOVE_TACKLE, MOVE_TAIL_WHIP},
    },
};

static const struct Trainer sOaksLabRival =
{
    .trainerName = _("TERRY"),
    .trainerClass = TRAINER_CLASS_RIVAL_EARLY_FRLG,
    .aiFlags = BROCK_AI,
    .party = sRivalParty,
    .partySize = ARRAY_COUNT(sRivalParty),
};

static void GivePlayerParty(const u8 *levels, u32 count)
{
    ZeroPlayerPartyMons();
    for (u32 i = 0; i < count; i++)
        CreateMon(&gParties[B_TRAINER_PLAYER][i], SPECIES_CHARMANDER, levels[i], 0, OTID_STRUCT_PLAYER_ID);
    CalculatePlayerPartyCount();
}

static void SetBadges(u32 count)
{
    for (u32 i = 0; i < NUM_BADGES; i++)
    {
        if (i < count)
            FlagSet(FLAG_BADGE01_GET + i);
        else
            FlagClear(FLAG_BADGE01_GET + i);
    }
}

static void SetMap(u32 map)
{
    gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(map);
    gSaveBlock1Ptr->location.mapNum = MAP_NUM(map);
}

static struct Pokemon *CreateParty(const struct Trainer *trainer, u16 trainerNum)
{
    struct Pokemon *party = AllocZeroed(PARTY_SIZE * sizeof(struct Pokemon));
    CreateOpponentTrainerParty(party, trainer, trainerNum);
    return party;
}

TEST("KJH: Brock keeps his levels whatever the party's")
{
    u32 partyLevel = 0;
    PARAMETRIZE { partyLevel = 8; }
    PARAMETRIZE { partyLevel = 50; }
    u8 levels[] = {partyLevel, partyLevel};
    FlagSet(FLAG_KJH_LEVELLESS);
    GivePlayerParty(levels, ARRAY_COUNT(levels));
    SetBadges(0);
    SetMap(MAP_PEWTER_CITY_GYM);
    struct Pokemon *party = CreateParty(&sBrock, TRAINER_LEADER_BROCK);
    EXPECT_EQ(GetMonData(&party[0], MON_DATA_LEVEL), 12);
    EXPECT_EQ(GetMonData(&party[1], MON_DATA_LEVEL), 14);
    Free(party);
}

TEST("KJH: Misty's ace is 22 with 1 badge, and follows the badges when she comes later")
{
    u32 badges = 0, staryu = 0, starmie = 0;
    PARAMETRIZE { badges = 1; staryu = 19; starmie = 22; }
    PARAMETRIZE { badges = 3; staryu = 37; starmie = 40; }
    static const u8 levels[] = {20, 20};
    FlagSet(FLAG_KJH_LEVELLESS);
    GivePlayerParty(levels, ARRAY_COUNT(levels));
    SetBadges(badges);
    SetMap(MAP_CERULEAN_CITY_GYM);
    struct Pokemon *party = CreateParty(&sMisty, TRAINER_LEADER_MISTY);
    EXPECT_EQ(GetMonData(&party[0], MON_DATA_LEVEL), staryu);
    EXPECT_EQ(GetMonData(&party[1], MON_DATA_LEVEL), starmie);
    Free(party);
}

TEST("KJH: a Gym Leader's ace is the team's ceiling for the badges: 14, 30, 80, and the Gym moves with it")
{
    u32 badges = 0, onix = 0;
    PARAMETRIZE { badges = 0; onix = 14; }
    PARAMETRIZE { badges = 2; onix = 30; }
    PARAMETRIZE { badges = 7; onix = 80; }
    static const u8 levels[] = {14, 14};
    FlagSet(FLAG_KJH_LEVELLESS);
    GivePlayerParty(levels, ARRAY_COUNT(levels));
    SetBadges(badges);
    SetMap(MAP_PEWTER_CITY_GYM);
    struct Pokemon *party = CreateParty(&sBrock, TRAINER_LEADER_BROCK);
    EXPECT_EQ(GetMonData(&party[1], MON_DATA_LEVEL), onix);
    EXPECT_EQ(GetMonData(&party[0], MON_DATA_LEVEL), onix - 2);
    Free(party);
}

TEST("KJH: without the levels-free game, a Gym Leader keeps the data's levels")
{
    static const u8 levels[] = {14, 14};
    FlagClear(FLAG_KJH_LEVELLESS);
    GivePlayerParty(levels, ARRAY_COUNT(levels));
    SetBadges(5);
    SetMap(MAP_PEWTER_CITY_GYM);
    struct Pokemon *party = CreateParty(&sBrock, TRAINER_LEADER_BROCK);
    EXPECT_EQ(GetMonData(&party[1], MON_DATA_LEVEL), 14);
    Free(party);
}

TEST("KJH: Brock gets boss IVs, EVs growing with badges and a nature for his moves")
{
    u32 badges = 0, evs = 0;
    PARAMETRIZE { badges = 0; evs = 28; }
    PARAMETRIZE { badges = 8; evs = 252; }
    static const u8 levels[] = {8, 6};
    FlagClear(FLAG_KJH_LEVELLESS); // His own levels at any badge count, so FireRed's moves.
    GivePlayerParty(levels, ARRAY_COUNT(levels));
    SetBadges(badges);
    SetMap(MAP_PEWTER_CITY_GYM);
    struct Pokemon *party = CreateParty(&sBrock, TRAINER_LEADER_BROCK);
    struct Pokemon *onix = &party[1];
    // Early boss: IVs 20, no Sitrus Berry, FireRed's moves.
    for (u32 i = 0; i < NUM_STATS; i++)
        EXPECT_EQ(GetMonData(onix, MON_DATA_HP_IV + i), 20);
    EXPECT_EQ(GetMonData(onix, MON_DATA_HELD_ITEM), ITEM_NONE);
    EXPECT_EQ(GetMonData(onix, MON_DATA_MOVE1), MOVE_TACKLE);
    EXPECT_EQ(GetMonData(onix, MON_DATA_MOVE2), MOVE_BIND);
    EXPECT_EQ(GetMonData(onix, MON_DATA_MOVE3), MOVE_ROCK_TOMB);
    // physical moves only: EVs in Attack and in Onix's best other stat (Defense); Adamant (+Atk -Sp. Atk)
    EXPECT_EQ(GetMonData(onix, MON_DATA_ATK_EV), evs);
    EXPECT_EQ(GetMonData(onix, MON_DATA_DEF_EV), evs);
    EXPECT_EQ(GetMonData(onix, MON_DATA_HP_EV), 0);
    EXPECT_EQ(GetMonData(onix, MON_DATA_SPEED_EV), 0);
    EXPECT_EQ(GetMonData(onix, MON_DATA_SPATK_EV), 0);
    EXPECT_EQ(GetMonData(onix, MON_DATA_SPDEF_EV), 0);
    EXPECT_EQ(GetMonData(onix, MON_DATA_HIDDEN_NATURE), NATURE_ADAMANT);
    Free(party);
}

TEST("KJH: a Brock moved up by the badges gets a boss moveset for his new level, and a late boss's IVs")
{
    static const u8 levels[] = {40, 40};
    FlagSet(FLAG_KJH_LEVELLESS);
    GivePlayerParty(levels, ARRAY_COUNT(levels));
    SetBadges(3);
    SetMap(MAP_PEWTER_CITY_GYM);
    struct Pokemon *party = CreateParty(&sBrock, TRAINER_LEADER_BROCK);
    struct Pokemon *onix = &party[1];
    enum Type type = GetMoveType(GetMonData(onix, MON_DATA_MOVE1));
    EXPECT_EQ(GetMonData(onix, MON_DATA_LEVEL), 40);
    // Slot 1: the best STAB attack.
    EXPECT(type == TYPE_ROCK || type == TYPE_GROUND);
    EXPECT_NE(GetMonData(onix, MON_DATA_MOVE1), MOVE_TACKLE);
    // Met that late, he is a late boss.
    EXPECT_EQ(GetMonData(onix, MON_DATA_HP_IV), MAX_PER_STAT_IVS);
    EXPECT_EQ(GetMonData(onix, MON_DATA_HELD_ITEM), ITEM_SITRUS_BERRY);
    Free(party);
}

TEST("KJH: outside a Gym, a Gym Leader keeps the data's levels")
{
    static const u8 levels[] = {14, 14};
    FlagSet(FLAG_KJH_LEVELLESS);
    GivePlayerParty(levels, ARRAY_COUNT(levels));
    SetBadges(3);
    SetMap(MAP_ROUTE3);
    struct Pokemon *party = CreateParty(&sBrock, TRAINER_LEADER_BROCK);
    EXPECT_EQ(GetMonData(&party[1], MON_DATA_LEVEL), 14);
    Free(party);
}

TEST("KJH: the first rival keeps the data's level and isn't a boss")
{
    static const u8 levels[] = {8};
    FlagSet(FLAG_KJH_LEVELLESS);
    GivePlayerParty(levels, ARRAY_COUNT(levels));
    SetBadges(0);
    struct Pokemon *party = CreateParty(&sOaksLabRival, TRAINER_RIVAL_OAKS_LAB_SQUIRTLE);
    EXPECT_EQ(GetMonData(&party[0], MON_DATA_LEVEL), 8);
    EXPECT_EQ(GetMonData(&party[0], MON_DATA_HP_IV), 0);
    EXPECT_EQ(GetMonData(&party[0], MON_DATA_ATK_EV), 0);
    Free(party);
}

TEST("KJH: bosses get the smart trainer AI, other trainers keep theirs and avoid useless moves")
{
    EXPECT_EQ(KJH_AiFlags(BROCK_AI, TRAINER_CLASS_LEADER_FRLG, TRAINER_LEADER_BROCK), BROCK_AI | KJH_BOSS_AI_FLAGS);
    EXPECT_EQ(KJH_AiFlags(BROCK_AI, TRAINER_CLASS_RIVAL_EARLY_FRLG, TRAINER_RIVAL_ROUTE22_EARLY_SQUIRTLE), BROCK_AI | KJH_BOSS_AI_FLAGS);
    EXPECT_EQ(KJH_AiFlags(BROCK_AI, TRAINER_CLASS_RIVAL_EARLY_FRLG, TRAINER_RIVAL_OAKS_LAB_SQUIRTLE), BROCK_AI);
    EXPECT_EQ(KJH_AiFlags(0, TRAINER_CLASS_YOUNGSTER_FRLG, TRAINER_YOUNGSTER_BEN), AI_FLAG_CHECK_BAD_MOVE);
    // the smart AI, but KJH's trainers don't Terastallize
    EXPECT_EQ(KJH_BOSS_AI_FLAGS & AI_FLAG_OMNISCIENT, AI_FLAG_OMNISCIENT);
    EXPECT_EQ(KJH_BOSS_AI_FLAGS & AI_FLAG_SMART_SWITCHING, AI_FLAG_SMART_SWITCHING);
    EXPECT_EQ(KJH_BOSS_AI_FLAGS & AI_FLAG_SMART_TERA, 0);
}

TEST("KJH: a party built without a trainer id (partners, debug test parties) keeps its data as it is")
{
    static const u8 levels[] = {50, 50};
    GivePlayerParty(levels, ARRAY_COUNT(levels));
    SetBadges(8);
    struct Pokemon *party = AllocZeroed(PARTY_SIZE * sizeof(struct Pokemon));
    CreateNPCTrainerPartyFromTrainer(party, &sBrock);
    EXPECT_EQ(GetMonData(&party[1], MON_DATA_LEVEL), 14);
    EXPECT_EQ(GetMonData(&party[1], MON_DATA_HP_IV), 0);
    EXPECT_EQ(GetMonData(&party[1], MON_DATA_ATK_EV), 0);
    EXPECT_EQ(GetMonData(&party[1], MON_DATA_MOVE1), MOVE_TACKLE);
    Free(party);
}
