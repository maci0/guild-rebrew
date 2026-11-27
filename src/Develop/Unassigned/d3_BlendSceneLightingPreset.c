/* Morphs the colour/position tables between animation slots a0 and a0+1 by
 * factor t, scales the first vector by scale, and blends the six palette
 * entries of the slot into g_1041d20. */
#include "client_types.h"
#include "Develop/Units/d3/d3_object.h"
extern float g_6628a8;
extern float g_6628a0;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_67a370;
extern VECTOR3 g_6b86c4;
extern Pal_1041d20 g_1041d20[6];
typedef struct {
	VECTOR3 a;
	VECTOR3 b;
	Pal_1041d20 pal[6];
} Slot445f50;

extern char g_1041d80[];
extern int g_10405e0[];

void __cdecl d3_VisitSceneObjects(int a, int b, int c, void* cb, void* q);
void __cdecl UpdateSceneLighting(int a);
char __cdecl d3_InterpolateObjectSlotCallback(int a, float* v);
char __cdecl d3_ScaleNodeIntensityCallback(char* p, float* q);

/* ADDRESS: GOLDTL 0x00445f50 */
char __cdecl d3_BlendSceneLightingPreset(unsigned int slot, float t, float scale, int updateLighting)
{
	float pos;
	Pal_1041d20* pc;
	Pal_1041d20* pn;
	Pal_1041d20* dst;
	unsigned char* rows;
	float inv;
	float c[4];
	unsigned int n;

	if (slot < 7) {
	} else {
		return 0;
	}
	if (!(t >= g_6628a8))
		return 0;
	if (!(t <= g_6628a0))
		return 0;
	pos = (float) slot + t;
	d3_VisitSceneObjects(g_67a370, 0, 0x1e, (void*) d3_InterpolateObjectSlotCallback, &pos);
	if (scale != g_6628a0)
		d3_VisitSceneObjects(g_67a370, 0, 8, (void*) d3_ScaleNodeIntensityCallback, &scale);
	n = (slot + 1) % 7;
	c[0] = ((D3_SCENE_SLOT*)g_1041d80)[n].a.x - ((D3_SCENE_SLOT*)g_1041d80)[slot].a.x;
	c[1] = ((D3_SCENE_SLOT*)g_1041d80)[n].a.y - ((D3_SCENE_SLOT*)g_1041d80)[slot].a.y;
	c[2] = ((D3_SCENE_SLOT*)g_1041d80)[n].a.z - ((D3_SCENE_SLOT*)g_1041d80)[slot].a.z;
	g_67bbdc.x = c[0] * t + ((D3_SCENE_SLOT*)g_1041d80)[slot].a.x;
	g_67bbdc.y = c[1] * t + ((D3_SCENE_SLOT*)g_1041d80)[slot].a.y;
	g_67bbdc.z = c[2] * t + ((D3_SCENE_SLOT*)g_1041d80)[slot].a.z;
	g_67bbdc.x *= scale;
	g_67bbdc.y *= scale;
	g_67bbdc.z *= scale;
	c[0] = ((D3_SCENE_SLOT*)g_1041d80)[n].b.x - ((D3_SCENE_SLOT*)g_1041d80)[slot].b.x;
	c[1] = ((D3_SCENE_SLOT*)g_1041d80)[n].b.y - ((D3_SCENE_SLOT*)g_1041d80)[slot].b.y;
	c[2] = ((D3_SCENE_SLOT*)g_1041d80)[n].b.z - ((D3_SCENE_SLOT*)g_1041d80)[slot].b.z;
	g_6b86c4.x = c[0] * t + ((D3_SCENE_SLOT*)g_1041d80)[slot].b.x;
	g_6b86c4.y = c[1] * t + ((D3_SCENE_SLOT*)g_1041d80)[slot].b.y;
	g_6b86c4.z = c[2] * t + ((D3_SCENE_SLOT*)g_1041d80)[slot].b.z;
	inv = g_6628a0 - t;
	pc = (Pal_1041d20*)((D3_SCENE_SLOT*)g_1041d80)[slot].pal;
	pn = (Pal_1041d20*)((D3_SCENE_SLOT*)g_1041d80)[n].pal;
	for (dst = g_1041d20; dst < g_1041d20 + 6; dst++) {
		((unsigned char*) &dst->color)[2] = (unsigned char) (int) (((unsigned char*) &pc->color)[2] * inv + ((unsigned char*) &pn->color)[2] * t);
		((unsigned char*) &dst->color)[1] = (unsigned char) (int) (((unsigned char*) &pn->color)[1] * t + ((unsigned char*) &pc->color)[1] * inv);
		((unsigned char*) &dst->color)[0] = (unsigned char) (int) (((unsigned char*) &pc->color)[0] * inv + ((unsigned char*) &pn->color)[0] * t);
		dst->f4 = inv * pc->f4 + t * pn->f4;
		dst->f8 = inv * pc->f8 + t * pn->f8;
		pc++;
		pn++;
	}
	UpdateSceneLighting(updateLighting);
	*(int*) 0x67a95c = slot;
	if (g_6b89c0 != 0) {
		*((unsigned char*) (g_6b89c0 + 0x0a)) =
			(unsigned char) (int) (((unsigned char*) g_10405e0)[slot * 4 + 2] * inv + ((unsigned char*) g_10405e0)[n * 4 + 2] * t);
		*((unsigned char*) (g_6b89c0 + 0x09)) =
			(unsigned char) (int) (((unsigned char*) g_10405e0)[slot * 4 + 1] * inv + ((unsigned char*) g_10405e0)[n * 4 + 1] * t);
		*((unsigned char*) (g_6b89c0 + 0x08)) =
			(unsigned char) (int) (((unsigned char*) g_10405e0)[slot * 4 + 0] * inv + ((unsigned char*) g_10405e0)[n * 4 + 0] * t);
	}
	return 1;
}
