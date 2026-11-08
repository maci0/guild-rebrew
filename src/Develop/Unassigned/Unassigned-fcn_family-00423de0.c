#include <string.h>

extern int g_6b7d6c;

char* __cdecl fcn_00423ac0(char*);

/* ADDRESS: GOLDTL 0x00423de0 */
int __cdecl fcn_00423de0(char* s)
{
	int r = 0;

	if (*(char**) 0x6b7d68 != 0) {
		strncpy(*(char**) 0x6b7d68, s, 0x32);
		g_6b7d6c++;
	} else {
		r = -1;
	}
	return r;
}

/* ADDRESS: GOLDTL 0x00423f20 */
int __cdecl fcn_00423f20(char* a1, char* s)
{
	int r = 0;
	char* p;

	p = fcn_00423ac0(a1);
	if (p != 0) {
		strncpy(p, s, 0x32);
		g_6b7d6c++;
	} else {
		r = -1;
	}
	return r;
}
