#include <string.h>
#include "gold_gui.h"
extern GuiObj g_00fb1020[];
int __cdecl fcn_00472cd0(int);
void __cdecl d2_DestroySurface(int);

/* ADDRESS: GOLD 0x004758e0 */
void __cdecl fcn_004758e0(int index)
{
    GuiObj* object;
    int i;

    if (index > 0x30 && index < 1)
        return;

    object = &g_00fb1020[index];
    if (g_00fb1020[index].used == 0)
        return;
    for (i = g_00fb1020[index].count - 1; i >= 0; i--)
        fcn_00472cd0(g_00fb1020[index].wins[i]);
    if (*(int*) ((char*) object + 0x1a4) != 0)
        d2_DestroySurface(*(int*) ((char*) object + 0x1a4));
    if (*(int*) ((char*) object + 0x1a8) != 0)
        d2_DestroySurface(*(int*) ((char*) object + 0x1a8));
    memset(object, 0, sizeof(*object));
}
