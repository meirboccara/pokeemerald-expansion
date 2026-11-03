#ifndef GUARD_KJH_LEVELLESS_H
#define GUARD_KJH_LEVELLESS_H

// KJH (LV-1): the levels-free design (docs/LEVELLESS_DESIGN.md). Each Pokémon carries a few values of its own, read
// and written with GetMonData/SetMonData:
//   MON_DATA_PEAK_LEVEL      the highest hidden level it has reached (0 = not recorded yet), up to 100
//   MON_DATA_TRAINING_BANK   its unspent Training points, 0..KJH_TRAINING_BANK_MAX
//   MON_DATA_TRAINING_HALF   a half Training point waiting for its other half, 0 or 1
//   MON_DATA_PEAK_BOND       the highest Bond it has reached (0 = not recorded yet), up to KJH_BOND_MAX
//   MON_DATA_TIER_MARK       enum KjhTierMark
// They live in four of FireRed's unused contest bytes (struct PokemonSubstruct2), so the save size is unchanged.
// A value above its limit is stored as the limit. SetMonData reads one byte for each value, two for the bank.

#define KJH_PEAK_LEVEL_MAX    100
#define KJH_TRAINING_BANK_MAX 630
#define KJH_BOND_MAX          20

enum KjhTierMark
{
    KJH_TIER_REGULAR,
    KJH_TIER_LEADER,
    KJH_TIER_ALPHA,
    KJH_TIER_COUNT,
};

#endif // GUARD_KJH_LEVELLESS_H
