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
extern char g_1041d80[];
extern int g_10405e0[];

void __cdecl fcn_004379a0(int a, int b, int c, void* cb, void* q);
void __cdecl UpdateSceneLighting(int a);
char __cdecl fcn_00445d20(int a, float* v);
char __cdecl fcn_00445d00(char* p, float* q);

/* ADDRESS: GOLDTL 0x00445f50 */
char __cdecl fcn_00445f50(unsigned int a0, float t, float scale, int a3)
{
	float pos;
	float* cur;
	float* next;
	Pal_1041d20* pc;
	Pal_1041d20* pn;
	Pal_1041d20* dst;
	unsigned char* rows;
	float inv;
	float c0;
	float c1;
	float c2;
	unsigned int n;

	if (a0 >= 7)
		return 0;
	if (!(t >= g_6628a8))
		return 0;
	if (!(t <= g_6628a0))
		return 0;
	pos = (float) a0 + t;
	fcn_004379a0(g_67a370, 0, 0x1e, (void*) fcn_00445d20, &pos);
	if (scale != g_6628a0)
		fcn_004379a0(g_67a370, 0, 8, (void*) fcn_00445d00, &scale);
	n = (a0 + 1) % 7;
	cur = (float*) (g_1041d80 + a0 * 0x60);
	next = (float*) (g_1041d80 + n * 0x60);
	c0 = next[0] - cur[0];
	c1 = next[1] - cur[1];
	c2 = next[2] - cur[2];
	g_67bbdc.x = c0 * t + cur[0];
	g_67bbdc.y = c1 * t + cur[1];
	g_67bbdc.z = c2 * t + cur[2];
	g_67bbdc.x *= scale;
	g_67bbdc.y *= scale;
	g_67bbdc.z *= scale;
	c0 = next[3] - cur[3];
	c1 = next[4] - cur[4];
	c2 = next[5] - cur[5];
	g_6b86c4.x = c0 * t + cur[3];
	g_6b86c4.y = c1 * t + cur[4];
	g_6b86c4.z = c2 * t + cur[5];
	inv = g_6628a0 - t;
	pc = (Pal_1041d20*) (cur + 6);
	pn = (Pal_1041d20*) (next + 6);
	for (dst = g_1041d20; dst < g_1041d20 + 6; dst++) {
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
