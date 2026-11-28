#include <math.h>
#include <stdlib.h>

typedef struct {
	float value;
	char* e;
	int pad;
} D3_LIGHT_SORT_ENTRY;

typedef struct D3_SCENE_LIGHT_NODE D3_SCENE_LIGHT_NODE;
struct D3_SCENE_LIGHT_NODE {
	char pad0[0x5c];
	float r;
	float g;
	float b;
	char pad1[0x28];
	float range;
	float power;
	float atten;
	char pad2[0x13c];
	float x;
	float y;
	float z;
	char pad3[0xc];
	D3_SCENE_LIGHT_NODE* next;
};

typedef struct {
	float x;
	float y;
	float z;
	float w;
} D3_LIGHT_PROBE_VEC;

#include "Develop/Units/d8_vesa/d3d_device_view.h"
typedef int (__stdcall* D3D8_ENABLE_LIGHT_FN)(D3D_DEVICE_VIEW*, int, int);








extern float g_67bc1c;
extern float g_67bc20;
extern char g_67bc24;
extern void* d3_LightSortList;

extern void* d3_DirectionalLightList;
extern void* d3_SceneLightListHead;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int d3_MaxLightListCount;
extern int d3_LightSortCount;

int __cdecl d3_CompareLightWeightDesc(float*, float*);
void __cdecl d3_SetupD3DLight(int, char*, float, float*, float*);

/* ADDRESS: GOLDTL 0x00450e90 */
void __cdecl d3_SelectActiveObjectLights(float radius, float scale, char* probes, float* dirMat, float* posMat)
{
	D3_SCENE_LIGHT_NODE* light;
	D3_LIGHT_PROBE_VEC* probe;
	float acc;
	float dist;
	float dx;
	float dy;
	float dz;
	float v;
	int sign;
	int i;
	int n;

	sign = (scale < 0.0f) ? (int) 0x80000000 : 0;
	if (!(scale > -scale)) {
		scale = -scale;
	}
	if (!g_67bc24) {
		return;
	}
	d3_LightSortCount = 0;
	for (light = (D3_SCENE_LIGHT_NODE*) d3_DirectionalLightList; light != 0 && d3_LightSortCount < d3_MaxLightListCount; light = light->next) {
		((D3_LIGHT_SORT_ENTRY*) d3_LightSortList)[d3_LightSortCount].e = (char*) light;
		((D3_LIGHT_SORT_ENTRY*) d3_LightSortList)[d3_LightSortCount].value = g_67bc1c * light->power * scale + 3.402823466e+38F;
		((D3_LIGHT_SORT_ENTRY*) d3_LightSortList)[d3_LightSortCount].pad = 0;
		d3_LightSortCount++;
	}
	probe = (D3_LIGHT_PROBE_VEC*) probes;
	for (light = (D3_SCENE_LIGHT_NODE*) d3_SceneLightListHead; light != 0 && d3_LightSortCount < d3_MaxLightListCount; light = light->next) {
		acc = 0.0f;
		for (i = 0; i < 9; i++) {
			dx = probe[i].x - light->x;
			dy = probe[i].y - light->y;
			dz = probe[i].z - light->z;
			dist = (float) sqrt(dx * dx + dy * dy + dz * dz);
			if (i == 8) {
				dist -= 0.5f * radius;
			}
			if (1.0f > dist) {
				dist = 1.0f;
			}
			if (dist <= light->range) {
				v = 1.0f / (dist * light->atten);
				v = v * light->power;
				v = v * g_67bc20;
				v = v * scale;
				v = v * (light->b + light->g + light->r);
				acc += v * 0.0013071895809844136f;
			}
		}
		if (acc > 0.0f) {
			((D3_LIGHT_SORT_ENTRY*) d3_LightSortList)[d3_LightSortCount].e = (char*) light;
			((D3_LIGHT_SORT_ENTRY*) d3_LightSortList)[d3_LightSortCount].value = acc;
			((D3_LIGHT_SORT_ENTRY*) d3_LightSortList)[d3_LightSortCount].pad = 0;
			d3_LightSortCount++;
		}
	}
	qsort((D3_LIGHT_SORT_ENTRY*) d3_LightSortList, d3_LightSortCount, 0xc, (int (__cdecl*)(const void*, const void*)) d3_CompareLightWeightDesc);
	if (d3_LightSortCount < d3_MaxActiveLights) {
		n = d3_LightSortCount;
	} else {
		n = d3_MaxActiveLights;
	}
	for (i = n; i < d3_MaxActiveLights; i++) {
		((D3D8_ENABLE_LIGHT_FN) ((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->unk_98[8])((D3D_DEVICE_VIEW*)g_6b5de0, i, 0);
	}
	for (i = 0; i < n; i++) {
		d3_SetupD3DLight(sign + i, ((D3_LIGHT_SORT_ENTRY*) d3_LightSortList)[i].e, scale, dirMat, posMat);
		((D3D8_ENABLE_LIGHT_FN) ((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->unk_98[8])((D3D_DEVICE_VIEW*)g_6b5de0, i, 1);
	}
}
unsigned char _dpad_1041d04[1180];
#if defined(REBREW_SERVER) || defined(REBREW_GOLD)
unsigned char _dpad_10405e0[5924];
#else
/* Reference gaps only; the emitted objects inside the span keep their own rows. */
unsigned char _dpad_10405e4[24];
unsigned char _dpad_1040604[12];
unsigned char _dpad_1040614[8];
unsigned char _dpad_1040628[24];
unsigned char _dpad_1040644[784];
unsigned char _dpad_1040964[784];
unsigned char _dpad_1040c7c[4];
#endif
