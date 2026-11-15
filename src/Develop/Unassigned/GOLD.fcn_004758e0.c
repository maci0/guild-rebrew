#include <string.h>
#include "gold_gui.h"
extern GuiObj g_00fb1020[];
int __cdecl fcn_00472cd0(int);
void __cdecl fcn_00478fb0(int);

/* ADDRESS: GOLD 0x004758e0 */
void __cdecl fcn_004758e0(int index)
{
    GuiObj* object;
    int i;
    int off;

    if (index > 0x30 && index < 1)
        return;
    off = index * sizeof(GuiObj);
    object = (GuiObj*) ((char*) g_00fb1020 + off);
    if (*(int*) ((char*) g_00fb1020 + off + 0x190) == 0)
        return;
    for (i = *(int*) ((char*) g_00fb1020 + off + 0x184) - 1; i >= 0; i--)
        fcn_00472cd0(*(int*) ((char*) g_00fb1020 + off + 4 + i * 4));
    if (*(int*) ((char*) object + 0x1a4) != 0)
        fcn_00478fb0(*(int*) ((char*) object + 0x1a4));
    if (*(int*) ((char*) object + 0x1a8) != 0)
        fcn_00478fb0(*(int*) ((char*) object + 0x1a8));
    memset(object, 0, sizeof(*object));
}
