// KJH: headbutt trees (CF-8, include/kjh_headbutt.h).
#include "global.h"
#include "battle_setup.h"
#include "event_data.h"
#include "field_player_avatar.h"
#include "fieldmap.h"
#include "kjh_headbutt.h"
#include "pokemon.h"
#include "random.h"
#include "wild_encounter.h"
#include "constants/flags.h"

// The odds of each slot of a headbutt_mons table: wild_encounters.json's headbutt_mons field (HeartGold/SoulSilver's).
// The generated ENCOUNTER_CHANCE_HEADBUTT_MONS_* macros live in data/wild_encounters.h, which only wild_encounter.c
// can include; kjh_tools/headbutt_trees.py writes the field and every table with these 6 slots.
static const u8 sHeadbuttSlotRates[] = {50, 15, 15, 10, 5, 5};

// Level-up (any level: the levels-free design opens them with the team) or a TM, HM or tutor move
bool32 KJH_CouldLearnMove(enum Species species, enum Move move)
{
    const struct LevelUpMove *learnset = GetSpeciesLevelUpLearnset(species);

    for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
    {
        if (learnset[i].move == move)
            return TRUE;
    }
    return CanLearnTeachableMove(species, move);
}

u16 KJH_GetHeadbuttPartySlot(void)
{
    if (!FlagGet(FLAG_BADGE02_GET))
        return PARTY_SIZE;
    for (u32 i = 0; i < PARTY_SIZE; i++)
    {
        enum Species species = GetMonData(&gPlayerParty[i], MON_DATA_SPECIES);

        if (species == SPECIES_NONE)
            break;
        if (!GetMonData(&gPlayerParty[i], MON_DATA_IS_EGG) && KJH_CouldLearnMove(species, MOVE_HEADBUTT))
            return i;
    }
    return PARTY_SIZE;
}

static u32 ChooseHeadbuttSlot(void)
{
    u32 roll = Random() % 100, slot;

    for (slot = 0; slot < ARRAY_COUNT(sHeadbuttSlotRates) - 1; slot++)
    {
        if (roll < sHeadbuttSlotRates[slot])
            break;
        roll -= sHeadbuttSlotRates[slot];
    }
    return slot;
}

// The tables are written for the default time only (kjh_tools/headbutt_trees.py, kjh_tools/johto/to_expansion.py)
#define HEADBUTT_TABLE(member)                                                                                         \
{                                                                                                                      \
    u32 headerId = GetCurrentMapWildMonHeaderId();                                                                     \
    const struct WildPokemonInfo *tree;                                                                                \
                                                                                                                       \
    if (headerId == HEADER_NONE)                                                                                       \
        return NULL;                                                                                                   \
    tree = gWildMonHeaders[headerId].encounterTypes[GetTimeOfDayForEncounters(headerId, WILD_AREA_LAND)].member;       \
    if (tree == NULL)                                                                                                  \
        tree = gWildMonHeaders[headerId].encounterTypes[TIME_OF_DAY_DEFAULT].member;                                   \
    return tree;                                                                                                       \
}

const struct WildPokemonInfo *KJH_GetHeadbuttTable(void)
HEADBUTT_TABLE(headbuttMonsInfo)

const struct WildPokemonInfo *KJH_GetHeadbuttRareTable(void)
HEADBUTT_TABLE(headbuttRareMonsInfo)

// Crystal's GetTreeScore: its map coordinates have a 4-tile border, and its trainer ID is the visible 16-bit one
u32 KJH_HeadbuttTreeScore(s32 x, s32 y, u32 trainerId)
{
    u32 tree = (((x + 4) * (y + 4) + (x + 4) + (y + 4)) / 5) % 10;
    u32 player = (trainerId & 0xFFFF) % 10;
    u32 diff = (tree + 10 - player) % 10;

    if (diff == 0)
        return KJH_TREE_RARE;
    if (diff < 5)
        return KJH_TREE_GOOD;
    return KJH_TREE_POOR;
}

static u32 VisibleTrainerId(void)
{
    return gSaveBlock2Ptr->playerTrainerId[0] | (gSaveBlock2Ptr->playerTrainerId[1] << 8);
}

bool32 KJH_TryCreateHeadbuttMonAtTree(s32 x, s32 y)
{
    static const u8 sCrystalChance[] = {[KJH_TREE_POOR] = 10, [KJH_TREE_GOOD] = 50, [KJH_TREE_RARE] = 80};
    const struct WildPokemonInfo *tree = KJH_GetHeadbuttTable();
    const struct WildPokemonInfo *rare = KJH_GetHeadbuttRareTable();
    const struct WildPokemon *mon;
    u32 level, chance;

    if (tree == NULL)
        return FALSE;
    chance = tree->encounterRate;
    if (rare != NULL) // Johto (CF-10): Crystal's rule
    {
        u32 score = KJH_HeadbuttTreeScore(x, y, VisibleTrainerId());

        chance = sCrystalChance[score];
        if (score == KJH_TREE_RARE)
            tree = rare;
    }
    if (Random() % 100 >= chance)
        return FALSE; // "Nothing..."

    mon = &tree->wildPokemon[ChooseHeadbuttSlot()];
    level = mon->minLevel;
    if (mon->maxLevel > mon->minLevel)
        level += Random() % (mon->maxLevel - mon->minLevel + 1);
    CreateWildMon(mon->species, level);
    return TRUE;
}

bool32 KJH_TryCreateHeadbuttMon(void)
{
    s16 x, y;

    GetXYCoordsOneStepInFrontOfPlayer(&x, &y);
    return KJH_TryCreateHeadbuttMonAtTree(x - MAP_OFFSET, y - MAP_OFFSET);
}

void KJH_HeadbuttWildEncounter(void)
{
    gSpecialVar_Result = KJH_TryCreateHeadbuttMon();
    if (gSpecialVar_Result)
        BattleSetup_StartWildBattle();
}
