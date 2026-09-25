// FUNCTION: GOLD 0x004e0e90
// SIZE: 219
// FUNCTION: GOLDTL 0x4e27b0
// SIZE: 219

#include <string.h>

extern char* g_14a9a28;
extern char g_6b5c60[];

char* __cdecl fcn_00508e40(int);
void __cdecl fcn_004c57e0(int, int);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_004e6240(char*, char*, char*, char*);

int __cdecl fcn_004e27b0(char* x)
{
	char buf[0x200];
	char* a;
	char* b;
	char* c;

	a = fcn_00508e40(*(int*) (x + 0x34));
	b = fcn_00508e40(*(int*) (x + 0x38));
	if (a == 0 || b == 0)
		return 0;
	c = fcn_00508e40(*(int*) (a + 0x5c));
	if (c == 0 || c[2] == 0xf) {
		fcn_004c57e0(*(int*) (b + 4), 1);
		return 0;
	}
	if (a[2] == 6 || a[2] == 7) {
		fcn_0051af00(buf, 0x11c1);
		strcat(buf, g_14a9a28);
		fcn_004e6240(a, x, buf, g_6b5c60);
	}
	return 1;
}
