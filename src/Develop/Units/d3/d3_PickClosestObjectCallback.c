#include <math.h>
#include "Develop/DieGildeAddOn/game/game_data.h"

extern float g_fc5348;
extern float g_fc2944;
extern float d3_ProjectionDist;

char __cdecl d3_GetObjectBoundingSphere(char*, char*, float*, float*);

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x00448540 */
char __cdecl d3_PickClosestObjectCallback(char* e, char* ctx)
{
	float v[4];
	float w;
	float inv;
	float x;
	float y;
	float d2;
	char* d;
	float* slot;

	if (*(int*) (ctx + 0x4c) != 0 && (*(int*) (e + 0x224) & *(int*) (ctx + 0x4c)) == 0) {
		return 1;
	}
	d = *(char**) (e + 0x1ec);
	if (d != 0 && (d[0x96d] & 0x40) != 0 && *(int*) (d + 4) == *(int*) (ctx + 0x48)) {
		return 1;
	}
	if (*(int*) (e + 0x218) == 4 && d == 0) {
		return 1;
	}
	if (d3_GetObjectBoundingSphere(e, *(char**) (ctx + 0x48), v, &w)) {
		inv = 1.0f / v[2];
		slot = (float*) (ctx + *(int*) (e + 0x218) * 8);
		w = g_fc5348 * inv * w;
		x = g_fc5348 * v[0] * inv + *(float*) (ctx + 0x50);
		y = g_fc2944 * v[1] * inv + *(float*) (ctx + 0x54);
		d2 = x * x + y * y;
		if (d2 < slot[1] && (float) sqrt(d2) < w) {
			slot[1] = d2;
			*(char**) slot = e;
		}
	}
	return 1;
}
#else
/* ADDRESS: GOLDTL 0x00443b00 */
char __cdecl d3_PickClosestObjectCallback(char* e, char* ctx)
{
	float v[4];
	float w;
	float inv;
	float x;
	float y;
	float d2;
	char* d;
	float* slot;

	if (*(int*) (ctx + 0x4c) != 0 && (*(int*) (e + 0x224) & *(int*) (ctx + 0x4c)) == 0) {
		return 1;
	}
	d = *(char**) (e + 0x1ec);
	if (d != 0 && (d[0x163d] & 0x40) != 0 && *(char**) (d + 4) == *(char**) (ctx + 0x48)) {
		return 1;
	}
	if (*(int*) (e + 0x218) == 4 && d == 0) {
		return 1;
	}
	if (d3_GetObjectBoundingSphere(e, *(char**) (ctx + 0x48), v, &w)) {
		inv = 1.0f / v[2];
		slot = (float*) (ctx + *(int*) (e + 0x218) * 8);
		w = d3_ProjectionDist * inv * w;
		x = d3_ProjectionDist * v[0] * inv + *(float*) (ctx + 0x50);
		y = d3_ProjectionScaleY * v[1] * inv + *(float*) (ctx + 0x54);
		d2 = x * x + y * y;
		if (d2 < slot[1] && (float) sqrt(d2) < w) {
			slot[1] = d2;
			*(char**) slot = e;
		}
	}
	return 1;
}
#endif
