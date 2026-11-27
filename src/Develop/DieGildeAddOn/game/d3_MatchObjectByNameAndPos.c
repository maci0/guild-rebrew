


#include <string.h>

int __cdecl _strnicmp(char*, char*, int);
void __cdecl d3_TransformPoint(char*, char*, float*);
#include "client_scene_transform.h"

char __cdecl d3_MatchObjectByNameAndPos(char* e, char* obj)
{
	float v[4];

	if (_strnicmp(e, obj, strlen(obj)) == 0 || _strnicmp(e + 1, obj, strlen(obj)) == 0) {
		d3_TransformPoint(e, e + 0x4c, v);
		if (CompareVector3WithinTolerance((float*) (obj + 0x40), v, 100.0f) != 0) {
			*(char**) (obj + 0x50) = e;
			return 0;
		}
	}
	return 1;
}
