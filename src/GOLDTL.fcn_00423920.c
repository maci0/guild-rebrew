

#include <stdio.h>

long __cdecl fcn_00423920(char* path)
{
	FILE* f;
	long r;

	r = 0;
	f = fopen(path, (char*) 0x6750e8);
	if (f != 0) {
		fseek(f, 0, 2);
		r = ftell(f);
		fclose(f);
	}
	return r;
}
