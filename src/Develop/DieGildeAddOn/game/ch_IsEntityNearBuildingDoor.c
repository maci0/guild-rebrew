extern unsigned char* lpGebaeudePROT;
extern char d3_Universes[];
#include "Develop/DieGildeAddOn/game/building_prototype.h"



char* __cdecl d3_FindSceneObject(char*, int, int, char*);
void __cdecl d3_TransformPoint(char*, char*, float*);
#include "Develop/Units/d3/client_scene_transform.h"

int __cdecl ch_IsEntityNearBuildingDoor(char* actor, unsigned char* building)
{
	float radius;
	float pos[4];
	char* fig;
	char* door;

	radius = 650.0f;
	if (((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*building].category == 10) {
		radius = 1950.0f;
	}
	fig = *(char**) (actor + 0x3b);
	if (*(char**) (building + 0x61) != 0) {
		if (fig == 0) {
			return 0;
		}
		if (*(char**) (fig + 0x88) == d3_Universes) {
			door = d3_FindSceneObject(*(char**) (building + 0x61), 0x100, 0, "dummy_TUER");
			if (door != 0) {
				d3_TransformPoint(door, door + 0x4c, pos);
			} else {
				d3_TransformPoint(*(char**) (building + 0x61), *(char**) (building + 0x61) + 0x4c, pos);
				radius = 3250.0f;
			}
			if (CompareVector3WithinTolerance((float*) (*(char**) (fig + 0x34) + 0x4c), pos, radius) != 0) {
				return 1;
			}
		}
	}
	if (fig != 0 && *(int*) (fig + 0x2c) == *(int*) (building + 1)) {
		return 1;
	}
	return 0;
}
