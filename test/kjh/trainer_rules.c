// KJH: trainer levels and boss rules (src/kjh_progression.c) on Brock, Misty and the first rival. Their levels are
// the data's, which kjh_tools/zone_levels.py set from the zones (LV-3); a Gym Leader's team follows the badges in
// the levels-free game. The test build has its own trainer table, so they are copied here from
// src/data/trainers_frlg.party.
#include "global.h"
#include "battle.h"
#include "battle_setup.h"
#include "data.h"
#include "event_data.h"
#include "kjh_bond.h"
#include "kjh_boss_rules.h"
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

static const struct TrainerMon sOneMonParty[] =
{
    {
        .species = SPECIES_RATTATA,
        .gender = TRAINER_MON_RANDOM_GENDER,
        .iv = TRAINER_PARTY_IVS(0, 0, 0, 0, 0, 0),
        .lvl = 18,
        .ball = POKEBALL_COUNT,
        .nature = NATURE_HARDY,
        .dynamaxLevel = MAX_DYNAMAX_LEVEL,
    },
};

static const struct Trainer sYoungster =
{
    .trainerName = _("BEN"),
    .trainerClass = TRAINER_CLASS_YOUNGSTER_FRLG,
    .party = sOneMonParty,
    .partySize = ARRAY_COUNT(sOneMonParty),
};

static const struct Trainer sSsAnneRival =
{
    .trainerName = _("TERRY"),
    .trainerClass = TRAINER_CLASS_RIVAL_EARLY_FRLG,
    .aiFlags = BROCK_AI,
    .party = sOneMonParty,
    .partySize = ARRAY_COUNT(sOneMonParty),
};

static const struct TrainerMon sChampionParty[] =
{
    {
        .species = SPECIES_PIDGEOT,
        .gender = TRAINER_MON_RANDOM_GENDER,
        .iv = TRAINER_PARTY_IVS(0, 0, 0, 0, 0, 0),
        .lvl = 96,
        .ball = POKEBALL_COUNT,
        .nature = NATURE_HARDY,
        .dynamaxLevel = MAX_DYNAMAX_LEVEL,
    },
    {
        .species = SPECIES_BLASTOISE,
        .gender = TRAINER_MON_RANDOM_GENDER,
        .iv = TRAINER_PARTY_IVS(0, 0, 0, 0, 0, 0),
        .lvl = 100,
        .ball = POKEBALL_COUNT,
        .nature = NATURE_HARDY,
        .dynamaxLevel = MAX_DYNAMAX_LEVEL,
    },
};

static const struct Trainer sChampion =
{
    .trainerName = _("TERRY"),
    .trainerClass = TRAINER_CLASS_CHAMPION_FRLG,
    .aiFlags = BROCK_AI,
    .party = sChampionParty,
    .partySize = ARRAY_COUNT(sChampionParty),
};

static u32 TotalEvs(struct Pokemon *mon)
{
    u32 total = 0;
    for (u32 i = 0; i < NUM_STATS; i++)
        total += GetMonData(mon, MON_DATA_HP_EV + i);

    return total;
}

static u32 GetBond(struct Pokemon *mon)
{
    return KJH_FriendshipToBond(GetMonData(mon, MON_DATA_FRIENDSHIP));
}

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
    // Met that late, he is a late boss (a Sitrus Berry), trained as the 4th Gym's ace (LV-16).
    EXPECT_EQ(GetMonData(onix, MON_DATA_HP_IV), 24);
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

