

#include <stdio.h>

int __cdecl fcn_00423960(void);

int __cdecl fcn_004254c0(char* path)
{
	int r;
	FILE* f;

	r = 0;
	if (*(int*) 0x6b7d74 != 0) {
		f = fopen(path, (char*) 0x6790b0);
		if (f != 0) {
			if (fwrite(*(void**) 0x6b7d78, fcn_00423960(), 1, f) != 1) {
				r = -1;
			}
			fclose(f);
		}
	}
	return r;
}
