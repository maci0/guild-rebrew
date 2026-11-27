#include <string.h>

#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl d3_SelectSceneContext(int, int);
int __cdecl d3_FindSceneObject(int, int, int, int*);
void __cdecl d3_TransformPoint(char*, char*, int*);
int __cdecl gm_SelectEntityHeadSet(int);
char* __cdecl ch_CreateAtPosition(char*, float*);
int __cdecl fcn_0064d41a(char*, char*, ...);
void __cdecl d3_SetObjectRotation(char*, int*);
void __cdecl fcn_004fdcf0(char*);
void __cdecl fcn_004fdfe0(char*);

/* ADDRESS: GOLDTL 0x004fe2e0 */
int __cdecl ch_SpawnEntityCharacter(char* entity, int sceneCtx, int* posPtr, int* rotPtr, int parentObj, int* dummyName)
{
	int savedContext;
	int transformed;
	float def[4];
	float opt[4];
	int* rot;
	int* pos;
	int v5;
	char* v6;

	savedContext = d3_CurrentContextIndex;
	transformed = 0;
	def[0] = 0.0f;
	def[1] = 0.0f;
	def[2] = 0.0f;
	def[3] = 0.0f;
	pos = posPtr;
	if (pos == 0) {
		pos = (int*) def;
	}
	rot = rotPtr;
	if (rot == 0) {
		rot = (int*) def;
	}
	if (sceneCtx < 0) {
		return 0;
	}
	d3_SelectSceneContext(sceneCtx, 1);
	if (dummyName != 0) {
		v5 = d3_FindSceneObject(parentObj, 0x100, 0, dummyName);
		if (v5 != 0) {
			transformed = 1;
			goto have;
		}
	}
	if (pos == 0 && rot == 0) {
		goto done;
	}
	*(int*) &opt[0] = pos[0];
	*(int*) &opt[1] = pos[1];
	*(int*) &opt[2] = pos[2];
have:
	if (transformed != 0) {
		d3_TransformPoint((char*) v5, (char*) v5 + 0x4c, (int*) opt);
	}
	v5 = gm_SelectEntityHeadSet(*(unsigned short*) entity);
	if (v5 != 0) {
		v6 = (char*) (v5 + 4);
		*(char**) (entity + 0x184) = ch_CreateAtPosition(v6, opt);
		if (*(char**) (entity + 0x184) != 0) {
			fcn_0064d41a(*(char**) (*(char**) (entity + 0x184) + 0x34), g_68b0d8, *(int*) (entity + 4));
			*(void**) (*(char**) (*(char**) (entity + 0x184) + 0x34) + 0x204) = entity;
			*(int*) (*(char**) (*(char**) (entity + 0x184) + 0x34) + 0x48) = *(unsigned short*) entity | 0x3000000;
			if (rotPtr != 0) {
				d3_SetObjectRotation(*(char**) (*(char**) (entity + 0x184) + 0x34), rotPtr);
			}
			strcpy(entity + 0x1f4, v6);
			fcn_004fdcf0(entity);
			fcn_004fdfe0(entity);
		}
	}
done:
	d3_SelectSceneContext(savedContext, 1);
	return *(int*) (entity + 0x184);
}
