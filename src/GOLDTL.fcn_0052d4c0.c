

#include <math.h>

#define MAXV(a, b) ((a) > (b) ? (a) : (b))
#define MINV(a, b) ((b) < (a) ? (b) : (a))

extern int g_6b8014;
extern float g_662d40[3];
extern float g_6a2558;
extern float g_6a2560;
extern float g_774690;
extern int g_6a256c;
extern int g_6b5cc0;
extern int g_6b5cbc;

int __cdecl fcn_004133e0(char* e, float* lo, float* hi);
float* __stdcall fcn_005ebbb9(float*, const float*);
void __cdecl fcn_00455350(char*, char*, float*);
float __cdecl fcn_00413d10(float* p);
void __cdecl fcn_00433780(char* cam);
void __cdecl fcn_00412cf0(char* cam, float* a, float* b, int d, int e);

void __cdecl fcn_0052d4c0(char* e)
{
	float lo;
	float hi;
	float w[4];
	float r[4];
	float t[3];
	float p[4];
	float m[16];
	float v0;
	float v1;
	float v2;
	float dir[4];
	float dy;
	float h;
	float dx;
	float dz;
	float len;
	float n;
	char* cam;

	fcn_004133e0(e, &lo, &hi);
	fcn_005ebbb9(m, (float*) ((char*) g_6b8014 + 0x18c));
	v0 = g_662d40[0] * -600.0f;
	v1 = g_662d40[1] * -600.0f;
	v2 = g_662d40[2] * -600.0f;
	r[0] = m[8] * v2 + m[4] * v1 + m[0] * v0;
	r[1] = m[9] * v2 + m[5] * v1 + m[1] * v0;
	r[2] = m[10] * v2 + m[6] * v1 + m[2] * v0;
	fcn_00455350(e, e + 0x4c, p);
	w[0] = p[0] + r[0];
	w[1] = p[1] + r[1];
	w[2] = p[2] + r[2];
	h = fcn_00413d10(w);
	w[1] = h + ((g_6a2560 - g_6a2558) * g_774690 + g_6a2558);
	dir[1] = w[1] - p[1];
	fcn_004133e0(e, &lo, &hi);
	n = r[1] / ((hi - lo) * 0.5f + dir[1]);
	w[0] = w[0] - (n * r[0] - r[0] * 1.8);
	w[2] = w[2] - (n * r[2] - r[2] * 1.8);
	cam = (char*) g_6b8014;
	t[0] = *(float*) (cam + 0x84);
	t[1] = *(float*) (cam + 0x88);
	t[2] = *(float*) (cam + 0x8c);
	fcn_00433780(cam);
	g_6b5cc0 = 0;
	g_6b5cbc = 0;
	h = fcn_00413d10(w);
	w[1] = h + ((g_6a2560 - g_6a2558) * g_774690 + g_6a2558);
	cam = (char*) g_6b8014;
	dx = w[0] - *(float*) (cam + 0x4c);
	dy = w[1] - *(float*) (cam + 0x50);
	dz = w[2] - *(float*) (cam + 0x54);
	n = (float) g_6a256c;
	len = (float) sqrt(dz * dz + dy * dy + dx * dx) * n * 0.0005f;
	fcn_00412cf0(cam, w, t, (int) MINV(MAXV(n, len), (float) (g_6a256c * 3)), 0x68);
}
