/* ADDRESS: GOLDTL 0x01015ea0 */
extern char* g_1015ea0;
#include "Develop/Units/d2.v1/d2_gui.h"

void __cdecl d2_CenterElement(int);

/* ADDRESS: GOLDTL 0x00469110 */
void __cdecl d2_SetElementWidth(int index, int a2)
{
	((D2_CONTROL_TL*)g_1015ea0)[index].width = a2;
	d2_CenterElement(index);
}
