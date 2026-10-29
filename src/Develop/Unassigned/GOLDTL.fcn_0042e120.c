#include <string.h>

extern char *g_6b7fd0;
extern char *g_6b7fd4;


/* ADDRESS: GOLDTL 0x0042e120 */
void __cdecl fcn_0042e120(char *a0, char *a1, int a2)
{
    if (g_6b7fd0 >= g_6b7fd4) {
        __asm { int 3 }
        return;
    }
    *(int *)(g_6b7fd0 + 0x70) = a2;
    strncpy(g_6b7fd0 + 0xe, a0, 0x2f);
    strncpy(g_6b7fd0 + 0x3e, a1, 0x2f);
    g_6b7fd0 = g_6b7fd0 + 0x84;
}
