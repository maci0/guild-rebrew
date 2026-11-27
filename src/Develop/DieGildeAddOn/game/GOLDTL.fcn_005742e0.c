

#include <stdio.h>
#include <string.h>

// SIZE 0x50
struct modelent {
	int k[4];
	char name[0x40];
};

// SIZE 0xc
struct vec3 {
	float x;
	float y;
	float z;
};

extern struct modelent g_6a6ee8[];
#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl d3_SelectSceneContext(int, int);
char* __cdecl d3_LoadObjectFile(char* name, int a, int b);
void __cdecl d3_SetNodePosition(char*, struct vec3*);
void __cdecl d3_SetObjectRotation(char*, float*);
void __cdecl d3_ReparentFackelLights(char*);
void __cdecl d3_AlignObjectToTerrain(char*, int, int);
void __cdecl d3_SetSubtreeVisible(char*, int);
void __cdecl d3_UpdateBuildStageMeshes(char*);
void __cdecl d3_BindEntitySceneObject(char*, unsigned char*, int);

char* __cdecl he_CreateGebaeudeSceneModel(float* rot, struct vec3* pos, unsigned char* kind, char* model, char* u)
{
	int saved;
	char name[0x100];
	char* h;
	int i;
	int j;
	int found;

	i = 0;
	found = 0;
	for (; g_6a6ee8[i].k[0] != 0; i++) {
		if (found) {
			break;
		}
		for (j = 0; j < 4; j++) {
			if (*kind == g_6a6ee8[i].k[j]) {
				strcpy(name, g_6a6ee8[i].name);
				found = 1;
				break;
			}
		}
	}
	if (!found) {
		strcpy(name, g_6a6ee8[i].name);
	}
	saved = d3_CurrentContextIndex;
	d3_SelectSceneContext(0, 1);
	h = d3_LoadObjectFile(name, 0, 0);
	if (h == 0) {
		d3_SelectSceneContext(saved, 1);
		return 0;
	}
	d3_SetNodePosition(h, pos);
	d3_SetObjectRotation(h, rot);
	h[0x215] &= 0xfe;
	h[0x214] |= 0x80;
	sprintf(h, "he_%i", *(int*) (u + 4));
	h = d3_LoadObjectFile(model, 0, 0);
	if (h == 0) {
		d3_SelectSceneContext(saved, 1);
		return 0;
	}
	d3_SetNodePosition(h, pos);
	d3_SetObjectRotation(h, rot);
	d3_ReparentFackelLights(h);
	d3_AlignObjectToTerrain(h, 1, 0);
	if (*(float*) (h + 0x50) < pos->y) {
		*(float*) (h + 0x4c) = pos->x;
		*(float*) (h + 0x50) = pos->y;
		*(float*) (h + 0x54) = pos->z;
	}
	d3_SetSubtreeVisible(h, 0);
	*(int*) (u + 0xbc) = *(int*) (u + 0xc8) = -1;
	d3_UpdateBuildStageMeshes(u);
	d3_BindEntitySceneObject(h, kind, 2);
	d3_SelectSceneContext(saved, 1);
	return h;
}
