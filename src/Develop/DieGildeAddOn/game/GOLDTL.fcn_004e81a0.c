

#include "Develop/DieGildeAddOn/game/aemter.h"

void __cdecl amt_VacateOfficeSlot(int id)
{
	amt_SendOfficeCommand(id, 0, 0, 3, 0xff);
}
