#include <string.h>

#pragma intrinsic(strlen, strcpy, strcat)

char* __cdecl fcn_00423a50(int);

char* __cdecl sbs_GetFirstSetSample(int dir, char* buf, int size);
char* __cdecl sbs_GetNextSample(char* p, char* buf, int size);

/* ADDRESS: GOLDTL 0x00423f60 */
int __cdecl sbs_RenameRootSample(int a1, char* src)
{
	char* dest;

	dest = fcn_00423a50(a1);
	if (dest != 0) {
		strcpy(dest, src);
		return 0;
	}
	return -1;
}

/* ADDRESS: GOLDTL 0x00423f90 */
int __cdecl sbs_RenameSetSample(int dir, const char* name, const char* src)
{
	char buf[0x100];
	char* p;
	int r;

	r = -1;
	p = sbs_GetFirstSetSample(dir, buf, 0x100);
	while (p != 0) {
		if (strcmp(p, name) == 0) {
			strcpy(p, src);
			r = 0;
			break;
		}
		p = sbs_GetNextSample(p, buf, 0x100);
	}
	return r;
}
