#ifndef GUARD_KJH_HEADBUTT_H
#define GUARD_KJH_HEADBUTT_H

// KJH: headbutt trees (CF-8). A tree is marked by a "sign" bg_event with EventScript_HeadbuttTree; its Pokemon are
// the map's headbutt_mons table in wild_encounters.json. Like KJH's HMs, Headbutt needs no teaching: from Kanto's
// Cascade Badge, any party Pokemon that could learn it can use it.

bool32 KJH_CouldLearnMove(enum Species species, enum Move move);
u16 KJH_GetHeadbuttPartySlot(void); // special: the first party Pokemon able to headbutt, or PARTY_SIZE
const struct WildPokemonInfo *KJH_GetHeadbuttTable(void); // the current map's headbutt_mons, or NULL
bool32 KJH_TryCreateHeadbuttMon(void); // at the table's chance, a wild Pokemon from it
void KJH_HeadbuttWildEncounter(void); // special: VAR_RESULT TRUE if a wild battle starts

#endif // GUARD_KJH_HEADBUTT_H
