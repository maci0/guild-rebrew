#include "g_10058a0.h"

extern IdSlot10058a0 g_10058a0[8];
void __cdecl fcn_004be520(int *id);

/* ADDRESS: GOLD 0x004bdca0 */
/* ADDRESS: GOLDTL 0x004be530 */
void __cdecl fcn_004be530(void)
{
    IdSlot10058a0 *tp_eintrag;

    /* The native bound comparison uses signed 32-bit addresses. */
    for (tp_eintrag = g_10058a0; (int)tp_eintrag < (int)(g_10058a0 + 8); tp_eintrag++) {
        if (tp_eintrag->id != -1)
            fcn_004be520(&tp_eintrag->id);
    }
}
