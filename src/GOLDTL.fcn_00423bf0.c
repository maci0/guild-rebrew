// FUNCTION: GOLDTL 0x423bf0
// SIZE: 83

#include <stdio.h>

int __cdecl fcn_00423bf0(char* path, int* d)
{
	int r;
	FILE* f;

	r = 0;
	f = fopen(path, (char*) 0x6750e8);
	if (d[1] != 0 && f != 0) {
		if (fwrite((void*) d[2], d[1], 1, f) != 1) {
			r = -1;
		}
		fclose(f);
		return r;
	}
	return -1;
}
