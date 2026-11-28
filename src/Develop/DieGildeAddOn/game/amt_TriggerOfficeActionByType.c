


#include "Develop/client_types.h"
typedef Rec18_68da68 Rec18;
// SIZE 0x18

extern Rec18_68da68 amt_OfficeSlots[42];

#include "Develop/DieGildeAddOn/game/aemter.h"

void __cdecl amt_TriggerOfficeActionByType(int type)
{
	int i;

	for (i = 0; i < 30; i++) {
		if (amt_OfficeSlots[i].type == type) {
			amt_SendOfficeCommand(amt_OfficeSlots[i].id, 0, 0, 3, 0xff);
			return;
		}
	}
}
