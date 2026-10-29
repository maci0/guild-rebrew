#include "client_types.h"
extern Rec18_68da68 g_9a9220[42];
extern Rec18_68da68 g_9a9220[42];



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
