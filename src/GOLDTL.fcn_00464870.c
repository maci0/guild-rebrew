#include <stdio.h>

int __cdecl fcn_00464830(FILE* fin, int* pi);

// FUNCTION: GOLD 0x00467a50
// FUNCTION: GOLDTL 0x464870
int __cdecl fcn_00464870(FILE* fin, unsigned long* pX)
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
		err = fcn_00464830(fin, &i);
	}
	x += ((unsigned long) i) << 16;
	if (err == 0) {
		err = fcn_00464830(fin, &i);
	}
	x += ((unsigned long) i) << 24;
	if (err == 0) {
		*pX = x;
	} else {
		*pX = 0;
	}
	return err;
}
