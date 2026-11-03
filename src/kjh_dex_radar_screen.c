// KJH (ENG-8, CF-7): the route radar's screen (include/kjh_dex_radar.h), opened with R from the Pokedex list. The
// first page lists the routes of the regions reached, by region, with how many of their species are caught and a
// SWARM mark on today's swarm routes; A on a route lists its wild Pokemon by method with their chance. Species never
// seen show as ?????; caught ones get the Pokedex's Poke Ball. B goes back (to the Pokedex from the route list).
#include "global.h"
#include "bg.h"
#include "gpu_regs.h"
#include "graphics.h"
#include "kjh_dex_radar.h"
#include "list_menu.h"
#include "main.h"
#include "malloc.h"
#include "menu.h"
#include "overworld.h"
#include "palette.h"
#include "pokedex.h"
#include "pokedex_common.h"
#include "region_map.h"
#include "scanline_effect.h"
#include "sound.h"
#include "sprite.h"
#include "string_util.h"
#include "task.h"
#include "text.h"
#include "window.h"
#include "constants/rgb.h"
#include "constants/songs.h"

#define RADAR_NAME_LENGTH 20
#define RADAR_MAX_SHOWED  8
#define RADAR_BALL_X      128 // the Poke Ball column
#define RADAR_SWARM_X     144 // the SWARM mark on the route list
#define RADAR_RIGHT_EDGE  220 // counts and chances end here (the scroll arrows are right of it)
#define RADAR_REGION_ROWS 4   // room for each region's header on the route list

// Colors of the Pokedex's background palette (graphics/pokedex/bg_national.pal), which the caught ball is drawn for
#define COLOR_PAPER  0  // white here: the backdrop is set to it
#define COLOR_BAND   6  // the title and controls bands
#define COLOR_TEXT   6
#define COLOR_SHADOW 3
#define COLOR_LIGHT  1
#define COLOR_SWARM  11 // pink

enum
{
    WIN_TITLE,
    WIN_LIST,
    WIN_CONTROLS,
};

struct RadarScreen
{
    void (*returnCallback)(void);
    struct KjhRadarRoute routes[KJH_RADAR_MAX_ROUTES];
    u8 routeNames[KJH_RADAR_MAX_ROUTES][RADAR_NAME_LENGTH];
    struct ListMenuItem routeItems[KJH_RADAR_MAX_ROUTES + RADAR_REGION_ROWS];
    struct KjhRadarEntry entries[KJH_RADAR_MAX_ENTRIES];
    struct ListMenuItem entryItems[KJH_RADAR_MAX_ENTRIES + KJH_RADAR_METHOD_COUNT];
    u16 numRouteItems;
    u16 numEntryItems;
    u16 routeScroll;
    u16 routeRow;
    u16 route;       // routes[] index of the open route
    u16 scrollOffset;
    u8 listTaskId;
    u8 arrowsTaskId;
    bool8 onRoutePage;
};

static EWRAM_DATA struct RadarScreen *sRadar = NULL;
static EWRAM_DATA void *sTilemapBuffer = NULL;

static const u8 sText_RouteRadar[] = _("ROUTE RADAR");
static const u8 sText_RouteListControls[] = _("{A_BUTTON}ROUTE  {B_BUTTON}POKéDEX");
static const u8 sText_RoutePageControls[] = _("{DPAD_UPDOWN}SCROLL  {B_BUTTON}ROUTES");
static const u8 sText_Swarm[] = _("SWARM");
static const u8 sText_NoRoutes[] = _("No route yet.");

static const u8 *const sMethodNames[KJH_RADAR_METHOD_COUNT] =
{
    [KJH_RADAR_SWARM_LAND]    = COMPOUND_STRING("TODAY'S SWARM: GRASS"),
    [KJH_RADAR_SWARM_FISHING] = COMPOUND_STRING("TODAY'S SWARM: FISHING"),
    [KJH_RADAR_GRASS]         = COMPOUND_STRING("LAND"),
    [KJH_RADAR_SURF]          = COMPOUND_STRING("SURFING"),
    [KJH_RADAR_OLD_ROD]       = COMPOUND_STRING("OLD ROD"),
    [KJH_RADAR_GOOD_ROD]      = COMPOUND_STRING("GOOD ROD"),
    [KJH_RADAR_SUPER_ROD]     = COMPOUND_STRING("SUPER ROD"),
    [KJH_RADAR_ROCK_SMASH]    = COMPOUND_STRING("ROCK SMASH"),
    [KJH_RADAR_HEADBUTT]      = COMPOUND_STRING("HEADBUTT"),
    [KJH_RADAR_HEADBUTT_RARE] = COMPOUND_STRING("HEADBUTT: RARE TREES"),
};

