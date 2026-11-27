#include "Develop/DieGildeAddOn/game/spiel.h"
#include <string.h>

#include "Develop/DieGildeAddOn/game/entity_record.h"

unsigned short* __cdecl gm_LookupEntityRecordById(int);
unsigned char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
unsigned char* __cdecl gm_AddObjekt(void);
unsigned char* __cdecl gm_FindNextFilteredEntity(void);

unsigned short __cdecl gm_RandomMod(unsigned short);
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl he_PostEntityMessage(int, int, char*, int, int, int);


/* ADDRESS: GOLDTL 0x004ba2e0 */
int __cdecl gm_HandleMsg2cPostWorkerNews(int* input)
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
	int x;

	n = 0;
	sel = 0;
	e = gm_LookupEntityRecordById(input[0]);
	if (e == 0)
		return 1;
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
		rec = ((char*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[i]);
		if (rec[2] == 0 && *(char**) (rec + 0x16c) == chosen && rec[0x165] != 0)
			ents[m++] = rec;
	}
	if (m > 1)
		sel = ents[gm_RandomMod(m)];
	if (chosen == 0 || sel == 0)
		return 0x400;
	x = (sel[9] != 0 ? 0x230 : 0x20d) + *(unsigned char*) (sel + 0x165);
	io_FormatTextBuffer(buf, *(unsigned short*) (input + 1) + 0x12e7, x,
	    *(unsigned short*) sel, *(unsigned short*) sel, x);
	he_PostEntityMessage(*(int*) (e + 2), *(int*) (e + 2), buf, strlen(buf) > 0x100, 0x603, 0);
	return 0;
}
