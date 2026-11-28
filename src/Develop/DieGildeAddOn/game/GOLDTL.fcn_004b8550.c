/* Owned (both targets) by src/GOLDTL.fcn_004cef70.c. */
extern char gm_EntitySlotTable[];
#include "Develop/DieGildeAddOn/game/entity_record.h"
#include <string.h>

void* __cdecl gm_LookupEntityRecordById(int);
int  __cdecl gm_HasActiveSpecialObject(void*, int);
int  __cdecl gm_FindEntityCandidatesInRange(void*, int, int*, float, float, unsigned short*);
unsigned short __cdecl gm_RandomMod(int);
void __cdecl cm_RequestCopyEntityData(int, int, int, int);
void __cdecl io_FormatTextBuffer(void*, int, int, int);
void __cdecl he_PostEntityMessage(int, int, void*, int, int, int);


/* ADDRESS: GOLDTL 0x004b8550 */
int __cdecl gm_HandleStenchFavorLoss(void* a1)
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
	if (gm_HasActiveSpecialObject(actor, 0x290) != 0) {
		return 0x400;
	}
	d2 = 0x600c00;
	if (gm_FindEntityCandidatesInRange(actor, 1, &d2, 0.0f, 100.0f, &w1) == 0) {
		return 0x400;
	}
	target = (void*) (((char *)&((ENTITY_RECORD_VIEW *)gm_EntitySlotTable)[w1]));
	n = 2 * gm_RandomMod(8) + 4;
	cm_RequestCopyEntityData(*(int*) ((char*) actor + 4), *(int*) ((char*) target + 4), -n, 1);
	io_FormatTextBuffer(buf, *(unsigned short*) ((char*) a1 + 4) + 0x12e7,
	    *(unsigned short*) target, *(unsigned short*) target);
	he_PostEntityMessage(*(int*) ((char*) actor + 4), *(int*) ((char*) actor + 4), buf,
	    (unsigned) strlen(buf) > 0x100, 0x603, 0);
	return 0;
}
