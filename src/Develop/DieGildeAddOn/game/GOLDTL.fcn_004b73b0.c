


extern unsigned char g_773d75;

void* __cdecl gm_LookupEntityRecordById(int);
unsigned short __cdecl gm_RandomMod(int);
#include "Develop/DieGildeAddOn/game/spiel.h"
int  __cdecl fcn_005c6270(void*, int);
void __cdecl io_FormatTextBuffer(void*, int, int);
void __cdecl cm_RequestTransferCurrencyNoKill(int, int, char, int);
void __cdecl fcn_00545d40(int, int, void*, int, int, int);

int __cdecl gm_HandleMsg0dGrantBonus(void* request)
{
	char buf[0x100];
	double d;
	int v;
	void* entity;
	int n;

	entity = gm_LookupEntityRecordById(*(int*) request);
	if (entity == 0) {
		return 1;
	}
	if (fcn_005c6270(entity, 0x290) != 0) {
		return 0x400;
	}
	v = gm_RandomMod(3);
	d = (double) v + 2.0;
	n = (int) (((double) gm_WalkEntityChain(*(unsigned short*) entity) * d) *
	    0.01);
	io_FormatTextBuffer(buf, *(unsigned short*) ((char*) request + 4) + 0x12e7, n);
	cm_RequestTransferCurrencyNoKill(-1, *(int*) request, (*(char*)&g_773d75), n);
	fcn_00545d40(*(int*) ((char*) entity + 4), *(int*) ((char*) entity + 4), buf,
	    (unsigned) strlen(buf) > 0x100, 0x603, 0);
	return 0;
}
