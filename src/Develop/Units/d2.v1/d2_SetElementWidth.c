/* ADDRESS: GOLDTL 0x01015ea0 */
extern char* d2_Controls;
#include "Develop/Units/d2.v1/d2_gui.h"

void __cdecl d2_CenterElement(int);

/* ADDRESS: GOLDTL 0x00469110 */
/* ADDRESS: GOLDDE 0x0045ca90 */
void __cdecl d2_SetElementWidth(int index, int width)
{
	((D2_CONTROL_TL*)d2_Controls)[index].width = width;
	d2_CenterElement(index);
}
