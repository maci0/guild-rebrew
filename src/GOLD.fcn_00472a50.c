#include "client_sprites.h"

void __cdecl fcn_00472a50(void)
{
    char** p;
    char* n;
    int f;

    /* Native comparison treats the cursor addresses as signed 32-bit values. */
    for (p = g_1015ec0; (int)p < (int)(g_1015ec0 + 32); p++) {
        n = *p;
        if (n != 0) {
            f = *(int*) n;
            if (f & 8) {
                fcn_00476850(n);
                *p = 0;
            } else {
                *(int*) n = f | 4;
            }
        }
    }
}
