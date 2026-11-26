#include "Develop/DieGildeAddOn/game/building_prototype.h"


#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern unsigned char* lpGebaeudePROT;

char* __cdecl gm_StartFilteredEntitySearch(int, ...);
char* __cdecl gm_AddObjekt(void);
int __cdecl gm_CheckEntityType(char*);
int __cdecl fcn_00505340(char*);
unsigned short __cdecl gm_RandomMod(unsigned short);
void __cdecl d3_TransformPoint(char*, char*, float*);
#include "client_scene_transform.h"

void __cdecl he_StartFireEvent(char* u)
{
	unsigned short n;
	unsigned short m;
	float targetPos[4];
	float sourcePos[4];
	char* list[0x100];
	char* e;
	char* t;
	char* pick;
	int i;

	n = 0;
	m = 1;
	for (e = gm_StartFilteredEntitySearch(1, 6); e != 0; e = gm_FindNextFilteredEntity()) {
		t = (char*)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*(unsigned char*) e];
		if (gm_CheckEntityType(e) == 0 && fcn_00505340(e) == 0 && *(char**) (e + 0x61) != 0 && ((char)(((BUILDING_PROTOTYPE*)t)->category)) != 3) {
			list[n++] = e;
		}
	}
	for (i = 0; i < 15; i++) {
		((int*) (u + 0xb0))[i] = -1;
	}
	if (*(int*) (u + 0xac) == -1) {
		pick = list[gm_RandomMod(n)];
		*(int*) (u + 0xac) = *(int*) (pick + 1);
	} else {
		pick = gm_StartFilteredEntitySearch(1, 1, *(int*) (u + 0xac));
	}
	for (i = 0; i < n && m < 0x10; i++) {
		e = list[i];
		d3_TransformPoint(*(char**) (e + 0x61), *(char**) (e + 0x61) + 0x4c, sourcePos);
		d3_TransformPoint(*(char**) (pick + 0x61), *(char**) (pick + 0x61) + 0x4c, targetPos);
		if (e != pick && CompareVector3WithinTolerance(sourcePos, targetPos, (float) *(int*) (u + 0xf0)) != 0) {
			((int*) (u + 0xac))[m++] = *(int*) (e + 1);
		}
	}
	*(int*) (u + 0xec) = *(int*) (pick + 1);
	*(pos14_7f4c00*) (u + 0x52) = gm_GameTime;
	if (*(unsigned short*) (u + 0x56) > 0x14) {
		*(unsigned short*) (u + 0x56) = gm_RandomMod(10) + 8;
		(*(int*) (u + 0x52))++;
	}
	*(pos14_7f4c00*) (u + 0x52) = gm_GameTime;
	if (*(unsigned short*) (u + 0x56) < 7) {
		*(unsigned short*) (u + 0x56) = gm_RandomMod(10) + 8;
	}
}
