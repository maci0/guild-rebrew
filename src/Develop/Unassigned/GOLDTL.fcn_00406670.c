


#include <string.h>

char* __cdecl fcn_0040c0a0(char*);
void __cdecl fcn_004065c0(void);

int __cdecl fcn_00406670(char* p, char* s)
{
	char* e;

	if (!(p[0x8c] & 0x10)) {
		return 0;
	}
	e = fcn_0040c0a0(p);
	if (e == 0) {
		return 0;
	}
	*(char**) (e + 0x14) = p;
	*(int*) (e + 0xc) = 0;
	*(void**) e = (void*) fcn_004065c0;
	e[9] = 0x30;
	*(int*) (e + 0x28) = 0;
	e[0x10] = 0;
	strcpy(e + 0xf0, s);
	return 1;
}
