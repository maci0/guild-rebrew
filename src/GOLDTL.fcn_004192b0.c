// FUNCTION: GOLD 0x00417cf0
// FUNCTION: GOLDTL 0x004192b0

#include <stdio.h>

void __cdecl fcn_004238f0(char* o, int v);
int __cdecl fcn_00423670(char* o, int a, int b);
void __cdecl fcn_00423550(char* o);

void __cdecl fcn_004192b0(char* r, int a2, int a3, int a4)
{
	char buf[0x100];

	if (r == 0 || *(char**) (r + 0x34) == 0) {
		return;
	}
	if (*(int*) (*(char**) (r + 0x34) + 4) == 0) {
		sprintf(buf, "Entry-Handle missing for %s", r);
		sprintf(buf, "3dSound-Handle is attached to %s", *(char**) (r + 0x38));
		return;
	}
	*(int*) (*(char**) (r + 0x34) + 0xc) = a3;
	*(int*) (r + 0x44) = a3;
	fcn_004238f0(*(char**) (r + 0x34), a3);
	*(int*) (r + 0x4c) = a4;
	if (*(int*) (r + 0x50) == 0) {
		fcn_00423670(*(char**) (r + 0x34), a2, a4);
		*(int*) (r + 0x3c) = 0;
		return;
	}
	fcn_00423550(*(char**) (r + 0x34));
	*(int*) (r + 0x3c) = 0;
}
