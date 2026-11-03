#ifndef GUARD_KJH_BOND_H
#define GUARD_KJH_BOND_H

// KJH (LV-5): Bond 1-20, the levels-free design's friendship scale (docs/LEVELLESS_DESIGN.md §3). Bond is stored as
// friendship: 70 = Bond 1, 255 = Bond 20, about 10 points a step. Gains and losses are in friendship points.
// The peak Bond (MON_DATA_PEAK_BOND, LV-1) follows every rise of friendship (SetBoxMonData) and never goes down.

#define KJH_BOND_MIN_FRIENDSHIP 70        // Bond 1
#define KJH_STARTER_BOND        5

// Gains, for each Pokemon on its own (a Soothe Bell makes them x1.5, rounded down)
#define KJH_BOND_GAIN_FOE       2         // a foe it fought is knocked out or caught
#define KJH_BOND_GAIN_WIN       1         // a battle won (or a catch) it fought in
#define KJH_BOND_GAIN_BOSS_WIN  3         // instead, against a Gym Leader or another boss
#define KJH_BOND_GAIN_WALK      1         // every KJH_BOND_WALK_STEPS steps in the party
#define KJH_BOND_WALK_STEPS     256
// Losses
#define KJH_BOND_LOSS_FAINT     20        // it faints (in battle, or from poison outside)
#define KJH_BOND_LOSS_WHITEOUT  50        // the player whites out: the whole party
#define KJH_BOND_LOSS_PC_WEEK   20        // each in-game week in a PC box (CF-4's clock: 7 days)
#define KJH_BOND_LOSS_DAYCARE   20        // once, when picked up from a Day Care

struct Pokemon;
struct BoxPokemon;

// The scale
u32 KJH_FriendshipToBond(u32 friendship);
u32 KJH_BondToFriendship(u32 bond);       // the least friendship with that Bond
u32 KJH_GetBond(struct Pokemon *mon);
u32 KJH_GetPeakBond(struct Pokemon *mon); // at least the current Bond
// The least friendship PC and Day Care losses leave: half the peak Bond, rounded up
u32 KJH_BondFloorFriendship(u32 peakBond);

// The rules, each on one Pokemon
void KJH_GainBond(struct Pokemon *mon, u32 points);
void KJH_LoseBond(struct Pokemon *mon, u32 points);              // down to Bond 1
void KJH_LoseBondFloored(struct Pokemon *mon, u32 points);       // down to half the peak Bond
void KJH_BoxMonLoseBondFloored(struct BoxPokemon *boxMon, u32 points);

// The hooks
void KJH_BondOnFoeDown(u32 sentInBits);   // each party Pokemon in sentInBits fought a foe that fell or was caught
void KJH_BondAfterBattle(void);           // battle won or caught: everyone sent out; whiteouts lose separately
void KJH_BondOnWhiteOut(void);
void KJH_BondPcWeeks(u32 weeks);          // every boxed Pokemon, once per in-game week passed
void KJH_BondOnDaycarePickup(struct Pokemon *mon);
s32 KJH_BondFriendshipEvent(u32 event);   // AdjustFriendship's points for a vanilla event, or 0 (none)
void KJH_SetStarterBond(void);            // special: the last party Pokemon starts at Bond KJH_STARTER_BOND

// The milestones (§3) and the Summary's BOND page. A one-time unlock is kept at the peak Bond; an ongoing perk
// follows the current Bond.
struct KjhBondMilestone
{
    u8 bond;
    bool8 keptAtPeak;
    const u8 *name;
};
#define KJH_BOND_MILESTONE_COUNT 9
extern const struct KjhBondMilestone gKjhBondMilestones[KJH_BOND_MILESTONE_COUNT];
bool32 KJH_IsBondMilestoneUnlocked(u32 bond, u32 peakBond, u32 milestone);
u32 KJH_NextBondMilestone(u32 bond, u32 peakBond);           // KJH_BOND_MILESTONE_COUNT when all are unlocked
u32 KJH_BondPercentToMilestone(u32 friendship, u32 milestone); // 0-99: how far from this Bond step to it
void KJH_FormatBondPage(struct Pokemon *mon, u8 *dest);      // the page's lines, one per text line

#endif // GUARD_KJH_BOND_H
