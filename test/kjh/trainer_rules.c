// KJH: trainer levels and boss rules (src/kjh_progression.c) on Brock and the first rival, with the numbers of
// docs/TRAINER_LEVELS.md in the KJH repo. The test build has its own trainer table, so Brock and the rival are
// copied here from src/data/trainers_frlg.party.
#include "global.h"
#include "battle.h"
#include "battle_setup.h"
#include "data.h"
#include "event_data.h"
#include "kjh_progression.h"
#include "malloc.h"
#include "move.h"
#include "pokemon.h"
#include "test/test.h"
#include "constants/battle_ai.h"
#include "constants/items.h"
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

static const struct TrainerMon sRivalParty[] =
{
    {
        .species = SPECIES_SQUIRTLE,
        .gender = TRAINER_MON_RANDOM_GENDER,
        .iv = TRAINER_PARTY_IVS(0, 0, 0, 0, 0, 0),
        .lvl = 5,
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

static struct Pokemon *CreateParty(const struct Trainer *trainer, u16 trainerNum)
{
    struct Pokemon *party = AllocZeroed(PARTY_SIZE * sizeof(struct Pokemon));
    CreateOpponentTrainerParty(party, trainer, trainerNum);
    return party;
}

TEST("KJH: Brock keeps FireRed's levels against a weaker party")
{
    static const u8 levels[] = {8, 6};
    GivePlayerParty(levels, ARRAY_COUNT(levels));
    SetBadges(0);
    struct Pokemon *party = CreateParty(&sBrock, TRAINER_LEADER_BROCK);
    EXPECT_EQ(GetMonData(&party[0], MON_DATA_LEVEL), 12);
    EXPECT_EQ(GetMonData(&party[1], MON_DATA_LEVEL), 14);
    Free(party);
}

TEST("KJH: Brock catches up with a strong party, his ace 1 under it before 3 badges")
{
    u32 partyLevel = 0, geodude = 0, onix = 0;
    PARAMETRIZE { partyLevel = 22; geodude = 19; onix = 21; }
    PARAMETRIZE { partyLevel = 50; geodude = 47; onix = 49; }
    u8 levels[] = {partyLevel, partyLevel, 5};
    GivePlayerParty(levels, ARRAY_COUNT(levels));
    SetBadges(0);
    struct Pokemon *party = CreateParty(&sBrock, TRAINER_LEADER_BROCK);
    EXPECT_EQ(GetMonData(&party[0], MON_DATA_LEVEL), geodude);
    EXPECT_EQ(GetMonData(&party[1], MON_DATA_LEVEL), onix);
    Free(party);
}

TEST("KJH: Brock's ace matches the party from 3 badges and goes 1 above it from 6")
{
    u32 badges = 0, onix = 0;
    PARAMETRIZE { badges = 3; onix = 30; }
    PARAMETRIZE { badges = 6; onix = 31; }
    static const u8 levels[] = {30, 30};
    GivePlayerParty(levels, ARRAY_COUNT(levels));
    SetBadges(badges);
    struct Pokemon *party = CreateParty(&sBrock, TRAINER_LEADER_BROCK);
    EXPECT_EQ(GetMonData(&party[1], MON_DATA_LEVEL), onix);
    Free(party);
}

TEST("KJH: Brock gets boss IVs, EVs growing with badges and a nature for his moves")
{
    u32 badges = 0, evs = 0;
    PARAMETRIZE { badges = 0; evs = 28; }
    PARAMETRIZE { badges = 8; evs = 252; }
    static const u8 levels[] = {8, 6};
    GivePlayerParty(levels, ARRAY_COUNT(levels));
    SetBadges(badges);
    struct Pokemon *party = CreateParty(&sBrock, TRAINER_LEADER_BROCK);
    struct Pokemon *onix = &party[1];
    // early Kanto boss (below Lv 25): IVs 20, no Sitrus Berry, FireRed's moves
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

TEST("KJH: a Brock raised to the party gets a boss moveset for his new level, still with early IVs")
{
    static const u8 levels[] = {50, 50};
    GivePlayerParty(levels, ARRAY_COUNT(levels));
    SetBadges(0);
    struct Pokemon *party = CreateParty(&sBrock, TRAINER_LEADER_BROCK);
    struct Pokemon *onix = &party[1];
    enum Type type = GetMoveType(GetMonData(onix, MON_DATA_MOVE1));
    EXPECT_EQ(GetMonData(onix, MON_DATA_LEVEL), 49);
    // slot 1: the best STAB attack
    EXPECT(type == TYPE_ROCK || type == TYPE_GROUND);
    EXPECT_NE(GetMonData(onix, MON_DATA_MOVE1), MOVE_TACKLE);
    // Brock's own levels still make him an early boss
    EXPECT_EQ(GetMonData(onix, MON_DATA_HP_IV), 20);
    EXPECT_EQ(GetMonData(onix, MON_DATA_HELD_ITEM), ITEM_NONE);
    Free(party);
}

TEST("KJH: the first rival matches your best Pokemon and isn't a boss")
{
    static const u8 levels[] = {7};
    GivePlayerParty(levels, ARRAY_COUNT(levels));
    SetBadges(0);
    struct Pokemon *party = CreateParty(&sOaksLabRival, TRAINER_RIVAL_OAKS_LAB_SQUIRTLE);
    EXPECT_EQ(GetMonData(&party[0], MON_DATA_LEVEL), 7);
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
