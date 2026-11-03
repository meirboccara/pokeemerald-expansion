#ifndef GUARD_KJH_MEGA_H
#define GUARD_KJH_MEGA_H

#include "constants/battle.h"
#include "constants/form_change_types.h"
#include "constants/items.h"
#include "constants/kjh_mega.h"
#include "constants/species.h"

struct Pokemon;
struct Trainer;
struct TrainerMon;

// KJH (LV-19): Mega Evolution, levels-free (docs/LEVELLESS_DESIGN.md, "Mega Evolution" in the open questions, and
// docs/MEGA.md in the KJH repo). On expansion's own Mega Evolution (src/battle_util.c, CanMegaEvolve):
// - the player's Pokemon Mega Evolves when the bracelet (expansion's ITEM_MEGA_RING, the MEGA BRACELET) works in
//   this region, its stone is held or in the bag, and, in the levels-free game, its peak Bond is KJH_MEGA_BOND;
// - the bracelet works in Kanto (the Saffron researcher gives it at 6 Kanto badges, data/scripts/kjh_mega.inc); in
//   Johto and Hoenn it is silent until their quest (LV-23), in the levels-free game; the classic game keeps
//   docs/MEGA.md's old rules (the bracelet everywhere, nothing held back);
// - with fewer than 6 badges in the region, the Mega's stat boost is held back by the power cap's table (LV-11:
//   4 badges 80%, 5 90%) and it keeps its old ability; *"Charizard's Mega Evolution is held back (80%)!"*;
// - bosses (Gym Leaders, the Elite Four, Champions, rivals, team bosses and admins) give their ace, the last Pokemon
//   of their party with a Mega, its stone, only when the player's bracelet works here; it follows the same rule.

#define KJH_MEGA_BOND 18 // the BOND page's "Evolve, Mega" milestone (gKjhBondMilestones)

// What the BOND page's Mega line says: the first thing missing
enum KjhMegaStatus
{
    KJH_MEGA_STATUS_NONE,            // no Mega form: no line
    KJH_MEGA_STATUS_NEEDS_BOND,
    KJH_MEGA_STATUS_NO_STONE,
    KJH_MEGA_STATUS_BRACELET_SILENT,
    KJH_MEGA_STATUS_HELD_BACK,       // ready, held back
    KJH_MEGA_STATUS_READY,
};

// Rules
u32 KJH_MegaHeldBackStat(u32 baseStat, u32 megaStat, u32 percent); // base + (Mega - base) x percent
bool32 KJH_SpeciesHasMega(enum Species species);
enum Item KJH_MegaStoneForSpecies(enum Species species);           // its first stone (ITEM_NONE: Rayquaza)
u32 KJH_MegaAceSlot(const struct Trainer *trainer);                // the last party slot with a Mega, or partySize

// The game
bool32 KJH_IsBraceletActiveHere(void);
u32 KJH_MegaPercentHere(void);                                      // 100: not held back (always, classic)
bool32 KJH_HasMegaBond(struct Pokemon *mon);
enum KjhMegaStatus KJH_MegaStatus(struct Pokemon *mon);
u8 *KJH_AppendMegaLine(u8 *dest, struct Pokemon *mon);             // the BOND page's line, nothing without a Mega

// Battle hooks (src/battle_util.c)
bool32 KJH_CanBattlerMegaEvolve(enum BattlerId battler);           // the player's own: bracelet here, Bond
enum Item KJH_MegaStoneInPlay(enum BattlerId battler, enum FormChanges method, enum Item heldItem);
void KJH_HoldBackMegaEvolution(enum BattlerId battler, struct Pokemon *mon, const u16 *statsBefore,
                               enum Ability abilityBefore);
