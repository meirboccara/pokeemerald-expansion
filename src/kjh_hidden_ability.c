// KJH: Hidden Abilities (ENG-7, include/kjh_hidden_ability.h).
#include "global.h"
#include "event_data.h"
#include "kjh_hidden_ability.h"
#include "kjh_team_level.h"
#include "pokemon.h"
#include "random.h"
#include "script.h"
#include "string_util.h"

static const u8 sText_HiddenMark[] = _(" (HIDDEN)");

enum Ability KJH_HiddenAbility(enum Species species)
{
    enum Ability hidden = GetSpeciesAbility(species, KJH_ABILITY_NUM_HIDDEN);

    for (u32 slot = 0; slot < NUM_NORMAL_ABILITY_SLOTS; slot++)
    {
        if (hidden == GetSpeciesAbility(species, slot)) return ABILITY_NONE;
    }
    return hidden;
}

u32 KJH_AbilityChoices(enum Species species, u8 *nums)
{
    u32 count = 0;
    enum Ability first = GetSpeciesAbility(species, 0);
    enum Ability second = GetSpeciesAbility(species, 1);

    nums[count++] = 0;
    if (second != ABILITY_NONE && second != first)
    {
        nums[count++] = 1;
    }

    if (KJH_HiddenAbility(species) != ABILITY_NONE)
    {
        nums[count++] = KJH_ABILITY_NUM_HIDDEN;
    }

    return count;
}

void KJH_RollWildHiddenAbility(struct Pokemon *mon)
{
    u32 abilityNum = KJH_ABILITY_NUM_HIDDEN;

    if (KJH_HiddenAbility(GetMonData(mon, MON_DATA_SPECIES)) == ABILITY_NONE) return;
    // Outcome 0 has it, so a test that doesn't set RNG_KJH_HIDDEN_ABILITY (its default is the last outcome) never
    // meets one
    if (RandomWeighted(RNG_KJH_HIDDEN_ABILITY, 1, KJH_HIDDEN_ABILITY_WILD_ODDS - 1) != 0) return;
    SetMonData(mon, MON_DATA_ABILITY_NUM, &abilityNum);
}

u32 KJH_BossAbilityNum(enum Species species, u32 abilityNum)
{
    switch (KJH_HiddenAbility(species))
    {
    case ABILITY_NONE:
    case ABILITY_RUN_AWAY:
    case ABILITY_PICKUP:
    case ABILITY_HONEY_GATHER:
    case ABILITY_BALL_FETCH:
        return abilityNum;
    default:
        return KJH_ABILITY_NUM_HIDDEN;
    }
}

void KJH_ScriptIsAbilitySwitchUnlocked(struct ScriptContext *ctx)
{
    Script_RequestEffects(SCREFF_V1);
    gSpecialVar_Result = KJH_CountKantoBadges() >= KJH_ABILITY_SWITCH_BADGES; // only Kanto's badges so far
}

void KJH_ScriptBufferAbilityChoices(struct ScriptContext *ctx)
{
    u8 *const names[KJH_MAX_ABILITY_CHOICES] = {gStringVar1, gStringVar2, gStringVar3};
    enum Species species = GetMonData(&gPlayerParty[gSpecialVar_0x8004], MON_DATA_SPECIES);
    u8 nums[KJH_MAX_ABILITY_CHOICES];
    u32 count = KJH_AbilityChoices(species, nums);

    Script_RequestEffects(SCREFF_V1);
    for (u32 i = 0; i < count; i++)
    {
        u8 *end = StringCopy(names[i], gAbilitiesInfo[GetSpeciesAbility(species, nums[i])].name);

        if (nums[i] == KJH_ABILITY_NUM_HIDDEN)
        {
            StringCopy(end, sText_HiddenMark);
        }
    }

    gSpecialVar_Result = count;
}

void KJH_ScriptSetChosenAbility(struct ScriptContext *ctx)
{
    struct Pokemon *mon = &gPlayerParty[gSpecialVar_0x8004];
    u8 nums[KJH_MAX_ABILITY_CHOICES];
    u32 count = KJH_AbilityChoices(GetMonData(mon, MON_DATA_SPECIES), nums);
    u32 abilityNum;

    Script_RequestEffects(SCREFF_V1 | SCREFF_SAVE);
    if (gSpecialVar_0x8005 >= count)
    {
        gSpecialVar_Result = KJH_ABILITY_SAME;
        return;
    }

    abilityNum = nums[gSpecialVar_0x8005];
    if (abilityNum == GetMonData(mon, MON_DATA_ABILITY_NUM))
    {
        gSpecialVar_Result = KJH_ABILITY_SAME;
        return;
    }
    SetMonData(mon, MON_DATA_ABILITY_NUM, &abilityNum);
    gSpecialVar_Result = abilityNum == KJH_ABILITY_NUM_HIDDEN ? KJH_ABILITY_HIDDEN : KJH_ABILITY_CHANGED;
}
