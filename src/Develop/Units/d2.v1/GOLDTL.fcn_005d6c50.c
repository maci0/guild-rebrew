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
void __cdecl fcn_004fcda0(int id, int a, void* out);
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
int __cdecl fcn_005d6c50(int a0, int a1)
{
    char frame[0x118];
    u16* p;
    int dlg;
    int v;
    int h;
    int h2;
    char* text;

    frame[8] = 0;
    *(int*) (frame + 4) = 0;
    *(int*) (frame + 9) = 0;
    *(int*) (frame + 0xd) = 0;
    *(int*) (frame + 0x11) = 0;
    *(u16*) (frame + 0x15) = 0;
    frame[0x17] = 0;

    p = (u16*) a0;
    if (*(int*) a1 != 3) {
        if (*(int*) a1 != 4)
            return 0x60;
        p = *(u16**) (a1 + 0x21c);
        if (p == 0)
            return 0x60;
    }
    fcn_004fcda0(*p, 0, frame + 8);
    v = gm_RandomMod(0xb0) & 0xffff;
    *(int*) frame = v + 0x19;
    h2 = _ftol();
    if (((u8*) a0)[2] != 6) {
        if (*(int*) (a0 + 0x194) < 4)
            return 0x20;
        fcn_004c51a0(*(int*) (a0 + 4), -1, 0, h2);
        fcn_004c6ae0(*(int*) (a0 + 4), -4);
        fcn_004c5420(*(int*) (p + 2), 0x1c8, 4, 0x400000, 0);
        return 0;
    }
    dlg = (int) fcn_00470820(0, 0, "privillegien\\unterschlagung");
    d2_SetOverlayAnimation(0, 0);
    fcn_00471b60(dlg);
    d2_SetForm(dlg, 1);
    io_AppendText(0x1dc2, *p);
    *(int*) frame = dlg;
    g_100f1dc = -1;
    for (;;) {
        if (g_100f1dc != -1) {
            if (g_100f1dc == 2) {
                if (fcn_00525f60(a0, 4) != 0) {
                    fcn_004c51a0(*(int*) (a0 + 4), -1, 0, h2);
                    fcn_004c6ae0(*(int*) (a0 + 4), -4);
                    h = fcn_004c5420(*(int*) (p + 2), 0x1c8, 4, 0x400000,
                                     0);
                    while (fcn_004c4450(h) == 0)
                        fcn_00535960();
                    io_FormatTextBuffer(frame + 0x18, 0x1dc3, h2);
                    fcn_00526120(frame + 0x18, 0);
                    *(int*) (frame + 4) = 0x90;
                    g_774654 = 1;
                }
            } else if (g_100f1dc == 1) {
                g_774654 = 1;
            }
        }
        if (g_14ce8e0 != 0)
            g_774654 = 1;
        if (fcn_005373e0((void*) 0x5d6c50, 0x657c7) == 0) {
            fcn_00471e30(dlg);
            return *(int*) (frame + 4);
        }
    }
}