static const struct BgTemplate sBgTemplates[] =
{
    {
        .bg = 0,
        .charBaseIndex = 0,
        .mapBaseIndex = 31,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0,
    },
};

static const struct WindowTemplate sWindowTemplates[] =
{
    [WIN_TITLE]    = {.bg = 0, .tilemapLeft = 0, .tilemapTop = 0,  .width = 30, .height = 2,  .paletteNum = 0, .baseBlock = 1},
    [WIN_LIST]     = {.bg = 0, .tilemapLeft = 0, .tilemapTop = 2,  .width = 30, .height = 16, .paletteNum = 0, .baseBlock = 61},
    [WIN_CONTROLS] = {.bg = 0, .tilemapLeft = 0, .tilemapTop = 18, .width = 30, .height = 2,  .paletteNum = 0, .baseBlock = 541},
    DUMMY_WIN_TEMPLATE,
};

static const u8 sBandColors[] = {COLOR_BAND, COLOR_LIGHT, COLOR_SHADOW};
static const u8 sSwarmColors[] = {COLOR_PAPER, COLOR_SWARM, COLOR_SHADOW};
static const u8 sTextColors[] = {COLOR_PAPER, COLOR_TEXT, COLOR_SHADOW};

static void CB2_InitRadar(void);
static void Task_RadarInput(u8 taskId);
static void Task_RadarExit(u8 taskId);

void KJH_OpenRouteRadar(void (*returnCallback)(void))
{
    sRadar = AllocZeroed(sizeof(*sRadar));
    sRadar->returnCallback = returnCallback;
    SetMainCallback2(CB2_InitRadar);
}

