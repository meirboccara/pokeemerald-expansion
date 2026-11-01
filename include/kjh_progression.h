#ifndef GUARD_KJH_PROGRESSION_H
#define GUARD_KJH_PROGRESSION_H

#include "data.h"
#include "constants/battle_ai.h"

// KJH: trainer levels and boss strategy (src/kjh_progression.c), ported from the KJH repo's pokefirered tree.
// The rules are the same: docs/TRAINER_LEVELS.md in the KJH repo.

// Boss trainers by kind (mugshots, trainer slides); KJH_BOSS_NONE for every other trainer
enum
{
    KJH_BOSS_NONE,
    KJH_BOSS_LEADER,
    KJH_BOSS_ELITE_FOUR,
    KJH_BOSS_CHAMPION,
    KJH_BOSS_RIVAL,      // rivals
    KJH_BOSS_TEAM,       // Giovanni, Archie, Maxie and their admins
    KJH_BOSS_KIND_COUNT
};
u8 KJH_BossKind(u8 trainerClass);
// A boss's strength (level, IVs, EVs, nature, AI, moves). The first rival battle, in Oak's lab, has the
// rival's mugshot and slides but not his strength.
bool32 KJH_IsBossTrainer(const struct Trainer *trainer, u16 trainerNum);

// Building an opponent's party (CreateOpponentTrainerParty, src/battle_setup.c). trainerNum TRAINER_NONE (battle
// partners, the debug menu's own test parties) keeps the trainer data as it is: no boost, nothing changed.
// 1. how many levels the whole team goes up to catch up with the player's party, once per party, from the
//    Pokemon it sends (monIndices: their entries in trainer->party, monsCount of them);
u8 KJH_TeamLevelBoost(const struct Trainer *trainer, u16 trainerNum, const u32 *monIndices, u8 monsCount);
// 2. before each Pokemon is created: its level (band + boost) and, for a team that was raised or moved to
//    another region, no fixed moves, so it gets its level-up moves for its new level;
void KJH_PrepareTrainerMon(struct TrainerMon *out, const struct TrainerMon *in, u16 trainerNum, u8 boost);
// 3. after: a boss's IVs, held item, moveset, EVs and nature.
void KJH_FinishTrainerMon(struct Pokemon *mon, const struct TrainerMon *in, const struct Trainer *trainer, u16 trainerNum, u8 boost);

// A boss's AI: expansion's smart trainer AI, without Terastallization (KJH's trainers don't Terastallize)
#define KJH_BOSS_AI_FLAGS (AI_FLAG_SMART_TRAINER & ~AI_FLAG_SMART_TERA)
// The AI flags an opponent battles with: its own, plus KJH_BOSS_AI_FLAGS for bosses
u64 KJH_AiFlags(u64 baseFlags, u8 trainerClass, u16 trainerNum);

#endif // GUARD_KJH_PROGRESSION_H
