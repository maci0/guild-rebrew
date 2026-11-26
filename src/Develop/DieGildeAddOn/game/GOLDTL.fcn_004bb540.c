/* Owned (both targets) by src/GOLDTL.fcn_005b24b0.c. */
extern unsigned char g_773d75;

#include <string.h>

unsigned char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl gm_RandomMod(int);
#include "Develop/DieGildeAddOn/game/spiel.h"
int __cdecl cm_RequestTransferCurrencyNoKill(int, int, unsigned char, int);
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl he_PostEntityMessage(int, int, void*, int, int, void*);


/* ADDRESS: GOLDTL 0x004bb540 */
int __cdecl fcn_004bb540(void* record)
{
	int n;
	double d;
	char buf[0x100];
	unsigned char* p;
	int r;
	unsigned int len;

	p = gm_LookupEntityRecordById(*(int*) record);
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
	io_FormatTextBuffer(buf, *(unsigned short*) ((char*) record + 4) + 0x12e7, r);
	len = strlen(buf);
	he_PostEntityMessage(*(int*) ((char*) p + 4), *(int*) ((char*) p + 4), buf,
	    0x100 < len, 0x603, 0);
	cm_RequestTransferCurrencyNoKill(-1, *(int*) record, g_773d75, r);
	return 0;
}
