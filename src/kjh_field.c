// KJH: the field bonus (LV-14, include/kjh_field.h).
#include "global.h"
#include "battle.h"
#include "battle_main.h"
#include "battle_setup.h"
#include "battle_util.h"
#include "decompress.h"
#include "graphics.h"
#include "kjh_field.h"
#include "kjh_masters.h"
#include "malloc.h"
#include "palette.h"
#include "pokemon.h"
#include "pokemon_summary_screen.h"
#include "window.h"

#include "data/kjh_fields.h"

static EWRAM_DATA struct KjhField sBattleField = {0};

// docs/LEVELLESS_DESIGN.md §8: building, plain and short grass are neutral (Hoenn's very tall grass is Grass)
enum Type KJH_FieldTypeFromEnvironment(enum BattleEnvironments environment)
{
    switch (environment)
    {
    case BATTLE_ENVIRONMENT_WATER:
    case BATTLE_ENVIRONMENT_POND:
    case BATTLE_ENVIRONMENT_UNDERWATER:
        return TYPE_WATER;
    case BATTLE_ENVIRONMENT_LONG_GRASS:
        return TYPE_GRASS;
    case BATTLE_ENVIRONMENT_CAVE:
    case BATTLE_ENVIRONMENT_MOUNTAIN:
        return TYPE_ROCK;
    case BATTLE_ENVIRONMENT_SAND:
        return TYPE_GROUND;
    default:
        return TYPE_NONE;
    }
}

// A map set by hand wins over the environment, wherever the player stands on it
struct KjhField KJH_FieldForMap(u16 mapId, enum BattleEnvironments environment)
{
    struct KjhField field = {.type = KJH_FieldTypeFromEnvironment(environment), .boostOnly = FALSE};

    for (u32 i = 0; i < ARRAY_COUNT(sKjhFieldMaps); i++)
    {
        if (sKjhFieldMaps[i].mapId == mapId)
            return sKjhFieldMaps[i].field;
    }

    return field;
}

// The field's own type always gets x1.2, never x0.8: Ghost and Dragon are super effective against themselves
uq4_12_t KJH_FieldMoveModifier(struct KjhField field, enum Type moveType)
{
    if (field.type == TYPE_NONE || moveType == TYPE_NONE || moveType == TYPE_MYSTERY)
        return UQ_4_12(1.0);
    if (moveType == field.type)
        return UQ_4_12(1.2);
    if (!field.boostOnly && GetTypeModifier(field.type, moveType) == UQ_4_12(2.0))
        return UQ_4_12(0.8);
    return UQ_4_12(1.0);
}

// With no field the weather's own modifier comes back unchanged (it is never above x1.5)
uq4_12_t KJH_CapWeatherAndField(uq4_12_t weatherModifier, uq4_12_t fieldModifier)
{
    uq4_12_t modifier = uq4_12_multiply(weatherModifier, fieldModifier);

    if (modifier > UQ_4_12(1.5))
        return UQ_4_12(1.5);
    return modifier;
}

static const u8 *const sFieldStartMessages[NUMBER_OF_MON_TYPES] =
{
    [TYPE_NORMAL]   = COMPOUND_STRING("The place feels calm and plain.\nNormal moves are boosted here!"),
    [TYPE_FIGHTING] = COMPOUND_STRING("A fighting spirit fills the air!\nFighting moves are boosted here!"),
    [TYPE_FLYING]   = COMPOUND_STRING("A strong wind is blowing!\nFlying moves are boosted here!"),
    [TYPE_POISON]   = COMPOUND_STRING("A toxic haze hangs in the air!\nPoison moves are boosted here!"),
    [TYPE_GROUND]   = COMPOUND_STRING("The ground is soft and sandy!\nGround moves are boosted here!"),
    [TYPE_ROCK]     = COMPOUND_STRING("Rocks are all around!\nRock moves are boosted here!"),
    [TYPE_BUG]      = COMPOUND_STRING("The air is buzzing with bugs!\nBug moves are boosted here!"),
    [TYPE_GHOST]    = COMPOUND_STRING("An eerie presence fills the air…\nGhost moves are boosted here!"),
    [TYPE_STEEL]    = COMPOUND_STRING("The air rings with metal!\nSteel moves are boosted here!"),
    [TYPE_FIRE]     = COMPOUND_STRING("The air is scorching hot!\nFire moves are boosted here!"),
    [TYPE_WATER]    = COMPOUND_STRING("Water is all around!\nWater moves are boosted here!"),
    [TYPE_GRASS]    = COMPOUND_STRING("The grass grows thick and wild!\nGrass moves are boosted here!"),
    [TYPE_ELECTRIC] = COMPOUND_STRING("The air crackles with electricity!\nElectric moves are boosted here!"),
    [TYPE_PSYCHIC]  = COMPOUND_STRING("A strange power fills the air!\nPsychic moves are boosted here!"),
    [TYPE_ICE]      = COMPOUND_STRING("A freezing cold fills the air!\nIce moves are boosted here!"),
    [TYPE_DRAGON]   = COMPOUND_STRING("A draconic aura fills the air!\nDragon moves are boosted here!"),
    [TYPE_DARK]     = COMPOUND_STRING("A deep darkness covers the field…\nDark moves are boosted here!"),
    [TYPE_FAIRY]    = COMPOUND_STRING("A sweet, mystic air drifts by!\nFairy moves are boosted here!"),
};

