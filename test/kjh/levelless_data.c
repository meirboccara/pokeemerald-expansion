// KJH: the levels-free data each Pokémon carries (LV-1): its peak level, its Training bank and half point, its peak
// Bond and its tier mark. Nothing reads them yet; these tests check that each value is kept at its limits, on party
// and boxed Pokémon, and through the PC. Where the bits live: LEVELLESS_DESIGN.md, "Where the bits live".
#include "global.h"
#include "event_data.h"
#include "kjh_levelless.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "test/test.h"

static void SetMonValue(struct Pokemon *mon, s32 field, u32 value)
{
    SetMonData(mon, field, &value);
}

static void SetBoxMonValue(struct BoxPokemon *boxMon, s32 field, u32 value)
{
    SetBoxMonData(boxMon, field, &value);
}

static void CreatePikachu(struct Pokemon *mon)
{
    CreateMon(mon, SPECIES_PIKACHU, 12, 0, OTID_STRUCT_PRESET(0));
}

TEST("KJH: a new Pokémon has no levels-free data yet")
{
    struct Pokemon mon;
    CreatePikachu(&mon);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_PEAK_LEVEL), 0);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_TRAINING_BANK), 0);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_TRAINING_HALF), 0);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_PEAK_BOND), 0);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_TIER_MARK), KJH_TIER_REGULAR);
}

TEST("KJH: a Pokémon keeps its peak level, up to 100")
{
    struct Pokemon mon;
    CreatePikachu(&mon);
    SetMonValue(&mon, MON_DATA_PEAK_LEVEL, 1);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_PEAK_LEVEL), 1);
    SetMonValue(&mon, MON_DATA_PEAK_LEVEL, 100);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_PEAK_LEVEL), 100);
    SetMonValue(&mon, MON_DATA_PEAK_LEVEL, 127); // The field's own maximum.
    EXPECT_EQ(GetMonData(&mon, MON_DATA_PEAK_LEVEL), KJH_PEAK_LEVEL_MAX);
}

TEST("KJH: a Pokémon keeps its Training bank, up to 630, and its half point")
{
    struct Pokemon mon;
    CreatePikachu(&mon);
    SetMonValue(&mon, MON_DATA_TRAINING_BANK, 630);
    SetMonValue(&mon, MON_DATA_TRAINING_HALF, 1);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_TRAINING_BANK), 630);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_TRAINING_HALF), 1);
    SetMonValue(&mon, MON_DATA_TRAINING_BANK, KJH_TRAINING_BANK_MAX + 1);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_TRAINING_BANK), KJH_TRAINING_BANK_MAX);
    SetMonValue(&mon, MON_DATA_TRAINING_BANK, 1023); // The field's own maximum.
    EXPECT_EQ(GetMonData(&mon, MON_DATA_TRAINING_BANK), KJH_TRAINING_BANK_MAX);
    SetMonValue(&mon, MON_DATA_TRAINING_BANK, 257); // More than a byte.
    EXPECT_EQ(GetMonData(&mon, MON_DATA_TRAINING_BANK), 257);
    SetMonValue(&mon, MON_DATA_TRAINING_HALF, 0);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_TRAINING_HALF), 0);
}

TEST("KJH: a Pokémon keeps its peak Bond, up to 20")
{
    struct Pokemon mon;
    CreatePikachu(&mon);
    SetMonValue(&mon, MON_DATA_PEAK_BOND, 1);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_PEAK_BOND), 1);
    SetMonValue(&mon, MON_DATA_PEAK_BOND, 20);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_PEAK_BOND), 20);
    SetMonValue(&mon, MON_DATA_PEAK_BOND, 31); // The field's own maximum.
    EXPECT_EQ(GetMonData(&mon, MON_DATA_PEAK_BOND), KJH_BOND_MAX);
}

TEST("KJH: a Pokémon keeps its tier mark")
{
    struct Pokemon mon;
    CreatePikachu(&mon);
    SetMonValue(&mon, MON_DATA_TIER_MARK, KJH_TIER_LEADER);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_TIER_MARK), KJH_TIER_LEADER);
    SetMonValue(&mon, MON_DATA_TIER_MARK, KJH_TIER_ALPHA);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_TIER_MARK), KJH_TIER_ALPHA);
    SetMonValue(&mon, MON_DATA_TIER_MARK, KJH_TIER_REGULAR);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_TIER_MARK), KJH_TIER_REGULAR);
}

