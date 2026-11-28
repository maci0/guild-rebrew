#include "Develop/Units/d2.v1/d2_gui.h"

/* ADDRESS: GOLDTL 0x00468cd0 */
/* ADDRESS: GOLDDE 0x0045c650 */
void __cdecl d2_SetValueGaugeFlags(int i, int v)
{
	*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[i].payload.fields.value_098)) = v;
}
