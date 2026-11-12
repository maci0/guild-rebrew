#include "gold_gui.h"

extern GuiObj g_00fb1020[];
extern GuiEnt* g_00f8f080;
void __cdecl fcn_00475a90(int index, int value);

/* ADDRESS: GOLD 0x00475580 */
void __cdecl fcn_00475580(int index, int value)
{
    GuiObj* object;
    int i;

    object = &g_00fb1020[index];
    if (object->used != 0) {
        for (i = 0; i < 0x300; i++) {
            if (g_00f8f080[i].kind != 0 &&
                g_00f8f080[i].f40 == (int) object) {
                fcn_00475a90(i, value);
            }
        }
        *(int*) ((char*) object + 0x1a0) = value;
    }
}
