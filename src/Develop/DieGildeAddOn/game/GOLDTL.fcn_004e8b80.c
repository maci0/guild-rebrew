


#include "client_types.h"
#include "Develop/DieGildeAddOn/game/aemter.h"
extern Rec18_68da68 g_9a9220[42];
extern Rec18_68da68 g_68da68[];

int __cdecl fcn_004e8b80(int kind, int max, OFFICE_SLOT* out)
{
	int n;
	int i;
	int start;

	if (kind == 0)
		return 0;
	if (kind <= 6)
		start = 30;
	else if (kind == 8)
		start = 42;
	else
		return 0;
	n = 0;
	for (i = start - 1; i >= 0 && n < max; i--) {
		if (((OFFICE_ROLE_TEMPLATE*)g_68da68)[((OFFICE_SLOT*)g_9a9220)[i].mamt].f4 == kind)
			out[n++] = ((OFFICE_SLOT*)g_9a9220)[i];
	}
	return n;
}
