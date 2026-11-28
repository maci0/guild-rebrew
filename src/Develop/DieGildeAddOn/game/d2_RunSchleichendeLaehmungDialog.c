/* Domicile cabinet: lets the player pick a target, then offers a priced spy
 * order in a dialog and sends it when confirmed. */

#include <string.h>
#include "Develop/client_types.h"
#include "Develop/DieGildeAddOn/game/game_player.h"
#include "Develop/Units/d2.v1/client_dialog_state.h"

/* SIZE 0x21c */
typedef struct {
    char p0[4];
    int f4;
    char p8[0x21c - 8];
} KABINETT_ENTITY_SLOT;

typedef struct F8 {
    int mask;
    int b;
} F8;
// SIZE 0x8

extern KABINETT_ENTITY_SLOT gm_EntitySlotTable[];
extern pos14_7f4c00 gm_GameTime;
extern unsigned char gm_ActiveTownIndex;
extern float g_6628ac;
extern int d2_CurrentWindowId;
extern int d2_DialogButtonAction;
extern int io_RightButtonReleased;
extern int d2_CurrentElementId;

int __cdecl gm_WalkEntityChain(unsigned short);
char *__cdecl d2_OpenTargetPicker(int *, int, int, int);
int __cdecl he_HasNoActiveAction0x9b(char *);
void __cdecl io_FormatTextBuffer(char *, int, ...);
int __cdecl d2_ShowModalMessageBox(char *, int);
int __cdecl d2_LoadForm(int, int, char *);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_InitWindowBounds(int);
int __cdecl io_AppendText();
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl gm_CheckEntityStock(KABINETT_ENTITY_SLOT *, int, unsigned char);
int __cdecl d2_CheckActionBlocker(KABINETT_ENTITY_SLOT *, int);
int __cdecl he_HasNoActiveAssassinAction(char *);
char *__cdecl gm_GetEntityTableEntry(KABINETT_ENTITY_SLOT *);
void __cdecl cm_RequestTransferCurrencyNoKill(int, int, unsigned char, int);
void __cdecl gm_ModifyHealth(int, int);
int __cdecl ai_FindEntityInFavorRange(KABINETT_ENTITY_SLOT *p, int kind, F8 f, int c, float r, int *out);
int __cdecl cm_SendCopyEntityData(char *);
int __cdecl cm_GetCommandStatus(int);
int __cdecl main_RunFrameLoop(void *, int);
int __cdecl d3snd_PlaySoundEffect(int, int, char *, int);
void __cdecl d2_DestroyForm(int);
void __cdecl d3_EndCameraAndUiMode(void);