bool32 KJH_TryPrepareMegaHeldBack(void);                              // the message's buffers, once per battle
void KJH_MegaStartBattle(void);                                       // from KJH_PowerCapStartBattle
void BS_KjhJumpIfMegaNotHeldBack(void);                               // callnative: jump unless held back
void BS_KjhTryMegaHeldBackMessage(void);                              // callnative: jump past the message if shown

// callnative: VAR_RESULT = Kanto's badges (the researcher's 6)
struct ScriptContext;
void KJH_ScriptCountKantoBadges(struct ScriptContext *ctx);

// LV-20, the Mt. Moon quest (data/scripts/kjh_mega.inc)
#define KJH_MEGA_GUARDIAN_LEVEL 45 // the guardian's level in the classic game; levels-free: an Alpha above the team
// The level of the guardian Alpha Clefable: an Alpha above the team's level, levels-free
u32 KJH_MegaGuardianLevel(u32 teamLevel);
// callnative after setwildbattle: the guardian is an Alpha at KJH_MegaGuardianLevel
void KJH_ScriptSetupMegaGuardian(struct ScriptContext *ctx);
// callnative: VAR_RESULT = KJH_MEGA_STARTER_* (include/constants/kjh_mega.h) for the player's starter: a Pokemon of
// the line chosen in Pallet Town (VAR_STARTER_MON), the player's own (OT ID), in the party; the most advanced one
void KJH_ScriptMegaStarterReady(struct ScriptContext *ctx);

// LV-21: the stone dealers sell the ordinary stones (data/scripts/kjh_mega.inc, KJH_Mart_MegaStones*) at this price
// (GetItemPrice); pseudo-legendaries' and legendaries' stones are never sold, only found where they belong, and can't
// be sold either (price 0)
#define KJH_MEGA_STONE_PRICE 10000
u32 KJH_ItemPrice(enum Item item, u32 price);
bool32 KJH_IsNeverSoldStone(enum Item item);

// LV-22: wild Mega Alphas and stone drops (docs/LEVELLESS_DESIGN.md, "Wild Megas"; docs/MEGA.md). Expansion lets a
// wild Pokemon Mega Evolve only through the battle AI (OpponentHandleChooseMove picks a random move, without a
// gimmick, for a plain wild one), so an Alpha holding its stone fights as a smart wild Pokemon (IsWildMonSmart).
// The stone of this species or of a species it evolves into (an Alpha Mareep: Ampharosite), ITEM_NONE without one
enum Item KJH_MegaStoneForFamily(enum Species species);
// The stone is in the bag or held by a party Pokemon
bool32 KJH_PlayerHasMegaStone(enum Item stone);
// A new wild Alpha (KJH_PackFinishWildMon): a Mega-capable one holds its stone when the player's bracelet works here
void KJH_GiveAlphaMegaStone(struct Pokemon *mon);
// This battle's wild Alpha holds a Mega Stone: it fights with the AI so it Mega Evolves on its first turn
bool32 KJH_IsMegaAlphaBattle(void);
// callnative NATIVE_ARGS(const u8 *doneInstr, u8 caught): a beaten or caught Alpha of a Mega family gives its stone
// when the player doesn't have it ("The ALPHA left its GYARADOSITE!"), once the player has the starter's stone (the
// Mt. Moon meteorite, FLAG_KJH_MEGA_GUARDIAN_DONE) and never a never-sold stone; a caught one holding it brings it
// along. A family's first branch counts (Ralts: Gardevoirite); the PC isn't searched for a stone the player has.
void BS_KjhTryAlphaStoneDrop(void);
// callnative NATIVE_ARGS(const u8 *jumpInstr): the Mega Evolving Pokemon is wild (its own "reacting" line)
void BS_KjhJumpIfWildMega(void);

// Trainers (src/kjh_progression.c): a boss's ace gets its stone when the player's bracelet works here
void KJH_GiveBossAceMegaStone(struct Pokemon *mon, const struct TrainerMon *in, const struct Trainer *trainer);

#endif // GUARD_KJH_MEGA_H
