// KJH: one training point for a voluntary Center heal, once per town per in-game day,
// when a Pokemon is below half HP (src/kjh_training.c).
#include "global.h"
#include "clock.h"
#include "kjh_training.h"
#include "pokemon.h"
#include "test/test.h"

static void Create(struct Pokemon *mon)
{
    CreateMon(mon, SPECIES_BULBASAUR, 20, 0, OTID_STRUCT_PRESET(0));
}

static void SetHp(struct Pokemon *mon, u32 hp, u32 maxHp)
{
    SetMonData(mon, MON_DATA_MAX_HP, &maxHp);
    SetMonData(mon, MON_DATA_HP, &hp);
}

TEST("KJH: a Center gives one training point for a Pokemon below half HP, once per town per day")
{
    struct Pokemon *party = gParties[B_TRAINER_PLAYER];
    u16 mapsec = gMapHeader.regionMapSectionId;

    ZeroPlayerPartyMons();
    Create(&party[0]);
    SetHp(&party[0], 10, 20); // exactly half does not qualify
    gMapHeader.regionMapSectionId = MAPSEC_VIRIDIAN_CITY;
    KJH_ClearCenterCare();
    EXPECT(!KJH_GrantCenterCarePoint());
    EXPECT_EQ(GetMonData(&party[0], MON_DATA_TRAINING_BANK), 0);

    SetHp(&party[0], 9, 20);
    EXPECT(KJH_GrantCenterCarePoint());
    EXPECT_EQ(GetMonData(&party[0], MON_DATA_TRAINING_BANK), 1);
    EXPECT_EQ(GetMonData(&party[0], MON_DATA_TRAINING_LIFETIME_HALVES), 2);
    EXPECT(!KJH_GrantCenterCarePoint());
    EXPECT_EQ(GetMonData(&party[0], MON_DATA_TRAINING_BANK), 1);

    gMapHeader.regionMapSectionId = MAPSEC_PEWTER_CITY;
    EXPECT(KJH_GrantCenterCarePoint());
    EXPECT_EQ(GetMonData(&party[0], MON_DATA_TRAINING_BANK), 2);

    DoDailyEvents(1);
    gMapHeader.regionMapSectionId = MAPSEC_VIRIDIAN_CITY;
    EXPECT(KJH_GrantCenterCarePoint());
    EXPECT_EQ(GetMonData(&party[0], MON_DATA_TRAINING_BANK), 3);

    gMapHeader.regionMapSectionId = MAPSEC_COUNT; // not a town: do not index the bitset
    EXPECT(!KJH_GrantCenterCarePoint());
    EXPECT_EQ(GetMonData(&party[0], MON_DATA_TRAINING_BANK), 3);

    gMapHeader.regionMapSectionId = mapsec;
}

TEST("KJH: the Center point goes to the first Pokemon below half HP, skipping an egg")
{
    struct Pokemon *party = gParties[B_TRAINER_PLAYER];
    u16 mapsec = gMapHeader.regionMapSectionId;
    u32 egg = TRUE;

    ZeroPlayerPartyMons();
    Create(&party[0]);
    SetHp(&party[0], 20, 20);
    Create(&party[1]);
    SetHp(&party[1], 0, 20);
    SetMonData(&party[1], MON_DATA_IS_EGG, &egg);
    Create(&party[2]);
    SetHp(&party[2], 0, 22); // fainted is below half
    gMapHeader.regionMapSectionId = MAPSEC_PALLET_TOWN;
    KJH_ClearCenterCare();
    EXPECT(KJH_GrantCenterCarePoint());
    EXPECT_EQ(GetMonData(&party[0], MON_DATA_TRAINING_BANK), 0);
    EXPECT_EQ(GetMonData(&party[1], MON_DATA_TRAINING_BANK), 0);
    EXPECT_EQ(GetMonData(&party[2], MON_DATA_TRAINING_BANK), 1);
    gMapHeader.regionMapSectionId = mapsec;
}
