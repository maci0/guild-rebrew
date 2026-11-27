#include "client_sprites.h"

void __cdecl d2_TickFadeOverlays(void)
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
                d2_FreeOverlaySprite(n);
                *p = 0;
            } else {
                *(int*) n = f | 4;
            }
        }
    }
}
