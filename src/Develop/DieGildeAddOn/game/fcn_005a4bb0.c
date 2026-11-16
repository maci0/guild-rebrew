extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_774654;
extern int g_774698;
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
#include "client_actions.h"
void* __cdecl fcn_00470820(short a, short b, char* c);
void __cdecl fcn_00471b60(int a);
void __cdecl d2_SetForm(int a, int b);
int __cdecl io_AppendText(void* id, ...);
int __cdecl fcn_00472250(int a, int b, int c);
int __cdecl fcn_0050b710(int a, unsigned char b);
int __cdecl fcn_0050b750(int a, int index);
void __cdecl d2_SetOverlayAnimation(int a, int b);
int __cdecl fcn_005373e0(void* a, int b);
int __cdecl fcn_00471f80(int a);
int __cdecl gm_QueryEntitySum(int a, unsigned char b);
int __cdecl gm_AccumulateTyped2(int a);
void __cdecl fcn_00472380(int a, ...);
void __cdecl fcn_004c5150(int a, int b, char c, int d);
void __cdecl fcn_004c4510(void* a, int b);
void __cdecl fcn_004c4570(int a, int b, int c, void* d);
void __cdecl fcn_004c5360(void);
void __cdecl fcn_00471e30(int a);

/* ADDRESS: GOLDTL 0x005a4bb0 */
void __cdecl fcn_005a4bb0(char* o)
{
    char* dlg;
    int have;
    int r;
    int txt;
    int it1;
    int it2;
    int sval;
    int v;
    int d;

    dlg = (char*) fcn_00470820(0, 0, "locations\\geldleihe\\geldleihe_KreditFreigabe");
    fcn_00471b60((int)dlg);
    d2_SetForm((int)dlg, 1);
    io_AppendText((void*)0x18e5);
    have = gm_QueryEntitySum(*(int*)(o + 0x5d), g_773d75);
    d2_SetForm((int)dlg, 2);
    txt = io_AppendText((void*)0x18e6, (void*)(2 * *(u16*)(g_773d75 * 0x2f4 + 0x8680b4) + 0x9a8));
    it1 = fcn_00472250((int)dlg, 2, txt);
    it2 = fcn_00472250((int)dlg, 2, txt + 1);
    fcn_00472380(it1, 5, 0x28, *(int*)(o + 0x65));
    sval = gm_AccumulateTyped2(*(u16*)(o + 0x27) * 0x21c + 0x7f4ca0);
    fcn_00472380(it2, 0, fcn_0050b710(sval, g_773d75), fcn_0050b710(have, g_773d75));
    d2_SetOverlayAnimation(0, 0);
    while (fcn_005373e0((void*)0x5a4bb0, 0x677c7) != 0) {
        if (g_14ce8e0 != 0 || g_100f1dc == 1)
            g_774654 = 1;
        v = fcn_0050b750(fcn_00471f80(it2), g_773d75);
        g_774698 = have - v;
        if (g_100f1dc == 2) {
            v = fcn_0050b750(fcn_00471f80(it2), g_773d75);
            if (have < v) {
                d = v - have;
                fcn_004c5150(*(int*)(o + 1),
                             *(int*)(0x7f4ca4 + *(u16*)(o + 0x27) * 0x21c), g_773d75, d);
            } else {
                d = have - v;
                fcn_004c5150(*(int*)(0x7f4ca4 + *(u16*)(o + 0x27) * 0x21c),
                             *(int*)(o + 1), g_773d75, d);
            }
            r = fcn_00471f80(it1);
            fcn_004c4510(o, *(int*)(o + 1));
            fcn_004c4570(4, 1, 0x65, &r);
            fcn_004c5360();
            g_774654 = 1;
        }
    }
    fcn_00471e30((int)dlg);
    g_774698 = 0;
}
