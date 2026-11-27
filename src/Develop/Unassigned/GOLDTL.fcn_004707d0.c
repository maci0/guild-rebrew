#include "client_types.h"
extern D2_FORM_RECORD g_1038140[];

void __cdecl d2_BringWindowToFront(int id);

/* ADDRESS: GOLDTL 0x004707d0 */
void __cdecl d2_BringFormToFront(int k)
{
	int j;

	for (j = 0; j < *(int*) (((char*)g_1038140) + k * 0x2bc + 0x184); j++) {
		d2_BringWindowToFront(((int*) (((char*)g_1038140) + k * 0x2bc + 4))[j]);
	}
}
