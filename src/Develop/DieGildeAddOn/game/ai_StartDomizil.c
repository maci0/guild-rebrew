extern unsigned char* lpGebaeudePROT;
extern unsigned char gm_ActiveTownIndex;
#include <string.h>
int __cdecl gm_CheckDomizilActionState(char*, char**);
int __cdecl he_StartHandlungSearch(int, ...);
int __cdecl gm_GetTypeProductValue(int);
int __cdecl gm_CalcBuildingCost(char*, int);
int __cdecl gm_SumQueryEntryValues(int, unsigned char);
int __cdecl ai_PrepareBuildSite(int, char*, int, int*, int*, int);
int __cdecl ai_StartKreditNehmen(int, char*, int, int*, int*);
#include "Develop/DieGildeAddOn/game/building_prototype.h"
/* ADDRESS: GOLDTL 0x0048d6c0 */
/* ADDRESS: GOLDDE 0x0047c590 */
int __cdecl ai_StartDomizil(int a0, char* a1, int a2, int* a3, int* a4)
{
	int v12[6];
	int v13[6];
	int first;
	int second;
	int* tail_src;
	char* entity = a1;

	if (gm_CheckDomizilActionState(a1, (char**) &a1) && a2 == 0 && (a0 == 0x40 || a0 == 0) &&
	    he_StartHandlungSearch(2, 0, 0xd, 2, *(unsigned short*) entity) == 0) {
		if (a1 != 0) {
			if (((BUILDING_PROTOTYPE *)lpGebaeudePROT)[*(unsigned char*) a1].level < 3 &&
			    !(a1[0x5a] & 0x41)) {
				v13[1] = *(unsigned char*) a1 + 1;
				v13[2] = 1;
				*(unsigned char*) v12 = 4;
				v12[1] = *(int*) (a1 + 1);
				v12[2] = 1;
				first = (int) (gm_GetTypeProductValue(v13[1]) * 0.3f);
				if (ai_PrepareBuildSite(a0, entity, 0, v13, v12, 0) != 0) {
					second = (int) (gm_SumQueryEntryValues(*(int*) (entity + 0x178), gm_ActiveTownIndex) * 0.95f);
					if (second < first) {
					int rem;
						rem = first - second;
						if ((float) rem / first < 0.25f) {
							a3[2] = rem;
							*(char*) a3 = 0x12;
							return ai_StartKreditNehmen(0x40, entity, 0, a3, a4);
						}
					} else {
						memcpy(a3, v13, sizeof(v13));
						tail_src = v12;
						goto do_copy40;
					}
				}
			}
		} else {
			*(unsigned char*) v12 = 5;
			v12[1] = 0x4b;
			v12[2] = 1;
			if (ai_PrepareBuildSite(a0, entity, 0, v12, v13, 1) != 0) {
				first = gm_CalcBuildingCost(entity, v12[1]);
				second = (int) (gm_SumQueryEntryValues(*(int*) (entity + 0x178), gm_ActiveTownIndex) * 0.95f);
				if (second < first) {
					int rem;
					rem = first - second;
					if ((float) rem / first < 0.25f) {
						a3[2] = rem;
						*(char*) a3 = 0x12;
						return ai_StartKreditNehmen(0x40, entity, 0, a3, a4);
					}
				} else {
					memcpy(a3, v12, sizeof(v12));
					tail_src = v13;
do_copy40:
					memcpy(a4, tail_src, 24);
					return 0x40;
				}
			}
		}
	}
	return 0;
}
