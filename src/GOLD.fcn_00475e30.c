#include "Develop/Units/d2.v1/d2_gui.h"

/* ADDRESS: GOLD 0x00475e30 */
void __cdecl fcn_00475e30(int idx, int flag)
{
    if (idx != -1) {
        g_00f8f080[idx].hidden = (flag == 0);
        *(int*) ((char*) (g_00f8f080 + idx) + 0x50) = (flag == 0);
    }
}
