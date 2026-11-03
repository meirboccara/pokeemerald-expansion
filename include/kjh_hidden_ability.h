#ifndef GUARD_KJH_HIDDEN_ABILITY_H
#define GUARD_KJH_HIDDEN_ABILITY_H

#include "constants/abilities.h"
#include "constants/kjh_stat_trainer.h"
#include "constants/pokemon.h"
#include "constants/species.h"

struct Pokemon;
struct ScriptContext;

// KJH: Hidden Abilities (ENG-7, docs/HIDDEN_ABILITIES.md in the KJH repo). A species' Hidden Ability is expansion's
// third ability (MON_DATA_ABILITY_NUM 2). In KJH's pokefirered tree only the 123 species whose Hidden Ability exists
// in Gen 3 had one; expansion's battle engine has them all, so every species with a third ability has it here.
#define KJH_ABILITY_NUM_HIDDEN NUM_NORMAL_ABILITY_SLOTS

// A wild Pokemon has its Hidden Ability 1 time in KJH_HIDDEN_ABILITY_WILD_ODDS (the roll is RNG_KJH_HIDDEN_ABILITY)
#define KJH_HIDDEN_ABILITY_WILD_ODDS 20
// Prof. Oak switches abilities once the player has this many badges in one region (only Kanto's so far)
#define KJH_ABILITY_SWITCH_BADGES 4

// ABILITY_NONE when the species has none, or its third ability is one of its first two
enum Ability KJH_HiddenAbility(enum Species species);
// The abilities a Pokemon can be switched to (stat trainer, Prof. Oak, the ability NPC), as MON_DATA_ABILITY_NUM
// values in nums: first, second (if any), Hidden (if any). Returns how many.
#define KJH_MAX_ABILITY_CHOICES 3
u32 KJH_AbilityChoices(enum Species species, u8 *nums);
// A new wild Pokemon (CreateWildMon, a pack's helper): its Hidden Ability 1 time in KJH_HIDDEN_ABILITY_WILD_ODDS
void KJH_RollWildHiddenAbility(struct Pokemon *mon);
// A boss trainer's Pokemon (KJH_FinishTrainerMon): its MON_DATA_ABILITY_NUM. It uses its Hidden Ability, unless that
// does nothing for a trainer's Pokemon (Run Away, Pickup, Honey Gather, Ball Fetch).
u32 KJH_BossAbilityNum(enum Species species, u32 abilityNum);

// Scripts (data/scripts/kjh_hidden_ability.inc), callnative
// VAR_RESULT: TRUE once the player has KJH_ABILITY_SWITCH_BADGES badges in one region
void KJH_ScriptIsAbilitySwitchUnlocked(struct ScriptContext *ctx);
// For the party Pokemon VAR_0x8004: VAR_RESULT = how many abilities it can have; their names in STR_VAR_1..3, the
// Hidden one marked
void KJH_ScriptBufferAbilityChoices(struct ScriptContext *ctx);
// Gives the party Pokemon VAR_0x8004 its choice VAR_0x8005 (an index into those names). VAR_RESULT: KJH_ABILITY_*
// (include/constants/kjh_stat_trainer.h).
void KJH_ScriptSetChosenAbility(struct ScriptContext *ctx);

#endif // GUARD_KJH_HIDDEN_ABILITY_H