TEST("KJH: the trainer tables follow LEVELLESS_DESIGN.md's Gym table")
{
    static const u8 leaderIvs[] = {14, 16, 18, 20, 22, 24, 26, 28}, aceIvs[] = {18, 20, 22, 24, 26, 28, 30, 31};
    static const u16 leaderEvs[] = {64, 128, 192, 256, 320, 384, 448, 510};
    static const u16 aceEvs[] = {192, 256, 320, 384, 448, 510, 510, 510};
    for (u32 gym = 1; gym <= 8; gym++)
    {
        struct KjhTraining leader = KJH_TrainerTraining(KJH_GROUP_GYM_LEADER, gym, FALSE);
        struct KjhTraining ace = KJH_TrainerTraining(KJH_GROUP_GYM_LEADER, gym, TRUE);
        struct KjhTraining trainer = KJH_TrainerTraining(KJH_GROUP_GYM_TRAINER, gym, FALSE);
        EXPECT_EQ(leader.iv, leaderIvs[gym - 1]);
        EXPECT_EQ(leader.evs, leaderEvs[gym - 1]);
        EXPECT_EQ(leader.bond, 12);
        EXPECT_EQ(ace.iv, aceIvs[gym - 1]);
        EXPECT_EQ(ace.evs, aceEvs[gym - 1]);
        EXPECT_EQ(ace.bond, 20);
        EXPECT_EQ(trainer.iv, leaderIvs[gym - 1] - 6);
        EXPECT_EQ(trainer.evs, leaderEvs[gym - 1] / 2);
        EXPECT_EQ(trainer.bond, 8);
    }
    EXPECT_EQ(KJH_TrainerTraining(KJH_GROUP_ROUTE, 3, FALSE).iv, 8);
    EXPECT_EQ(KJH_TrainerTraining(KJH_GROUP_ROUTE, 3, FALSE).evs, 0);
    EXPECT_EQ(KJH_TrainerTraining(KJH_GROUP_LEAGUE, 0, FALSE).evs, 510);
}

TEST("KJH: 510 EVs go 252 in the attack stat, 252 in the best other stat and 6 in a third")
{
    static const u8 baseStats[NUM_STATS] = {79, 83, 100, 78, 85, 105}; // Blastoise: HP, Atk, Def, Spe, SpA, SpD
    u8 evs[NUM_STATS];
    KJH_TrainingEvs(baseStats, 0, 110, 510, evs);
    EXPECT_EQ(evs[STAT_SPATK], 252);
    EXPECT_EQ(evs[STAT_SPDEF], 252);
    EXPECT_EQ(evs[STAT_HP], 6);
    EXPECT_EQ(evs[STAT_ATK], 0);
}

TEST("KJH: Brock's team is trained as the 1st Gym's: IVs 14 and 18, EVs 64 and 192, Bond 12 and 20")
{
    static const u8 levels[] = {14, 14};
    FlagSet(FLAG_KJH_LEVELLESS);
    GivePlayerParty(levels, ARRAY_COUNT(levels));
    SetBadges(0);
    SetMap(MAP_PEWTER_CITY_GYM);
    struct Pokemon *party = CreateParty(&sBrock, TRAINER_LEADER_BROCK);
    struct Pokemon untrained;
    CreateMon(&untrained, SPECIES_ONIX, 14, 0, OTID_STRUCT_PRESET(0));
    for (u32 i = 0; i < NUM_STATS; i++)
    {
        EXPECT_EQ(GetMonData(&party[0], MON_DATA_HP_IV + i), 14);
        EXPECT_EQ(GetMonData(&party[1], MON_DATA_HP_IV + i), 18);
    }
    EXPECT_EQ(TotalEvs(&party[0]), 64);
    EXPECT_EQ(TotalEvs(&party[1]), 192);
    EXPECT_EQ(GetBond(&party[0]), 12);
    EXPECT_EQ(GetBond(&party[1]), 20);
    // Onix's stats show it: its Attack and Defense (where its EVs went) beat an untrained Onix's.
    EXPECT_GT(GetMonData(&party[1], MON_DATA_ATK), GetMonData(&untrained, MON_DATA_ATK));
    EXPECT_GT(GetMonData(&party[1], MON_DATA_DEF), GetMonData(&untrained, MON_DATA_DEF));
    Free(party);
}

