#ifndef GUARD_KJH_LEGENDARY_H
#define GUARD_KJH_LEGENDARY_H

#include "constants/species.h"

struct ScriptContext;

// KJH: a legendary met in a set place fights as a boss (CF-12; the rule is in docs/LEGENDARIES.md in the KJH
// repo). Its battle starts with a totem aura, +1 to its two highest stats, and it fights with the boss trainers'
// AI (KJH_BOSS_AI_FLAGS). Only for that one battle: stat stages end with the battle, and so does the AI.

// The aura's two stats: the species' two highest base stats, HP not counted. A tie goes to the stat that comes
// first in STAT_* order (Attack, Defense, Speed, Sp. Atk, Sp. Def). Returns a (1 << STAT_*) bit for each.
u32 KJH_LegendaryBoostedStats(enum Species species);

// The next battle is a legendary boss battle with this species as the wild Pokemon: queues its aura (on
// B_POSITION_OPPONENT_LEFT) and turns on the boss AI. A script does it with kjh_legendaryboss, after setwildbattle,
// right before the battle starts.
void KJH_SetupLegendaryBoss(enum Species species);
void KJH_ScriptSetupLegendaryBoss(struct ScriptContext *ctx);

// TRUE from KJH_SetupLegendaryBoss to the end of the battle (FreeBattleResources calls KJH_EndLegendaryBossBattle).
bool32 KJH_IsLegendaryBossBattle(void);
void KJH_EndLegendaryBossBattle(void);

// A wild battle's AI flags (GetWildAiFlags, src/battle_ai_main.c): the wild ones, plus KJH_BOSS_AI_FLAGS in a
// legendary boss battle.
u64 KJH_LegendaryWildAiFlags(u64 wildFlags);

#endif // GUARD_KJH_LEGENDARY_H
