typedef struct Kind {
	char pad0[0x247];
	unsigned char cap;
	char pad248[0x24d - 0x248];
} Kind;
// SIZE 0x24d
#include "Develop/DieGildeAddOn/game/building_prototype.h"
extern unsigned char* lpGebaeudePROT;

char* __cdecl gm_StartFilteredEntitySearch(int a, int b, int id, int c, int d);
char* __cdecl gm_AddObjekt(void);
char* __cdecl gm_FindNextFilteredEntity(void);
char* __cdecl fcn_00502cd0(int a, int b, int c, int d);
int __cdecl he_StartHandlungSearch(int a, int b, int c, int d, int e);

/* ADDRESS: GOLDTL 0x004ab010 */
int __cdecl ai_FindDunkleEckeTarget(unsigned short* actor, char* first_out, char* second_out)
{
	char* building;
	char* room;

	for (building = gm_StartFilteredEntitySearch(2, 4, *actor, 5, 0x16); building; building = gm_FindNextFilteredEntity()) {
		if (((BUILDING_PROTOTYPE *)lpGebaeudePROT)[*(unsigned char*) building].level > 1) {
			room = fcn_00502cd0(*(int*) (building + 0x5d), 1, 0, 0x120);
			if (room && fcn_00502cd0(*(int*) (room + 0x14), 1, 0, 0x12c) && !he_StartHandlungSearch(2, 0, 0x74, 3, *(int*) (building + 1))) {
				first_out[0] = 4;
				*(int*) (first_out + 4) = *(int*) (building + 1);
				second_out[0] = 1;
				*(int*) (second_out + 4) = *(int*) (room + 2);
				return 1;
			}
		}
	}
	return 0;
}
