#include "Develop/Units/d2.v1/d2_gui.h"
#include <stddef.h>

typedef char GUI_GROESSE_PRUEFUNG[sizeof(GuiEnt) == 0x2ec ? 1 : -1];
typedef char GUI_BREITE_PRUEFUNG[offsetof(GuiEnt, w) == 0x14 ? 1 : -1];

void __cdecl fcn_0046c1c0(int element);

/* ADDRESS: GOLD 0x0046c250 */
void __cdecl fcn_0046c250(int element, int breite)
{
    g_00f8f080[element].w = (short)breite;
    fcn_0046c1c0(element);
}
