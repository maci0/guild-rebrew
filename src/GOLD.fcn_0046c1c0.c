#include "Develop/Units/d2.v1/d2_gui.h"

void __cdecl fcn_0046cd90(int x, int y, int element);

/* ADDRESS: GOLD 0x0046c1c0 */
void __cdecl fcn_0046c1c0(int element)
{
    GuiEnt *tp_eintrag;
    GuiWin *tp_fenster;
    int x;

    tp_eintrag = &g_00f8f080[element];
    if (*(int *)((char *)tp_eintrag + 0x5c) != 0) {
        tp_fenster = tp_eintrag->parent;
        if (tp_fenster != 0) {
            x = tp_fenster->width / 2 - tp_eintrag->w / 2 + tp_fenster->x;
            fcn_0046cd90(x, tp_eintrag->y, element);
        } else {
            x = g_00fb9072 / 2 - tp_eintrag->w / 2;
            fcn_0046cd90(x, tp_eintrag->y, element);
        }
    }
}
