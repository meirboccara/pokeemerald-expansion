// KJH: helpers for scripts translated from Pokemon Crystal (see kjh_tools/johto/scripts.py).
#include "global.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "field_player_avatar.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "pokedex.h"
#include "fieldmap.h"
#include "constants/species.h"

static u32 CountJohtoBadges(void)
{
    u32 i, count = 0;

    for (i = 0; i < 8; i++)
        count += FlagGet(FLAG_JOHTO_BADGE01_GET + i);
    return count;
}

// Crystal VAR_* ids (constants/script_constants.asm)
enum {
    CR_VAR_PARTYCOUNT = 1, CR_VAR_TIMEOFDAY = 4, CR_VAR_DEXCAUGHT = 5, CR_VAR_DEXSEEN = 6, CR_VAR_BADGES = 7,
    CR_VAR_MOVEMENT = 8, CR_VAR_FACING = 9, CR_VAR_HOUR = 10, CR_VAR_WEEKDAY = 11, CR_VAR_UNOWNCOUNT = 14,
    CR_VAR_BOXSPACE = 16, CR_VAR_XCOORD = 18, CR_VAR_YCOORD = 19,
};


// VAR_0x8004 = Crystal var id -> VAR_RESULT
void KJH_CrystalReadVar(void)
{
    u16 result = 0;
    s16 x, y;
    switch (gSpecialVar_0x8004)
    {
    case CR_VAR_PARTYCOUNT: result = CalculatePlayerPartyCount(); break;
    case CR_VAR_TIMEOFDAY:  result = 1; break;                     // DAY_F: KJH has no clock
    case CR_VAR_DEXCAUGHT:  result = GetNationalPokedexCount(FLAG_GET_CAUGHT); break;
    case CR_VAR_DEXSEEN:    result = GetNationalPokedexCount(FLAG_GET_SEEN); break;
    case CR_VAR_BADGES:     result = CountJohtoBadges(); break;
    case CR_VAR_MOVEMENT:   // Crystal PLAYER_NORMAL 0, PLAYER_BIKE 1, PLAYER_SURF 4
        if (TestPlayerAvatarFlags(PLAYER_AVATAR_FLAG_SURFING))
            result = 4;
        else if (TestPlayerAvatarFlags(PLAYER_AVATAR_FLAG_MACH_BIKE | PLAYER_AVATAR_FLAG_ACRO_BIKE))
            result = 1;
        break;
    case CR_VAR_FACING:
        switch (GetPlayerFacingDirection())
        {
        case DIR_NORTH: result = 1; break;
        case DIR_WEST:  result = 2; break;
        case DIR_EAST:  result = 3; break;
        default:        result = 0; break;
        }
        break;
    case CR_VAR_HOUR:       result = 12; break;
    case CR_VAR_WEEKDAY:    result = gSaveBlock2Ptr->playTimeHours % 7; break;   // days advance with play time
    case CR_VAR_UNOWNCOUNT: result = GetSetPokedexFlag(SpeciesToNationalPokedexNum(SPECIES_UNOWN), FLAG_GET_CAUGHT) ? 26 : 0; break;
    case CR_VAR_BOXSPACE:   result = 30; break;
    case CR_VAR_XCOORD:     PlayerGetDestCoords(&x, &y); result = x - MAP_OFFSET; break;
    case CR_VAR_YCOORD:     PlayerGetDestCoords(&x, &y); result = y - MAP_OFFSET; break;
    }
    gSpecialVar_Result = result;
}

// VAR_0x8004 = species -> VAR_RESULT TRUE if it is in the party
void KJH_CheckPartySpecies(void)
{
    u8 i, count = CalculatePlayerPartyCount();
    gSpecialVar_Result = FALSE;
    for (i = 0; i < count; i++)
        if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES_OR_EGG) == gSpecialVar_0x8004)
            gSpecialVar_Result = TRUE;
}

void KJH_GetLeadFriendship(void)
{
    gSpecialVar_Result = GetMonData(&gPlayerParty[0], MON_DATA_FRIENDSHIP);
}

// Crystal's BeastsCheck (Tin Tower sage, Rainbow Wing): TRUE once Suicune, Raikou and Entei have all been
// faced. In KJH Raikou and Entei are static encounters in Tin Tower 1F (docs/kjh/LEGENDARIES.md).
void KJH_BeastsCheck(void)
{
    gSpecialVar_Result = FlagGet(FLAG_J_FOUGHT_SUICUNE) && FlagGet(FLAG_KJH_HIDE_RAIKOU) && FlagGet(FLAG_KJH_HIDE_ENTEI);
}
