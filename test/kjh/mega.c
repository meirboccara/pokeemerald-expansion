// KJH: Mega Evolution, levels-free (LV-19, src/kjh_mega.c): Bond 18, the bracelet by region, held back by the
// region's badges, the BOND page's Mega line and bosses' aces.
#include "global.h"
#include "event_data.h"
#include "item.h"
#include "kjh_bond.h"
#include "kjh_mega.h"
#include "kjh_pack.h"
#include "kjh_power_cap.h"
#include "pokemon.h"
#include "script.h"
#include "string_util.h"
#include "tv.h"
#include "test/battle.h"
#include "test/overworld_script.h"
#include "test/test.h"
#include "constants/characters.h"
#include "constants/johto_flags.h"
#include "constants/map_groups.h"
#include "constants/region_map_sections.h"
#include "constants/trainers.h"

static void SetKantoBadges(u32 count)
{
    for (u32 i = 0; i < NUM_BADGES; i++)
    {
        if (i < count)
            FlagSet(FLAG_BADGE01_GET + i);
        else
            FlagClear(FLAG_BADGE01_GET + i);
    }
}

static void StandIn(u32 mapsec, u32 map)
{
    gMapHeader.regionMapSectionId = mapsec;
    gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(map);
    gSaveBlock1Ptr->location.mapNum = MAP_NUM(map);
}

static void CreateBondMon(struct Pokemon *mon, enum Species species, u32 bond)
{
    u32 friendship = KJH_BondToFriendship(bond);

    CreateMon(mon, species, 50, 0, OTID_STRUCT_PRESET(0));
    SetMonData(mon, MON_DATA_FRIENDSHIP, &friendship);
}

TEST("KJH: a held-back Mega gets that share of its boost: 80% with 4 badges, 90% with 5, all of it with 6")
{
    EXPECT_EQ(KJH_PowerCapPercent(4), 80);
    EXPECT_EQ(KJH_PowerCapPercent(5), 90);
    EXPECT_EQ(KJH_PowerCapPercent(6), 100);
    // a stat of 100 that the Mega raises to 140
    EXPECT_EQ(KJH_MegaHeldBackStat(100, 140, 80), 132);
    EXPECT_EQ(KJH_MegaHeldBackStat(100, 140, 90), 136);
    EXPECT_EQ(KJH_MegaHeldBackStat(100, 140, 100), 140);
    EXPECT_EQ(KJH_MegaHeldBackStat(100, 90, 80), 90); // a stat a Mega lowers isn't held back
}

TEST("KJH: the BOND page's Mega line shows the first thing missing")
{
    struct Pokemon mon;
    u8 line[64];
    u32 friendship;

    FlagSet(FLAG_KJH_LEVELLESS);
    StandIn(MAPSEC_CELADON_CITY, MAP_CELADON_CITY);
    SetKantoBadges(6);
    RemoveBagItem(ITEM_MEGA_RING, 1);
    RemoveBagItem(ITEM_CHARIZARDITE_X, 1);

    CreateBondMon(&mon, SPECIES_CHARMANDER, 20);
    EXPECT_EQ(KJH_MegaStatus(&mon), KJH_MEGA_STATUS_NONE);
    line[0] = EOS;
    KJH_AppendMegaLine(line, &mon);
    EXPECT_EQ(line[0], EOS);

    CreateBondMon(&mon, SPECIES_CHARIZARD, 17);
    EXPECT_EQ(KJH_MegaStatus(&mon), KJH_MEGA_STATUS_NEEDS_BOND);
    CreateBondMon(&mon, SPECIES_CHARIZARD, 18);
    EXPECT_EQ(KJH_MegaStatus(&mon), KJH_MEGA_STATUS_NO_STONE);
    AddBagItem(ITEM_CHARIZARDITE_X, 1); // in the bag is enough
    EXPECT_EQ(KJH_MegaStatus(&mon), KJH_MEGA_STATUS_BRACELET_SILENT);
    AddBagItem(ITEM_MEGA_RING, 1);
    EXPECT_EQ(KJH_MegaStatus(&mon), KJH_MEGA_STATUS_READY);
    line[0] = EOS;
    KJH_AppendMegaLine(line, &mon);
    EXPECT_EQ(StringCompare(line, COMPOUND_STRING("\nMega: ready")), 0);
    // Held back follows the power cap, which is off in the test build (B_KJH_POWER_CAP): ready with 4 badges here
    SetKantoBadges(4);
    EXPECT_EQ(KJH_MegaStatus(&mon), KJH_MEGA_STATUS_READY);
    // Bond 18 is kept at its peak
    friendship = KJH_BondToFriendship(10);
    SetMonData(&mon, MON_DATA_FRIENDSHIP, &friendship);
    EXPECT_EQ(KJH_MegaStatus(&mon), KJH_MEGA_STATUS_READY);

    // Johto's bracelet is silent until its quest (LV-23); in the classic game it works everywhere
    StandIn(MAPSEC_J_GOLDENROD_CITY, MAP_JOHTO_GOLDENROD_CITY);
    EXPECT_EQ(KJH_MegaStatus(&mon), KJH_MEGA_STATUS_BRACELET_SILENT);
    FlagClear(FLAG_KJH_LEVELLESS);
    EXPECT_EQ(KJH_MegaStatus(&mon), KJH_MEGA_STATUS_READY);
    FlagSet(FLAG_KJH_LEVELLESS);

    StandIn(MAPSEC_CELADON_CITY, MAP_CELADON_CITY);
    SetKantoBadges(0);
    RemoveBagItem(ITEM_MEGA_RING, 1);
    RemoveBagItem(ITEM_CHARIZARDITE_X, 1);
    FlagClear(FLAG_KJH_LEVELLESS);
}

