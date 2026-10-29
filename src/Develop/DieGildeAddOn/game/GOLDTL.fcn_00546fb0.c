


#include "he_tables.h"

extern ApEvent g_7dcae0[256];

int __cdecl fcn_00546fb0(int k)
{
	int sum;
	int i;

	sum = 0;
	for (i = 0; i < 0x100; i++) {
		if (*(int*) ((char*) g_7dcae0 + i * 0x50 + 8) != 0 && *(int*) ((char*) g_7dcae0 + i * 0x50 + 4) == k) {
			sum += *(int*) ((char*) g_7dcae0 + i * 0x50 + 8);
		}
	}
	return sum;
}
