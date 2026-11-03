// KJH (ENG-10, Hoenn): Emerald's story in the FireRed build (docs/STORY.md, "Chapter 3: Hoenn").
// - Birch's bag holds Hoenn's starters (FireRed's starter_choose.c tables are Oak's), and his choice is Hoenn's own
//   variable: Oak's VAR_STARTER_MON still picks Kanto's rival, the Indigo rematches and the Mega Stone. Hoenn's
//   scripts read VAR_STARTER_MON as VAR_KJH_HOENN_STARTER (constants/kjh_hoenn_scope_begin.h).
// - The S.S. AQUA's first landing in Slateport sends the player home to Littleroot in the moving truck: Emerald's
//   own opening (the truck, Mom, the clock, the rival, Birch on Route 101) plays from there.
// - Ever Grande's Hall of Fame (Emerald's special GameClear) makes the player Hoenn Champion.
#include "global.h"
#include "event_data.h"
#include "field_screen_effect.h"
#include "field_special_scene.h"
#include "kjh_hoenn_story.h"
#include "load_save.h"
#include "overworld.h"
#include "constants/heal_locations.h"
#include "constants/map_groups.h"

#if IS_FRLG

static const u16 sHoennStarters[] = {SPECIES_TREECKO, SPECIES_TORCHIC, SPECIES_MUDKIP};

u16 KJH_HoennStarterSpecies(u16 choice)
{
    if (choice >= ARRAY_COUNT(sHoennStarters))
        choice = 0;
    return sHoennStarters[choice];
}

// Birch's bag (CB2_GiveStarter): the choice is remembered as Hoenn's; returns the species to give
u16 KJH_ChooseHoennStarter(u16 choice)
{
    VarSet(VAR_KJH_HOENN_STARTER, choice);
    return KJH_HoennStarterSpecies(choice);
}

// Ever Grande's Hall of Fame. Returns whether the Hall of Fame already holds records (the Kanto and Johto Leagues'):
// they are kept. CONTINUE wakes the player at home in Littleroot, where Emerald's post-game starts (the Lati TV
// program, the S.S. Ticket), as FireRed's Hall of Fame wakes them in Pallet Town.
bool32 KJH_HoennGameClear(void)
{
    bool32 records = FlagGet(FLAG_SYS_GAME_CLEAR) || FlagGet(FLAG_HOENN_GAME_CLEAR);

    FlagSet(FLAG_HOENN_GAME_CLEAR);
    SetContinueGameWarpStatus();
    if (gSaveBlock2Ptr->playerGender == MALE)
        SetContinueGameWarpToHealLocation(HEAL_LOCATION_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F);
    else
        SetContinueGameWarpToHealLocation(HEAL_LOCATION_LITTLEROOT_TOWN_MAYS_HOUSE_2F);
    return records;
}

// Special (data/scripts/kjh_ferry.inc): into the moving truck as in Emerald's new game: it drives, stops and opens
// on Littleroot Town (InsideOfTruck's own events), then Emerald's opening goes on.
void KJH_RideMovingTruck(void)
{
    SetWarpDestination(MAP_GROUP(MAP_INSIDE_OF_TRUCK), MAP_NUM(MAP_INSIDE_OF_TRUCK), WARP_ID_NONE, -1, -1);
    DoWarp();
    gFieldCallback = ExecuteTruckSequence;
}

#endif // IS_FRLG
