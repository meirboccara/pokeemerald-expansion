// KJH: the Shiny Charm and the Oval Charm (CF-3, include/kjh_charms.h). The charms' effects are expansion's own
// (ComputePlayerShinyOdds in pokemon.c, ModifyBreedingScoreForOvalCharm in daycare.c); this file decides when
// they are earned.
#include "global.h"
#include "event_data.h"
#include "kjh_charms.h"
#include "overworld.h"
#include "pokedex.h"
#include "string_util.h"
#include "constants/game_stat.h"
#include "constants/pokedex.h"

// The species Prof. Oak counts for the Shiny Charm: every species obtainable in KJH, as National Pokedex ranges.
// A species that can't be obtained is left out by splitting its range; Gen 4/5 species are added as new ranges.
// Every Gen 1-3 species can be obtained in KJH's three regions (wild, gifts, the Game Corner, trades, evolution,
// breeding, the Legend Keeper's tickets), so the table is one range for now. FEATURES.md lists it.
static const u16 sShinyCharmDex[][2] =
{
    {NATIONAL_DEX_BULBASAUR, NATIONAL_DEX_DEOXYS},
};

u32 KJH_ShinyCharmSpeciesCount(void)
{
    u32 count = 0;
    for (u32 i = 0; i < ARRAY_COUNT(sShinyCharmDex); i++)
        count += sShinyCharmDex[i][1] - sShinyCharmDex[i][0] + 1;
    return count;
}

u16 KJH_ShinyCharmSpeciesLeft(void)
{
    u32 left = 0;
    for (u32 i = 0; i < ARRAY_COUNT(sShinyCharmDex); i++)
    {
        for (u32 dexNum = sShinyCharmDex[i][0]; dexNum <= sShinyCharmDex[i][1]; dexNum++)
        {
            if (!GetSetPokedexFlag(dexNum, FLAG_GET_CAUGHT))
                left++;
        }
    }
    ConvertIntToDecimalStringN(gStringVar1, left, STR_CONV_MODE_LEFT_ALIGN, 4);
    return left;
}

u16 KJH_HasHatchedAnEgg(void)
{
    return GetGameStat(GAME_STAT_HATCHED_EGGS) > 0;
}
