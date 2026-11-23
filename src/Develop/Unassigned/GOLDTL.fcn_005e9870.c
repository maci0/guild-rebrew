/* Same record layout as src/Develop/Units/d3/GOLDTL.fcn_004efde0.c, its caller. */
typedef struct Sefde0Entry {
	int f00[12];
	int obj;
	int f34[10];
	int state;
	int f60[2];
} Sefde0Entry;

extern float g_6ad620;
extern float g_6660e8;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_1043370;

char __cdecl fcn_0045b990(int, float*, int*, int*, float*);
int __cdecl fcn_005ea2d0(int, float*, float*, int, int, int*, int*);

/* ADDRESS: GOLDTL 0x005e9870 */
int __cdecl fcn_005e9870(Sefde0Entry *entry)
{
	char *obj;
	float step;
	float inv;
	float f[3];
	float q[3];
	float m[3];
	float r[3];
	float t[3];
	float pf[3];
	float v[3];
	float h;
	int remain;
	int n;
	int ox;
	int oy;
	int nx;
	int ny;
	int map;

	obj = (char *)entry;
	map = g_1043370;
	step = *(float *)0x6660ec * g_6660e8;
	inv = *(float *)0x6660ec / *(float*) (obj + 0x54);
	if (*(int*) (obj + 0x5c) != 1) {
		return 0;
	}
	remain = g_6b7fac - *(int*) (obj + 0x60);
	if (fcn_0045b990(map, (float*) (obj + 0x30), &ox, &oy, &h) == 0) {
		*(int*) (obj + 0x5c) = 3;
		*(int*) (obj + 0x58) = 0;
		return 0;
	}
	f[0] = *(float*) (obj + 0x50) * *(float*) (obj + 0x40) * *(float*) (obj + 0x40) * (*(float*) (obj + 0x40) > 0.0f ? 1.0f : -1.0f) * g_6ad620 * 1.2f * 0.5f;
	f[1] = ((*(float*) (obj + 0x44) > 0.0f ? 1.0f : -1.0f) * *(float*) (obj + 0x50) * g_6ad620 * 1.2f) * *(float*) (obj + 0x44) * *(float*) (obj + 0x44) * 0.5f;
	f[2] = *(float*) (obj + 0x50) * (*(float*) (obj + 0x48) > 0.0f ? 1.0f : -1.0f) * g_6ad620 * 1.2f * *(float*) (obj + 0x48) * *(float*) (obj + 0x48) * 0.5f;
	n = 0;
	while (n < remain) {
		v[0] = *(float*) (obj + 0x10);
		v[1] = *(float*) (obj + 0x14);
		v[2] = *(float*) (obj + 0x18);
		q[0] = ((v[0] > 0.0f ? 1.0f : -1.0f) * *(float*) (obj + 0x50) * g_6ad620 * 1.2f) * v[0] * v[0] * 0.5f;
		q[1] = ((v[1] > 0.0f ? 1.0f : -1.0f) * *(float*) (obj + 0x50) * g_6ad620 * 1.2f) * v[1] * v[1] * 0.5f;
		q[2] = ((v[2] > 0.0f ? 1.0f : -1.0f) * *(float*) (obj + 0x50) * g_6ad620 * 1.2f) * v[2] * v[2] * 0.5f;
		m[0] = (q[0] + f[0]) * inv;
		m[1] = (q[1] + f[1]) * inv - step;
		m[2] = (q[2] + f[2]) * inv;
		v[0] += m[0];
		v[1] += m[1];
		v[2] += m[2];
		r[0] = ((v[0] > 0.0f ? 1.0f : -1.0f) * *(float*) (obj + 0x50) * g_6ad620 * 1.2f) * v[0] * v[0] * 0.5f;
		r[1] = ((v[1] > 0.0f ? 1.0f : -1.0f) * *(float*) (obj + 0x50) * g_6ad620 * 1.2f) * v[1] * v[1] * 0.5f;
		r[2] = ((v[2] > 0.0f ? 1.0f : -1.0f) * *(float*) (obj + 0x50) * g_6ad620 * 1.2f) * v[2] * v[2] * 0.5f;
		pf[0] = *(float*) (obj + 0x30);
		pf[1] = *(float*) (obj + 0x34);
		pf[2] = *(float*) (obj + 0x38);
		*(int*) (obj + 0x60) += 1;
		*(int*) (obj + 0x64) += 1;
		t[0] = (r[0] + f[0]) * inv;
		t[1] = (r[1] + f[1]) * inv - step;
		t[2] = (r[2] + f[2]) * inv;
		v[0] = (t[0] + m[0]) * 0.5f + *(float*) (obj + 0x10);
		v[1] = (t[1] + m[1]) * 0.5f + *(float*) (obj + 0x14);
		v[2] = (t[2] + m[2]) * 0.5f + *(float*) (obj + 0x18);
		*(float*) (obj + 0x10) = v[0];
		*(float*) (obj + 0x14) = v[1];
		*(float*) (obj + 0x18) = v[2];
		pf[0] += v[0] * 39.37008f * *(float *)0x6660ec;
		pf[1] += v[1] * 39.37008f * *(float *)0x6660ec;
		pf[2] += v[2] * 39.37008f * *(float *)0x6660ec;
		nx = ox;
		ny = oy;
		if (fcn_005ea2d0(map, (float*) (obj + 0x30), pf, ox, oy, &nx, &ny) != 0 && *(unsigned int*) (obj + 0x64) > 0x32) {
			*(float*) (obj + 0x30) = pf[0];
			*(float*) (obj + 0x34) = pf[1];
			*(float*) (obj + 0x38) = pf[2];
			*(int*) (obj + 0x5c) = 2;
			*(float*) (obj + 0x58) =
				(*(float*)(obj + 0x18) * *(float*)(obj + 0x18) + *(float*)(obj + 0x14) * *(float*)(obj + 0x14) + *(float*)(obj + 0x10) * *(float*)(obj + 0x10)) * *(float*) (obj + 0x54) * 0.5f;
			return 0;
		}
		*(float*) (obj + 0x30) = pf[0];
		*(float*) (obj + 0x34) = pf[1];
		*(float*) (obj + 0x38) = pf[2];
		ox = nx;
		oy = ny;
		n++;
	}
	return 1;
}
