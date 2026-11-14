extern char* g_006ed918;

#include "Develop/Units/Error/error_message.h"

/* ADDRESS: GOLD 0x0046cab0 */
void __cdecl fcn_0046cab0(int i)
{
	char* e;
	int* p;

	e = g_006ed918 + i * 0x54;
	if ((*(int*) (e + 0x3c) == 5 || *(int*) (e + 0x3c) == 8) && *(int*) (e + 0x30) == 0) {
		i = *(int*) (e + 0x4c);
	}
	p = (int*) (g_006ed918 + i * 0x54 + 0x40);
	if (*p > 0) {
		*p -= 1;
		return;
	}
	ReportClientMessage("d2_SubRefcount: invalid refcount!");
}
