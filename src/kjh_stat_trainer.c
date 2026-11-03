// KJH: the stat trainer (ENG-7, include/kjh_stat_trainer.h), ported from KJH's pokefirered tree.
//
// In a Pokemon Center, he sets a party Pokemon's IVs, EVs or nature exactly, or switches its ability
// (data/scripts/kjh_stat_trainer.inc). The nature is the Pokemon's stat nature (MON_DATA_HIDDEN_NATURE, what a Mint
// changes), so its personality (gender, shininess, ability, Unown letter, Spinda's spots) stays as it is.
#include "global.h"
#include "event_data.h"
#include "kjh_bond.h"
#include "kjh_stat_trainer.h"
#include "kjh_team_level.h"
#include "kjh_training.h"
#include "main.h"
#include "menu.h"
#include "party_menu.h"
#include "pokemon.h"
#include "script.h"
#include "sound.h"
#include "string_util.h"
#include "strings.h"
#include "task.h"
#include "text.h"
#include "window.h"
#include "constants/songs.h"

#define ROW_HEIGHT 13
#define NUM_ROWS   NUM_STATS

#define tCursor   data[0]
#define tWindowId data[1]
#define tMode     data[2]
#define tNature   data[3]
#define tValues   data[4] // data[4..9]: the six values, in the row order below

// Rows: HP, ATTACK, DEFENSE, SP. ATK, SP. DEF, SPEED, as the summary lists them
static const enum Stat sRowStats[NUM_ROWS] = {STAT_HP, STAT_ATK, STAT_DEF, STAT_SPATK, STAT_SPDEF, STAT_SPEED};

static const u8 sText_Hp[] = _("HP");
static const u8 sText_Attack[] = _("ATTACK");
static const u8 sText_Defense[] = _("DEFENSE");
static const u8 sText_SpAtk[] = _("SP. ATK");
static const u8 sText_SpDef[] = _("SP. DEF");
static const u8 sText_Speed[] = _("SPEED");
static const u8 *const sRowNames[NUM_ROWS] = {sText_Hp, sText_Attack, sText_Defense, sText_SpAtk, sText_SpDef, sText_Speed};
static const u8 sText_Total[] = _("TOTAL");
static const u8 sText_Nature[] = _("NATURE");
static const u8 sText_Raises[] = _("+");
static const u8 sText_Lowers[] = _("-");
static const u8 sText_NoEffect[] = _("No stat changes");
static const u8 sText_Arrows[] = _("{DPAD_LEFTRIGHT}");

static const struct WindowTemplate sStatWindowTemplate =
{
    .bg = 0,
    .tilemapLeft = 1,
    .tilemapTop = 1,
    .width = 15,
    .height = 12,
    .paletteNum = 15,
    .baseBlock = 0x038,
};

static void Task_StatTrainer(u8 taskId);

static struct Pokemon *CurrentMon(void)
{
    return &gPlayerParty[gSpecialVar_0x8004];
}

static u32 StatData(u32 mode, enum Stat stat)
{
    return (mode == KJH_STAT_TRAINER_IVS ? MON_DATA_HP_IV : MON_DATA_HP_EV) + stat;
}

u32 KJH_ClampIv(s32 iv)
{
    return min(max(iv, 0), MAX_PER_STAT_IVS);
}

u32 KJH_ClampEv(const u8 *evs, u32 row, s32 ev)
{
    s32 others = 0;

    for (u32 i = 0; i < NUM_STATS; i++)
    {
        if (i != row)
        {
            others += evs[i];
        }
    }

    return min(max(ev, 0), min(MAX_PER_STAT_EVS, MAX_TOTAL_EVS - others));
}

bool32 KJH_CanTrainIvs(struct Pokemon *mon)
{
    return !KJH_IsLevelsFree() || KJH_GetPeakBond(mon) >= KJH_STAT_TRAINER_IV_BOND;
}

void KJH_ResetTrainingPoints(struct Pokemon *mon)
{
    u32 placed = KJH_TrainingPlaced(mon), zero = 0;

    for (enum Stat stat = 0; stat < NUM_STATS; stat++)
    {
        SetMonData(mon, MON_DATA_HP_EV + stat, &zero);
    }
    KJH_TrainingRefund(mon, placed);
    CalculateMonStats(mon);
}

