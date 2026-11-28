#include "Develop/DieGildeAddOn/game/spiel.h"
#include <string.h>

typedef struct {
	char x0[2];
	char kind;
	char pad3[0x169];
	char* owner;
	char pad170[0xac];
} Ent;
// SIZE 0x21c

#include "Develop/DieGildeAddOn/game/entity_record.h"

unsigned short* __cdecl gm_LookupEntityRecordById(int);
unsigned char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
unsigned char* __cdecl gm_AddObjekt(void);
unsigned char* __cdecl gm_FindNextFilteredEntity(void);

unsigned short __cdecl gm_RandomMod(unsigned short);
void __cdecl cm_RequestModifyEntityLevel(int, int, int);
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl he_PostEntityMessage(int, int, char*, int, int, int);


/* ADDRESS: GOLDTL 0x004ba690 */
/* ADDRESS: GOLDDE 0x004a8730 */
int __cdecl gm_BoostRandomBuildingLevel(int* request)
{
	char* ents[8];
	char buf[0x100];
	unsigned short* e;
	unsigned char* it;
	char* chosen;
	char* rec;
	int n;
	int i;
	int amount;

	n = 0;
	rec = 0;
	e = gm_LookupEntityRecordById(request[0]);
	if (e == 0)
		return 1;
	for (it = gm_StartFilteredEntitySearch(1, 3, *e); it != 0 && n < 8; it = gm_FindNextFilteredEntity()) {
		if (gm_GetBuildingTypeCategory(it[0]) == 1)
			ents[n++] = (char*) it;
	}
	if (n == 0)
		return 0x400;
	chosen = ents[gm_RandomMod(n)];
	for (i = 0; i < 768; i++) {
		if ((*(char*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].entity_type) == 1 && (*(char**)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].ptr_16c) == chosen) {
			rec = (char*) ((Ent*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i]);
			break;
		}
	}
	if (chosen == 0 || rec == 0)
		return 0x400;
	amount = 0xfc - *(unsigned char*) (rec + 0x81);
	if (amount <= 0)
		return 0x400;
	cm_RequestModifyEntityLevel(*(int*) (rec + 4), 1,
	    (char) (amount < gm_RandomMod(10) + 5 ? amount : gm_RandomMod(10) + 5));
	io_FormatTextBuffer(buf, *(unsigned short*) (request + 1) + 0x12e7, 0x16b8, *(unsigned short*) rec, chosen);
	he_PostEntityMessage(*(int*) (e + 2), *(int*) (e + 2), buf, strlen(buf) > 0x100, 0x603, 0);
	return 0;
}
