#include <string.h>

#include "Develop/DieGildeAddOn/game/game_data.h"
extern char *g_6b7fd4;


/* ADDRESS: GOLDTL 0x0042e120 */
void __cdecl PushErrorContext(char *msg, char *module, int line)
{
    if (g_6b7fd0 >= g_6b7fd4) {
        __asm { int 3 }
        return;
    }
    *(int *)(g_6b7fd0 + 0x70) = line;
    strncpy(g_6b7fd0 + 0xe, msg, 0x2f);
    strncpy(g_6b7fd0 + 0x3e, module, 0x2f);
    g_6b7fd0 = g_6b7fd0 + 0x84;
}
