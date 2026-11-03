// KJH: headbutt trees (CF-8, include/kjh_headbutt.h).
#include "global.h"
#include "battle_setup.h"
#include "event_data.h"
#include "kjh_headbutt.h"
#include "pokemon.h"
#include "random.h"
#include "wild_encounter.h"
#include "constants/flags.h"

// The odds of each slot of a headbutt_mons table: wild_encounters.json's headbutt_mons field (HeartGold/SoulSilver's)
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

const struct WildPokemonInfo *KJH_GetHeadbuttTable(void)
{
    u32 headerId = GetCurrentMapWildMonHeaderId();

    if (headerId == HEADER_NONE)
        return NULL;
    return gWildMonHeaders[headerId].encounterTypes[GetTimeOfDayForEncounters(headerId, WILD_AREA_LAND)].headbuttMonsInfo;
}

bool32 KJH_TryCreateHeadbuttMon(void)
{
    const struct WildPokemonInfo *tree = KJH_GetHeadbuttTable();
    const struct WildPokemon *mon;
    u32 level;

    if (tree == NULL || Random() % 100 >= tree->encounterRate)
        return FALSE; // "Nothing..."

    mon = &tree->wildPokemon[ChooseHeadbuttSlot()];
    level = mon->minLevel;
    if (mon->maxLevel > mon->minLevel)
        level += Random() % (mon->maxLevel - mon->minLevel + 1);
    CreateWildMon(mon->species, level);
    return TRUE;
}

void KJH_HeadbuttWildEncounter(void)
{
    gSpecialVar_Result = KJH_TryCreateHeadbuttMon();
    if (gSpecialVar_Result)
        BattleSetup_StartWildBattle();
}
