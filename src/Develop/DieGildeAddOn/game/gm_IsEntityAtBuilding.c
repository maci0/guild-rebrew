


char* __cdecl d3_FindSceneObject(char*, int, int, char*);
void __cdecl d3_TransformPoint(char*, char*, float*);
#include "Develop/Units/d3/client_scene_transform.h"

int __cdecl gm_IsEntityAtBuilding(char* a, char* b)
{
	float pos[4];
	char* d;
	char* x;

	d = *(char**) (a + 0x184);
	if (*(char**) (b + 0x61) != 0) {
		if (d == 0) {
			return 0;
		}
		x = d3_FindSceneObject(*(char**) (b + 0x61), 0x100, 0, "dummy_TUER");
		if (x != 0) {
			d3_TransformPoint(x, x + 0x4c, pos);
		} else {
			d3_TransformPoint(*(char**) (b + 0x61), *(char**) (b + 0x61) + 0x4c, pos);
		}
		if (CompareVector3WithinTolerance((float*) (*(char**) (d + 0x34) + 0x4c), pos, 750.0f) != 0 &&
		    *(int*) (d + 0x128) == 0) {
			return 1;
		}
	}
	if (d != 0 && *(int*) (d + 0x2c) == *(int*) (b + 1)) {
		return 1;
	}
	return 0;
}
