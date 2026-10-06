// FUNCTION: GOLD 0x0053f210
// FUNCTION: GOLDTL 0x00546fe0

#include "he_tables.h"

extern ApEvent g_7dcae0[256];

int __cdecl fcn_00546fe0(int k)
{
	int sum;
	int i;

	sum = 0;
	for (i = 0; i < 0x100; i++) {
		if (*(int*) ((char*) g_7dcae0 + i * 0x50 + 0xc) != 0 && *(int*) ((char*) g_7dcae0 + i * 0x50 + 4) == k) {
			sum += *(int*) ((char*) g_7dcae0 + i * 0x50 + 0xc);
		}
	}
	return sum;
}
