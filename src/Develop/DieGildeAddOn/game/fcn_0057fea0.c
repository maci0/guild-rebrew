#include "Develop/DieGildeAddOn/game/entity.h"

void __cdecl fcn_004ec780(int);
int __cdecl fcn_004e8d10(EntityStruct* slot, int mode, int* out);
void __cdecl fcn_004e7d40(EntityStruct* slot, int value);

/* ADDRESS: GOLDTL 0x0057fea0 */
void __cdecl fcn_0057fea0(int a1)
{
	unsigned char* p;
	EntityStruct* slot;
	int index;
	int value[3];

	if (a1 == 0) {
		fcn_004ec780(1);
		return;
	}
	if (a1 != 1) {
		return;
	}
	for (index = 0, p = (unsigned char*) 0x7f4ca2; (int) p < 0x85a0a2; p += 0x21c, index++) {
		if (*p == 5) {
			slot = (EntityStruct*) (0x7f4ca0 + index * 0x21c);
			if (fcn_004e8d10(slot, 1, value) > 0) {
				fcn_004e7d40(slot, value[0]);
			}
			break;
		}
	}
}
