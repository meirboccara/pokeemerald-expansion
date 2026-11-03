// KJH (ENG-10, Hoenn): Emerald's story in the FireRed build (src/kjh_hoenn_story.c). Birch's bag holds Hoenn's
// starters, and his choice is Hoenn's own: Oak's (VAR_STARTER_MON) still picks Kanto's rival and Mega Stone. The Hoenn
// League's Hall of Fame makes the player Hoenn Champion, not Kanto's again, and keeps the earlier Leagues' records.
#include "global.h"
#include "bg.h"
#include "event_data.h"
#include "kjh_hoenn_story.h"
#include "kjh_swarms.h"
#include "overworld.h"
#include "pokemon.h"
#include "test/test.h"
#include "constants/heal_locations.h"
#include "constants/map_groups.h"

#if IS_FRLG

bool8 IsStarterInParty(void); // src/field_specials.c, a special

TEST("KJH: Hoenn story: Birch's bag holds Hoenn's starters")
{
    EXPECT_EQ(KJH_HoennStarterSpecies(0), SPECIES_TREECKO);
    EXPECT_EQ(KJH_HoennStarterSpecies(1), SPECIES_TORCHIC);
    EXPECT_EQ(KJH_HoennStarterSpecies(2), SPECIES_MUDKIP);
}

TEST("KJH: Hoenn story: Birch's starter is Hoenn's own choice; Oak's stays")
{
    u16 oaks = VarGet(VAR_STARTER_MON);
    VarSet(VAR_STARTER_MON, 2); // Charmander's rival and Mega Stone in Kanto
    EXPECT_EQ(KJH_ChooseHoennStarter(1), SPECIES_TORCHIC);
    EXPECT_EQ(VarGet(VAR_KJH_HOENN_STARTER), 1);
    EXPECT_EQ(VarGet(VAR_STARTER_MON), 2);
    VarSet(VAR_STARTER_MON, oaks);
    VarSet(VAR_KJH_HOENN_STARTER, 0);
}

TEST("KJH: Hoenn story: Petalburg's nurse asks about Birch's starter, not Oak's")
{
    ZeroPlayerPartyMons();
    CreateMon(&gParties[B_TRAINER_PLAYER][0], SPECIES_MUDKIP, 5, 0, OTID_STRUCT_PRESET(0));
    VarSet(VAR_STARTER_MON, 0);      // Oak's Bulbasaur
    VarSet(VAR_KJH_HOENN_STARTER, 2); // Birch's Mudkip
    EXPECT(IsStarterInParty());
    VarSet(VAR_KJH_HOENN_STARTER, 0); // Treecko
    EXPECT(!IsStarterInParty());
    ZeroPlayerPartyMons();
}

TEST("KJH: Hoenn story: the Hoenn League's Hall of Fame makes the player Hoenn Champion and keeps the Kanto records")
{
    bool32 kanto = FlagGet(FLAG_SYS_GAME_CLEAR);
    FlagSet(FLAG_SYS_GAME_CLEAR);   // the Kanto League, long before
    FlagClear(FLAG_HOENN_GAME_CLEAR);
    EXPECT(KJH_HoennGameClear());   // earlier Hall of Fame records: kept
    EXPECT(FlagGet(FLAG_HOENN_GAME_CLEAR));
    EXPECT(FlagGet(FLAG_SYS_GAME_CLEAR));
    EXPECT(KJH_HoennGameClear());   // again: still kept
    FlagClear(FLAG_HOENN_GAME_CLEAR);
    if (!kanto)
        FlagClear(FLAG_SYS_GAME_CLEAR);
}

TEST("KJH: Hoenn story: after the Hoenn Hall of Fame, CONTINUE wakes the player at home in Littleroot")
{
    u8 gender = gSaveBlock2Ptr->playerGender;
    gSaveBlock2Ptr->playerGender = FEMALE;
    KJH_HoennGameClear();
    EXPECT_EQ(gSaveBlock1Ptr->continueGameWarp.mapGroup, MAP_GROUP(MAP_LITTLEROOT_TOWN_MAYS_HOUSE_2F));
    EXPECT_EQ(gSaveBlock1Ptr->continueGameWarp.mapNum, MAP_NUM(MAP_LITTLEROOT_TOWN_MAYS_HOUSE_2F));
    gSaveBlock2Ptr->playerGender = MALE;
    KJH_HoennGameClear();
    EXPECT_EQ(gSaveBlock1Ptr->continueGameWarp.mapNum, MAP_NUM(MAP_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F));
    gSaveBlock2Ptr->playerGender = gender;
    FlagClear(FLAG_HOENN_GAME_CLEAR);
}

TEST("KJH: Hoenn story: the S.S. AQUA's first landing makes Hoenn reached, and today has a Hoenn swarm")
{
    gSaveBlock3Ptr->kjhSwarms[KJH_SWARM_HOENN].species = SPECIES_NONE;
    FlagClear(FLAG_KJH_HOENN_ARRIVED);
    EXPECT(!FlagGet(KJH_HOENN_REACHED_FLAG));
    FlagSet(FLAG_KJH_HOENN_ARRIVED); // KJH_EventScript_FerryToHoenn
    EXPECT(FlagGet(KJH_HOENN_REACHED_FLAG)); // CF-6's swarms and ENG-8's radar page
    KJH_HoennArrived();               // the landing, before the truck
    EXPECT_NE(gSaveBlock3Ptr->kjhSwarms[KJH_SWARM_HOENN].species, SPECIES_NONE);
    KJH_StartDailySwarm();            // and the next day too
    EXPECT_NE(gSaveBlock3Ptr->kjhSwarms[KJH_SWARM_HOENN].species, SPECIES_NONE);
    FlagClear(FLAG_KJH_HOENN_ARRIVED);
    gSaveBlock3Ptr->kjhSwarms[KJH_SWARM_HOENN].species = SPECIES_NONE;
}

// FireRed's credits (after every League's Hall of Fame) set up their windows with the tile allocator on: marking a
// window's tiles returns 0, which is a success (the first free block is 1: the reset keeps tile 0)
TEST("KJH: Hoenn story: the credits' windows can mark and free their tiles")
{
    static const struct BgTemplate bg = {.bg = 0, .charBaseIndex = 0, .mapBaseIndex = 31, .priority = 0};
    ResetBgsAndClearDma3BusyFlags(1);
    InitBgsFromTemplates(0, &bg, 1);
    EXPECT_EQ(BgTileAllocOp(0, 0, 16, 0), 1);
    EXPECT_EQ(BgTileAllocOp(0, 8, 64, 1), 0);
    EXPECT_EQ(BgTileAllocOp(0, 8, 64, 2), 0);
    ResetBgsAndClearDma3BusyFlags(0);
}

#endif
