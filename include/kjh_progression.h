#ifndef GUARD_KJH_PROGRESSION_H
#define GUARD_KJH_PROGRESSION_H

#include "data.h"
#include "constants/battle_ai.h"

// KJH: trainer levels and boss strategy (src/kjh_progression.c). Trainers' levels come from the zones of the
// levels-free design (LV-3, kjh_tools/zone_levels.py rewrites src/data/trainers_frlg.party); a Gym Leader's team
// follows the player's badges.

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
// partners, the debug menu's own test parties) keeps the trainer data as it is: no shift, nothing changed.
// 1. how many levels the whole team moves, once per party: in the levels-free game, a Gym's trainers move with
//    the player's badges (KJH_GymLevelShift); 0 for everyone else;
s32 KJH_TeamLevelShift(u16 trainerNum);
// 2. before each Pokemon is created: its level (+ shift) and, for a moved team, no fixed moves, so it gets its
//    level-up moves for its new level;
void KJH_PrepareTrainerMon(struct TrainerMon *out, const struct TrainerMon *in, u16 trainerNum, s32 shift);
// 3. after: a boss's held item and moveset; in the levels-free game every trainer's IVs, EVs and Bond from its
//    group's table (LV-16, KJH_TrainerTraining; ace: the team's highest level), else a boss's IVs, EVs and nature.
void KJH_FinishTrainerMon(struct Pokemon *mon, const struct TrainerMon *in, const struct Trainer *trainer,
                          u16 trainerNum, s32 shift, bool32 ace);

// A boss's AI: expansion's smart trainer AI, without Terastallization (KJH's trainers don't Terastallize)
#define KJH_BOSS_AI_FLAGS (AI_FLAG_SMART_TRAINER & ~AI_FLAG_SMART_TERA)
// The AI flags an opponent battles with: its own, plus KJH_BOSS_AI_FLAGS for bosses
u64 KJH_AiFlags(u64 baseFlags, u8 trainerClass, u16 trainerNum);

#endif // GUARD_KJH_PROGRESSION_H
