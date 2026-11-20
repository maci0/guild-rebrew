/* ADDRESS: GOLDTL 0x01015ea0 */
extern char* g_1015ea0;
#include "Develop/Units/d2.v1/d2_gui.h"

void __cdecl fcn_00469090(int);

/* ADDRESS: GOLDTL 0x00469110 */
void __cdecl fcn_00469110(int index, int a2)
{
	((D2_CONTROL_TL*)g_1015ea0)[index].width = a2;
	fcn_00469090(index);
}
