#include "client_types.h"
extern Rec18_68da68 amt_OfficeSlots[42];
extern Rec18_68da68 amt_OfficeSlots[42];



#include <string.h>

#pragma intrinsic(memcpy, memset)

int __cdecl amt_FindOfficeSlotByKey(unsigned char key, void* dst)
{
	int i;
	int a;

	i = 0;
	a = (int) amt_OfficeSlots;
	for (;;) {
		if (a >= (int) amt_OfficeSlots + 0x3f0) {
			return 0;
		}
		if (*(unsigned char*) a == key) {
			break;
		}
		a += 0x18;
		i++;
	}
	if (i >= 0x2a) {
		return 0;
	}
	memcpy(dst, (void*) ((int) amt_OfficeSlots + i * 24), 24);
	return 1;
}
