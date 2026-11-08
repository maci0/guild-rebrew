#include <string.h>

#pragma intrinsic(strlen, strcpy, strcat)

char* __cdecl fcn_00423a50(int);

char* __cdecl fcn_004247c0(int dir, char* buf, int size);
char* __cdecl fcn_00424790(char* p, char* buf, int size);

/* ADDRESS: GOLDTL 0x00423f60 */
int __cdecl fcn_00423f60(int a1, char* a2)
{
	char* dest;

	dest = fcn_00423a50(a1);
	if (dest != 0) {
		strcpy(dest, a2);
		return 0;
	}
	return -1;
}

/* ADDRESS: GOLDTL 0x00423f90 */
int __cdecl fcn_00423f90(int dir, const char* name, const char* src)
{
	char buf[0x100];
	char* p;
	int r;

	r = -1;
	p = fcn_004247c0(dir, buf, 0x100);
	while (p != 0) {
		if (strcmp(p, name) == 0) {
			strcpy(p, src);
			r = 0;
			break;
		}
		p = fcn_00424790(p, buf, 0x100);
	}
	return r;
}
