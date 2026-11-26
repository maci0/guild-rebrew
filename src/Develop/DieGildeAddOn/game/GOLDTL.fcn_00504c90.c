#include "Develop/DieGildeAddOn/game/building_prototype.h"


#include <math.h>

// SIZE 0x10
typedef struct {
	float x;
	float y;
	float z;
	float w;
} Vec4;

extern unsigned char* lpGebaeudePROT;

unsigned char* __cdecl gm_StartFilteredEntitySearch(int mode, int kind);
unsigned char* __cdecl gm_AddObjekt(void);
unsigned char* __cdecl gm_FindNextFilteredEntity(void);
int __cdecl gm_CheckEntityType(unsigned char* e);
int __cdecl gm_IsWarehouse(unsigned char* e);
void __cdecl d3_TransformPoint(char* view, char* pos, Vec4* out);

unsigned char* __cdecl gm_FindNearestBuildingByKind(unsigned char* me, int kind)
{
	float best_d;
	Vec4 a;
	Vec4 b;
	unsigned char* best;
	unsigned char* e;
	unsigned char* rec;
	float dx;
	float dy;
	float dz;
	float d;

	best = 0;
	best_d = 1.0e8f;
	if (me == 0 || *(char**) (me + 0x61) == 0) {
		return 0;
	}
	for (e = gm_StartFilteredEntitySearch(1, 6); e != 0; e = gm_FindNextFilteredEntity()) {
		rec = (unsigned char*)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*e];
		if (!gm_CheckEntityType(e) && !gm_IsWarehouse(e) && *(char**) (e + 0x61) != 0 && e != me && (((BUILDING_PROTOTYPE*)rec)->category) == kind) {
			d3_TransformPoint(*(char**) (e + 0x61), *(char**) (e + 0x61) + 0x4c, &a);
			d3_TransformPoint(*(char**) (me + 0x61), *(char**) (me + 0x61) + 0x4c, &b);
			dx = a.x - b.x;
			dy = a.y - b.y;
			dz = a.z - b.z;
			d = (float) sqrt(dx * dx + dy * dy + dz * dz);
			if (d < best_d) {
				best_d = d;
				best = e;
			}
		}
	}
	return best;
}