static void VBlankCB_Radar(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static void CB2_Radar(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    DoScheduledBgTilemapCopiesToVram();
    UpdatePaletteFade();
}

static void PrintBand(u32 windowId, const u8 *str)
{
    FillWindowPixelBuffer(windowId, PIXEL_FILL(COLOR_BAND));
    AddTextPrinterParameterized4(windowId, FONT_NORMAL, (240 - GetStringWidth(FONT_NORMAL, str, 0)) / 2, 1, 0, 0,
                                 sBandColors, TEXT_SKIP_DRAW, str);
    CopyWindowToVram(windowId, COPYWIN_FULL);
}

static void PrintRight(u8 windowId, const u8 *str, u8 y)
{
    AddTextPrinterParameterized4(windowId, FONT_SMALL, RADAR_RIGHT_EDGE - GetStringWidth(FONT_SMALL, str, 0), y, 0, 0,
                                 sTextColors, TEXT_SKIP_DRAW, str);
}

static void DrawCaughtBall(u8 windowId, u8 y)
{
    BlitBitmapToWindow(windowId, sCaughtBall_Gfx, RADAR_BALL_X, y, 8, 16);
}

// Route: caught/species on the right, SWARM for today's swarm routes, and a Poke Ball once all are caught
static void ItemPrintFunc_Route(u8 windowId, u32 itemId, u8 y)
{
    const struct KjhRadarRoute *route;
    u8 buffer[8];
    u8 *end;

    if (itemId == (u32)LIST_HEADER)
        return;
    route = &sRadar->routes[itemId];
    if (route->speciesCount != 0 && route->caughtCount == route->speciesCount)
        DrawCaughtBall(windowId, y);
    if (route->swarm)
        AddTextPrinterParameterized4(windowId, FONT_SMALL, RADAR_SWARM_X, y, 0, 0, sSwarmColors, TEXT_SKIP_DRAW,
                                     sText_Swarm);
    end = ConvertIntToDecimalStringN(buffer, route->caughtCount, STR_CONV_MODE_LEFT_ALIGN, 3);
    *end++ = CHAR_SLASH;
    ConvertIntToDecimalStringN(end, route->speciesCount, STR_CONV_MODE_LEFT_ALIGN, 3);
    PrintRight(windowId, buffer, y);
}

// Species: a Poke Ball if caught, and its chance by this method
static void ItemPrintFunc_Entry(u8 windowId, u32 itemId, u8 y)
{
    const struct KjhRadarEntry *entry;
    u8 buffer[6];
    u8 *end;

    if (itemId == (u32)LIST_HEADER)
        return;
    entry = &sRadar->entries[itemId];
    if (GetSetPokedexFlag(SpeciesToNationalPokedexNum(entry->species), FLAG_GET_CAUGHT))
        DrawCaughtBall(windowId, y);
    end = ConvertIntToDecimalStringN(buffer, entry->rate, STR_CONV_MODE_LEFT_ALIGN, 3);
    *end++ = CHAR_PERCENT;
    *end = EOS;
    PrintRight(windowId, buffer, y);
}

// The list's scroll and row to show item in the middle when it can
static void PlaceCursor(u16 item, u16 total, u16 *scroll, u16 *row)
{
    u16 top = 0;

    if (total > RADAR_MAX_SHOWED)
    {
        if (item > RADAR_MAX_SHOWED / 2)
            top = item - RADAR_MAX_SHOWED / 2;
        if (top > total - RADAR_MAX_SHOWED)
            top = total - RADAR_MAX_SHOWED;
    }
    *scroll = top;
    *row = item - top;
}

static void BuildRouteList(void)
{
    u16 numRoutes = KJH_RadarBuildRoutes(sRadar->routes, KJH_RADAR_MAX_ROUTES);
    u16 n = 0, current = 1;
    u8 region = 0xFF;

    for (u32 i = 0; i < numRoutes; i++)
    {
        if (sRadar->routes[i].region != region && n < ARRAY_COUNT(sRadar->routeItems) - 1)
        {
            region = sRadar->routes[i].region;
            sRadar->routeItems[n].name = KJH_RadarRegionName(region);
            sRadar->routeItems[n].id = LIST_HEADER;
            n++;
        }
        GetMapName(sRadar->routeNames[i], sRadar->routes[i].mapSec, 0);
        sRadar->routeItems[n].name = sRadar->routeNames[i];
        sRadar->routeItems[n].id = i;
        if (sRadar->routes[i].mapSec == gMapHeader.regionMapSectionId)
            current = n;
        n++;
    }
    sRadar->numRouteItems = n;
    // open on the route the player is on
    PlaceCursor(current, n, &sRadar->routeScroll, &sRadar->routeRow);
}

static void BuildEntryList(void)
{
    u8 count = KJH_RadarBuildRoute(sRadar->routes[sRadar->route].mapSec, sRadar->entries, KJH_RADAR_MAX_ENTRIES);
    u8 method = KJH_RADAR_METHOD_COUNT;
    u16 n = 0;

    for (u32 i = 0; i < count; i++)
    {
        if (sRadar->entries[i].method != method)
        {
            method = sRadar->entries[i].method;
            sRadar->entryItems[n].name = sMethodNames[method];
            sRadar->entryItems[n].id = LIST_HEADER;
            n++;
        }
        sRadar->entryItems[n].name = KJH_RadarSpeciesName(sRadar->entries[i].species);
        sRadar->entryItems[n].id = i;
        n++;
    }
    sRadar->numEntryItems = n;
}

static void ShowList(const struct ListMenuItem *items, u16 count, void (*printFunc)(u8, u32, u8), u16 scroll, u16 row,
                     const u8 *title, const u8 *controls)
{
    struct ListMenuTemplate template =
    {
        .items = items,
        .moveCursorFunc = ListMenuDefaultCursorMoveFunc,
        .itemPrintFunc = printFunc,
        .totalItems = count,
        .maxShowed = RADAR_MAX_SHOWED,
        .windowId = WIN_LIST,
        .header_X = 4,
        .item_X = 14,
        .cursor_X = 4,
        .upText_Y = 1,
        .cursorPal = COLOR_TEXT,
        .fillValue = COLOR_PAPER,
        .cursorShadowPal = COLOR_SHADOW,
        .lettersSpacing = 0,
        .itemVerticalPadding = 0,
        .scrollMultiple = LIST_MULTIPLE_SCROLL_L_R,
        .fontId = FONT_NORMAL,
        .cursorKind = CURSOR_BLACK_ARROW,
    };

    PrintBand(WIN_TITLE, title);
    PrintBand(WIN_CONTROLS, controls);
    FillWindowPixelBuffer(WIN_LIST, PIXEL_FILL(COLOR_PAPER));
    if (count == 0)
    {
        AddTextPrinterParameterized4(WIN_LIST, FONT_NORMAL, 14, 1, 0, 0, sTextColors, TEXT_SKIP_DRAW, sText_NoRoutes);
        CopyWindowToVram(WIN_LIST, COPYWIN_FULL);
        sRadar->listTaskId = TASK_NONE;
        sRadar->arrowsTaskId = TASK_NONE;
        return;
    }
    sRadar->listTaskId = ListMenuInit(&template, scroll, row);
    sRadar->scrollOffset = scroll;
    sRadar->arrowsTaskId = TASK_NONE;
    if (count > RADAR_MAX_SHOWED)
        sRadar->arrowsTaskId = AddScrollIndicatorArrowPairParameterized(SCROLL_ARROW_UP, 232, 20, 140,
                                                                        count - RADAR_MAX_SHOWED, 0x2000, 0x2000,
                                                                        &sRadar->scrollOffset);
    CopyWindowToVram(WIN_LIST, COPYWIN_FULL);
}

static void HideList(u16 *scroll, u16 *row)
{
    if (sRadar->arrowsTaskId != TASK_NONE)
        RemoveScrollIndicatorArrowPair(sRadar->arrowsTaskId);
    sRadar->arrowsTaskId = TASK_NONE;
    if (sRadar->listTaskId != TASK_NONE)
        DestroyListMenuTask(sRadar->listTaskId, scroll, row);
    sRadar->listTaskId = TASK_NONE;
}

static void ShowRouteList(void)
{
    sRadar->onRoutePage = FALSE;
    ShowList(sRadar->routeItems, sRadar->numRouteItems, ItemPrintFunc_Route, sRadar->routeScroll, sRadar->routeRow,
             sText_RouteRadar, sText_RouteListControls);
}

static void ShowRoutePage(void)
{
    sRadar->onRoutePage = TRUE;
    BuildEntryList();
    // the first item is a method header
    ShowList(sRadar->entryItems, sRadar->numEntryItems, ItemPrintFunc_Entry, 0, sRadar->numEntryItems > 1 ? 1 : 0,
             sRadar->routeNames[sRadar->route], sText_RoutePageControls);
}

static void CB2_InitRadar(void)
{
    switch (gMain.state)
    {
    case 0:
        SetVBlankCallback(NULL);
        ResetOtherVideoRegisters(0);
        DmaClearLarge16(3, (void *)VRAM, VRAM_SIZE, 0x1000);
        DmaClear32(3, OAM, OAM_SIZE);
        DmaClear16(3, PLTT, PLTT_SIZE);
        ScanlineEffect_Stop();
        ResetTasks();
        ResetSpriteData();
        ResetPaletteFade();
        FreeAllSpritePalettes();
        gMain.state++;
        break;
    case 1:
        ResetBgsAndClearDma3BusyFlags(0);
        InitBgsFromTemplates(0, sBgTemplates, ARRAY_COUNT(sBgTemplates));
        sTilemapBuffer = AllocZeroed(BG_SCREEN_SIZE);
        SetBgTilemapBuffer(0, sTilemapBuffer);
        InitWindows(sWindowTemplates);
        DeactivateAllTextPrinters();
        LoadPalette(gPokedexBgNational_Pal, BG_PLTT_ID(0), PLTT_SIZE_4BPP);
        gPlttBufferUnfaded[BG_PLTT_ID(0) + COLOR_PAPER] = RGB_WHITE;
        gPlttBufferFaded[BG_PLTT_ID(0) + COLOR_PAPER] = RGB_WHITE;
        for (u32 i = 0; i < WIN_CONTROLS + 1; i++)
            PutWindowTilemap(i);
        gMain.state++;
        break;
    case 2:
        BuildRouteList();
        ShowRouteList();
        ScheduleBgCopyTilemapToVram(0);
        gMain.state++;
        break;
    case 3:
        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_MODE_0 | DISPCNT_OBJ_1D_MAP | DISPCNT_OBJ_ON);
        ShowBg(0);
        BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
        SetVBlankCallback(VBlankCB_Radar);
        CreateTask(Task_RadarInput, 0);
        SetMainCallback2(CB2_Radar);
        break;
    }
}

