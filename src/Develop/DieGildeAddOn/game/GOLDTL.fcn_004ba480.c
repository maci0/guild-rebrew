#include "Develop/DieGildeAddOn/game/spiel.h"
#include <string.h>

typedef struct {
	short v[7];
} stamp14;
// SIZE 0xe

typedef struct Kind {
	char pad0[0x231];
	unsigned char slots_a;
	unsigned char slots_b;
	char pad233[0x24d - 0x233];
} Kind;
// SIZE 0x24d

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern unsigned char* lpGebaeudePROT;
extern unsigned short g_774970;
extern char g_7f4ca0[];

unsigned short* __cdecl fcn_00508e40(int);
unsigned char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
unsigned char* __cdecl gm_AddObjekt(void);

unsigned short __cdecl gm_RandomMod(unsigned short);
float __cdecl fcn_0050f980(int, int, int);
char* __cdecl fcn_005049a0(unsigned char*);
void __cdecl fcn_004c5530(void*);


/* ADDRESS: GOLDTL 0x004ba480 */
int __cdecl fcn_004ba480(int* a1)
{
	unsigned short* e;
	Kind* kind;
	int lim;
	unsigned char* ents[8];
	char m[0xf8];
	unsigned char* it;
	unsigned char* chosen;
	char* rec;
	char* p;
	int n;
	int k;
	int i;
	int cnt;
	int v;

	n = 0;
	e = fcn_00508e40(a1[0]);
	if (e == 0)
		return 1;
	for (it = gm_StartFilteredEntitySearch(1, 3, *e); it != 0 && n < 8; it = gm_FindNextFilteredEntity()) {
		k = gm_GetBuildingTypeCategory(it[0]);
		if (k == 1 || k == 2)
			ents[n++] = it;
	}
	if (n == 0)
		goto fail;
	cnt = 0;
	lim = gm_RandomMod(0x14) + 0x19;
	chosen = ents[gm_RandomMod(n)];
	kind = &((Kind*)lpGebaeudePROT)[chosen[0]];
	for (i = 0; i < 768; i++) {
		rec = g_7f4ca0 + i * 540;
		if (rec[2] == 0 && *(unsigned char**) (rec + 0x16c) == chosen) {
			if (fcn_0050f980(*e, i, 1) < lim)
				goto fail;
			cnt++;
			if (cnt >= kind->slots_b + kind->slots_a)
				goto fail;
		}
	}
	if (cnt >= 2) {
		p = fcn_005049a0(chosen);
		memset(m, 0, sizeof(m));
		v = *(int*) (chosen + 1);
		m[4] = 0x4a;
		*(int*) (m + 0xc) = v;
		m[0x36] = 1;
		*(int*) (m + 0x5c) = v;
		*(int*) (m + 8) = *(int*) (g_7f4ca0 + g_774970 * 540 + 4);
		*(stamp14*) (m + 0x28) = (*(stamp14*)&g_7f4c00);
		*(short*) (m + 0x64) = *(unsigned short*) (a1 + 1) + 0x12e7;
		*(int*) (m + 0x58) = *(int*) (e + 2);
		*(int*) (m + 0x60) = *(int*) (p + 2);
		fcn_004c5530(m);
		return 0;
	}
fail:
	return 0x400;
}
