#ifndef GUARD_KJH_LEVEL_BANDS_H
#define GUARD_KJH_LEVEL_BANDS_H

#include "gba/types.h"

// KJH: level bands, in play order. Each band maps its source game's levels (FireRed, Crystal,
// FireRed rematch teams, Emerald) to the levels used in KJH. Kanto is played first and keeps
// FireRed's levels. A new region's first gym sits just below the League won before it, then the
// region climbs past it (docs/TRAINER_LEVELS.md).
enum {
    KJH_BAND_KANTO,          // FireRed, unchanged (Kanto League included)
    KJH_BAND_JOHTO,          // Crystal
    KJH_BAND_JOHTO_LEAGUE,   // FireRed's Elite Four / Champion rematch teams at Indigo Plateau
    KJH_BAND_HOENN,          // Emerald (Hoenn League included)
    KJH_BAND_COUNT
};

u8 KJH_BandLevel(u8 band, u8 level);

// Trainers catch up with the player's party (src/kjh_progression.c), after Pokemon Unbound
// (docs/UNBOUND_RESEARCH.md). The party's level, against a trainer with topN Pokemon, is the average of the
// party's topN best levels (rounded down): a trainer is matched against the Pokemon you would send against
// it, so one strong starter doesn't count alone and a fresh catch only counts against big teams.
// topN 0 or above count: the whole party.
u8 KJH_PartyLevel(const u8 *levels, u8 count, u8 topN);
// How many levels a trainer's whole team goes up (its levels after the band; teamTop: its best one). Only up,
// never past MAX_LEVEL. The target follows the party's level (not its best Pokemon, so one strong starter
// doesn't drag a whole boss team up) and the badges (all regions):
//   badges   normal trainer's best   boss's ace
//   0-2      party - 3               party - 1
//   3-5      party - 2               party
//   6+       party - 2               party + 1
u8 KJH_TrainerLevelBoost(u8 teamTop, u8 partyLevel, u8 badges, bool8 boss);

#endif // GUARD_KJH_LEVEL_BANDS_H
