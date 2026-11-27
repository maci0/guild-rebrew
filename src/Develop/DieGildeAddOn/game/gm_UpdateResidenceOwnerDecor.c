#include "Develop/DieGildeAddOn/game/building_prototype.h"


extern unsigned char* lpGebaeudePROT;

void* __cdecl fcn_00502cd0(int list, int a, int b, int c);
void* __cdecl gm_NextEntityQueryMatch(void);
void __cdecl d3_UpdateEntityStageMeshes(unsigned char* e, void* q, int k);

void __cdecl gm_UpdateResidenceOwnerDecor(unsigned char* e)
{
	void* list[32];
	void* q;
	int n;
	int i;

	n = 0;
	if (((BUILDING_PROTOTYPE *)lpGebaeudePROT)[e[0]].category == 2) {
		q = fcn_00502cd0(*(int*) (e + 0x5d), 1, 4, 2);
		while (q != 0) {
			list[n++] = q;
			q = gm_NextEntityQueryMatch();
		}
		for (i = 0; i < n; i++) {
			d3_UpdateEntityStageMeshes(e, list[i], *(unsigned short*) (e + 0x27));
		}
	}
}