TEST("KJH: a boss's ace is the last Pokemon of its party with a Mega, and gets its stone once the bracelet works")
{
    static const struct TrainerMon party[] =
    {
        { .species = SPECIES_GYARADOS },
        { .species = SPECIES_CHARIZARD },
        { .species = SPECIES_SNORLAX }, // no Mega (Dragonite has one, from Legends Z-A)
    };
    static const struct Trainer trainer = { .party = party, .partySize = ARRAY_COUNT(party) };
    struct Pokemon mon;

    EXPECT_EQ(KJH_MegaAceSlot(&trainer), 1);
    StandIn(MAPSEC_CELADON_CITY, MAP_CELADON_CITY);
    RemoveBagItem(ITEM_MEGA_RING, 1);
    CreateMon(&mon, SPECIES_CHARIZARD, 50, 0, OTID_STRUCT_PRESET(0));
    KJH_GiveBossAceMegaStone(&mon, &party[1], &trainer);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_HELD_ITEM), ITEM_NONE);
    AddBagItem(ITEM_MEGA_RING, 1);
    KJH_GiveBossAceMegaStone(&mon, &party[0], &trainer);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_HELD_ITEM), ITEM_NONE);
    KJH_GiveBossAceMegaStone(&mon, &party[1], &trainer);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_HELD_ITEM), ITEM_CHARIZARDITE_X);
    RemoveBagItem(ITEM_MEGA_RING, 1);
}

SINGLE_BATTLE_TEST("KJH: in the levels-free game a Bond 17 Charizard can't Mega Evolve, a Bond 18 one can")
{
    u32 bond;

    PARAMETRIZE { bond = 17; }
    PARAMETRIZE { bond = 18; }
    GIVEN {
        FLAG_SET(FLAG_KJH_LEVELLESS);
        PLAYER(SPECIES_CHARIZARD) { Item(ITEM_CHARIZARDITE_X); Friendship(KJH_BondToFriendship(bond)); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH, gimmick: GIMMICK_MEGA); }
    } SCENE {
        if (bond == 18)
        {
            ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_MEGA_EVOLUTION, player);
        }
        else
        {
            NOT ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_MEGA_EVOLUTION, player);
        }
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
    } THEN {
        EXPECT_EQ(player->species, bond == 18 ? SPECIES_CHARIZARD_MEGA_X : SPECIES_CHARIZARD);
    }
}

// LV-20: the Mt. Moon quest
TEST("KJH: the Mt. Moon guardian is an Alpha above the team's level, 45 in the classic game")
{
    EXPECT_EQ(KJH_MegaGuardianLevel(0), KJH_MEGA_GUARDIAN_LEVEL);
    EXPECT_EQ(KJH_MegaGuardianLevel(60), KJH_AlphaLevel(60));
    EXPECT_GT(KJH_MegaGuardianLevel(60), 60);
}

