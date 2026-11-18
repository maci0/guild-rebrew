#include "client_types.h"
#include "Develop/DieGildeAddOn/game/aemter.h"

extern Rec18_68da68 amt_OfficeSlots[42];
extern Rec18_68da68 g_68da68[];
extern char* __cdecl gm_LookupEntityRecordById(int id);

/* ADDRESS: GOLDTL 0x004e8c00 */
int __cdecl fcn_004e8c00(int group, int max, OFFICE_SLOT* out)
{
	int n;
	int i;
	int start;

	if (group == 0)
		return 0;
	if (group <= 6)
		start = 30;
	else if (group == 5)
		start = 42;
	else
		return 0;
	n = 0;
	for (i = start - 1; i >= 0 && n < max; i--) {
		if (((OFFICE_ROLE_TEMPLATE*)g_68da68)[((OFFICE_SLOT*)amt_OfficeSlots)[i].mamt].f4 == group &&
		    gm_LookupEntityRecordById(((OFFICE_SLOT*)amt_OfficeSlots)[i].mplayerid) != 0)
			out[n++] = ((OFFICE_SLOT*)amt_OfficeSlots)[i];
	}
	return n;
}
