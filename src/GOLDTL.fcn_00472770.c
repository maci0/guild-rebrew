#include "Develop/Units/d2.v1/d2_gui.h"

/* ADDRESS: GOLDTL 0x00472770 */
void __cdecl fcn_00472770(int i, int v)
{
	*(int*) (d2_BildArgument2 + *(int*) (g_1015ea0 + i * 0x2f4 + 0x88) * 0x160) = v;
}
