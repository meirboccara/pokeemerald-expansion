// KJH: Oak offers one nature change for the Kanto starter line (src/kjh_stat_trainer.c).
#include "global.h"
#include "event_data.h"
#include "kjh_stat_trainer.h"
#include "pokemon.h"
#include "test/test.h"
#include "constants/species.h"
#include "constants/vars.h"

static void Create(struct Pokemon *mon, u32 species)
{
    CreateMon(mon, species, 5, 0, OTID_STRUCT_PRESET(0));
}

TEST("KJH: Oak offers a nature change for the Kanto starter line, once, and only while it is in the party")
{
    struct Pokemon *party = gParties[B_TRAINER_PLAYER];
    u16 starter = VarGet(VAR_STARTER_MON);
    u32 egg = TRUE;

    ZeroPlayerPartyMons();
    FlagClear(FLAG_KJH_OAK_NATURE_OFFERED);
    VarSet(VAR_STARTER_MON, 2); // Charmander
    Create(&party[0], SPECIES_PIDGEY);
    Create(&party[2], SPECIES_CHARMANDER);
    EXPECT_EQ(KJH_OakNatureOfferSlot(), 2);
    EXPECT(!FlagGet(FLAG_KJH_OAK_NATURE_OFFERED));

    ZeroPlayerPartyMons();
    Create(&party[0], SPECIES_CHARIZARD);
    EXPECT_EQ(KJH_OakNatureOfferSlot(), 0);

    ZeroPlayerPartyMons();
    Create(&party[0], SPECIES_BULBASAUR);
    EXPECT_EQ(KJH_OakNatureOfferSlot(), PARTY_SIZE);
    EXPECT(!FlagGet(FLAG_KJH_OAK_NATURE_OFFERED));

    VarSet(VAR_STARTER_MON, 0); // Bulbasaur
    Create(&party[0], SPECIES_BULBASAUR);
    EXPECT_EQ(KJH_OakNatureOfferSlot(), 0);
    ZeroPlayerPartyMons();
    Create(&party[1], SPECIES_IVYSAUR);
    EXPECT_EQ(KJH_OakNatureOfferSlot(), 1);

    VarSet(VAR_STARTER_MON, 1); // Squirtle
    ZeroPlayerPartyMons();
    Create(&party[0], SPECIES_WARTORTLE);
    EXPECT_EQ(KJH_OakNatureOfferSlot(), 0);
    Create(&party[0], SPECIES_SQUIRTLE);
    SetMonData(&party[0], MON_DATA_IS_EGG, &egg);
    EXPECT_EQ(KJH_OakNatureOfferSlot(), PARTY_SIZE);

    VarSet(VAR_STARTER_MON, 2);
    ZeroPlayerPartyMons();
    Create(&party[0], SPECIES_CHARMANDER);
    FlagSet(FLAG_KJH_OAK_NATURE_OFFERED);
    EXPECT_EQ(KJH_OakNatureOfferSlot(), PARTY_SIZE);

    VarSet(VAR_STARTER_MON, 3);
    FlagClear(FLAG_KJH_OAK_NATURE_OFFERED);
    EXPECT_EQ(KJH_OakNatureOfferSlot(), PARTY_SIZE);

    VarSet(VAR_STARTER_MON, starter);
    FlagClear(FLAG_KJH_OAK_NATURE_OFFERED);
}
