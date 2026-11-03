#ifndef GUARD_KJH_BATTLE_SCENES_H
#define GUARD_KJH_BATTLE_SCENES_H

#include "battle_transition.h"

struct Trainer;

// KJH: battle presentation after Pokemon Unbound (ENG-7, docs/FEATURES.md "Battle scenes" in the KJH repo).
// Every boss (KJH_IsBossTrainer: gym leaders, the Elite Four, champions, rivals, team bosses) opens its battle with
// the mugshot transition and its own picture. A trainer with its own Mugshot color in its party file (the Elite Four,
// the champion) keeps it; the other bosses get a banner by their kind, as in KJH's pokefirered tree: gym leaders
// green (Bruno's), team bosses pink (Agatha's), rivals and champions yellow (Blue's). Others have none.
enum MugshotColor KJH_BossMugshotColor(const struct Trainer *trainer, u16 trainerNum);
// The same, by trainer number (GetTrainerBattleTransition and the mugshot's banner)
enum MugshotColor KJH_TrainerMugshotColor(u16 trainerNum);

#endif // GUARD_KJH_BATTLE_SCENES_H
