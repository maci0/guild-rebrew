#include <string.h>
typedef unsigned char u8;
typedef unsigned short u16;

extern int d2_DialogButtonAction; extern float g_664138;
extern int io_RightButtonReleased;
#include "Develop/Units/d2.v1/client_dialog_state.h"

void* __cdecl d2_LoadForm(int a, int b, char* name);
void __cdecl d2_SetOverlayAnimation(int a, int b);
void __cdecl d2_CenterDialogWindows(int dlg);
void __cdecl d2_SetForm(int dlg, int a);
int __cdecl io_AppendText(int id, ...);
void __cdecl amt_ProcessPrivilegeIncome(u16 id, int a, void* out);
int __cdecl gm_RandomMod(int a);
int __cdecl _ftol(void);
int __cdecl cm_RequestTransferCurrencyNoKill(int a, int b, int c, int d);
void __cdecl cm_RequestModifyHealth(int a, int b);
int __cdecl cm_RequestChangeBits(int a, int b, int c, int d, int e);
int __cdecl cm_GetCommandStatus(int a);
void __cdecl cm_StepCommandQueue(void);
void __cdecl io_FormatTextBuffer(char* out, int id, ...);
int __cdecl d2_ShowModalMessageBox(char* text, int a);
int __cdecl d2_DestroyForm(int dlg);
int __cdecl main_RunFrameLoop(void* fn, int msg);
int __cdecl d2_CheckActionBlocker(int a, int b);

/* ADDRESS: GOLDTL 0x005d6c50 */
int __cdecl d2_RunUnterschlagungDialog(int actor, int a1)
{
    char frame[0x114];
    u16* p;
    int dlg;
    int v;
    int h;
    int h2;
    u16* q;

    memset(frame + 5, 0, 15);




    *(int*) (frame + 0) = 0;
    h = *(int*) a1;
    frame[4] = 0;

    if (h == 3) {
        p = (u16*) actor;
    } else if (h == 4) {
        q = *(u16**) (a1 + 0x21c);
        if (q == 0)
            return 0x60;
        p = q;
    } else {
        return 0x60;
    }
    amt_ProcessPrivilegeIncome(*p, 0, frame + 4);
    v = gm_RandomMod(0xb0) & 0xffff;
    h2 = (int) ((double) (v + 0x19) * g_664138 * *(int*) (frame + 0x8));
    if (((u8*) actor)[2] != 6) {
        if (*(int*) (actor + 0x194) < 4)
            return 0x20;
        cm_RequestTransferCurrencyNoKill(*(int*) (actor + 4), -1, 0, h2);
        cm_RequestModifyHealth(*(int*) (actor + 4), -4);
        cm_RequestChangeBits(*(int*) (p + 2), 0x1c8, 4, 0x400000, 0);
        return *(int*) (frame + 0);
    }
    dlg = (int) d2_LoadForm(0, 0, "privillegien\\unterschlagung");
    *(int*) (frame + 0x8) = dlg;
    d2_SetOverlayAnimation(0, 0);
    d2_CenterDialogWindows(dlg);
    d2_SetForm(dlg, 1);
    io_AppendText(0x1dc2, *(u16*) actor);
    d2_DialogButtonAction = -1;
    for (;;) {
        if (d2_DialogButtonAction != -1) {
            if (d2_DialogButtonAction == 2) {
                if (d2_CheckActionBlocker(actor, 4) != 0) {
                    cm_RequestTransferCurrencyNoKill(*(int*) (actor + 4), -1, 0, h2);
                    cm_RequestModifyHealth(*(int*) (actor + 4), -4);
                    dlg = cm_RequestChangeBits(*(int*) (p + 2), 0x1c8, 4, 0x400000,
                                     0);
                    while (cm_GetCommandStatus(dlg) == 0)
                        cm_StepCommandQueue();
                    io_FormatTextBuffer(frame + 0x14, 0x1dc3, h2);
                    d2_ShowModalMessageBox(frame + 0x14, 0);
                    dlg = *(int*) (frame + 0x8);
                    *(int*) (frame + 0) = 0x90;
                    d2_DialogCloseRequested = 1;
                }
            } else if (d2_DialogButtonAction == 1) {
                d2_DialogCloseRequested = 1;
            }
        }
        if (io_RightButtonReleased != 0)
            d2_DialogCloseRequested = 1;
        if (main_RunFrameLoop((void*) d2_RunUnterschlagungDialog, 0x657c7) == 0) {
            d2_DestroyForm(dlg);
            return *(int*) (frame + 0);
        }
    }
}
