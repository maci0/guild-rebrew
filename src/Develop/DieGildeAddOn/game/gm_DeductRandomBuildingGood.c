#include "Develop/DieGildeAddOn/game/spiel.h"
extern unsigned char gm_ActiveTownIndex;

unsigned char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
unsigned char* __cdecl gm_AddObjekt(void);
unsigned char* __cdecl gm_FindNextFilteredEntity(void);

unsigned short __cdecl gm_RandomMod(unsigned short);
char* __cdecl fcn_00502cd0(int, int, int, ...);
char* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl cm_SendSellObjekt(int, int, int, int, unsigned char, int);


/* ADDRESS: GOLDTL 0x004bac00 */
int __cdecl gm_DeductRandomBuildingGood(unsigned short* entity, int* outId, float factor)
{
	char* arr[12];
	unsigned char* it;
	char* c;
	char* q;
	char* s;
	int n;
	int m;
	int k;
	int i;
	int v;

	n = 0;
	for (it = gm_StartFilteredEntitySearch(1, 3, *entity); it != 0 && n < 8; it = gm_FindNextFilteredEntity()) {
		k = gm_GetBuildingTypeCategory(it[0]);
		if (k == 1 || k == 2)
			arr[n++] = (char*) it;
	}
	if (n == 0)
		goto fail;
	m = 0;
	c = arr[gm_RandomMod(n)];
	*outId = *(int*) (c + 1);
	q = fcn_00502cd0(*(int*) (c + 0x5d), 2, 6, 0, 0x2a);
	if (q == 0)
		goto fail;
	for (s = fcn_00502cd0(*(int*) (q + 0x14), 1, 5); s != 0 && m < 12; s = gm_NextEntityQueryMatch())
		arr[m++] = s;
	if (m != 0) {
		for (i = 0; i < m; i++) {
			s = arr[i];
			k = *(int*) (s + 0xe);
			if (k > 1) {
				v = (int) (k * factor);
				if (v < 1)
					v = 1;
				cm_SendSellObjekt(-1, *(int*) (q + 2), *(unsigned short*) s, v, gm_ActiveTownIndex, 0);
			}
		}
		return 1;
	}
fail:
	return 0;
}
