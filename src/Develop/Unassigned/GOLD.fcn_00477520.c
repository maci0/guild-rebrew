#include "Develop/Units/d2.v1/d2_gui.h"
extern void* g_006ed9dc;
extern int g_005f323c, g_006310b4, g_00f8a664, g_00f8a66c;

/* ADDRESS: GOLD 0x00477520 */
void __cdecl fcn_00477520(void)
{
    int idx;
    int p;
    int neg;
    int a;
    int b;
    char *base;

    if ((int) g_006ed9dc == 0)
        return;
    idx = *(int *)((int) g_006ed9dc + 0x134);
    base = (char*) g_00f8f080;
    *(int *)(base + idx * 187 * 4 + 0x2c) = 0;
    neg = -1;
    p = *(int *)0x5febc4;
    g_006ed9dc = 0;
    if (p != neg) {
        a = g_00f8a664;
        b = g_00f8a66c;
        *(int *)0x5febc4 = neg;
        g_005f323c = a;
        g_006310b4 = b;
    }
}
