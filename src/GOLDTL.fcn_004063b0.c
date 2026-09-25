// FUNCTION: GOLD 0x00405810
// SIZE: 91
// FUNCTION: GOLDTL 0x4063b0
// SIZE: 91

#include <string.h>

char* __cdecl fcn_0040c0a0(int);
void __cdecl fcn_00406280(void);

char* __cdecl fcn_004063b0(int a1, char* s, int a3, float a4)
{
	char* e;

	e = fcn_0040c0a0(a1);
	if (e == 0) {
		return e;
	}
	*(int*) (e + 0x30) = a3;
	*(void**) e = (void*) fcn_00406280;
	e[9] = 0x2e;
	*(float*) (e + 0x178) = 1.0f;
	*(int*) (e + 0x28) = 0;
	e[0x10] = 0;
	strcpy(e + 0xf0, s);
	*(float*) (e + 0x178) = a4;
	return e;
}