TEST("KJH: the starter's stone answers at once only for its final form at Bond 18")
{
    u32 trainerId = GetPlayerIDAsU32();

    ZeroPlayerPartyMons();
    FlagSet(FLAG_KJH_LEVELLESS);
    VarSet(VAR_STARTER_MON, 2); // Charmander
    CreateBondMon(&gPlayerParty[0], SPECIES_CHARMELEON, 20);
    SetMonData(&gPlayerParty[0], MON_DATA_OT_ID, &trainerId);
    RUN_OVERWORLD_SCRIPT(callnative KJH_ScriptMegaStarterReady, requests_effects=1;);
    EXPECT_EQ(gSpecialVar_Result, KJH_MEGA_STARTER_EVOLVE);
    CreateBondMon(&gPlayerParty[1], SPECIES_CHARIZARD, 17);
    SetMonData(&gPlayerParty[1], MON_DATA_OT_ID, &trainerId);
    RUN_OVERWORLD_SCRIPT(callnative KJH_ScriptMegaStarterReady, requests_effects=1;);
    EXPECT_EQ(gSpecialVar_Result, KJH_MEGA_STARTER_BOND);
    CreateBondMon(&gPlayerParty[1], SPECIES_CHARIZARD, 18);
    SetMonData(&gPlayerParty[1], MON_DATA_OT_ID, &trainerId);
    RUN_OVERWORLD_SCRIPT(callnative KJH_ScriptMegaStarterReady, requests_effects=1;);
    EXPECT_EQ(gSpecialVar_Result, KJH_MEGA_STARTER_READY);
    EXPECT_EQ(gSpecialVar_0x8005, SPECIES_CHARIZARD);
    trainerId++; // a Charizard traded in isn't the starter
    SetMonData(&gPlayerParty[1], MON_DATA_OT_ID, &trainerId);
    RUN_OVERWORLD_SCRIPT(callnative KJH_ScriptMegaStarterReady, requests_effects=1;);
    EXPECT_EQ(gSpecialVar_Result, KJH_MEGA_STARTER_EVOLVE);
    VarSet(VAR_STARTER_MON, 0); // Bulbasaur's player
    RUN_OVERWORLD_SCRIPT(callnative KJH_ScriptMegaStarterReady, requests_effects=1;);
    EXPECT_EQ(gSpecialVar_Result, KJH_MEGA_STARTER_MISSING);
    FlagClear(FLAG_KJH_LEVELLESS);
}

// LV-21: Kanto's stone dealer
extern const u16 KJH_Mart_MegaStonesKanto[];

static bool32 OnSale(enum Item item)
{
    for (u32 i = 0; KJH_Mart_MegaStonesKanto[i] != ITEM_NONE; i++)
    {
        if (KJH_Mart_MegaStonesKanto[i] == item)
            return TRUE;
    }
    return FALSE;
}

TEST("KJH: Celadon's dealer sells Kanto's ordinary Mega Stones at 10,000, never a special one")
{
    for (u32 i = 0; KJH_Mart_MegaStonesKanto[i] != ITEM_NONE; i++)
    {
        EXPECT_EQ(GetItemHoldEffect(KJH_Mart_MegaStonesKanto[i]), HOLD_EFFECT_MEGA_STONE);
        EXPECT(!KJH_IsNeverSoldStone(KJH_Mart_MegaStonesKanto[i]));
        EXPECT_EQ(GetItemPrice(KJH_Mart_MegaStonesKanto[i]), KJH_MEGA_STONE_PRICE);
    }
    EXPECT(OnSale(ITEM_GYARADOSITE));
    EXPECT(OnSale(ITEM_CHARIZARDITE_Y)); // the other Charizardite
    EXPECT(!OnSale(ITEM_MEWTWONITE_X));
    EXPECT(!OnSale(ITEM_DRAGONINITE));
    EXPECT(KJH_IsNeverSoldStone(ITEM_MEWTWONITE_Y));
    EXPECT_EQ(GetItemPrice(ITEM_MEWTWONITE_Y), 0); // so it can't be sold either
    EXPECT_EQ(GetItemPrice(ITEM_POTION), gItemsInfo[ITEM_POTION].price); // other items keep their price
}
