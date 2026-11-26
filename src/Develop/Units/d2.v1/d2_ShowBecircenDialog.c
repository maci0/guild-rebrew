typedef unsigned char u8;
typedef unsigned short u16;

extern int g_100f1dc;
extern int g_14ce8e0;
#include "client_dialog_state.h"

void* __cdecl fcn_00470820(int a, int b, char* name);
void __cdecl d2_SetOverlayAnimation(int a, int b);
void __cdecl d2_CenterDialogWindows(int dlg);
void __cdecl d2_SetForm(int dlg, int a);
int __cdecl io_AppendText(int id, ...);
int __cdecl d2_GetWindowListItem(int dlg, int a, int b);
void __cdecl fcn_00472380(int a, int b, int c, int d);
void __cdecl io_FormatTextBuffer(char* out, int id, ...);
int __cdecl fcn_00526120(char* buf, int a);
int __cdecl main_RunFrameLoop(void* fn, int msg);
int __cdecl fcn_00471e30(int dlg);
int __cdecl d2_GetControlValue(int h);
int __cdecl fcn_00525f60(void* tbl, int player);
int __cdecl fcn_004946f0(void* tbl, int a0, int player);
void __cdecl fcn_004c6ae0(int a, int b);
void __cdecl fcn_004c54c0(int a, int b, int c, int d);

/* ADDRESS: GOLDTL 0x005d6ea0 */
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
    v = *(u8*) (0x7f4ca9 + 540 * *(u16*) 0x774970);
    if (v == *(u8*) ((char*) entity + 9)) {
        if (v == 0)
            io_FormatTextBuffer(buf, 0x1db1, 0x1db2);
        else
            io_FormatTextBuffer(buf, 0x1db1, 0x1db3);
        fcn_00526120(buf, 0);
        return 0;
    }
    dlg = (int) fcn_00470820(0, 0, "privillegien\\becircen");
    d2_SetOverlayAnimation(0, 0);
    d2_CenterDialogWindows(dlg);
    d2_SetForm(dlg, 1);
    wnd = d2_GetWindowListItem(dlg, 1,
                       io_AppendText(0x1db4, *(u16*) entity, *(u16*) entity));
    fcn_00472380(wnd, 1, 5, 1);
    g_100f1dc = -1;
    for (;;) {
        if (g_100f1dc != -1) {
            if (g_100f1dc == 2) {
                player = d2_GetControlValue(wnd);
                if (fcn_00525f60((void*) (0x7f4ca0 + 540 * *(u16*) 0x774970),
                                 player) != 0) {
                    t = fcn_004946f0((void*) (0x7f4ca0 +
                                              540 * *(u16*) 0x774970),
                                     entity, player);
                    fcn_004c6ae0(*(int*) (0x7f4ca4 + 540 * *(u16*) 0x774970),
                                 -player);
                    fcn_004c54c0(*(int*) (0x7f4ca4 +
                                          540 * *(u16*) 0x774970),
                                 *(int*) ((char*) entity + 4), t, 1);
                    io_FormatTextBuffer(buf, 0x1db5, *(u16*) entity, *(u16*) entity);
                    fcn_00526120(buf, 0);
                    g_774654 = 4;
                    result = 1;
                }
            } else if (g_100f1dc == 1) {
                g_774654 = 2;
            }
        }
        if (g_14ce8e0 != 0)
            g_774654 = 1;
        if (main_RunFrameLoop((void*) 0x5d6ea0, 0x657c7) == 0)
            break;
    }
    fcn_00471e30(dlg);
    return result;
}