void KJH_ScriptCanTrainIvs(struct ScriptContext *ctx)
{
    Script_RequestEffects(SCREFF_V1);
    gSpecialVar_Result = KJH_CanTrainIvs(CurrentMon());
}

void KJH_ScriptBufferPlacedPoints(struct ScriptContext *ctx)
{
    struct Pokemon *mon = CurrentMon();

    Script_RequestEffects(SCREFF_V1);
    gSpecialVar_Result = KJH_TrainingPlaced(mon);
    GetMonNickname(mon, gStringVar1);
    ConvertIntToDecimalStringN(gStringVar2, gSpecialVar_Result, STR_CONV_MODE_LEFT_ALIGN, 3);
}

void KJH_ScriptResetTrainingPoints(struct ScriptContext *ctx)
{
    Script_RequestEffects(SCREFF_V1 | SCREFF_SAVE);
    KJH_ResetTrainingPoints(CurrentMon());
}

static void PrintText(u32 windowId, const u8 *text, u32 x, u32 y)
{
    AddTextPrinterParameterized(windowId, FONT_NORMAL, text, x, y, TEXT_SKIP_DRAW, NULL);
}

static void PrintNumber(u32 windowId, s32 value, u32 x, u32 y)
{
    ConvertIntToDecimalStringN(gStringVar1, value, STR_CONV_MODE_RIGHT_ALIGN, 3);
    PrintText(windowId, gStringVar1, x, y);
}

static void DrawNature(struct Task *task)
{
    const struct NatureInfo *nature = &gNaturesInfo[task->tNature];
    u32 windowId = task->tWindowId;

    PrintText(windowId, sText_Nature, 8, 2);
    PrintText(windowId, sText_Arrows, 0, 2 + ROW_HEIGHT);
    PrintText(windowId, nature->name, 20, 2 + ROW_HEIGHT);
    if (nature->statUp == nature->statDown)
    {
        PrintText(windowId, sText_NoEffect, 8, 2 + 2 * ROW_HEIGHT);
        return;
    }
    for (u32 row = 0; row < NUM_ROWS; row++)
    {
        if (sRowStats[row] == nature->statUp)
        {
            PrintText(windowId, sText_Raises, 8, 2 + 2 * ROW_HEIGHT);
            PrintText(windowId, sRowNames[row], 20, 2 + 2 * ROW_HEIGHT);
        }
        if (sRowStats[row] == nature->statDown)
        {
            PrintText(windowId, sText_Lowers, 8, 2 + 3 * ROW_HEIGHT);
            PrintText(windowId, sRowNames[row], 20, 2 + 3 * ROW_HEIGHT);
        }
    }
}

static void DrawStats(struct Task *task)
{
    u32 windowId = task->tWindowId;
    s32 total = 0;

    for (u32 row = 0; row < NUM_ROWS; row++)
    {
        u32 y = 2 + row * ROW_HEIGHT;

        if (row == task->tCursor)
        {
            PrintText(windowId, gText_SelectorArrow2, 0, y);
        }
        PrintText(windowId, sRowNames[row], 8, y);
        PrintNumber(windowId, (&task->tValues)[row], 92, y);
        total += (&task->tValues)[row];
    }

    if (task->tMode == KJH_STAT_TRAINER_EVS)
    {
        PrintText(windowId, sText_Total, 8, 2 + NUM_ROWS * ROW_HEIGHT);
        PrintNumber(windowId, total, 92, 2 + NUM_ROWS * ROW_HEIGHT);
    }
}

static void Redraw(struct Task *task)
{
    FillWindowPixelBuffer(task->tWindowId, PIXEL_FILL(1));
    if (task->tMode == KJH_STAT_TRAINER_NATURE)
    {
        DrawNature(task);
    }
    else
    {
        DrawStats(task);
    }
    CopyWindowToVram(task->tWindowId, COPYWIN_GFX);
}

