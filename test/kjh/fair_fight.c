// KJH (LV-17): fair fights (src/kjh_fair_fight.c): pick as many Pokemon as the Gym Leader has.
#include "global.h"
#include "battle_setup.h"
#include "event_data.h"
#include "kjh_fair_fight.h"
#include "party_menu.h"
#include "pokemon.h"
#include "script_pokemon_util.h"
#include "test/overworld_script.h"
#include "test/test.h"
#include "constants/opponents.h"

static void GiveParty(u32 count)
{
    static const u16 sSpecies[] = {SPECIES_PIKACHU, SPECIES_BULBASAUR, SPECIES_CHARMANDER, SPECIES_SQUIRTLE,
                                   SPECIES_PIDGEY, SPECIES_RATTATA};
    ZeroPlayerPartyMons();
    for (u32 i = 0; i < count; i++)
        ScriptGiveMon(sSpecies[i], 10, ITEM_NONE);
}

TEST("KJH: before Brock, a party with more healthy Pokemon than his picks as many as he has")
{
    u32 brock = GetTrainerPartySizeFromId(TRAINER_LEADER_BROCK), hp = 0;

    ASSUME(brock < 4);
    ClearTrainerFlag(TRAINER_LEADER_BROCK);
    gSpecialVar_0x8004 = TRAINER_LEADER_BROCK;
    GiveParty(brock + 1);
    EXPECT_EQ(KJH_FairFightCount(), brock);
    SetMonData(&gPlayerParty[0], MON_DATA_HP, &hp); // a fainted one doesn't count
    EXPECT_EQ(KJH_FairFightCount(), 0);              // fewer healthy than needed: no choice
    GiveParty(brock);
    EXPECT_EQ(KJH_FairFightCount(), 0);
    GiveParty(6);
    SetTrainerFlag(TRAINER_LEADER_BROCK);           // beaten: no battle, no choice
    EXPECT_EQ(KJH_FairFightCount(), 0);
    ClearTrainerFlag(TRAINER_LEADER_BROCK);
}

TEST("KJH: no choice before a trainer who isn't a Gym Leader")
{
    GiveParty(6);
    gSpecialVar_0x8004 = TRAINER_ELITE_FOUR_LORELEI;
    EXPECT_EQ(KJH_FairFightCount(), 0);
    gSpecialVar_0x8004 = TRAINER_YOUNGSTER_BEN;
    EXPECT_EQ(KJH_FairFightCount(), 0);
}

TEST("KJH: the chosen Pokemon fight, the others wait and come back in their places, the fighters' changes kept")
{
    u32 hp = 1;

    GiveParty(4); // Pikachu, Bulbasaur, Charmander, Squirtle
    memset(gSelectedOrderFromParty, 0, sizeof(gSelectedOrderFromParty));
    gSelectedOrderFromParty[0] = 3; // Charmander first
    gSelectedOrderFromParty[1] = 1; // then Pikachu
    KJH_ApplyFairFightParty();
    EXPECT(KJH_IsFairFightActive());
    EXPECT_EQ(gPlayerPartyCount, 2);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPECIES), SPECIES_CHARMANDER);
    EXPECT_EQ(GetMonData(&gPlayerParty[1], MON_DATA_SPECIES), SPECIES_PIKACHU);
    EXPECT_EQ(GetMonData(&gPlayerParty[2], MON_DATA_SPECIES), SPECIES_NONE);
    SetMonData(&gPlayerParty[0], MON_DATA_HP, &hp); // the battle

    KJH_RestoreFairFightParty();
    EXPECT(!KJH_IsFairFightActive());
    EXPECT_EQ(gPlayerPartyCount, 4);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPECIES), SPECIES_PIKACHU);
    EXPECT_EQ(GetMonData(&gPlayerParty[1], MON_DATA_SPECIES), SPECIES_BULBASAUR);
    EXPECT_EQ(GetMonData(&gPlayerParty[2], MON_DATA_SPECIES), SPECIES_CHARMANDER);
    EXPECT_EQ(GetMonData(&gPlayerParty[2], MON_DATA_HP), 1);
    EXPECT_EQ(GetMonData(&gPlayerParty[3], MON_DATA_SPECIES), SPECIES_SQUIRTLE);
    KJH_RestoreFairFightParty(); // nothing to restore twice
    EXPECT_EQ(gPlayerPartyCount, 4);
}
