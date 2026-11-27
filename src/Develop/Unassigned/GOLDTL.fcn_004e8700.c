


#include "client_types.h"
typedef Rec18_68da68 Rec18;
// SIZE 0x18

extern Rec18_68da68 amt_OfficeSlots[42];

void __cdecl amt_SetType26OfficeHolder(int holder)
{
	int i;

	for (i = 41; i != 0; i--) {
		if (amt_OfficeSlots[i].type == 0x26) {
			amt_OfficeSlots[i].x4 = holder;
			return;
		}
	}
}
