#include <string.h>

extern unsigned char g_773d75;

char* __cdecl fcn_00508e40(int id);
unsigned short __cdecl fcn_0042e410(int n);
#include "Develop/DieGildeAddOn/game/spiel.h"
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_004c51a0(int, int, char, int);
void __cdecl fcn_00545d40(int, int, char*, int, int, int);

// FUNCTION: GOLD 0x4b6480
// FUNCTION: GOLDTL 0x004b6650
int __cdecl fcn_004b6650(int* a)
{
	char buf[0x100];
	double d;
	char* t;
	int n;

	t = fcn_00508e40(a[0]);
	if (t == 0) {
		return 1;
	}
	d = fcn_0042e410(3) + 1.0;
	n = (int) (gm_WalkEntityChain(*(unsigned short*) t) * d * 0.01);
	fcn_0051af00(buf, *(unsigned short*) (a + 1) + 0x12e7, n);
	fcn_004c51a0(a[0], -1, (*(char*)&g_773d75), n);
	fcn_00545d40(*(int*) (t + 4), *(int*) (t + 4), buf, strlen(buf) > 0x100 ? strlen(buf) > 0x100 : 0, 0x603, 0);
	return 0;
}