const u8 *KJH_FieldStartMessage(enum Type fieldType)
{
    if (fieldType >= NUMBER_OF_MON_TYPES)
        return NULL;
    return sFieldStartMessages[fieldType];
}

// As MAP_* constants are built: num | group << 8 (constants/map_groups.h)
static u16 GetCurrentMapId(void)
{
    return gSaveBlock1Ptr->location.mapNum | (gSaveBlock1Ptr->location.mapGroup << 8);
}

// Called once gBattleEnvironment is set (CB2_InitBattleInternal). Link battles have no field: the two players'
// maps can differ. (Recorded battles keep it: expansion's test runner plays its battles as recorded link ones.)
void KJH_FieldStartBattle(void)
{
    sBattleField.type = TYPE_NONE;
    sBattleField.boostOnly = FALSE;
    if (gBattleTypeFlags & BATTLE_TYPE_LINK)
        return;
    sBattleField = KJH_FieldForMap(GetCurrentMapId(), gBattleEnvironment);
    if (KJH_MasterBattleType() != TYPE_NONE) // LV-13: a master's spot has its type, only for its battle
    {
        sBattleField.type = KJH_MasterBattleType();
        sBattleField.boostOnly = FALSE;
    }
}

struct KjhField KJH_GetBattleField(void)
{
    return sBattleField;
}

uq4_12_t KJH_BattleFieldModifier(enum Type moveType)
{
    return KJH_FieldMoveModifier(sBattleField, moveType);
}

// The Safari Zone has no damage, so no message there
bool32 KJH_ShouldShowFieldMessage(void)
{
    return !(gBattleTypeFlags & BATTLE_TYPE_SAFARI) && KJH_FieldStartMessage(sBattleField.type) != NULL;
}

// The field a battle would get where the player stands now
enum Type KJH_FieldTypeHere(void)
{
    return KJH_FieldForMap(GetCurrentMapId(), BattleSetup_GetEnvironmentId()).type;
}

// The icon is the type's Summary icon (32x16) in a window of its own on BG0, right of the pop-up's frame, so it
// slides with the pop-up. It uses the tiles of the Gen 5 pop-up's second window, which the Gen 3 pop-up never has.
#define POPUP_ICON_LEFT        12      // tiles: the pop-up's window is at 1..10, its frame at 0 and 11
#define POPUP_ICON_TOP         1       // the pop-up window's rows, 1..3
#define POPUP_ICON_ROWS        3
#define POPUP_ICON_PALETTE     13
#define POPUP_ICON_BASE_BLOCK  0x161   // AddSecondaryPopUpWindow's (menu.c)
#define TYPE_ICON_WIDTH        32      // the Summary's type icons (gSpriteSheet_MoveTypes): 4x2 tiles each,
#define TYPE_ICON_HEIGHT       16      // in type order
#define TYPE_ICON_BYTES        (TYPE_ICON_WIDTH * TYPE_ICON_HEIGHT / 2)
#define TYPE_ICON_TOP          ((POPUP_ICON_ROWS * TILE_HEIGHT - TYPE_ICON_HEIGHT) / 2)
#define TYPE_ICON_FIRST_PAL    13      // gTypesInfo[].palette counts from the OBJ palette the Summary loads them at

u8 KJH_FieldShowPopUpIcon(void)
{
    enum Type type = KJH_FieldTypeHere();
    struct WindowTemplate template =
    {
        .bg = 0,
        .tilemapLeft = POPUP_ICON_LEFT,
        .tilemapTop = POPUP_ICON_TOP,
        .width = TYPE_ICON_WIDTH / TILE_WIDTH,
        .height = POPUP_ICON_ROWS,
        .paletteNum = POPUP_ICON_PALETTE,
        .baseBlock = POPUP_ICON_BASE_BLOCK,
    };
    u8 windowId;
    u8 *icons;

    if (type == TYPE_NONE || type >= NUMBER_OF_MON_TYPES)
        return WINDOW_NONE;
    icons = Alloc(gSpriteSheet_MoveTypes.size);
    if (icons == NULL)
        return WINDOW_NONE;
    windowId = AddWindow(&template);
    if (windowId == WINDOW_NONE)
    {
        Free(icons);
        return WINDOW_NONE;
    }

    DecompressDataWithHeaderWram(gSpriteSheet_MoveTypes.data, icons);
    FillWindowPixelBuffer(windowId, PIXEL_FILL(0));
    BlitBitmapToWindow(windowId, icons + type * TYPE_ICON_BYTES, 0, TYPE_ICON_TOP, TYPE_ICON_WIDTH, TYPE_ICON_HEIGHT);
    Free(icons);
    LoadPalette(&gMoveTypes_Pal[PLTT_ID(gTypesInfo[type].palette - TYPE_ICON_FIRST_PAL)],
                BG_PLTT_ID(POPUP_ICON_PALETTE), PLTT_SIZE_4BPP);
    PutWindowTilemap(windowId);
    CopyWindowToVram(windowId, COPYWIN_FULL);
    return windowId;
}

void KJH_FieldHidePopUpIcon(u8 windowId)
{
    if (windowId == WINDOW_NONE)
        return;
    ClearWindowTilemap(windowId);
    CopyWindowToVram(windowId, COPYWIN_MAP);
    RemoveWindow(windowId);
}
