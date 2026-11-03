// KJH: no roaming legendaries (LEGENDARIES.md rule 1 in the KJH repo; CF-13, ENG-10). Every legendary is a static,
// one-time encounter, so the special that starts a roamer (Emerald's Latias or Latios after the TV news, FireRed's One
// Island call) starts none.
#include "global.h"
#include "event_data.h"
#include "roamer.h"
#include "test/test.h"

TEST("KJH: InitRoamer starts no roamer, whatever color the player names")
{
    u32 color, i;

    for (color = 0; color < 2; color++) // MULTI_TV_LATI: 0 red (Latias), 1 blue (Latios)
    {
        DeactivateAllRoamers();
        gSpecialVar_0x8004 = color;
        InitRoamer();
        for (i = 0; i < ROAMER_COUNT; i++)
            EXPECT(!gSaveBlock1Ptr->roamer[i].active);
    }
}
