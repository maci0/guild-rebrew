/* Owned (both targets) by src/GOLDTL.fcn_005b24b0.c. */
extern unsigned char g_773d75;

#include <string.h>

unsigned char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl gm_RandomMod(int);
#include "Develop/DieGildeAddOn/game/spiel.h"
int __cdecl fcn_004c51a0(int, int, unsigned char, int);
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl fcn_00545d40(int, int, void*, int, int, void*);


/* ADDRESS: GOLDTL 0x004bb540 */
int __cdecl fcn_004bb540(void* a1)
{
	int n;
	double d;
	char buf[0x100];
	unsigned char* p;
	int r;
	unsigned int len;

	p = gm_LookupEntityRecordById(*(int*) a1);
	if (p == 0) {
		return 1;
	}
	if (*(int*) ((char*) p + 0x2c) == 0) {
		return 0x400;
	}
	n = gm_RandomMod(4) & 0xffff;
	d = (double) n + 1.0;
	n = gm_WalkEntityChain(*(short*) p);
	r = (int) (((double) n * d) * 0.01);
	io_FormatTextBuffer(buf, *(unsigned short*) ((char*) a1 + 4) + 0x12e7, r);
	len = strlen(buf);
	fcn_00545d40(*(int*) ((char*) p + 4), *(int*) ((char*) p + 4), buf,
	    0x100 < len, 0x603, 0);
	fcn_004c51a0(-1, *(int*) a1, g_773d75, r);
	return 0;
}
