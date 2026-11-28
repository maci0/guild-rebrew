#include "Develop/DieGildeAddOn/game/building_prototype.h"


extern char* d2_VisitedBuilding;
extern unsigned char* lpGebaeudePROT;
extern char str_empty[];

char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
char* __cdecl fcn_00502cd0(int, int, int, int);
void __cdecl d2_EnterBuildingObjekt(char*, int, char*);

void __cdecl d2_FocusTutorialBuilding0x12(int a)
{
	char* e;
	char* r;

	if (a == 0) {
		if (((unsigned char*)d2_VisitedBuilding) == 0 || ((char)(((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*((unsigned char*)d2_VisitedBuilding)].category)) != 0x12) {
			e = gm_StartFilteredEntitySearch(1, 5, 0x12);
			if (e != 0) {
				r = fcn_00502cd0(*(int*) (e + 0x5d), 1, 0, 0x74);
				if (r != 0) {
					d2_EnterBuildingObjekt(e, *(int*) (r + 2), str_empty);
				}
			}
		}
	}
}
