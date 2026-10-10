/* Owned (both targets) by src/GOLDTL.fcn_004b6f00.c. */
extern double g_6629c8;
extern double g_6640e8;
/* Owned (both targets) by src/GOLDTL.fcn_005b24b0.c. */
extern unsigned char g_773d75;

#include <string.h>

unsigned char* __cdecl fcn_00508e40(int);
int __cdecl fcn_0042e410(int);
#include "Develop/DieGildeAddOn/game/spiel.h"
int __cdecl fcn_004c51a0(int, int, unsigned char, int);
void __cdecl fcn_0051af00(void*, int, ...);
void __cdecl fcn_00545d40(int, int, void*, int, int, void*);

// FUNCTION: GOLDTL 0x4bb540
// FUNCTION: GOLD 0x4bb150

int __cdecl fcn_004bb540(void* a1)
{
	int n;
	double d;
	char buf[0x100];
	unsigned char* p;
	int r;
	unsigned int len;

	p = fcn_00508e40(*(int*) a1);
	if (p == 0) {
		return 1;
	}
	if (*(int*) ((char*) p + 0x2c) == 0) {
		return 0x400;
	}
	n = fcn_0042e410(4) & 0xffff;
	d = (double) n + g_6629c8;
	n = gm_WalkEntityChain(*(short*) p);
	r = (int) (((double) n * d) * g_6640e8);
	fcn_0051af00(buf, *(unsigned short*) ((char*) a1 + 4) + 0x12e7, r);
	len = strlen(buf);
	fcn_00545d40(*(int*) ((char*) p + 4), *(int*) ((char*) p + 4), buf,
	    0x100 < len, 0x603, 0);
	fcn_004c51a0(-1, *(int*) a1, g_773d75, r);
	return 0;
}
