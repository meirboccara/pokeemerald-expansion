#ifndef GUARD_KJH_FIELD_H
#define GUARD_KJH_FIELD_H

#include "constants/battle.h"
#include "fpmath.h"

// KJH: the field bonus (LV-14, docs/LEVELLESS_DESIGN.md §8 in the KJH repo). A battle fought on a field of type X
// gives X-type moves x1.2 and the types X is super effective against x0.8, for both sides. The field comes from the
// map (sKjhFieldMaps, src/data/kjh_fields.h: Gyms, Elite Four rooms, a few special places), else from the battle
// environment (water, cave, sand...). Weather and field together are capped at x1.5.

struct KjhField
{
    enum Type type;    // TYPE_NONE: no field
    bool8 boostOnly;   // the first 2 Gyms of a region: only the x1.2 part
};

// Rules (no game state)
enum Type KJH_FieldTypeFromEnvironment(enum BattleEnvironments environment);
struct KjhField KJH_FieldForMap(u16 mapId, enum BattleEnvironments environment);
uq4_12_t KJH_FieldMoveModifier(struct KjhField field, enum Type moveType);
uq4_12_t KJH_CapWeatherAndField(uq4_12_t weatherModifier, uq4_12_t fieldModifier);
const u8 *KJH_FieldStartMessage(enum Type fieldType);

// The battle's field, set when a battle starts
void KJH_FieldStartBattle(void);
struct KjhField KJH_GetBattleField(void);
uq4_12_t KJH_BattleFieldModifier(enum Type moveType);
bool32 KJH_ShouldShowFieldMessage(void);

// The area-name pop-up's field icon (src/map_name_popup.c). Show returns the icon's window, or WINDOW_NONE.
enum Type KJH_FieldTypeHere(void);
u8 KJH_FieldShowPopUpIcon(void);
void KJH_FieldHidePopUpIcon(u8 windowId);

#endif // GUARD_KJH_FIELD_H
