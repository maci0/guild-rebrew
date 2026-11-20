#include "Develop/DieGildeAddOn/game/entity.h"

void __cdecl fcn_004ec780(int);
int __cdecl amt_SelectOfficeCandidates(EntityStruct* slot, int mode, int* out);
void __cdecl amt_ApplyForOffice(EntityStruct* slot, int value);

/* ADDRESS: GOLDTL 0x0057fea0 */
void __cdecl fcn_0057fea0(int action)
{
	unsigned char* p;
	EntityStruct* slot;
	int index;
	int value[3];

	if (action == 0) {
		fcn_004ec780(1);
		return;
	}
	if (action != 1) {
		return;
	}
	for (index = 0, p = (unsigned char*) 0x7f4ca2; (int) p < 0x85a0a2; p += 0x21c, index++) {
		if (*p == 5) {
			slot = (EntityStruct*) (0x7f4ca0 + index * 0x21c);
			if (amt_SelectOfficeCandidates(slot, 1, value) > 0) {
				amt_ApplyForOffice(slot, value[0]);
			}
			break;
		}
	}
}
