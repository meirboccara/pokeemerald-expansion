// KJH: battle presentation after Pokemon Unbound (ENG-7, include/kjh_battle_scenes.h).
#include "global.h"
#include "data.h"
#include "kjh_battle_scenes.h"
#include "kjh_progression.h"

enum MugshotColor KJH_BossMugshotColor(const struct Trainer *trainer, u16 trainerNum)
{
    if (trainer->mugshotColor != MUGSHOT_COLOR_NONE) return trainer->mugshotColor;
    if (!KJH_IsBossTrainer(trainer, trainerNum)) return MUGSHOT_COLOR_NONE;

    switch (KJH_BossKind(trainer->trainerClass))
    {
    case KJH_BOSS_LEADER:
        return MUGSHOT_COLOR_GREEN;
    case KJH_BOSS_ELITE_FOUR:
        return MUGSHOT_COLOR_PURPLE;
    case KJH_BOSS_TEAM:
        return MUGSHOT_COLOR_PINK;
    case KJH_BOSS_CHAMPION:
    case KJH_BOSS_RIVAL:
        return MUGSHOT_COLOR_YELLOW;
    default:
        return MUGSHOT_COLOR_NONE; // not a boss: KJH_IsBossTrainer said otherwise
    }
}

enum MugshotColor KJH_TrainerMugshotColor(u16 trainerNum)
{
    return KJH_BossMugshotColor(GetTrainerStructFromId(trainerNum), trainerNum);
}
