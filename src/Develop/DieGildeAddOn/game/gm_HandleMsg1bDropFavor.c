/* Owned (both targets) by src/GOLDTL.fcn_004cef70.c. */
extern char gm_EntitySlotTable[];

#include <string.h>

void* __cdecl gm_LookupEntityRecordById(int);
int  __cdecl gm_HasActiveSpecialObject(void*, int);
int  __cdecl gm_FindEntityCandidatesInRange(void*, int, int*, float, float, unsigned short*);
unsigned short __cdecl gm_RandomMod(int);
void __cdecl cm_RequestCopyEntityData(int, int, int, int);
void __cdecl io_FormatTextBuffer(void*, int, int);
void __cdecl he_PostEntityMessage(int, int, void*, int, int, int);


/* ADDRESS: GOLDTL 0x004b8410 */
int __cdecl gm_HandleMsg1bDropFavor(void* request)
{
	char buf[0x400];
	int mask;
	unsigned short index;
	void* entity;
	void* target;
	int delta;

	entity = gm_LookupEntityRecordById(*(int*) request);
	if (entity == 0) {
		return 1;
	}
	if (gm_HasActiveSpecialObject(entity, 0x290) != 0) {
		return 0x400;
	}
	mask = 0x600c00;
	if (gm_FindEntityCandidatesInRange(entity, 1, &mask, 0.0f, 100.0f, &index) == 0) {
		return 0x400;
	}
	target = (void*) (gm_EntitySlotTable + 540 * index);
	if (target == 0) {
		return 0x400;
	}
	delta = 2 * gm_RandomMod(0xf) + 10;
	cm_RequestCopyEntityData(*(int*) ((char*) entity + 4), *(int*) ((char*) target + 4), -delta, 1);
	io_FormatTextBuffer(buf, *(unsigned short*) ((char*) request + 4) + 0x12e7,
	    *(unsigned short*) target);
	he_PostEntityMessage(*(int*) ((char*) entity + 4), *(int*) ((char*) entity + 4), buf,
	    (unsigned) strlen(buf) > 0x100, 0x603, 0);
	return 0;
}
