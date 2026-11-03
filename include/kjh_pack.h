#ifndef GUARD_KJH_PACK_H
#define GUARD_KJH_PACK_H

#include "constants/battle.h"
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
// A helper's level: the caller's level (without the leader bonus) minus levelDrop, 0 to KJH_PACK_HELPER_MAX_LEVEL_DROP
#define KJH_PACK_HELPER_MAX_LEVEL_DROP 2
u32 KJH_PackHelperLevel(u32 callerLevel, bool32 callerIsLeader, u32 levelDrop);

// Calling for help uses the caller's turn. At most KJH_PACK_MAX_HELPERS answer, so a pack is 5 at most.
#define KJH_PACK_MAX_HELPERS 4
// Percent chance to call this turn. A leader picks its moment: never on the first turn, then the more it is hurt
// the more it calls (healthy above half HP, hurt down to a quarter, desperate below), half as often when its side
// is full (the helper then waits for a slot). An ordinary wild Pokemon calls now and then.
#define KJH_PACK_CALL_LEADER_HEALTHY   20
#define KJH_PACK_CALL_LEADER_HURT      50
#define KJH_PACK_CALL_LEADER_DESPERATE 80
#define KJH_PACK_CALL_ORDINARY         10
u32 KJH_PackCallChance(bool32 leader, u32 helpersCalled, bool32 freeSlot, bool32 firstTurn, u32 hp, u32 maxHp);
// Percent chance that someone answers
#define KJH_PACK_ANSWER_LEADER   80
#define KJH_PACK_ANSWER_ORDINARY 50
u32 KJH_PackAnswerChance(bool32 leader);

// When the first helper comes, the battle turns into a double battle and the player's first healthy Pokemon that
// isn't fighting steps in next to the one fighting. usable[PARTY_SIZE]: the party slot has a healthy non-egg
// Pokemon. fighting: the party slot already in battle.
#define KJH_PACK_NO_PARTNER PARTY_SIZE
u32 KJH_PackPartnerSlot(const bool8 *usable, u32 fighting);
// No partner: the right slot stays empty, pointing at a fainted or empty party slot (there is always one)
u32 KJH_PackEmptySlot(const bool8 *usable, u32 fighting);
// order: the battle party order (PARTY_SIZE / 2 bytes, 4 bits per slot, high nibble first). Puts partnerSlot
// second, as a double battle lists both fighters first; the slot it pushes out takes the partner's old place.
void KJH_PackPutPartnerSecond(u8 *order, u32 partnerSlot);

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
enum KjhPackRole KJH_PackRole(enum BattlerId battler);
bool32 KJH_PackIsLeader(enum BattlerId battler);
// A wild Pokemon sent out once the battle is a pack's double battle: a helper, that comes without a ball, with its cry
// (StartSendOutAnim), and the message "Another wild ... joined the fight!"
bool32 KJH_PackIsHelperSendOut(enum BattlerId battler);
// A healthbox shows its Pokemon's name (UpdateNickInHealthbox): the leader's is gold, with a crown on the box
void KJH_PackDecorateHealthbox(u32 healthboxSpriteId, enum BattlerId battler);
// Before the turn's moves, after the Megas (RunTurnActionsFunctions): a wild Pokemon may call for help. TRUE while
// a call script runs.
bool32 KJH_TryPackCallsBeforeTurn(void);
// The battle script command kjhpack (asm/macros/battle_script.inc): one step of BattleScript_KjhPackCall
void BS_KjhPack(void);
// Helpers that answered so far (they are in the wild party's slots 1 to KJH_PACK_MAX_HELPERS)
u32 KJH_PackHelpers(void);

#endif // GUARD_KJH_PACK_H
