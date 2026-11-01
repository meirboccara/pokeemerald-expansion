#ifndef GUARD_KJH_BOSS_RULES_H
#define GUARD_KJH_BOSS_RULES_H

#include "gba/types.h"

// KJH: rules for boss trainers (gym leaders, Elite Four, champions, rivals, team bosses), after Pokemon
// Unbound (docs/UNBOUND_RESEARCH.md). src/kjh_progression.c and src/kjh_battle_scenes.c apply them. No GBA
// dependencies, so they are unit-tested on the host (kjh_tools/test/test_boss_rules.c).

// A boss Pokemon's EVs grow with the player's badges: 252 x (badges + 1) / 9 in each of its two stats, so 28 at
// the first gym, full (252) from this many badges on
#define KJH_BOSS_FULL_EV_BADGES 8

// baseStats: the species' base stats in STAT_* order. physicalPower / specialPower: the summed base power of
// its damaging moves, split the Gen 3 way (by type). It puts EVs in the stat it attacks with (by its moves;
// by base stats when it has no damaging move) and in its best other stat (HP, Defense, Speed, Sp. Def);
// evs[NUM_STATS] gets them.
void KJH_BossEvs(const u8 *baseStats, u16 physicalPower, u16 specialPower, u8 badges, u8 *evs);
// Its nature (NATURE_*): raises the stat it attacks with; lowers the other attack stat when its moves don't
// use it, else its weaker defence
u8 KJH_BossNature(const u8 *baseStats, u16 physicalPower, u16 specialPower);

// Trainer slides: the boss slides in and says a line (src/kjh_battle_scenes.c)
#define KJH_SLIDE_NONE        0
#define KJH_SLIDE_LAST_MON    1 // its last Pokemon is out
#define KJH_SLIDE_LAST_LOW_HP 2 // and down to a quarter of its HP
// monsLeft: the boss's Pokemon that can still fight; hp / maxHp: the one in battle; shown: bit
// (1 << KJH_SLIDE_*) for each line already said in this battle. Each line comes once.
u8 KJH_SlideToShow(u8 monsLeft, u16 hp, u16 maxHp, u8 shown);

#endif // GUARD_KJH_BOSS_RULES_H