static void Task_RadarInput(u8 taskId)
{
    s32 input = LIST_NOTHING_CHOSEN;

    if (gPaletteFade.active)
        return;
    if (sRadar->listTaskId != TASK_NONE)
    {
        input = ListMenu_ProcessInput(sRadar->listTaskId);
        ListMenuGetScrollAndRow(sRadar->listTaskId, &sRadar->scrollOffset, NULL);
    }

    if (!sRadar->onRoutePage)
    {
        if (JOY_NEW(A_BUTTON) && input >= 0)
        {
            PlaySE(SE_SELECT);
            sRadar->route = input;
            HideList(&sRadar->routeScroll, &sRadar->routeRow);
            ShowRoutePage();
            ScheduleBgCopyTilemapToVram(0);
        }
        else if (JOY_NEW(B_BUTTON))
        {
            PlaySE(SE_PC_OFF);
            BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
            gTasks[taskId].func = Task_RadarExit;
        }
    }
    else if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_SELECT);
        HideList(NULL, NULL);
        ShowRouteList();
        ScheduleBgCopyTilemapToVram(0);
    }
}

static void Task_RadarExit(u8 taskId)
{
    void (*returnCallback)(void);

    if (gPaletteFade.active)
        return;
    HideList(sRadar->onRoutePage ? NULL : &sRadar->routeScroll, sRadar->onRoutePage ? NULL : &sRadar->routeRow);
    FreeAllWindowBuffers();
    FREE_AND_SET_NULL(sTilemapBuffer);
    returnCallback = sRadar->returnCallback;
    FREE_AND_SET_NULL(sRadar);
    DestroyTask(taskId);
    SetMainCallback2(returnCallback);
}
