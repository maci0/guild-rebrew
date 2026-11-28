#include "d2_gui.h"

/* ADDRESS: GOLDDE 0x00459eb0 */
void __cdecl d2_SetElementImage(int element, int bild)
{
    D2_GUI_ITEM* eintrag;

#ifdef REBREW_GOLD
    eintrag = &g_00f8f080[element];
    if (eintrag->f08 == bild) {
        return;
    }
#else
    eintrag = &((D2_GUI_ITEM*) d2_Controls)[element];
#endif
    if (eintrag->kind < 0x40) {
        d2_SubRefcount(eintrag->f08);
    }
    eintrag->data = d2_GetResourceData(bild);
    eintrag->bild_offset = d2_ResourceOffset;
    eintrag->f08 = d2_ResourceOffset + bild;
    eintrag->w = ((D2_BILD_GROESSE*) d2_FileObjTable)[bild].breite;
    eintrag->f16 = ((D2_BILD_GROESSE*) d2_FileObjTable)[bild].hoehe;
    eintrag->f22 = 0;
#ifdef REBREW_GOLD
    eintrag->f24 = g_00fb9070;
    eintrag->f1e = 0;
    eintrag->f20 = g_00fb9072;
#else
    eintrag->f24 = d2_ScreenHeight;
    eintrag->f1e = 0;
    eintrag->f20 = g_1040494;
#endif
    if (eintrag->kind < 0x40) {
        d2_AddRefcount(eintrag->f08);
    }
}
