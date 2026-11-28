#include <stdio.h>
#include <string.h>
#include "Develop/Units/d2.v1/client_dialog_state.h"
#include "Develop/DieGildeAddOn/game/game_data.h"
#define D(a) (*(int *)(a))
#define B(a) (*(unsigned char *)(a))
#define W(a) (*(unsigned short *)(a))
#define F(a) (*(float *)(a))
short *__cdecl gm_GetEntityTableEntry(char *);
int __cdecl gm_WalkEntityChain(unsigned short);
int __cdecl gm_AmountToUnits(int, unsigned char);
int __cdecl gm_ConvertUnitsToAmount(int, int);
float __cdecl gm_RandomFloat01(void);
int __cdecl gm_RandomMod(unsigned short);
int __cdecl d2_LoadForm(int, int, char *);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl io_FormatTextBuffer(char *, int, ...);
int __cdecl io_AppendText(char *, ...);
int __cdecl main_RunFrameLoop(void *, int);
void __cdecl d2_DestroyForm(int);
int __cdecl d2_OpenPokerDialog(void);
int __cdecl gm_InitCardGame(char *, void *);
void __cdecl d2_DestroyCardGameForm(void);
unsigned short __cdecl gm_StepCardGameRound(void);
void __cdecl d2_SetElementEnabled(int, int);
void __cdecl d2_UpdateCardGameBetGauge(int);
int __cdecl d2_ShowModalMessageBox(char *, int);
void __cdecl d2_SetFormVisibility(int, int);
int __cdecl d2_ShowPokerHandsDialog(void);
void __cdecl d2_LayoutCardGameRow(int, int, void *);
int __cdecl d2_SetForm(int, int);
int __cdecl d2_GetControlValue(int);
int __cdecl gm_ReplaceActivePlayerCardSlot(int);

