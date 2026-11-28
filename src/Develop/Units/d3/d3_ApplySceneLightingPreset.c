extern int g_67a370;
extern int g_7e4530;
extern float g_6a2a18[7][4];
extern float g_6a2b68[7][4];
#include "Develop/client_types.h"
extern VECTOR3 g_67bbdc;
extern float g_67bbe0;
extern float g_67bbe4;
#include "Develop/Units/d3/d3_object.h"
// SIZE 0x60
struct s_1041d80 {
	float v[3];
	char pad[0x54];
};

extern char g_1041d80[];




void __cdecl d3_VisitSceneObjects(char*, int, int, void*, void*);
char __cdecl d3_ApplyLightingVectorsToObject(char*);

void __cdecl d3_ApplySceneLightingPreset(void)
{
	float (*src)[4];
	int i;

	if (*(int*) (((char*)g_67a370) + 0xac) != 0) {
		d3_VisitSceneObjects(((char*)g_67a370), 0, 8, (void*) d3_ApplyLightingVectorsToObject, 0);
		if (g_7e4530 == 0) {
			src = g_6a2a18;
		} else {
			src = g_6a2b68;
		}
		for (i = 0; i < 7; i++) {
			*(float*) (((char*)g_67a370) + i * 0x60 + 0x128) = src[i][0];
			*(float*) (((char*)g_67a370) + i * 0x60 + 0x12c) = src[i][1];
			*(float*) (((char*)g_67a370) + i * 0x60 + 0x130) = src[i][2];
			(*(float*)&g_67bbdc) = src[i][0];
			g_67bbe0 = src[i][1];
			g_67bbe4 = src[i][2];
			((D3_SCENE_SLOT*)g_1041d80)[i].a.x = src[i][0];
			((D3_SCENE_SLOT*)g_1041d80)[i].a.y = src[i][1];
			((D3_SCENE_SLOT*)g_1041d80)[i].a.z = src[i][2];
		}
	}
}
