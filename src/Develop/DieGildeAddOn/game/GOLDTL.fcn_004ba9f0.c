#include <string.h>
#include "Develop/DieGildeAddOn/game/entity_record.h"
extern char g_7f4ca0[]; extern unsigned char g_773d75;

unsigned short* __cdecl gm_LookupEntityRecordById(int);
unsigned char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
unsigned char* __cdecl gm_FindNextFilteredEntity(void);
int __cdecl gm_GetBuildingTypeCategory(int);
unsigned short __cdecl gm_RandomMod(int);
void __cdecl cm_SendSellObjekt(int, int, int, int, unsigned char, int);
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl he_MessageBoxQuickjump(int, int, char*, int, int, int, int, int, int);

/* ADDRESS: GOLDTL 0x004ba9f0 */
int __cdecl fcn_004ba9f0(int* noticeRequest)
{
	char buf[0x100];
	char* ents[16];
	unsigned short* e;
	char* chosen;
	char* found;
	unsigned char* it;
	unsigned char* rp;
	int n;
	int k;
	int i;
	int end;
	int step;
	int stride;
	int cat;

	n = 0; found = 0; k = 0;
	e = gm_LookupEntityRecordById(noticeRequest[0]);
	if (e == 0)
		return 1;

	for (it = gm_StartFilteredEntitySearch(1, 3, *e); it != 0;
	    it = gm_FindNextFilteredEntity()) {
		if (n >= 8)
			break;
		cat = gm_GetBuildingTypeCategory(it[0]);
		if (cat == 1 || cat == 2)
			ents[n++] = (char*) it;
	}
	if (n != 0) {
		chosen = ents[gm_RandomMod(n)];
		step = 1;
		if (gm_RandomMod(2) != 0) {
			i = 0;
			end = 0x180;
		} else {
			i = 0x180;
			end = 0x300;
		}
		if (gm_RandomMod(2) != 0) {
			end = 0;
			i = 0x180;
			step = -1;
		}

		stride = step * (int)sizeof(ENTITY_RECORD);
		for (rp = &((ENTITY_RECORD*)g_7f4ca0)[i].entity_state; i < end;
		    i += step, rp += stride) {
			if (rp[0] == 6 || rp[0] == 7 || rp[0] >= 0xa)
				continue;
			if (*(unsigned short*) (rp - 2) == 0xffff)
				continue;
			ents[k++] = (char*) (rp - 2);
			if (k == 0x10)
				break;
		}
		if (k != 0)
			found = ents[gm_RandomMod(k)];
		if (chosen == 0 || found == 0)
			return 0x400;
		cm_SendSellObjekt(*(int*) (chosen + 1), -1, gm_RandomMod(2) + 0x134, 1,
		    g_773d75, 0);
		io_FormatTextBuffer(buf, *(unsigned short*) (noticeRequest + 1) + 0x12e7,
		    *(unsigned short*) found);
		he_MessageBoxQuickjump(*(int*) (e + 2), *(int*) (e + 2), buf,
		    strlen(buf) > 0x100, 0x603, *(int*) (chosen + 1), -1, 0, 0);
		return 0;
	}
	return 0x400;
}
