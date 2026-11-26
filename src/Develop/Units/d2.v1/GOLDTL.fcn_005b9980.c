extern int d2_CurrentWindowId;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern unsigned char g_773d75;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_dialog_state.h"
extern int g_100f1dc;

extern int __cdecl gm_CollectEntityCarts(int a0, int a1);
extern int __cdecl io_FormatTextBuffer(char *a0, char *a1, ...);
extern int __cdecl fcn_00526120(char *a0, int a1);
extern int __cdecl fcn_00470820(int a0, int a1, char *a2);
extern void __cdecl d2_CenterDialogWindows(int a0);
extern void __cdecl d2_SetForm(int a0, int a1);
extern int __cdecl io_AppendText(int a0);
extern int __cdecl d2_GetWindowListItem(int a0, int a1, int a2);
extern void __cdecl d2_DrawPanelFrame(int a0, int a1, int a2);
extern int __cdecl d2_CreateRadioGroup(int a0, int a1, int a2, int a3);
extern int __cdecl d2_SelectRadioGroup(int a0, int a1);

extern int __cdecl main_RunFrameLoop(void *a0, int a1);
extern void __cdecl fcn_00471e30(int a0);
extern int __cdecl d2_ClearRadioGroup(int a0);
extern float __cdecl eval_ObjektPreis2Credits(int a0, int a1);
extern int __cdecl gm_CheckEntityStock(char *a0, int a1, unsigned char a2);
extern int __cdecl fcn_0051e070(void);
extern int __cdecl fcn_00526120(char *a0, int a1);
extern void __cdecl fcn_0046f9b0(int a0, char *a1);
extern void __cdecl fcn_00469090(int a0);
extern void __cdecl fcn_004c51a0(int a0, int a1, char a2, int a3);
extern int __cdecl gm_GetEntityTableEntry(int a0);
extern void __cdecl fcn_004c51f0(int a0, int a1, int a2, int a3, char a4, int a5);

/* ADDRESS: GOLDTL 0x005b9980 */
void __cdecl d2_ShowNewCartDialog(int sourceObj)
{
    int choiceIndex;
    int confirmButton;
    int groupId;
    int groupOffset;
    int optionButtons[3];
    char messageBuf[512];
    char confirmBuf[1024];
    int h;
    int i;
    int priceValue;
    int v;

    choiceIndex = 0;
    if (gm_CollectEntityCarts(sourceObj, 0) >= 3)
    {
        io_FormatTextBuffer(messageBuf, (char *)0xf1, 3);
        fcn_00526120(messageBuf, 0);
        return;
    }
    h = fcn_00470820(0, 0, (char *)0x6ac354);
    d2_CenterDialogWindows(h);
    d2_SetForm(h, 2);
    io_AppendText(0xd8);
    optionButtons[0] = d2_GetWindowListItem(h, 1, 0);
    optionButtons[1] = d2_GetWindowListItem(h, 1, 1);
    optionButtons[2] = d2_GetWindowListItem(h, 1, 2);
    d2_SetForm(h, 0);
    d2_DrawPanelFrame(d2_CurrentWindowId, 0x70b, 0x741);
    d2_SetForm(h, 3);
    confirmButton = d2_GetWindowListItem(h, 3, io_AppendText(0xdb));
    groupId = d2_CreateRadioGroup(3, optionButtons[0], optionButtons[1], optionButtons[2]);
    d2_SelectRadioGroup(groupId, 0);
    groupOffset = 35 * groupId;
    do
    {
        if (g_100f1dc >= 0x5e2 && g_100f1dc <= 0x5e4)
        {
            for (i = 0; i < 3; i++)
            {
                if (d2_CurrentElementId == optionButtons[i])
                    choiceIndex = i;
            }
        }
        else if (g_100f1dc == 2)
        {
            if (d2_CurrentElementId == confirmButton)
            {
                priceValue = (int) eval_ObjektPreis2Credits(choiceIndex + 0x134, 100);
                if (gm_CheckEntityStock((char *)(g_774970 * 0x21c + 0x7f4ca0), priceValue,
                        (priceValue & 0xffffff00) | g_773d75))
                {
                    switch (fcn_0051e070())
                    {
                    case 1:
                        io_FormatTextBuffer(confirmBuf, (char *)0xd9, choiceIndex * 2 + 0xc10, priceValue);
                        break;
                    case 0:
                        io_FormatTextBuffer(confirmBuf, (char *)0xd9, priceValue, choiceIndex * 2 + 0xc10);
                        break;
                    }
                    if (fcn_00526120(confirmBuf, 0x101))
                    {
                        fcn_004c51a0(-1, *(int *)(g_774970 * 0x21c + 0x7f4ca4),
                            g_773d75, priceValue);
                        v = gm_GetEntityTableEntry(g_774970 * 0x21c + 0x7f4ca0);
                        if (v != 0)
                            *(int *)(v + 0x50) = *(int *)(v + 0x50) + priceValue;
                        fcn_004c51f0(*(int *)(sourceObj + 1), -1, choiceIndex + 0x134, 1,
                            g_773d75, 0);
                        g_774654 = 1;
                    }
                }
            }
        }
        if (*(int *)(0x102cbc8 + groupOffset * 4) != -1)
        {
            io_FormatTextBuffer(messageBuf, (char *)0xda, choiceIndex * 2 + 0xc10,
                (int) eval_ObjektPreis2Credits(choiceIndex + 0x134, 100));
            fcn_0046f9b0(confirmButton, messageBuf);
            fcn_00469090(confirmButton);
        }
        if (g_14ce8e0 != 0)
            g_774654 = 1;
    } while (main_RunFrameLoop((void *)0x5b9980, 0x677c7) != 0);
    fcn_00471e30(h);
    d2_ClearRadioGroup(groupId);
}
