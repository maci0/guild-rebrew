#include "Develop/Units/d2.v1/d2_gui.h"
#include "Develop/client_types.h"
extern D2_RADIO_GROUP g_102cbc4[8];

/* ADDRESS: GOLDTL 0x00469540 */
void __cdecl d2_SetRadioGroupEnabled(int g, int flag)
{
	int j;

	for (j = 0; j < *(int*) (((char*)g_102cbc4) + g * 0x8c); j++) {
		*(int*)&((D2_CONTROL_TL*)d2_Controls)[((int*) (((char*)g_102cbc4) + g * 0x8c + 8))[j]].disabled = flag == 0;
	}
}
