#include "client_types.h"
// GLOBAL: GOLDTL 0x9a9220
extern Rec18_68da68 g_9a9220[42];
// GLOBAL: GOLD 0x925120
extern Rec18_68da68 g_9a9220[42];
// FUNCTION: GOLD 0x004e6f30
// FUNCTION: GOLDTL 0x4e8af0

#include <string.h>

#pragma intrinsic(memcpy, memset)

int __cdecl fcn_004e8af0(unsigned char key, void* dst)
{
	int i;
	int a;

	i = 0;
	a = (int) g_9a9220;
	for (;;) {
		if (a >= (int) g_9a9220 + 0x3f0) {
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
	memcpy(dst, (void*) ((int) g_9a9220 + i * 24), 24);
	return 1;
}