TEST("KJH: the levels-free values don't overwrite each other or the rest of the Pokémon")
{
    struct Pokemon mon;
    CreatePikachu(&mon);
    SetMonValue(&mon, MON_DATA_SPDEF_EV, 252);
    SetMonValue(&mon, MON_DATA_TOUGH, 7);
    SetMonValue(&mon, MON_DATA_SHEEN, 9);
    SetMonValue(&mon, MON_DATA_PEAK_LEVEL, 100);
    SetMonValue(&mon, MON_DATA_PEAK_BOND, 20);
    SetMonValue(&mon, MON_DATA_TIER_MARK, KJH_TIER_ALPHA);
    SetMonValue(&mon, MON_DATA_TRAINING_HALF, 1);
    SetMonValue(&mon, MON_DATA_TRAINING_BANK, 630);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_PEAK_LEVEL), 100);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_PEAK_BOND), 20);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_TIER_MARK), KJH_TIER_ALPHA);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_TRAINING_HALF), 1);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_TRAINING_BANK), 630);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_SPDEF_EV), 252);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_TOUGH), 7);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_SHEEN), 9);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_SPECIES), SPECIES_PIKACHU);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_LEVEL), 12);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_SANITY_IS_BAD_EGG), FALSE);
}

TEST("KJH: contest stats (as FireRed's in-game trades write them) don't reach the levels-free data")
{
    struct Pokemon mon;
    CreatePikachu(&mon);
    SetMonValue(&mon, MON_DATA_PEAK_LEVEL, 100);
    SetMonValue(&mon, MON_DATA_TRAINING_BANK, 630);
    SetMonValue(&mon, MON_DATA_COOL, 30);
    SetMonValue(&mon, MON_DATA_BEAUTY, 5);
    SetMonValue(&mon, MON_DATA_CUTE, 5);
    SetMonValue(&mon, MON_DATA_SMART, 5);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_COOL), 0);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_BEAUTY), 0);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_CUTE), 0);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_SMART), 0);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_PEAK_LEVEL), 100);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_TRAINING_BANK), 630);
}

TEST("KJH: a boxed Pokémon keeps its levels-free values")
{
    struct BoxPokemon boxMon;
    CreateBoxMon(&boxMon, SPECIES_PIKACHU, 12, 0, OTID_STRUCT_PRESET(0));
    SetBoxMonValue(&boxMon, MON_DATA_PEAK_LEVEL, 100);
    SetBoxMonValue(&boxMon, MON_DATA_TRAINING_BANK, 630);
    SetBoxMonValue(&boxMon, MON_DATA_TRAINING_HALF, 1);
    SetBoxMonValue(&boxMon, MON_DATA_PEAK_BOND, 20);
    SetBoxMonValue(&boxMon, MON_DATA_TIER_MARK, KJH_TIER_LEADER);
    EXPECT_EQ(GetBoxMonData(&boxMon, MON_DATA_PEAK_LEVEL), 100);
    EXPECT_EQ(GetBoxMonData(&boxMon, MON_DATA_TRAINING_BANK), 630);
    EXPECT_EQ(GetBoxMonData(&boxMon, MON_DATA_TRAINING_HALF), 1);
    EXPECT_EQ(GetBoxMonData(&boxMon, MON_DATA_PEAK_BOND), 20);
    EXPECT_EQ(GetBoxMonData(&boxMon, MON_DATA_TIER_MARK), KJH_TIER_LEADER);
}

TEST("KJH: a Pokémon put in the PC and taken out keeps its levels-free values")
{
    struct Pokemon mon, back;
    CreatePikachu(&mon);
    SetMonValue(&mon, MON_DATA_PEAK_LEVEL, 54);
    SetMonValue(&mon, MON_DATA_TRAINING_BANK, 333);
    SetMonValue(&mon, MON_DATA_TRAINING_HALF, 1);
    SetMonValue(&mon, MON_DATA_PEAK_BOND, 17);
    SetMonValue(&mon, MON_DATA_TIER_MARK, KJH_TIER_ALPHA);
    ASSUME(CopyMonToPC(&mon) == MON_GIVEN_TO_PC);
    BoxMonToMon(GetBoxedMonPtr(gSpecialVar_MonBoxId, gSpecialVar_MonBoxPos), &back);
    EXPECT_EQ(GetMonData(&back, MON_DATA_SPECIES), SPECIES_PIKACHU);
    EXPECT_EQ(GetMonData(&back, MON_DATA_PEAK_LEVEL), 54);
    EXPECT_EQ(GetMonData(&back, MON_DATA_TRAINING_BANK), 333);
    EXPECT_EQ(GetMonData(&back, MON_DATA_TRAINING_HALF), 1);
    EXPECT_EQ(GetMonData(&back, MON_DATA_PEAK_BOND), 17);
    EXPECT_EQ(GetMonData(&back, MON_DATA_TIER_MARK), KJH_TIER_ALPHA);
}
