/* Morphs the colour/position tables between animation slots a0 and a0+1 by
 * factor t, scales the first vector by scale, and blends the six palette
 * entries of the slot into g_1041d20. */
#include "client_types.h"

extern float g_6628a8;
extern float g_6628a0;
extern int g_67a370;
extern int g_6b89c0;
extern VECTOR3 g_6b86c4;
extern Pal_1041d20 g_1041d20[6];
typedef struct {
	VECTOR3 a;
	VECTOR3 b;
	Pal_1041d20 pal[6];
} Slot445f50;

extern Slot445f50 g_1041d80[];
extern int g_10405e0[];

void __cdecl fcn_004379a0(int a, int b, int c, void* cb, void* q);
void __cdecl UpdateSceneLighting(int a);
char __cdecl fcn_00445d20(int a, float* v);
char __cdecl fcn_00445d00(char* p, float* q);

/* ADDRESS: GOLDTL 0x00445f50 */
char __cdecl fcn_00445f50(unsigned int a0, float t, float scale, int a3)
{
	float pos;
	Pal_1041d20* pc;
	Pal_1041d20* pn;
	Pal_1041d20* dst;
	unsigned char* rows;
	float inv;
	float c[3];
	unsigned int n;

	if (a0 < 7) {
	} else {
		return 0;
	}
	if (!(t >= 0.0f))
		return 0;
	if (!(t <= 1.0f))
		return 0;
	pos = (float) a0 + t;
	fcn_004379a0(g_67a370, 0, 0x1e, (void*) fcn_00445d20, &pos);
	if (scale != 1.0f)
		fcn_004379a0(g_67a370, 0, 8, (void*) fcn_00445d00, &scale);
	n = (a0 + 1) % 7;
	c[0] = g_1041d80[n].a.x - g_1041d80[a0].a.x;
	c[1] = g_1041d80[n].a.y - g_1041d80[a0].a.y;
	c[2] = g_1041d80[n].a.z - g_1041d80[a0].a.z;
	g_67bbdc.x = c[0] * t + g_1041d80[a0].a.x;
	g_67bbdc.y = c[1] * t + g_1041d80[a0].a.y;
	g_67bbdc.z = c[2] * t + g_1041d80[a0].a.z;
	g_67bbdc.x *= scale;
	g_67bbdc.y *= scale;
	g_67bbdc.z *= scale;
	c[0] = g_1041d80[n].b.x - g_1041d80[a0].b.x;
	c[1] = g_1041d80[n].b.y - g_1041d80[a0].b.y;
	c[2] = g_1041d80[n].b.z - g_1041d80[a0].b.z;
	g_6b86c4.x = c[0] * t + g_1041d80[a0].b.x;
	g_6b86c4.y = c[1] * t + g_1041d80[a0].b.y;
	g_6b86c4.z = c[2] * t + g_1041d80[a0].b.z;
	inv = 1.0f - t;
	pc = g_1041d80[a0].pal;
	pn = g_1041d80[n].pal;
	for (dst = g_1041d20; (int) dst < (int) (g_1041d20 + 6); dst++) {
		((unsigned char*) &dst->color)[2] = (unsigned char) (int) (((unsigned char*) &pc->color)[2] * inv + ((unsigned char*) &pn->color)[2] * t);
		((unsigned char*) &dst->color)[1] = (unsigned char) (int) (((unsigned char*) &pn->color)[1] * t + ((unsigned char*) &pc->color)[1] * inv);
		((unsigned char*) &dst->color)[0] = (unsigned char) (int) (((unsigned char*) &pc->color)[0] * inv + ((unsigned char*) &pn->color)[0] * t);
		dst->f4 = inv * pc->f4 + t * pn->f4;
		dst->f8 = inv * pc->f8 + t * pn->f8;
		pc++;
		pn++;
	}
	UpdateSceneLighting(a3);
	*(int*) 0x67a95c = a0;
	if (g_6b89c0 != 0) {
		rows = (unsigned char*) g_10405e0;
		*((unsigned char*) (g_6b89c0 + 0x0a)) =
			(unsigned char) (int) (rows[a0 * 4 + 2] * inv + rows[n * 4 + 2] * t);
		*((unsigned char*) (g_6b89c0 + 0x09)) =
			(unsigned char) (int) (rows[a0 * 4 + 1] * inv + rows[n * 4 + 1] * t);
		*((unsigned char*) (g_6b89c0 + 0x08)) =
			(unsigned char) (int) (rows[a0 * 4 + 0] * inv + rows[n * 4 + 0] * t);
	}
	return 1;
}
