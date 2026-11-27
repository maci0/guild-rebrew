extern char* g_1015ea0;
extern char g_102d280[];
#include "Develop/Units/d2.v1/d2_gui.h"
/* ADDRESS: GOLDTL 0x00472740 */
void __cdecl d2_SetFieldMultiplier(int element_id, int multiplier)
{
	*(int*) (g_102d280 + ((D2_CONTROL_TL*) (g_1015ea0))[element_id].value_088 * 0x160) = multiplier;
}