void KJH_ScriptStatTrainerEdit(struct ScriptContext *ctx)
{
    u8 taskId;
    struct Task *task;
    struct Pokemon *mon = CurrentMon();

    // Before any effect: the script's effects check stops here
    Script_RequestEffects(SCREFF_V1 | SCREFF_SAVE | SCREFF_HARDWARE);
    taskId = CreateTask(Task_StatTrainer, 80);
    task = &gTasks[taskId];
    task->tMode = gSpecialVar_0x8005;
    task->tCursor = 0;
    task->tNature = GetMonData(mon, MON_DATA_HIDDEN_NATURE);
    if (task->tMode != KJH_STAT_TRAINER_NATURE)
    {
        for (u32 row = 0; row < NUM_ROWS; row++)
        {
            (&task->tValues)[row] = GetMonData(mon, StatData(task->tMode, sRowStats[row]));
        }
    }

    LockPlayerFieldControls();
    task->tWindowId = AddWindow(&sStatWindowTemplate);
    SetStandardWindowBorderStyle(task->tWindowId, FALSE);
    PutWindowTilemap(task->tWindowId);
    Redraw(task);
    CopyWindowToVram(task->tWindowId, COPYWIN_FULL);
}

static void ChangeValue(struct Task *task, s32 delta)
{
    s16 *value = &(&task->tValues)[task->tCursor];
    s32 before = *value;

    if (task->tMode == KJH_STAT_TRAINER_IVS)
    {
        *value = KJH_ClampIv(*value + delta);
    }
    else
    {
        u8 evs[NUM_ROWS];

        for (u32 row = 0; row < NUM_ROWS; row++)
        {
            evs[row] = (&task->tValues)[row];
        }

        *value = KJH_ClampEv(evs, task->tCursor, *value + delta);
    }

    if (*value != before)
    {
        PlaySE(SE_SELECT);
        Redraw(task);
    }
}

static void Save(struct Task *task)
{
    struct Pokemon *mon = CurrentMon();

    if (task->tMode == KJH_STAT_TRAINER_NATURE)
    {
        u32 nature = task->tNature;

        SetMonData(mon, MON_DATA_HIDDEN_NATURE, &nature);
    }
    else
    {
        for (u32 row = 0; row < NUM_ROWS; row++)
        {
            u32 value = (&task->tValues)[row];

            SetMonData(mon, StatData(task->tMode, sRowStats[row]), &value);
        }
    }

    CalculateMonStats(mon);
    gSpecialVar_Result = TRUE;
}

static void Close(u8 taskId)
{
    struct Task *task = &gTasks[taskId];

    ClearStdWindowAndFrameToTransparent(task->tWindowId, TRUE);
    RemoveWindow(task->tWindowId);
    DestroyTask(taskId);
    ScriptContext_Enable();
}

static void Task_StatTrainer(u8 taskId)
{
    struct Task *task = &gTasks[taskId];

    if (JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);
        Save(task);
        Close(taskId);
    }
    else if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_SELECT);
        gSpecialVar_Result = FALSE;
        Close(taskId);
    }
    else if (task->tMode == KJH_STAT_TRAINER_NATURE)
    {
        if (JOY_REPEAT(DPAD_RIGHT | DPAD_DOWN))
        {
            task->tNature = (task->tNature + 1) % NUM_NATURES;
        }
        else if (JOY_REPEAT(DPAD_LEFT | DPAD_UP))
        {
            task->tNature = (task->tNature + NUM_NATURES - 1) % NUM_NATURES;
        }
        else
        {
            return;
        }
        PlaySE(SE_SELECT);
        Redraw(task);
    }
    else if (JOY_REPEAT(DPAD_UP) || JOY_REPEAT(DPAD_DOWN))
    {
        task->tCursor = (task->tCursor + (JOY_REPEAT(DPAD_UP) ? NUM_ROWS - 1 : 1)) % NUM_ROWS;
        PlaySE(SE_SELECT);
        Redraw(task);
    }
    else if (JOY_REPEAT(DPAD_RIGHT))
    {
        ChangeValue(task, 1);
    }
    else if (JOY_REPEAT(DPAD_LEFT))
    {
        ChangeValue(task, -1);
    }
    else if (JOY_REPEAT(START_BUTTON))
    {
        ChangeValue(task, 10);
    }
    else if (JOY_REPEAT(SELECT_BUTTON))
    {
        ChangeValue(task, -10);
    }
}
