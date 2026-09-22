// FUNCTION: GOLDTL 0x4e8af0
// SIZE: 80

#include <string.h>

#pragma intrinsic(memcpy, memset)

int __cdecl fcn_004e8af0(unsigned char key, void* dst)
{
	int i;
	int a;

	i = 0;
	a = 0x9a9220;
	for (;;) {
		if (a >= 0x9a9610) {
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
	memcpy(dst, (void*) (0x9a9220 + i * 24), 24);
	return 1;
}
