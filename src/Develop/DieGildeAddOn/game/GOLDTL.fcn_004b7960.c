

void* __cdecl gm_LookupEntityRecordById(int);
unsigned short __cdecl gm_RandomMod(int);
#include "Develop/DieGildeAddOn/game/spiel.h"
int  __cdecl fcn_005c6270(void*, int);
void __cdecl io_FormatTextBuffer(void*, int, int);
void __cdecl cm_RequestTransferCurrencyNoKill(int, int, char, int);
void __cdecl fcn_00545d40(int, int, void*, int, int, int);

int __cdecl fcn_004b7960(void* request)
{
	char buf[0x400];
	double d;
	int roll;
	void* p;
	int n;

	p = gm_LookupEntityRecordById(*(int*) request);
	if (p == 0) {
		return 1;
	}
	if (fcn_005c6270(p, 0x290) != 0) {
		return 0x400;
	}
	roll = gm_RandomMod(2);
	d = (double) roll + *(double*) 0x6629c8;
	n = (int) (((double) gm_WalkEntityChain(*(unsigned short*) p) * d) *
	    *(double*) 0x6640e8);
	io_FormatTextBuffer(buf, *(unsigned short*) ((char*) request + 4) + 0x12e7, n);
	cm_RequestTransferCurrencyNoKill(-1, *(int*) request, *(char*) 0x773d75, n);
	fcn_00545d40(*(int*) ((char*) p + 4), *(int*) ((char*) p + 4), buf,
	    (unsigned) strlen(buf) > 0x100, 0x603, 0);
	return 0;
}
