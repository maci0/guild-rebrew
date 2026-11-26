#include "Develop/DieGildeAddOn/game/spiel.h"



void __cdecl d3_TransformPoint(int, int, float*);
#include "client_scene_transform.h"


int __cdecl fcn_005ba020(char* building, char* target)
{
	char* s;
	int id;
	char* owner;
	char* next;
	int last;
	float pos[4];

	s = *(char**) (target + 0x3b);
	if (s == 0) {
		return 0;
	}
	if (*(int*) (building + 0x61) != 0) {
		d3_TransformPoint(*(int*) (building + 0x61), *(int*) (building + 0x61) + 0x4c, pos);
		if (CompareVector3WithinTolerance((float*) (*(char**) (s + 0x34) + 0x4c), pos, 1350.0f) != 0 && *(int*) (s + 0x128) == 0) {
			return 1;
		}
	}
	id = *(int*) (target + 6);
	while (id != -1) {
		if (gm_ResolveEntityById((void**) (&owner), (void**) (&next), (void**) (&last), id) == 0) {
			return 0;
		}
		if (owner != 0) {
			return owner == building;
		}
		if (next != 0) {
			id = *(int*) (next + 6);
		}
		if (last != 0) {
			return 0;
		}
	}
	return 0;
}