TEST("KJH: the Champion's team is maxed: IVs 31, EVs 510, Bond 20")
{
    static const u8 levels[] = {100};
    FlagSet(FLAG_KJH_LEVELLESS);
    GivePlayerParty(levels, ARRAY_COUNT(levels));
    SetBadges(8);
    SetMap(MAP_POKEMON_LEAGUE_CHAMPIONS_ROOM);
    struct Pokemon *party = CreateParty(&sChampion, TRAINER_CHAMPION_FIRST_SQUIRTLE);
    struct Pokemon untrained;
    CreateMon(&untrained, SPECIES_BLASTOISE, 100, 0, OTID_STRUCT_PRESET(0));
    for (u32 k = 0; k < 2; k++)
    {
        for (u32 i = 0; i < NUM_STATS; i++)
            EXPECT_EQ(GetMonData(&party[k], MON_DATA_HP_IV + i), 31);
        EXPECT_EQ(TotalEvs(&party[k]), 510);
        EXPECT_EQ(GetBond(&party[k]), 20);
    }
    EXPECT_GT(GetMonData(&party[1], MON_DATA_MAX_HP), GetMonData(&untrained, MON_DATA_MAX_HP));
    Free(party);
}

TEST("KJH: a route trainer has IVs 5 + badges, no EVs, Bond 5; in a Gym, the Gym trainers' row")
{
    static const u8 levels[] = {18};
    FlagSet(FLAG_KJH_LEVELLESS);
    GivePlayerParty(levels, ARRAY_COUNT(levels));
    SetBadges(2);
    SetMap(MAP_ROUTE3);
    struct Pokemon *party = CreateParty(&sYoungster, TRAINER_YOUNGSTER_BEN);
    EXPECT_EQ(GetMonData(&party[0], MON_DATA_ATK_IV), 7);
    EXPECT_EQ(TotalEvs(&party[0]), 0);
    EXPECT_EQ(GetBond(&party[0]), 5);
    Free(party);
    SetMap(MAP_CERULEAN_CITY_GYM); // 2 badges: the 3rd Gym of the run
    party = CreateParty(&sYoungster, TRAINER_YOUNGSTER_BEN);
    EXPECT_EQ(GetMonData(&party[0], MON_DATA_ATK_IV), 12);
    EXPECT_EQ(TotalEvs(&party[0]), 96);
    EXPECT_EQ(GetBond(&party[0]), 8);
    Free(party);
}

TEST("KJH: the rival grows with each battle: on the S.S. Anne IVs 18, EVs 192, Bond 12")
{
    static const u8 levels[] = {26};
    FlagSet(FLAG_KJH_LEVELLESS);
    GivePlayerParty(levels, ARRAY_COUNT(levels));
    SetBadges(2);
    SetMap(MAP_ROUTE3);
    struct Pokemon *party = CreateParty(&sSsAnneRival, TRAINER_RIVAL_SS_ANNE_SQUIRTLE);
    EXPECT_EQ(GetMonData(&party[0], MON_DATA_SPEED_IV), 18);
    EXPECT_EQ(TotalEvs(&party[0]), 192);
    EXPECT_EQ(GetBond(&party[0]), 12);
    Free(party);
}

TEST("KJH: Hoenn's rival grows with each of Emerald's battles: on Route 119, the 4th, IVs 18, EVs 192, Bond 12")
{
    static const u8 levels[] = {56};
    FlagSet(FLAG_KJH_LEVELLESS);
    GivePlayerParty(levels, ARRAY_COUNT(levels));
    SetMap(MAP_ROUTE119);
    struct Pokemon *party = CreateParty(&sSsAnneRival, TRAINER_MAY_ROUTE_119_TREECKO);
    EXPECT_EQ(GetMonData(&party[0], MON_DATA_SPEED_IV), 18);
    EXPECT_EQ(TotalEvs(&party[0]), 192);
    EXPECT_EQ(GetBond(&party[0]), 12);
    Free(party);
}
