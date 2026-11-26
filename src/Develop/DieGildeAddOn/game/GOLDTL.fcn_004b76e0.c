


extern unsigned char g_773d75;

void* __cdecl gm_LookupEntityRecordById(int);
unsigned short __cdecl gm_RandomMod(int);
#include "Develop/DieGildeAddOn/game/spiel.h"
int  __cdecl fcn_005c6270(void*, int);

void __cdecl io_FormatTextBuffer(void*, int, int);
void __cdecl fcn_004c51a0(int, int, char, int);
void __cdecl fcn_00545d40(int, int, void*, int, int, int);

int __cdecl gm_ApplyOfficePercentCredit(void* request)
{
	char buf[0x100];
	double d;
	int v;
	void* entity;
	int amount;

	entity = gm_LookupEntityRecordById(*(int*) request);
	if (entity == 0) {
		return 1;
	}
	if (*(char*) ((char*) entity + 0x166) == 0 && *(char*) ((char*) entity + 0x169) == 0) {
		return 0x400;
	}
	if (fcn_005c6270(entity, 0x290) != 0) {
		return 0x400;
	}
	v = gm_RandomMod(4);
	d = (double) v + 1.0;
	amount = (int) (((double) gm_WalkEntityChain(*(unsigned short*) entity) * d) *
	    0.01);
	io_FormatTextBuffer(buf, *(unsigned short*) ((char*) request + 4) + 0x12e7, amount);
	fcn_004c51a0(-1, *(int*) request, (*(char*)&g_773d75), amount);
	fcn_00545d40(*(int*) ((char*) entity + 4), *(int*) ((char*) entity + 4), buf,
	    (unsigned) strlen(buf) > 0x100, 0x603, 0);
	return 0;
}
