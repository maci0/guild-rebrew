#include "Develop/DieGildeAddOn/game/spiel.h"
#include <string.h>

extern char g_7f4ca0[];

unsigned short* __cdecl fcn_00508e40(int);
int __cdecl fcn_005c6270(void*, int);
unsigned char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
unsigned char* __cdecl gm_AddObjekt(void);
unsigned char* __cdecl gm_FindNextFilteredEntity(void);

unsigned short __cdecl gm_RandomMod(unsigned short);
void __cdecl fcn_0051af00(void*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, int);
float __cdecl fcn_004ff210(unsigned short, int);


/* ADDRESS: GOLDTL 0x004b8a70 */
int __cdecl fcn_004b8a70(int* a1)
{
	char* ents[8];
	char buf[0x200];
	unsigned short* e;
	unsigned char* it;
	char* chosen;
	char* rec;
	int n;
	int k;
	int i;
	int found;
	int a;
	int b;

	n = 0;
	e = fcn_00508e40(a1[0]);
	if (e == 0)
		return 1;
	if (fcn_005c6270(e, 0x290) != 0)
		return 0x400;
	for (it = gm_StartFilteredEntitySearch(1, 3, *e); it != 0 && n < 8; it = gm_FindNextFilteredEntity()) {
		k = gm_GetBuildingTypeCategory(it[0]);
		if (k == 1 || k == 2)
			ents[n++] = (char*) it;
	}
	if (n == 0)
		return 0x400;
	found = -1;
	chosen = ents[gm_RandomMod(n)];
	for (i = 0; i < 768; i++) {
		rec = g_7f4ca0 + i * 540;
		if (*(unsigned char*) (rec + 2) != 0xffff && *(char**) (rec + 0x16c) == chosen
		    && rec[0x165] != 0)
			found = i;
	}
	if (found == -1 || chosen == 0)
		return 0x400;
	if (gm_RandomMod(2) != 0) {
		fcn_0051af00(buf, *(unsigned short*) (a1 + 1) + 0x12e7, chosen);
		fcn_00545d40(*(int*) (e + 2), *(int*) (e + 2), buf, strlen(buf) > 0x100, 0x603, 0);
		a = (int) (*(float*) (e + 0xe) * 0.25);
		b = (int) (*(float*) (e + 0xe) * 0.05);
		fcn_004ff210(*e, -(gm_RandomMod(a) + b));
	}
	return 0;
}
