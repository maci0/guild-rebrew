#include "d2_gui.h"

void __cdecl d2_SetElementImage(int element, int bild)
{
    D2_GUI_ITEM* eintrag;

#ifdef REBREW_GOLD
    eintrag = &g_00f8f080[element];
    if (eintrag->f08 == bild) {
        return;
    }
#else
    eintrag = &((D2_GUI_ITEM*) g_1015ea0)[element];
#endif
    if (eintrag->kind < 0x40) {
        d2_SubRefcount(eintrag->f08);
    }
    eintrag->data = d2_GetResourceData(bild);
    eintrag->bild_offset = g_772568;
    eintrag->f08 = g_772568 + bild;
    eintrag->w = ((D2_BILD_GROESSE*) g_772500)[bild].breite;
    eintrag->f16 = ((D2_BILD_GROESSE*) g_772500)[bild].hoehe;
    eintrag->f22 = 0;
#ifdef REBREW_GOLD
    eintrag->f24 = g_00fb9070;
    eintrag->f1e = 0;
    eintrag->f20 = g_00fb9072;
#else
    eintrag->f24 = g_1040490;
    eintrag->f1e = 0;
    eintrag->f20 = g_1040494;
#endif
    if (eintrag->kind < 0x40) {
        fcn_00469900(eintrag->f08);
    }
}
