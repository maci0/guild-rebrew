#include "Develop/Units/d2.v1/d2_radio_slot.h"

extern D2_RADIO_SLOT g_10058a0[8];
void __cdecl d2_PollRadioSlotControl(int *id);

/* ADDRESS: GOLDTL 0x004be530 */
void __cdecl d2_PollRadioSlots(void)
{
    D2_RADIO_SLOT *tp_eintrag;

    /* The native bound comparison uses signed 32-bit addresses. */
    for (tp_eintrag = g_10058a0; (int)tp_eintrag < (int)(g_10058a0 + 8); tp_eintrag++) {
        if (tp_eintrag->id != -1)
            d2_PollRadioSlotControl(&tp_eintrag->id);
    }
}
