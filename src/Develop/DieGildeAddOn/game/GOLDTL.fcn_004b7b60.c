#include <string.h>

extern unsigned char g_773d75;

unsigned short* __cdecl fcn_00508e40(int);
int __cdecl fcn_005c6270(void*, int);
unsigned short __cdecl gm_RandomMod(unsigned short);
#include "Develop/DieGildeAddOn/game/spiel.h"
void __cdecl fcn_0051af00(void*, int, ...);
void __cdecl fcn_004c51a0(int, int, unsigned char, int);
void __cdecl fcn_00545d40(int, int, char*, int, int, int);


/* ADDRESS: GOLDTL 0x004b7b60 */
int __cdecl fcn_004b7b60(int* a1)
{
	char buf[0x400];
	unsigned short* e;
	int v;

	e = fcn_00508e40(a1[0]);
	if (e == 0)
		return 1;
	if (fcn_005c6270(e, 0x290) != 0)
		return 0x400;
	v = (int) ((gm_RandomMod(3) + 1.0) * gm_WalkEntityChain(*e) * 0.01);
	fcn_0051af00(buf, *(unsigned short*) (a1 + 1) + 0x12e7, gm_RandomMod(0xf) + 2, v);
	fcn_004c51a0(-1, a1[0], g_773d75, v);
	fcn_00545d40(*(int*) (e + 2), *(int*) (e + 2), buf, strlen(buf) > 0x100, 0x603, 0);
	return 0;
}
