#ifndef GUARD_KJH_PACK_H
#define GUARD_KJH_PACK_H

#include "constants/species.h"

// KJH: wild packs (docs/PACKS.md in the KJH repo), ported from its pokefirered tree (ENG-6). The rules are in
// src/kjh_pack_rules.c, the battle side in src/kjh_pack.c; tests in test/kjh/packs.c.

// 1 random wild Pokemon in KJH_PACK_LEADER_ODDS leads a pack (the roll is RNG_KJH_PACK_LEADER)
#define KJH_PACK_LEADER_ODDS 20
// Legendaries, mythicals, Ultra Beasts and Unown never form packs
bool32 KJH_PackSpeciesAllowed(enum Species species);
// A leader is a few levels above its pack
#define KJH_PACK_LEADER_LEVEL_BONUS 3
u32 KJH_PackLeaderLevel(u32 level);
// A leader has perfect IVs, and is harder to catch: half its species' catch rate (at least 1)
#define KJH_PACK_LEADER_IV 31
u32 KJH_PackCatchRate(u32 catchRate, bool32 leader);
// A leader gives a lot of Exp.: KJH_PACK_LEADER_EXP_MULTIPLIER times what it would give; a helper it called
// KJH_PACK_HELPER_EXP_MULTIPLIER times
#define KJH_PACK_LEADER_EXP_MULTIPLIER 4
#define KJH_PACK_HELPER_EXP_MULTIPLIER 2
enum KjhPackRole
{
    KJH_PACK_ROLE_NONE,          // a lone wild Pokemon, or a helper an ordinary wild Pokemon called
    KJH_PACK_ROLE_LEADER,
    KJH_PACK_ROLE_LEADER_HELPER, // a helper the leader called
};
u32 KJH_PackExp(u32 exp, enum KjhPackRole role);

// Battle side (src/kjh_pack.c)
struct Pokemon;

// A random wild Pokemon is being made (CreateWildMon, wild_encounter.c): may make it a leader, remembered until
// the battle starts. Returns its level.
u32 KJH_PackWildEncounterLevel(enum Species species, u32 level);
// After it is made: a leader gets perfect IVs
void KJH_PackFinishWildMon(struct Pokemon *mon);
// Tests: the next battle's wild Pokemon leads a pack (or not), as if KJH_PackWildEncounterLevel had rolled it
void KJH_PackSetNextEncounter(bool32 leader);
// A battle starts (BeginBattleIntro): a plain random wild battle keeps the pack roll, any other battle drops it
void KJH_PackBattleStart(void);
bool32 KJH_PackIsLeaderBattle(void);
// The battler's place in a pack (the Exp. it gives); the pack's leader is harder to catch
enum KjhPackRole KJH_PackRole(u32 battler);
bool32 KJH_PackIsLeader(u32 battler);
// A healthbox shows its Pokemon's name (UpdateNickInHealthbox): the leader's is gold, with a crown on the box
void KJH_PackDecorateHealthbox(u32 healthboxSpriteId, u32 battler);

#endif // GUARD_KJH_PACK_H
