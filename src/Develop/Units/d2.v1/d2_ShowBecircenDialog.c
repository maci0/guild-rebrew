extern char gm_EntitySlotTable[];
extern char gm_LocalPlayerSlot[];
typedef unsigned char u8;
typedef unsigned short u16;

extern int d2_DialogButtonAction;
extern int io_RightButtonReleased;
#include "Develop/Units/d2.v1/client_dialog_state.h"

void* __cdecl d2_LoadForm(int a, int b, char* name);
void __cdecl d2_SetOverlayAnimation(int a, int b);
void __cdecl d2_CenterDialogWindows(int dlg);
void __cdecl d2_SetForm(int dlg, int a);
int __cdecl io_AppendText(int id, ...);
int __cdecl d2_GetWindowListItem(int dlg, int a, int b);
void __cdecl d2_CreateGuiWindow(int a, int b, int c, int d);
void __cdecl io_FormatTextBuffer(char* out, int id, ...);
int __cdecl d2_ShowModalMessageBox(char* buf, int a);
int __cdecl main_RunFrameLoop(void* fn, int msg);
int __cdecl d2_DestroyForm(int dlg);
int __cdecl d2_GetControlValue(int h);
int __cdecl d2_CheckActionBlocker(void* tbl, int player);
int __cdecl gm_CalcBecircenFavor(void* tbl, int a0, int player);
void __cdecl cm_RequestModifyHealth(int a, int b);
void __cdecl cm_RequestCopyEntityData(int a, int b, int c, int d);

/* ADDRESS: GOLDTL 0x005d6ea0 */
/* ADDRESS: GOLDDE 0x005b8700 */
int __cdecl d2_ShowBecircenDialog(int entity)
{
    int dlg;
    int wnd;
    char buf[0x100];
    int player;
    int result;
    int t;
    u8 v;

    result = 0;
    v = *(u8*) (((int) &gm_EntitySlotTable + 0x9) + 540 * *(u16*) &gm_LocalPlayerSlot);
    if (v == *(u8*) ((char*) entity + 9)) {
        if (v == 0)
            io_FormatTextBuffer(buf, 0x1db1, 0x1db2);
        else
            io_FormatTextBuffer(buf, 0x1db1, 0x1db3);
        d2_ShowModalMessageBox(buf, 0);
        return 0;
    }
    dlg = (int) d2_LoadForm(0, 0, "privillegien\\becircen");
    d2_SetOverlayAnimation(0, 0);
    d2_CenterDialogWindows(dlg);
    d2_SetForm(dlg, 1);
    wnd = d2_GetWindowListItem(dlg, 1,
                       io_AppendText(0x1db4, *(u16*) entity, *(u16*) entity));
    d2_CreateGuiWindow(wnd, 1, 5, 1);
    d2_DialogButtonAction = -1;
    for (;;) {
        if (d2_DialogButtonAction != -1) {
            if (d2_DialogButtonAction == 2) {
                player = d2_GetControlValue(wnd);
                if (d2_CheckActionBlocker((void*) ((int) &gm_EntitySlotTable + 540 * *(u16*) &gm_LocalPlayerSlot),
                                 player) != 0) {
                    t = gm_CalcBecircenFavor((void*) ((int) &gm_EntitySlotTable +
                                              540 * *(u16*) &gm_LocalPlayerSlot),
                                     entity, player);
                    cm_RequestModifyHealth(*(int*) (((int) &gm_EntitySlotTable + 0x4) + 540 * *(u16*) &gm_LocalPlayerSlot),
                                 -player);
                    cm_RequestCopyEntityData(*(int*) (((int) &gm_EntitySlotTable + 0x4) +
                                          540 * *(u16*) &gm_LocalPlayerSlot),
                                 *(int*) ((char*) entity + 4), t, 1);
                    io_FormatTextBuffer(buf, 0x1db5, *(u16*) entity, *(u16*) entity);
                    d2_ShowModalMessageBox(buf, 0);
                    d2_DialogCloseRequested = 4;
                    result = 1;
                }
            } else if (d2_DialogButtonAction == 1) {
                d2_DialogCloseRequested = 2;
            }
        }
        if (io_RightButtonReleased != 0)
            d2_DialogCloseRequested = 1;
        if (main_RunFrameLoop((void*) d2_ShowBecircenDialog, 0x657c7) == 0)
            break;
    }
    d2_DestroyForm(dlg);
    return result;
}
