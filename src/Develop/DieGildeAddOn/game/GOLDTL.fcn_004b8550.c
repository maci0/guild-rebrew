/* Owned (both targets) by src/GOLDTL.fcn_004cef70.c. */
extern char g_7f4ca0[];
#include "Develop/DieGildeAddOn/game/entity_record.h"
#include <string.h>

void* __cdecl gm_LookupEntityRecordById(int);
int  __cdecl fcn_005c6270(void*, int);
int  __cdecl fcn_004a55c0(void*, int, int*, float, float, unsigned short*);
unsigned short __cdecl gm_RandomMod(int);
void __cdecl cm_RequestCopyEntityData(int, int, int, int);
void __cdecl io_FormatTextBuffer(void*, int, int, int);
void __cdecl fcn_00545d40(int, int, void*, int, int, int);


/* ADDRESS: GOLDTL 0x004b8550 */
int __cdecl fcn_004b8550(void* a1)
{
	char buf[0x400];
	int d2;
	unsigned short w1;
	void* actor;
	void* target;
	int n;

	actor = gm_LookupEntityRecordById(*(int*) a1);
	if (actor == 0) {
		return 1;
	}
	if (fcn_005c6270(actor, 0x290) != 0) {
		return 0x400;
	}
	d2 = 0x600c00;
	if (fcn_004a55c0(actor, 1, &d2, 0.0f, 100.0f, &w1) == 0) {
		return 0x400;
	}
	target = (void*) (((char *)&((ENTITY_RECORD_VIEW *)g_7f4ca0)[w1]));
	n = 2 * gm_RandomMod(8) + 4;
	cm_RequestCopyEntityData(*(int*) ((char*) actor + 4), *(int*) ((char*) target + 4), -n, 1);
	io_FormatTextBuffer(buf, *(unsigned short*) ((char*) a1 + 4) + 0x12e7,
	    *(unsigned short*) target, *(unsigned short*) target);
	fcn_00545d40(*(int*) ((char*) actor + 4), *(int*) ((char*) actor + 4), buf,
	    (unsigned) strlen(buf) > 0x100, 0x603, 0);
	return 0;
}
