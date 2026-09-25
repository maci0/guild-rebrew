#include <stdio.h>

int __cdecl fcn_00464830(FILE* fin, int* pi);

// FUNCTION: GOLD 0x004679c0
// SIZE: 77
// FUNCTION: GOLDTL 0x4647e0
// SIZE: 77
int __cdecl fcn_004647e0(FILE* fin, unsigned long* pX)
{
	unsigned long x;
	int i;
	int err;

	err = fcn_00464830(fin, &i);
	x = (unsigned long) i;
	if (err == 0) {
		err = fcn_00464830(fin, &i);
	}
	x += ((unsigned long) i) << 8;
	if (err == 0) {
		*pX = x;
	} else {
		*pX = 0;
	}
	return err;
}
