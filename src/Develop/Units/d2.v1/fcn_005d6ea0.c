typedef unsigned char u8;
typedef unsigned short u16;

extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_774654;

void* __cdecl fcn_00470820(int a, int b, char* name);
void __cdecl d2_SetOverlayAnimation(int a, int b);
void __cdecl fcn_00471b60(int dlg);
void __cdecl d2_SetForm(int dlg, int a);
int __cdecl io_AppendText(int id, ...);
int __cdecl fcn_00472250(int dlg, int a, int b);
void __cdecl fcn_00472380(int a, int b, int c, int d);
void __cdecl io_FormatTextBuffer(char* out, int id, ...);
int __cdecl fcn_00526120(char* buf, int a);
int __cdecl fcn_005373e0(void* fn, int msg);
int __cdecl fcn_00471e30(int dlg);
int __cdecl fcn_00471f80(int h);
int __cdecl fcn_00525f60(void* tbl, int player);
int __cdecl fcn_004946f0(void* tbl, int a0, int player);
void __cdecl fcn_004c6ae0(int a, int b);
void __cdecl fcn_004c54c0(int a, int b, int c, int d);

/* ADDRESS: GOLDTL 0x005d6ea0 */
int __cdecl fcn_005d6ea0(int a0)
{
    int dlg;
    int wnd;
    char buf[0x100];
    int player;
    int r;
    int t;
    u8 v;

    r = 0;
    v = *(u8*) (0x7f4ca9 + 540 * *(u16*) 0x774970);
    if (v == *(u8*) ((char*) a0 + 9)) {
        if (v == 0)
            io_FormatTextBuffer(buf, 0x1db1, 0x1db2);
        else
            io_FormatTextBuffer(buf, 0x1db1, 0x1db3);
        fcn_00526120(buf, 0);
        return 0;
    }
    dlg = (int) fcn_00470820(0, 0, "privillegien\\becircen");
    d2_SetOverlayAnimation(0, 0);
    fcn_00471b60(dlg);
    d2_SetForm(dlg, 1);
    wnd = fcn_00472250(dlg, 1,
                       io_AppendText(0x1db4, *(u16*) a0, *(u16*) a0));
    fcn_00472380(wnd, 1, 5, 1);
    g_100f1dc = -1;
    for (;;) {
        if (g_100f1dc != -1) {
            if (g_100f1dc == 2) {
                player = fcn_00471f80(wnd);
                if (fcn_00525f60((void*) (0x7f4ca0 + 540 * *(u16*) 0x774970),
                                 player) != 0) {
                    t = fcn_004946f0((void*) (0x7f4ca0 +
                                              540 * *(u16*) 0x774970),
                                     a0, player);
                    fcn_004c6ae0(*(int*) (0x7f4ca4 + 540 * *(u16*) 0x774970),
                                 -player);
                    fcn_004c54c0(*(int*) (0x7f4ca4 +
                                          540 * *(u16*) 0x774970),
                                 *(int*) ((char*) a0 + 4), t, 1);
                    io_FormatTextBuffer(buf, 0x1db5, *(u16*) a0, *(u16*) a0);
                    fcn_00526120(buf, 0);
                    g_774654 = 4;
                    r = 1;
                }
            } else if (g_100f1dc == 1) {
                g_774654 = 2;
            }
        }
        if (g_14ce8e0 != 0)
            g_774654 = 1;
        if (fcn_005373e0((void*) 0x5d6ea0, 0x657c7) == 0)
            break;
    }
    fcn_00471e30(dlg);
    return r;
}
