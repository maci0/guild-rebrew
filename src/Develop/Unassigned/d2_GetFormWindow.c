#include "client_types.h"
extern D2_FORM_RECORD g_1038140[];

/* ADDRESS: GOLDTL 0x00472830 */
int __cdecl d2_GetFormWindow(int formIndex, int windowIndex)
{
	if (windowIndex > *(int*) (((char*)g_1038140) + formIndex * 0x2bc + 0x184) || windowIndex < 0) {
		return -1;
	}
	return ((int*) (((char*)g_1038140) + formIndex * 0x2bc + 4))[windowIndex];
}
