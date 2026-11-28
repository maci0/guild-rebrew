#include "Develop/DieGildeAddOn/game/spiel.h"
#include <string.h>
#include "Develop/DieGildeAddOn/game/entity_record.h"
extern char gm_EntitySlotTable[];

unsigned short* __cdecl gm_LookupEntityRecordById(int);
int __cdecl gm_HasActiveSpecialObject(void*, int);
unsigned char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
unsigned char* __cdecl gm_AddObjekt(void);

unsigned short __cdecl gm_RandomMod(unsigned short);
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl he_PostEntityMessage(int, int, char*, int, int, int);
float __cdecl gm_ApplyEntityHealthDelta(unsigned short, int);


/* ADDRESS: GOLDTL 0x004b8860 */
int __cdecl gm_HandleMsg1eDamageWorker(int* request)
{
	char* ents[8];
	char buf[0x200];
	unsigned short* e;
	unsigned char* it;
	char* chosen;
	char* sel;
	char* rec;
	int n;
	int m;
	int k;
	int i;
	int selectedIndex;
	int otherIndex;

	n = 0;
	sel = 0;
	e = gm_LookupEntityRecordById(request[0]);
	if (e == 0)
		return 1;
	if (gm_HasActiveSpecialObject(e, 0x290) != 0)
		return 0x400;
	for (it = gm_StartFilteredEntitySearch(1, 3, *e); it != 0 && n < 8; it = gm_FindNextFilteredEntity()) {
		k = gm_GetBuildingTypeCategory(it[0]);
		if (k == 1 || k == 2)
			ents[n++] = (char*) it;
	}
	if (n == 0)
		return 0x400;
	m = 0;
	chosen = ents[gm_RandomMod(n)];
	for (i = 0; i < 768; i++) {
		if (m >= 6)
			break;
		rec = ((char *)&((ENTITY_RECORD_VIEW *)gm_EntitySlotTable)[i]);
		if (*(unsigned char*)&((ENTITY_RECORD_VIEW*)rec)->entity_type != 0xffff && *(char**) (rec + 0x16c) == chosen
		    && (*(char*)&((ENTITY_RECORD_VIEW*)rec)->active) != 0)
			ents[m++] = rec;
	}
	if (m > 2) {
		selectedIndex = gm_RandomMod(m);
		sel = ents[selectedIndex];
		otherIndex = gm_RandomMod(m);
		while (otherIndex == selectedIndex)
			otherIndex = gm_RandomMod(m);
	}
	if (chosen == 0 || sel == 0)
		return 0x400;
	if (gm_RandomMod(2) != 0) {
		io_FormatTextBuffer(buf, *(unsigned short*) (request + 1) + 0x12e7, chosen,
		    (sel[9] != 0 ? 0x230 : 0x20d) + *(unsigned char*) (sel + 0x165),
		    *(unsigned short*) sel, *(unsigned short*) sel);
		he_PostEntityMessage(*(int*) (e + 2), *(int*) (e + 2), buf, strlen(buf) > 0x100, 0x603, 0);
		gm_ApplyEntityHealthDelta(*(unsigned short*) sel, (int) -(*(float*) (sel + 0x1c) + 1.0f));
	}
	return 0;
}
