#include "Develop/DieGildeAddOn/game/entity_record.h"


extern char g_7f4ca0[];
void* __cdecl gm_LookupEntityRecordById(int);
int  __cdecl fcn_004a55c0(void*, int, int*, float, float, unsigned short*);
unsigned short __cdecl gm_RandomMod(int);
void __cdecl fcn_004c54c0(int, int, int, int);
void __cdecl io_FormatTextBuffer(void*, int, int, int);
void __cdecl fcn_00545d40(int, int, void*, int, int, int);

int __cdecl fcn_004b7e70(void* request)
{
	char buf[0x400];
	int d2;
	unsigned short w1;
	void* p;
	void* e;
	int n;

	p = gm_LookupEntityRecordById(*(int*) request);
	if (p == 0) {
		return 1;
	}
	d2 = 0x600c01;
	if (fcn_004a55c0(p, 1, &d2, 33.0f, 100.0f, &w1) == 0) {
		return 0x400;
	}
	e = (void*) ((int) ((char *)&((ENTITY_RECORD_VIEW *)g_7f4ca0)[w1]));
	n = 2 * gm_RandomMod(7) + 6;
	fcn_004c54c0(*(int*) ((char*) p + 4), *(int*) ((char*) e + 4), n, 1);
	io_FormatTextBuffer(buf, *(unsigned short*) ((char*) request + 4) + 0x12e7,
	    *(unsigned short*) e, *(unsigned short*) e);
	fcn_00545d40(*(int*) ((char*) p + 4), *(int*) ((char*) p + 4), buf,
	    (unsigned) strlen(buf) > 0x100, 0x603, 0);
	return 0;
}
