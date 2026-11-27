#include "Develop/Units/d2.v1/d2_gui.h"
extern void* g_006ed9dc;
extern int g_005f323c, g_006310b4, g_00f8a664, g_00f8a66c;

/* ADDRESS: GOLD 0x00477520 */
void __cdecl d2_ResetSelectedControl(void)
{
    int idx;
    char *base;

    if (g_006ed9dc != 0) {
        idx = *(int *)((char *) g_006ed9dc + 0x134);
        base = (char*) g_00f8f080;
        *(int *)(base + idx * 187 * 4 + 0x2c) = 0;
        g_006ed9dc = 0;
        if (*(int *)0x5febc4 != -1) {
            g_005f323c = g_00f8a664;
            g_006310b4 = g_00f8a66c;
            *(int *)0x5febc4 = -1;
        }
    }
}
