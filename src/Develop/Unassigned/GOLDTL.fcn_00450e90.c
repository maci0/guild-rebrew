#include <math.h>
#include <stdlib.h>

typedef struct {
	float value;
	char* e;
	int pad;
} SortEntry450e90;

typedef struct SceneLight450e90 SceneLight450e90;
struct SceneLight450e90 {
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
	SceneLight450e90* next;
};

typedef struct {
	float x;
	float y;
	float z;
	float w;
} Probe450e90;

typedef struct Device450e90 Device450e90;
typedef struct {
	char pad0[0xb8];
	int (__stdcall* SetTransform)(Device450e90*, int, int);
} DeviceVtbl450e90;
struct Device450e90 {
	DeviceVtbl450e90* vtbl;
};

extern float g_6628a8;
extern float g_67bc1c;
extern float g_67bc20;
extern char g_67bc24;
extern void* g_1041d04;
extern Device450e90* g_6b5de0;
extern void* g_6b86e4;
extern void* g_6b86e8;
extern int g_6b86fc;
extern int g_6b8704;
extern int g_6b8708;

int __cdecl fcn_00451120(float*, float*);
void __cdecl fcn_00451150(int, char*, float, float*, float*);

/* ADDRESS: GOLDTL 0x00450e90 */
void __cdecl fcn_00450e90(float a, float b, char* c, float* d, float* e)
{
	SceneLight450e90* light;
	Probe450e90* probe;
	float acc;
	float dist;
	float dx;
	float dy;
	float dz;
	float v;
	int sign;
	int i;
	int n;

	sign = (b < g_6628a8) ? (int) 0x80000000 : 0;
	if (!(b > -b)) {
		b = -b;
	}
	if (!g_67bc24) {
		return;
	}
	g_6b8708 = 0;
	for (light = (SceneLight450e90*) g_6b86e4; light != 0 && g_6b8708 < g_6b8704; light = light->next) {
		((SortEntry450e90*) g_1041d04)[g_6b8708].e = (char*) light;
		((SortEntry450e90*) g_1041d04)[g_6b8708].value = g_67bc1c * light->power * b + 3.402823466e+38F;
		((SortEntry450e90*) g_1041d04)[g_6b8708].pad = 0;
		g_6b8708++;
	}
	probe = (Probe450e90*) c;
	for (light = (SceneLight450e90*) g_6b86e8; light != 0 && g_6b8708 < g_6b8704; light = light->next) {
		acc = g_6628a8;
		for (i = 0; i < 9; i++) {
			dx = probe[i].x - light->x;
			dy = probe[i].y - light->y;
			dz = probe[i].z - light->z;
			dist = (float) sqrt(dx * dx + dy * dy + dz * dz);
			if (i == 8) {
				dist -= 0.5f * a;
			}
			if (1.0f > dist) {
				dist = 1.0f;
			}
			if (dist <= light->range) {
				v = 1.0f / (dist * light->atten);
				v = v * light->power;
				v = v * g_67bc20;
				v = v * b;
				v = v * (light->b + light->g + light->r);
				acc += v * 0.0013071895809844136f;
			}
		}
		if (acc > g_6628a8) {
			((SortEntry450e90*) g_1041d04)[g_6b8708].e = (char*) light;
			((SortEntry450e90*) g_1041d04)[g_6b8708].value = acc;
			((SortEntry450e90*) g_1041d04)[g_6b8708].pad = 0;
			g_6b8708++;
		}
	}
	qsort((SortEntry450e90*) g_1041d04, g_6b8708, 0xc, (int (__cdecl*)(const void*, const void*)) fcn_00451120);
	if (g_6b8708 < g_6b86fc) {
		n = g_6b8708;
	} else {
		n = g_6b86fc;
	}
	for (i = n; i < g_6b86fc; i++) {
		g_6b5de0->vtbl->SetTransform(g_6b5de0, i, 0);
	}
	for (i = 0; i < n; i++) {
		fcn_00451150(sign + i, ((SortEntry450e90*) g_1041d04)[i].e, b, d, e);
		g_6b5de0->vtbl->SetTransform(g_6b5de0, i, 1);
	}
}
unsigned char _dpad_1041d04[1180];
unsigned char _dpad_10405e0[5924];
