


#include "Develop/Units/d3/client_scene_transform.h"
void __cdecl d3_SetNodePosition(char*, float*);
void __cdecl d3_SetObjectRotation(char*, float*);

void __cdecl cut_SyncEntityTransform(char* entity, float* pos, float* rot, int state)
{
	if (entity != 0 && *(char**) (entity + 0x184) != 0) {
		if (CompareVector3WithinTolerance((float*) (*(char**) (*(char**) (entity + 0x184) + 0x34) + 0x4c), pos, 8.0f) == 0)
			d3_SetNodePosition(*(char**) (*(char**) (entity + 0x184) + 0x34), pos);
		if (CompareVector3WithinTolerance((float*) (*(char**) (*(char**) (entity + 0x184) + 0x34) + 0x84), rot, 8.0f) == 0)
			d3_SetObjectRotation(*(char**) (*(char**) (entity + 0x184) + 0x34), rot);
		*(int*) (entity + 0x24) = state;
	}
}
