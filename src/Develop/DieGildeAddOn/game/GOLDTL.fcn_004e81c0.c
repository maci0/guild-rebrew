


#include "Develop/DieGildeAddOn/game/aemter.h"

int __cdecl amt_AssignEntityOfficeDefault(unsigned char* entity, unsigned char* other_entity)
{
	int l0[6];
	int l1[6];

	if (srv_GetEntityOfficeSlot(entity, l1, l0) == 0) {
		return -1;
	}
	if (other_entity == 0) {
		return -1;
	}
	return amt_SendOfficeCommand(l0[0], entity, other_entity, 2, 1);
}
