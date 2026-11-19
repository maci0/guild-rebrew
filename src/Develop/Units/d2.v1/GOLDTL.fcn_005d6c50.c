#include <string.h>
typedef unsigned char u8;
typedef unsigned short u16;

extern int g_100f1dc; extern float g_664138;
extern int g_14ce8e0;
#include "client_dialog_state.h"

void* __cdecl fcn_00470820(int a, int b, char* name);
void __cdecl d2_SetOverlayAnimation(int a, int b);
void __cdecl d2_CenterDialogWindows(int dlg);
void __cdecl d2_SetForm(int dlg, int a);
int __cdecl io_AppendText(int id, ...);
void __cdecl fcn_004fcda0(u16 id, int a, void* out);
int __cdecl gm_RandomMod(int a);
int __cdecl _ftol(void);
int __cdecl fcn_004c51a0(int a, int b, int c, int d);
void __cdecl fcn_004c6ae0(int a, int b);
int __cdecl fcn_004c5420(int a, int b, int c, int d, int e);
int __cdecl fcn_004c4450(int a);
void __cdecl fcn_00535960(void);
void __cdecl io_FormatTextBuffer(char* out, int id, ...);
int __cdecl fcn_00526120(char* text, int a);
int __cdecl fcn_00471e30(int dlg);
int __cdecl fcn_005373e0(void* fn, int msg);
int __cdecl fcn_00525f60(int a, int b);

/* ADDRESS: GOLDTL 0x005d6c50 */
int __cdecl fcn_005d6c50(int actor, int a1)
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
    fcn_004fcda0(*p, 0, frame + 4);
    v = gm_RandomMod(0xb0) & 0xffff;
    h2 = (int) ((double) (v + 0x19) * g_664138 * *(int*) (frame + 0x8));
    if (((u8*) actor)[2] != 6) {
        if (*(int*) (actor + 0x194) < 4)
            return 0x20;
        fcn_004c51a0(*(int*) (actor + 4), -1, 0, h2);
        fcn_004c6ae0(*(int*) (actor + 4), -4);
        fcn_004c5420(*(int*) (p + 2), 0x1c8, 4, 0x400000, 0);
        return *(int*) (frame + 0);
    }
    dlg = (int) fcn_00470820(0, 0, "privillegien\\unterschlagung");
    *(int*) (frame + 0x8) = dlg;
    d2_SetOverlayAnimation(0, 0);
    d2_CenterDialogWindows(dlg);
    d2_SetForm(dlg, 1);
    io_AppendText(0x1dc2, *(u16*) actor);
    g_100f1dc = -1;
    for (;;) {
        if (g_100f1dc != -1) {
            if (g_100f1dc == 2) {
                if (fcn_00525f60(actor, 4) != 0) {
                    fcn_004c51a0(*(int*) (actor + 4), -1, 0, h2);
                    fcn_004c6ae0(*(int*) (actor + 4), -4);
                    dlg = fcn_004c5420(*(int*) (p + 2), 0x1c8, 4, 0x400000,
                                     0);
                    while (fcn_004c4450(dlg) == 0)
                        fcn_00535960();
                    io_FormatTextBuffer(frame + 0x14, 0x1dc3, h2);
                    fcn_00526120(frame + 0x14, 0);
                    dlg = *(int*) (frame + 0x8);
                    *(int*) (frame + 0) = 0x90;
                    g_774654 = 1;
                }
            } else if (g_100f1dc == 1) {
                g_774654 = 1;
            }
        }
        if (g_14ce8e0 != 0)
            g_774654 = 1;
        if (fcn_005373e0((void*) fcn_005d6c50, 0x657c7) == 0) {
            fcn_00471e30(dlg);
            return *(int*) (frame + 0);
        }
    }
}