/* ADDRESS: GOLDTL 0x005e6e00 */
int __cdecl d2_RunCardGameDialog(void)
{
    char text[256], prompt[256];
    char *entry;
    int money, dialog, previous, choice, control;
    unsigned short flags;

    previous = -1;
    entry = (char *)gm_GetEntityTableEntry(gm_EntitySlotTable + gm_LocalPlayerSlot * 0x21c);
    if (!entry) return 0;
    money = gm_AmountToUnits(gm_WalkEntityChain(gm_LocalPlayerSlot), gm_ActiveTownIndex);
    if (gm_RandomFloat01() < *(float *)(entry + 0x60) && W(0x7f4c04) > 11 && money >= 10000) {
    *(float *)(entry + 0x60) = *(float *)(entry + 0x60) * F(0x664178) - g_662a3c;
    B(0x14cf71e) = 0;
    if (!d2_OpenPokerDialog()) return 0;
    if (!gm_InitCardGame(gm_EntitySlotTable + gm_LocalPlayerSlot * 0x21c, (void *)0x7765a0)) {
        d2_DestroyCardGameForm();
        return 0;
    }
    flags = gm_StepCardGameRound();
    d2_DialogButtonAction = -1;
    do {
        if (io_RightButtonReleased) d2_DialogCloseRequested = 1;
        d2_SetElementEnabled(D(0x6ad56c), flags & 1);
        d2_SetElementEnabled(D(0x6ad570), flags & 8);
        d2_SetElementEnabled(D(0x6ad578), flags & 0x10);
        d2_UpdateCardGameBetGauge((flags & 1) && (flags & 0x20));
        if (d2_DialogButtonAction != -1) {
            if (D(0x6ad570) == D(0x67d370)) {
                io_FormatTextBuffer(prompt, 0x4263);
                if (d2_ShowModalMessageBox(prompt, 0x101)) d2_DialogCloseRequested = 1;
            }
            if (D(0x6ad57c) == D(0x67d370)) {
                d2_SetFormVisibility(D(0x6ad568), 0);
                d2_ShowPokerHandsDialog();
                d2_SetFormVisibility(D(0x6ad568), 1);
            }
        }
        switch (D(0x7765a0)) {
        case 1:
            if (previous != 1) {
                previous = 1;
                d2_LayoutCardGameRow(1, 0, 0); d2_LayoutCardGameRow(2, 0, 0); d2_LayoutCardGameRow(0, 0, 0);
            }
            d2_SetForm(D(0x6ad568), 4);
            if (!D(0x776650)) {
                strcpy(text, (char *)D(0x14b5c60)); io_AppendText(text);
                if (d2_DialogButtonAction != -1 && D(0x6ad56c) == D(0x67d370)) {
                    choice = d2_GetControlValue(D(0x6ad580));
                    D(0x77664c) = gm_ConvertUnitsToAmount(choice, gm_ActiveTownIndex);
                    flags = gm_StepCardGameRound();
                }
            } else {
                choice = *(int *)((char *)0x7765a4 + D(0x776650) * 0x34);
                sprintf(text, (char *)D(0x14b5c5c), choice + 0x30, choice + 0x40);
                io_AppendText(text);
                io_FormatTextBuffer(text, 0x4251, D(0x776644)); io_AppendText(text);
                if (d2_DialogButtonAction != -1 && D(0x6ad578) == D(0x67d370)) flags = gm_StepCardGameRound();
            }
            break;
        case 2:
            d2_SetForm(D(0x6ad568), 4);
            io_FormatTextBuffer(text, 0x4252, D(0x776640)); io_AppendText(text);
            io_FormatTextBuffer(text, (unsigned short)gm_RandomMod(3) + 0x4253, 0x4256); io_AppendText(text);
            if (D(0x776650)) {
                io_FormatTextBuffer(text, 0x425a, D(0x77664c)); io_AppendText(text);
            } else io_AppendText((char *)D(0x14b5c84));
            d2_LayoutCardGameRow(1, 3, (void *)0x7765e0);
            d2_LayoutCardGameRow(2, 3, (void *)0x776614);
            d2_LayoutCardGameRow(0, 3, (void *)0x7765ac);
            flags = gm_StepCardGameRound();
            break;
        case 3:
            if (d2_DialogButtonAction != -1) {
                if (D(0x6ad56c) == D(0x67d370)) {
                    if (!D(0x776650)) {
                        choice = d2_GetControlValue(D(0x6ad580));
                        D(0x77664c) = gm_ConvertUnitsToAmount(choice, gm_ActiveTownIndex);
                    }
                    flags = gm_StepCardGameRound();
                    d2_LayoutCardGameRow(0, 4, (void *)0x7765ac);
                    d2_LayoutCardGameRow(1, 4, (void *)0x7765e0);
                    d2_LayoutCardGameRow(2, 4, (void *)0x776614);
                } else if (D(0x6ad570) == D(0x67d370)) d2_DialogCloseRequested = 1;
            }
            break;
        case 4:
            d2_SetForm(D(0x6ad568), 4);
            io_FormatTextBuffer(text, 0x4252, D(0x776640)); io_AppendText(text);
            io_FormatTextBuffer(text, (unsigned short)gm_RandomMod(3) + 0x4253, 0x4257); io_AppendText(text);
            if (D(0x776650)) {
                io_FormatTextBuffer(text, 0x425a, D(0x77664c)); io_AppendText(text);
            } else io_AppendText((char *)D(0x14b5c84));
            if (previous != 4) {
                previous = 4;
                d2_LayoutCardGameRow(1, 4, (void *)0x7765e0);
                d2_LayoutCardGameRow(2, 4, (void *)0x776614);
                d2_LayoutCardGameRow(0, 4, (void *)0x7765ac);
            }
            flags = gm_StepCardGameRound();
            break;
        case 5:
            if (d2_DialogButtonAction != -1) {
                if (D(0x6ad56c) == D(0x67d370)) {
                    if (!D(0x776650)) {
                        choice = d2_GetControlValue(D(0x6ad580));
                        D(0x77664c) = gm_ConvertUnitsToAmount(choice, gm_ActiveTownIndex);
                    }
                    flags = gm_StepCardGameRound();
                    d2_LayoutCardGameRow(0, 4, (void *)0x7765ac);
                    d2_LayoutCardGameRow(1, 4, (void *)0x7765e0);
                    d2_LayoutCardGameRow(2, 4, (void *)0x776614);
                } else if (D(0x6ad570) == D(0x67d370)) d2_DialogCloseRequested = 1;
            }
            break;
        case 6:
            d2_SetForm(D(0x6ad568), 4);
            io_FormatTextBuffer(text, 0x4252, D(0x776640)); io_AppendText(text);
            io_AppendText((char *)D(0x14b5c8c));
            D(D(0x1015ea0) + 0x60 + D(0x6ad588) * 0x2f4) = 0;
            D(D(0x1015ea0) + 0x60 + D(0x6ad58c) * 0x2f4) = 0;
            D(D(0x1015ea0) + 0x60 + D(0x6ad590) * 0x2f4) = 1;
            D(D(0x1015ea0) + 0x60 + D(0x6ad594) * 0x2f4) = 1;
            D(D(0x1015ea0) + 0x5c + D(0x6ad588) * 0x2f4) = 1;
            D(D(0x1015ea0) + 0x1d0 + D(0x6ad588) * 0x2f4) = 3;
            D(D(0x1015ea0) + 0x5c + D(0x6ad58c) * 0x2f4) = 1;
            D(D(0x1015ea0) + 0x1d0 + D(0x6ad58c) * 0x2f4) = 3;
            if (d2_DialogButtonAction != -1) {
                int clk = D(0x67d370);
                if (D(0x6ad588) == clk) {
                    control = D(0x1015ea0) + 0x38 + D(0x6ad588) * 0x2f4;
                    D(control) = !D(control);
                    D(D(0x1015ea0) + 0x38 + D(0x6ad58c) * 0x2f4) = 0;
                    control = D(0x6ad588);
                    goto set_btn;
                } else if (D(0x6ad58c) == clk) {
                    control = D(0x1015ea0) + 0x38 + D(0x6ad58c) * 0x2f4;
                    D(control) = !D(control);
                    D(D(0x1015ea0) + 0x38 + D(0x6ad588) * 0x2f4) = 0;
                    control = D(0x6ad58c);
                set_btn:
                    if (D(D(0x1015ea0) + 0x38 + control * 0x2f4) != 0) d2_SetElementEnabled(D(0x6ad574), 1);
                    else d2_SetElementEnabled(D(0x6ad574), 0);
                } else if (D(0x6ad574) == clk) {
                    d2_SetElementEnabled(D(0x6ad574), 0);
                    if (D(D(0x1015ea0) + 0x38 + D(0x6ad588) * 0x2f4)) gm_ReplaceActivePlayerCardSlot(0);
                    else if (D(D(0x1015ea0) + 0x38 + D(0x6ad58c) * 0x2f4)) gm_ReplaceActivePlayerCardSlot(1);
                    flags = gm_StepCardGameRound();
                    d2_LayoutCardGameRow(0, 4, (void *)0x7765ac);
                    d2_LayoutCardGameRow(1, 4, (void *)0x7765e0);
                    d2_LayoutCardGameRow(2, 4, (void *)0x776614);
                } else if (D(0x6ad578) == clk) {
                    d2_SetElementEnabled(D(0x6ad574), 0);
                    flags = gm_StepCardGameRound();
                    d2_LayoutCardGameRow(0, 4, (void *)0x7765ac);
                    d2_LayoutCardGameRow(1, 4, (void *)0x7765e0);
                    d2_LayoutCardGameRow(2, 4, (void *)0x776614);
                } else if (D(0x6ad570) == clk) d2_DialogCloseRequested = 1;
            }
            break;
        case 7:
            D(D(0x1015ea0) + 0x60 + D(0x6ad588) * 0x2f4) = 1;
            D(D(0x1015ea0) + 0x60 + D(0x6ad58c) * 0x2f4) = 1;
            D(D(0x1015ea0) + 0x60 + D(0x6ad590) * 0x2f4) = 0;
            D(D(0x1015ea0) + 0x60 + D(0x6ad594) * 0x2f4) = 0;
            D(D(0x1015ea0) + 0x5c + D(0x6ad588) * 0x2f4) = 0;
            D(D(0x1015ea0) + 0x1d0 + D(0x6ad588) * 0x2f4) = 0;
            D(D(0x1015ea0) + 0x5c + D(0x6ad58c) * 0x2f4) = 0;
            D(D(0x1015ea0) + 0x1d0 + D(0x6ad58c) * 0x2f4) = 0;
            d2_SetForm(D(0x6ad568), 4);
            io_FormatTextBuffer(text, 0x4252, D(0x776640)); io_AppendText(text);
            if (D(0x7765fc) != -1) sprintf(text, (char *)D(0x14b5c90), D(0x7765d8) + 0x30, D(0x7765d8) + 0x40);
            else sprintf(text, (char *)D(0x14b5c94), D(0x7765d8) + 0x30, D(0x7765d8) + 0x40);
            io_AppendText(text);
            if (D(0x776630) != -1) sprintf(text, (char *)D(0x14b5c90), D(0x77660c) + 0x30, D(0x77660c) + 0x40);
            else sprintf(text, (char *)D(0x14b5c94), D(0x77660c) + 0x30, D(0x77660c) + 0x40);
            io_AppendText(text);
            if (d2_DialogButtonAction != -1 && D(0x6ad578) == D(0x67d370)) flags = gm_StepCardGameRound();
            break;
        case 8:
            d2_SetForm(D(0x6ad568), 4);
            io_FormatTextBuffer(text, 0x4252, D(0x776640)); io_AppendText(text);
            io_FormatTextBuffer(text, (unsigned short)gm_RandomMod(3) + 0x4253, 0x4258); io_AppendText(text);
            if (D(0x776650)) {
                io_FormatTextBuffer(text, 0x425a, D(0x77664c)); io_AppendText(text);
            } else io_AppendText((char *)D(0x14b5c84));
            d2_LayoutCardGameRow(1, 5, (void *)0x7765e0);
            d2_LayoutCardGameRow(2, 5, (void *)0x776614);
            d2_LayoutCardGameRow(0, 5, (void *)0x7765ac);
            flags = gm_StepCardGameRound();
            break;
        case 9:
            if (d2_DialogButtonAction != -1) {
                if (D(0x6ad56c) == D(0x67d370)) {
                    if (!D(0x776650)) {
                        choice = d2_GetControlValue(D(0x6ad580));
                        D(0x77664c) = gm_ConvertUnitsToAmount(choice, gm_ActiveTownIndex);
                    }
                    flags = gm_StepCardGameRound();
                    d2_LayoutCardGameRow(0, 5, (void *)0x7765ac);
                    d2_LayoutCardGameRow(1, 5, (void *)0x7765e0);
                    d2_LayoutCardGameRow(2, 5, (void *)0x776614);
                } else if (D(0x6ad570) == D(0x67d370)) d2_DialogCloseRequested = 1;
            }
            break;
        case 10:
            gm_StepCardGameRound();
            d2_LayoutCardGameRow(0, 5, (void *)0x7765ac); d2_LayoutCardGameRow(1, 5, (void *)0x7765e0); d2_LayoutCardGameRow(2, 5, (void *)0x776614);
            d2_SetForm(D(0x6ad568), 4);
            if (!W(0x776658)) {
                io_FormatTextBuffer(text, 0x4265, D(0x77665c) + 0x4266, D(0x776640));
            } else {
                choice = *(int *)((char *)0x7765a4 + W(0x776658) * 0x34);
                io_FormatTextBuffer(text, 0x4264, choice + 0x30, choice + 0x40, D(0x77665c) + 0x4266, D(0x776640));
            }
            io_AppendText(text);
            break;
        case 11:
            if (d2_DialogButtonAction != -1 && D(0x6ad578) == D(0x67d370)) d2_DialogCloseRequested = 1;
            break;
        }
    } while (main_RunFrameLoop((void *)d2_RunCardGameDialog, 0x777c7));
    d2_DestroyCardGameForm();
    return 1;
    }
    dialog = d2_LoadForm(0, 0, (char *)0x6ad5f4);
    if (!dialog) return 0;
    d2_CenterDialogWindows(D(0x6ad568));
    io_FormatTextBuffer(text, 0x4239, 0x4238);
    io_AppendText(text);
    while (main_RunFrameLoop((void *)d2_RunCardGameDialog, 0x777c7)) {
        if (io_RightButtonReleased || B(0x14cf701)) d2_DialogCloseRequested = 1;
    }
    d2_DestroyForm(dialog);
    return 0;
}
