extern char* g_1015ea0;
extern char g_102d280[];
#include "Develop/Units/d2.v1/d2_gui.h"
/* ADDRESS: GOLDTL 0x00472740 */
void __cdecl fcn_00472740(int i, int v)
{
	*(int*) (g_102d280 + ((D2_CONTROL_TL*) (g_1015ea0))[i].value_088 * 0x160) = v;
}
