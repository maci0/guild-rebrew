


#include "client_types.h"
typedef Rec18_68da68 Rec18;
// SIZE 0x18

extern Rec18_68da68 amt_OfficeSlots[42];

int __cdecl amt_FindOfficeSlotByType(int type, Rec18* out)
{
	int i;

	for (i = 0; i < 42; i++) {
		if (amt_OfficeSlots[i].type == type) {
			break;
		}
	}
	if (i >= 42) {
		return 0;
	}
	*out = amt_OfficeSlots[i];
	return 1;
}
