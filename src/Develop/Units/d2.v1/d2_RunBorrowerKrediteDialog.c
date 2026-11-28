#include "d2_gui.h"
typedef unsigned short u16;
typedef unsigned int   u32;
extern int d2_CurrentWindowId, io_RightButtonReleased, d2_DialogCloseRequested;
void* __cdecl d2_LoadForm(int a, int b, char* c);
void __cdecl d2_CenterDialogWindows(int a);
void __cdecl d2_SetForm(int a, int b);
void __cdecl io_AppendText(void* id, ...);
void __cdecl d2_SetOverlayAnimation(int a, int b);
int __cdecl main_RunFrameLoop(void* a, int b);
void __cdecl d2_CloseWindow(int w);
int __cdecl d2_DestroyElement(int id);
int __cdecl he_GetActiveKrediteByBorrower(int id, char* owner, char** out);
int __cdecl d2_AddElementToWindow(int a, int b, int c, int d);
int __cdecl d2_CreateChildWindow(int a, int b, int c, int d, int e, int f);
void __cdecl d2_DestroyForm(int a);
void __cdecl d3_EndCameraAndUiMode(void);
/* ADDRESS: GOLDTL 0x005a4960 */
void __cdecl d2_RunBorrowerKrediteDialog(char* owner, int id)
{
    int slot[9][3];
    char* entries[9];
    int count;
    int cx;
    int cy;
    char* dlg;
    int idx;
    int i;
    int ebx = 0;
    int esi = 1;
    for (i = 0; i < 9; i++) {
        slot[i][0] = -1;
        slot[i][1] = -1;
        slot[i][2] = 0;
    }
    dlg = d2_LoadForm(0, 0, "locations\\geldleihe\\geldleihe_kreditaufnehmen");
    d2_CenterDialogWindows((int)dlg);
    d2_SetForm((int)dlg, 0);
    idx = 972 * d2_CurrentWindowId;
    *(int*)(0x10162e8 + idx) = 0xe;
    *(int*)(0x10162ec + idx) = 0x18;
    *(int*)(0x10162f0 + idx) = 0x18;
    *(int*)(0x10162f4 + idx) = 0xe;
    d2_SetForm((int)dlg, 1);
    io_AppendText((void*)0x18d9);
    d2_SetOverlayAnimation(0, 0);
    while (main_RunFrameLoop((void*)0x5a4960, 0x677c7)) {
        if (esi != 0) {
            for (i = 0; i < 9; i++) {
                if (slot[i][0] != -1) {
                    d2_CloseWindow(slot[i][0]);
                    d2_DestroyElement(slot[i][1]);
                    slot[i][0] = -1;
                    slot[i][1] = -1;
                    slot[i][2] = 0;
                }
            }

            count = he_GetActiveKrediteByBorrower(id, owner, entries);
            cx = *(short*) (d2_FileObjTable + 0x269d8);
            cy = *(short*) (d2_FileObjTable + 0x269da);
            for (i = 0; i < count; i++) {
                d2_SetForm((int)dlg, 2);
                slot[i][1] = d2_AddElementToWindow(0, ebx, 0x75a,
                                           d2_CurrentWindowId);
                slot[i][0] = d2_CreateChildWindow(0, ebx, cx, cy,
                                           0x110, d2_CurrentWindowId);
                slot[i][2] = (int) entries[i];
                idx = 972 * slot[i][0];
                *(int*)(0x10161cc + idx) = 0x56;
                *(int*)(0x1015f58 + idx) = 0x10;
                io_AppendText((void*)0x18e0,
                             (void*)*(int*)(slot[i][2] + 0xb4));
                io_AppendText((void*)0x18e1,
                             (void*)(slot[i][2] + 0xc4));
                io_AppendText((void*)0x18e2,
                             (void*)*(int*)(slot[i][2] + 0xc0));
                ebx += cy + 4;
            }
            ebx = 0;
        }
        esi = 0;

        if (io_RightButtonReleased != 0)
            d2_DialogCloseRequested = 1;
    }

    d2_DestroyForm((int)dlg);
    d3_EndCameraAndUiMode();
}
