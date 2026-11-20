#include "g_10058a0.h"

extern D2_RADIO_SLOT g_10058a0[8];
void __cdecl fcn_004be520(int *id);

/* ADDRESS: GOLDTL 0x004be530 */
void __cdecl fcn_004be530(void)
{
    D2_RADIO_SLOT *tp_eintrag;

    /* The native bound comparison uses signed 32-bit addresses. */
    for (tp_eintrag = g_10058a0; (int)tp_eintrag < (int)(g_10058a0 + 8); tp_eintrag++) {
        if (tp_eintrag->id != -1)
            fcn_004be520(&tp_eintrag->id);
    }
}
