

#include <string.h>

char* __cdecl fcn_00423ac0(char*);

char* __cdecl fcn_004247c0(char* name, char* dst, int n)
{
	char* r = 0;
	char* p;
	char* s;

	if (*(char**) 0x6b7d68 != 0) {
		p = fcn_00423ac0(name);
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
