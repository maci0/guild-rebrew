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

extern char g_7f4ca0[];

unsigned short* __cdecl gm_LookupEntityRecordById(int);
unsigned char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
unsigned char* __cdecl gm_AddObjekt(void);
unsigned char* __cdecl gm_FindNextFilteredEntity(void);

unsigned short __cdecl gm_RandomMod(unsigned short);
void __cdecl fcn_004c6ba0(int, int, int);
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, int);


/* ADDRESS: GOLDTL 0x004ba690 */
int __cdecl fcn_004ba690(int* a1)
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
	e = gm_LookupEntityRecordById(a1[0]);
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
		if (((Ent*)g_7f4ca0)[i].kind == 1 && ((Ent*)g_7f4ca0)[i].owner == chosen) {
			rec = (char*) &((Ent*)g_7f4ca0)[i];
			break;
		}
	}
	if (chosen == 0 || rec == 0)
		return 0x400;
	amount = 0xfc - *(unsigned char*) (rec + 0x81);
	if (amount <= 0)
		return 0x400;
	fcn_004c6ba0(*(int*) (rec + 4), 1,
	    (char) (amount < gm_RandomMod(10) + 5 ? amount : gm_RandomMod(10) + 5));
	io_FormatTextBuffer(buf, *(unsigned short*) (a1 + 1) + 0x12e7, 0x16b8, *(unsigned short*) rec, chosen);
	fcn_00545d40(*(int*) (e + 2), *(int*) (e + 2), buf, strlen(buf) > 0x100, 0x603, 0);
	return 0;
}
