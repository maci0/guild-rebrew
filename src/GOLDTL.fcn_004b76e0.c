


extern unsigned char g_773d75;

void* __cdecl fcn_00508e40(int);
unsigned short __cdecl gm_RandomMod(int);
#include "Develop/DieGildeAddOn/game/spiel.h"
int  __cdecl fcn_005c6270(void*, int);

void __cdecl fcn_0051af00(void*, int, int);
void __cdecl fcn_004c51a0(int, int, char, int);
void __cdecl fcn_00545d40(int, int, void*, int, int, int);

int __cdecl fcn_004b76e0(void* a1)
{
	char buf[0x100];
	double d;
	int v;
	void* p;
	int n;

	p = fcn_00508e40(*(int*) a1);
	if (p == 0) {
		return 1;
	}
	if (*(char*) ((char*) p + 0x166) == 0 && *(char*) ((char*) p + 0x169) == 0) {
		return 0x400;
	}
	if (fcn_005c6270(p, 0x290) != 0) {
		return 0x400;
	}
	v = gm_RandomMod(4);
	d = (double) v + 1.0;
	n = (int) (((double) gm_WalkEntityChain(*(unsigned short*) p) * d) *
	    0.01);
	fcn_0051af00(buf, *(unsigned short*) ((char*) a1 + 4) + 0x12e7, n);
	fcn_004c51a0(-1, *(int*) a1, (*(char*)&g_773d75), n);
	fcn_00545d40(*(int*) ((char*) p + 4), *(int*) ((char*) p + 4), buf,
	    (unsigned) strlen(buf) > 0x100, 0x603, 0);
	return 0;
}
