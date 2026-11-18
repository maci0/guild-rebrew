


extern unsigned char g_773d75;

void* __cdecl gm_LookupEntityRecordById(int);
unsigned short __cdecl gm_RandomMod(int);
#include "Develop/DieGildeAddOn/game/spiel.h"
int  __cdecl fcn_005c6270(void*, int);

void __cdecl io_FormatTextBuffer(void*, int, int);
void __cdecl fcn_004c51a0(int, int, char, int);
void __cdecl fcn_00545d40(int, int, void*, int, int, int);

int __cdecl fcn_004b75c0(void* record)
{
	char buf[0x100];
	double d;
	int roll;
	void* p;
	int n;

	p = gm_LookupEntityRecordById(*(int*) record);
	if (p == 0) {
		return 1;
	}
	if (fcn_005c6270(p, 0x290) != 0) {
		return 0x400;
	}
	if (gm_MapEntityStatRange(*(unsigned char*) ((char*) p + 0x164)) == 7) {
		return 0x400;
	}
	roll = gm_RandomMod(4);
	d = (double) roll + 1.0;
	n = (int) (((double) gm_WalkEntityChain(*(unsigned short*) p) * d) *
	    0.01);
	io_FormatTextBuffer(buf, *(unsigned short*) ((char*) record + 4) + 0x12e7, n);
	fcn_004c51a0(-1, *(int*) record, (*(char*)&g_773d75), n);
	fcn_00545d40(*(int*) ((char*) p + 4), *(int*) ((char*) p + 4), buf,
	    (unsigned) strlen(buf) > 0x100, 0x603, 0);
	return 0;
}
