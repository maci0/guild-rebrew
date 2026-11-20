


#include "client_types.h"
typedef Rec18_68da68 Rec18;
// SIZE 0x18

extern Rec18_68da68 amt_OfficeSlots[42];
extern Rec18_68da68 g_68da68[];

int __cdecl amt_CollectOfficeGroup7(int all, int max, Rec18* out)
{
	int n;
	int i;

	n = 0;
	for (i = 30; i < 37; i++) {
		if (n >= max) {
			break;
		}
		if (g_68da68[amt_OfficeSlots[i].type].x4 == 7 && (all != 0 || amt_OfficeSlots[i].x4 != -1)) {
			*out = amt_OfficeSlots[i];
			n++;
			out++;
		}
	}
	return n;
}
