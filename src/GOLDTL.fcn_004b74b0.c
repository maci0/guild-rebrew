#include <string.h>

extern unsigned char g_773d75;

unsigned short* __cdecl fcn_00508e40(int);
int __cdecl fcn_005c6270(void*, int);
unsigned short __cdecl fcn_0042e410(unsigned short);
#include "Develop/DieGildeAddOn/game/spiel.h"
void __cdecl fcn_0051af00(void*, int, ...);
void __cdecl fcn_004c51a0(int, int, unsigned char, int);
void __cdecl fcn_00545d40(int, int, char*, int, int, int);

// FUNCTION: GOLD 0x004b7200
// FUNCTION: GOLDTL 0x4b74b0

int __cdecl fcn_004b74b0(int* a1)
{
	char buf[0x100];
	unsigned short* e;
	int v;

	e = fcn_00508e40(a1[0]);
	if (e == 0)
		return 1;
	if (fcn_005c6270(e, 0x290) != 0)
		return 0x400;
	v = (int) ((fcn_0042e410(2) + 1.0) * gm_WalkEntityChain(*e) * 0.01);
	if (v > gm_WalkEntityChain(*e))
		return 0;
	fcn_0051af00(buf, *(unsigned short*) (a1 + 1) + 0x12e7, v);
	fcn_004c51a0(-1, a1[0], g_773d75, v);
	fcn_00545d40(*(int*) (e + 2), *(int*) (e + 2), buf, strlen(buf) > 0x100, 0x603, 0);
	return 0;
}
