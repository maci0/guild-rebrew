#include "Develop/Units/d3/d3_object.h"


typedef struct {
	char pad[0x40];
	int a;
	int b;
	char pad2[0x2ac];
} MAP_TABLE_MARKER;
// SIZE 0x2f4

extern char g_868060[];
extern char g_6a40d0[];
extern char g_6a40b0[];
extern char g_6a40a0[];
extern char g_6a4080[];
extern float g_66418c;
extern float g_665e64;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_dialog_state.h"

char* __cdecl d3_FindSceneObject(int, int, int, char*);
char* __cdecl d3_CreateSceneModelObject(int, float*, char*, char*);
void __cdecl d3_ApplyObjectAnimation(char*, char*, int);
int __cdecl main_RunFrameLoop(void*, int);


void __cdecl d3_ShowMapTableTowerMarkers(void)
{
	float dx;
	float dz;
	float pos[4];
	char* objs[4];
	char* a;
	char* b;
	char* o;
	int i;
	float z;

	pos[0] = 0.0f;
	pos[1] = 0.0f;
	pos[2] = 0.0f;
	pos[3] = 0.0f;
	a = d3_FindSceneObject(0, 0x140, 0, g_6a40d0);
	b = d3_FindSceneObject(0, 0x140, 0, g_6a40b0);
	if (a == 0 || b == 0) {
		return;
	}
	dx = *(float*) (b + 0x4c) - *(float*) (a + 0x4c);
	dz = *(float*) (b + 0x54) - *(float*) (a + 0x54);
	for (i = 0; i < 4; i++) {
		pos[0] = 0.0f;
		pos[1] = 0.0f;
		pos[2] = 0.0f;
		pos[3] = 0.0f;
		pos[0] = *(float*) (a + 0x4c);
		pos[1] = *(float*) (a + 0x50);
		z = *(float*) (a + 0x54);
		pos[0] += ((MAP_TABLE_MARKER*)g_868060)[i].a * g_66418c * dx;
		pos[2] = ((MAP_TABLE_MARKER*)g_868060)[i].b * g_665e64 * dz + z;
		o = d3_CreateSceneModelObject(0, pos, a + 0x84, g_6a40a0);
		o[0x215] |= 1;
		o[0x216] = (o[0x216] & ~2) | 1;
		objs[i] = o;
		d3_ApplyObjectAnimation(o, g_6a4080, 1);
	}
	while (main_RunFrameLoop(d3_ShowMapTableTowerMarkers, 0x67fff) != 0) {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
	}
	for (i = 0; i < 4; i++) {
		d3_DestroyObject((D3_OBJECT*) (objs[i]));
	}
}
