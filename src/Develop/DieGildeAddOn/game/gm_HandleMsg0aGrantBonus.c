


extern unsigned char gm_ActiveTownIndex;

void* __cdecl gm_LookupEntityRecordById(int);
unsigned short __cdecl gm_RandomMod(int);
#include "Develop/DieGildeAddOn/game/spiel.h"
void __cdecl io_FormatTextBuffer(void*, int, int);
void __cdecl cm_RequestTransferCurrencyNoKill(int, int, char, int);
void __cdecl he_PostEntityMessage(int, int, void*, int, int, int);

int __cdecl gm_HandleMsg0aGrantBonus(void* request)
{
	char buf[0x100];
	double d;
	int roll;
	void* p;
	int n;

	p = gm_LookupEntityRecordById(*(int*) request);
	if (p == 0) {
		return 1;
	}
	roll = gm_RandomMod(2);
	d = (double) roll + 1.0;
	n = (int) (((double) gm_WalkEntityChain(*(unsigned short*) p) * d) *
	    0.0125);
	io_FormatTextBuffer(buf, *(unsigned short*) ((char*) request + 4) + 0x12e7, n);
	cm_RequestTransferCurrencyNoKill(*(int*) request, -1, (*(char*)&gm_ActiveTownIndex), n);
	he_PostEntityMessage(*(int*) ((char*) p + 4), *(int*) ((char*) p + 4), buf,
	    (unsigned) strlen(buf) > 0x100, 0x603, 0);
	return 0;
}
