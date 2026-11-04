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
#define KJH_BOND_LOSS_FAINT     10        // it faints (in battle, or from poison outside): -1 Bond
#define KJH_BOND_LOSS_WHITEOUT  30        // the player whites out: the whole party, -3 Bond...
#define KJH_BOND_WHITEOUT_MIN_PARTY 3     // ...only with 3 Pokemon or more (a lone partner already paid its faint)
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

#define KJH_BOND_CARE_MAX 10 // displayed Bond points, not friendship units
#define KJH_BOND_CARE_PRICE 500

enum KjhBondCareStatus
{
    KJH_BOND_CARE_OK,
    KJH_BOND_CARE_NO_LOSS,
    KJH_BOND_CARE_NO_CLOCK,
    KJH_BOND_CARE_USED,
    KJH_BOND_CARE_NO_MONEY,
};
bool32 KJH_BondBattleProtected(void);
u32 KJH_BondCareRecovery(struct Pokemon *mon);
bool32 KJH_BondCareDayAvailable(u32 seconds);
void KJH_PreviewBondCare(void); // selected party slot in VAR_0x8004, status in VAR_RESULT
void KJH_ApplyBondCare(void);

// The hooks
void KJH_BondOnFoeDown(u32 sentInBits);   // each party Pokemon in sentInBits fought a foe that fell or was caught
void KJH_BondAfterBattle(void);           // battle won or caught: everyone sent out; whiteouts lose separately
void KJH_BondOnWhiteOut(void);
void KJH_BondRecalculatePartyStats(void);  // LV-6: once a battle is over, the stat bonus follows the new Bond
void KJH_BondPcWeeks(u32 weeks);          // every boxed Pokemon, once per in-game week passed
void KJH_BondOnDaycarePickup(struct Pokemon *mon);
s32 KJH_BondFriendshipEvent(u32 event);   // AdjustFriendship's points for a vanilla event, or 0 (none)
void KJH_SetStarterBond(void);            // special: the last party Pokemon starts at Bond KJH_STARTER_BOND

// LV-6: the perks. Ongoing perks follow the current Bond, for the player's Pokemon and trainers' (not wild ones');
// hard mode (expansion's DIFFICULTY_HARD) turns them all off.
#define KJH_BOND_STATS_SMALL    5         // stats +2% (at least +1)
#define KJH_BOND_STATS_BIG      15        // stats +5% instead (at least +1)
#define KJH_BOND_EMOTIONS       3         // the follower shows emotions
#define KJH_BOND_SHAKE_CONFUSION 10       // end of turn: sometimes snaps out of confusion or infatuation
#define KJH_BOND_SHAKE_STATUS   19        // end of turn: sometimes shakes off a status
#define KJH_BOND_SHAKE_CONFUSION_CHANCE 25 // %
#define KJH_BOND_SHAKE_STATUS_CHANCE    20 // %, as expansion's affection status heal
bool32 KJH_BondPerksOn(void);
s32 KJH_BondStatBonus(s32 stat, u32 friendship);     // what CalculateMonStats adds to a stat
bool32 KJH_HasBondEmotions(struct Pokemon *mon);
enum KjhBondShake
{
    KJH_BOND_SHAKE_NONE,
    KJH_BOND_SHAKE_OFF_STATUS,
    KJH_BOND_SHAKE_OFF_CONFUSION,
    KJH_BOND_SHAKE_OFF_INFATUATION,
};
enum KjhBondShake KJH_TryBondShake(u32 battler);     // the end-of-turn perk, rolled; the caller runs its script

// LV-4: no level shown. While the levels-free design is on (FLAG_KJH_LEVELLESS), no Pokemon shows a level. The Bond
// is shown on the Summary only ("BOND 12" where the level was, and the BOND page); the party menu, the PC, the Day
// Care and the battle healthbox show neither (playtest, 2026-11-04).
bool32 KJH_HideLevels(void);
u8 *KJH_BufferBondLabel(u8 *dest, u32 friendship); // "BOND 12"

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
