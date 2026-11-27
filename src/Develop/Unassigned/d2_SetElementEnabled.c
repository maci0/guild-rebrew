extern char* g_1015ea0;
#include "Develop/Units/d2.v1/d2_gui.h"
/* ADDRESS: GOLDTL 0x00472640 */
void __cdecl d2_SetElementEnabled(int elementId, int enabled)
{
	int disabled;

	if (elementId != -1) {
		disabled = enabled == 0;
		((D2_CONTROL_TL*) (g_1015ea0))[elementId].disabled = disabled;
		((D2_CONTROL_TL*) (g_1015ea0))[elementId].value_060 = disabled;
	}
}
