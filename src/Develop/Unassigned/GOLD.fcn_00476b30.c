#include "client_sprites.h"

void __cdecl fcn_00476b30(void)
{
    char** p;
    /* Native comparison treats the cursor addresses as signed 32-bit values. */
    for (p = g_1015ec0; (int)p < (int)(g_1015ec0 + 32); p++) {
        if (*p != 0) {
            fcn_00476850(*p);
            *p = 0;
        }
    }
}
