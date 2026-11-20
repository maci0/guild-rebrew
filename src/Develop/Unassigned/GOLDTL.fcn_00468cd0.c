#include "Develop/Units/d2.v1/d2_gui.h"

/* ADDRESS: GOLDTL 0x00468cd0 */
void __cdecl fcn_00468cd0(int i, int v)
{
	*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[i].payload.fields.value_098)) = v;
}
