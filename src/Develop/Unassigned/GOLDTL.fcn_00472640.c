extern char* g_1015ea0;
#include "Develop/Units/d2.v1/d2_gui.h"
/* ADDRESS: GOLDTL 0x00472640 */
void __cdecl fcn_00472640(int i, int flag)
{
	int v;

	if (i != -1) {
		v = flag == 0;
		((D2_CONTROL_TL*) (g_1015ea0))[i].disabled = v;
		((D2_CONTROL_TL*) (g_1015ea0))[i].value_060 = v;
	}
}
