#ifndef GUARD_KJH_HEADBUTT_H
#define GUARD_KJH_HEADBUTT_H

// KJH: headbutt trees (CF-8). A tree is marked by a "sign" bg_event with EventScript_HeadbuttTree; its Pokemon are
// the map's headbutt_mons table in wild_encounters.json. Like KJH's HMs, Headbutt needs no teaching: from Kanto's
// Cascade Badge, any party Pokemon that could learn it can use it.
//
// CF-10: Johto's maps also have Crystal's rare table (headbutt_rare_mons), and then each tree follows Crystal's rule
// (engine/events/treemons.asm, GetTreeScore): it scores against the player's trainer ID as rare (the rare table, 80%
// of the time), good (the common table, 50%) or poor (the common table, 10%). Kanto's trees keep the table's chance.

enum
{
    KJH_TREE_POOR,
    KJH_TREE_GOOD,
    KJH_TREE_RARE,
};

bool32 KJH_CouldLearnMove(enum Species species, enum Move move);
u16 KJH_GetHeadbuttPartySlot(void); // special: the first party Pokemon able to headbutt, or PARTY_SIZE
const struct WildPokemonInfo *KJH_GetHeadbuttTable(void); // the current map's headbutt_mons, or NULL
const struct WildPokemonInfo *KJH_GetHeadbuttRareTable(void); // the current map's headbutt_rare_mons, or NULL
u32 KJH_HeadbuttTreeScore(s32 x, s32 y, u32 trainerId); // KJH_TREE_*: the tree at map coordinates (x, y), as Crystal
bool32 KJH_TryCreateHeadbuttMonAtTree(s32 x, s32 y); // at the tree's chance, a wild Pokemon from its table
bool32 KJH_TryCreateHeadbuttMon(void); // the same for the tree the player faces
void KJH_HeadbuttWildEncounter(void); // special: VAR_RESULT TRUE if a wild battle starts

#endif // GUARD_KJH_HEADBUTT_H
