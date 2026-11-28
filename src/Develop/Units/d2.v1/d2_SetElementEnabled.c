extern char* d2_Controls;
#include "Develop/Units/d2.v1/d2_gui.h"
/* ADDRESS: GOLDTL 0x00472640 */
/* ADDRESS: GOLDDE 0x00465830 */
void __cdecl d2_SetElementEnabled(int elementId, int enabled)
{
	int disabled;

	if (elementId != -1) {
		disabled = enabled == 0;
		((D2_CONTROL_TL*) (d2_Controls))[elementId].disabled = disabled;
		((D2_CONTROL_TL*) (d2_Controls))[elementId].value_060 = disabled;
	}
}