/* ADDRESS: GOLDTL 0x0058a6b0 */
void __cdecl d2_RunSchleichendeLaehmungDialog(char *gebaeude)
{
    int tmp;
    int dlg;
    int h2;
    int h1;
    int query[0x14];
    char msg[0xf8];
    char text[0x400];
    int base;
    int price;
    char *sel;
    char *rec;
    F8 f;

    base = gm_WalkEntityChain(gm_LocalPlayerSlot);
    memset(query, 0, sizeof(query));
    memset(query + 7, 0xff, 8 * sizeof(int));
    query[0] = 1;
    query[1] = 0x400;
    query[4] = 6;
    sel = d2_OpenTargetPicker(query, *(int *) 0x14b53d0, 0, 0);
    if (he_HasNoActiveAction0x9b(sel) == 0) {
        io_FormatTextBuffer(text, 0x4030, *(unsigned short *) sel);
        d2_ShowModalMessageBox(text, 0);
        return;
    }
    if (sel == 0)
        return;
    tmp = gm_WalkEntityChain(*(unsigned short *) sel) + base;
    price = (int) (tmp * 0.02f);
    dlg = d2_LoadForm(0, 0, "Locations\\Domizil\\kabinett");
    d2_SetOverlayAnimation(0, 0);
    d2_CenterDialogWindows(dlg);
    d2_SetForm(dlg, 0);
    d2_InitWindowBounds(d2_CurrentWindowId);
    d2_SetForm(dlg, 1);
    io_AppendText("$C");
    io_AppendText(0x402e, 0x402b, price, *(unsigned short *) sel);
    d2_SetForm(dlg, 2);
    h2 = io_AppendText(0x402f);
    h1 = d2_GetWindowListItem(dlg, 2, h2);
    h2 = d2_GetWindowListItem(dlg, 2, h2 + 1);
    d2_DialogButtonAction = -1;
    do {
        if (io_RightButtonReleased != 0) {
            d2_DialogCloseRequested = 1;
        } else if (d2_DialogButtonAction != -1) {
            if (d2_CurrentElementId == h1) {
                if (gm_CheckEntityStock(&gm_EntitySlotTable[gm_LocalPlayerSlot], price, gm_ActiveTownIndex) != 0
                    && d2_CheckActionBlocker(&gm_EntitySlotTable[gm_LocalPlayerSlot], 0x10) == 1
                    && he_HasNoActiveAssassinAction(gebaeude) != 0) {
                    rec = gm_GetEntityTableEntry(&gm_EntitySlotTable[gm_LocalPlayerSlot]);
                    if (rec != 0)
                        *(int *) (rec + 0x28) += price;
                    cm_RequestTransferCurrencyNoKill(-1, gm_EntitySlotTable[gm_LocalPlayerSlot].f4, gm_ActiveTownIndex, price);
                    gm_ModifyHealth(gm_EntitySlotTable[gm_LocalPlayerSlot].f4, -0x10);
                    memset(msg, 0, sizeof(msg));
                    msg[4] = (char) 0x99;
                    *(int *) (msg + 8) = gm_EntitySlotTable[*(unsigned short *) (gebaeude + 0x27)].f4;
                    *(int *) (msg + 0xc) = *(int *) (gebaeude + 1);
                    *(int *) (msg + 0x28) = gm_GameTime.a;
                    *(int *) (msg + 0x2c) = gm_GameTime.b;
                    *(int *) (msg + 0x30) = gm_GameTime.c;
                    *(short *) (msg + 0x34) = gm_GameTime.d;
                    msg[0x36] = 2;
                    *(int *) (msg + 0x5c) = *(int *) (gebaeude + 1);
                    *(int *) (msg + 0x60) = *(int *) (sel + 4);
                    *(int *) (msg + 0x64) = -1;
                    *(int *) (msg + 0x68) = 4;
                    *(int *) (msg + 0x6c) = 0;
                    if (*(char **) (sel + 0x170) != 0) {
                        *(int *) (msg + 0x58) = *(int *) (*(char **) (sel + 0x170) + 1);
                    } else if (*(char **) (sel + 0x16c) != 0) {
                        *(int *) (msg + 0x58) = *(int *) (*(char **) (sel + 0x16c) + 1);
                    } else {
                        tmp = -1;
                        f.mask = 0x7b4c4a0;
                        f.b = 0;
                        ai_FindEntityInFavorRange(&gm_EntitySlotTable[gm_LocalPlayerSlot], 0, f, 0, 100.0f, &tmp);
                        *(int *) (msg + 0x58) = tmp;
                    }
                    tmp = cm_SendCopyEntityData(msg);
                    while (tmp != -1 && cm_GetCommandStatus(tmp) == 0)
                        main_RunFrameLoop(0, 0x20007);
                    d3snd_PlaySoundEffect(-7, 0, "KOMMENTARE", -1);
                    d2_DialogCloseRequested = 1;
                }
            } else if (d2_CurrentElementId == h2) {
                d2_DialogCloseRequested = 1;
            }
        }
    } while (main_RunFrameLoop((void *) d2_RunSchleichendeLaehmungDialog, 0x677c7) != 0);
    d2_DestroyForm(dlg);
    d3_EndCameraAndUiMode();
}
