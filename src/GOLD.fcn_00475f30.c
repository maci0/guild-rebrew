#include "Develop/Units/d2.v1/d2_gui.h"

/* ADDRESS: GOLD 0x00475f30 */
void __cdecl fcn_00475f30(int a, int b)
{
    *(int*) (d2_BildArgument2 + g_00f8f080[a].bild_offset * 0x160) = b;
}
