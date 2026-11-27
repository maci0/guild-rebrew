

#include <string.h>

char* __cdecl sbs_FindSet(char*);

char* __cdecl sbs_GetFirstSetSample(char* name, char* dst, int n)
{
	char* r = 0;
	char* p;
	char* s;

	if (*(char**) 0x6b7d68 != 0) {
		p = sbs_FindSet(name);
		if (p != 0) {
			s = *(char**) (p + 0x38);
			if (s != 0) {
				strncpy(dst, s, n);
				r = s;
			}
		}
	}
	return r;
}
