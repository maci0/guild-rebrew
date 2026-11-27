

#include <stdio.h>

long __cdecl sbs_GetFileSize(char* path)
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
