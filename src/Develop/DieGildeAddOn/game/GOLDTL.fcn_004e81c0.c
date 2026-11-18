


#include "Develop/DieGildeAddOn/game/aemter.h"

int __cdecl fcn_004e81c0(unsigned char* entity, unsigned char* a2)
{
	int l0[6];
	int l1[6];

	if (srv_GetEntityOfficeSlot(entity, l1, l0) == 0) {
		return -1;
	}
	if (a2 == 0) {
		return -1;
	}
	return fcn_004e8240(l0[0], entity, a2, 2, 1);
}
