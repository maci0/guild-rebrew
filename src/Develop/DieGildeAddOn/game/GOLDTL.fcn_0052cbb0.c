#include <math.h>

#define MAXV(a, b) ((a) > (b) ? (a) : (b))
#define MINV(a, b) ((b) < (a) ? (b) : (a))

#include "Develop/Units/d3/d3_camera.h"
#include "Develop/DieGildeAddOn/game/spiel.h"

extern float g_662d40[3];
extern float g_6a2558;
extern float g_6a2560;
extern float g_774690;
extern int g_6a256c;
extern int g_6b5cc0;
extern int g_6b5cbc;
extern float g_7e3a40[3];
extern float g_7e3a50[3];
extern unsigned short g_774970;
extern char g_7f4ca0[];
extern char* g_7e2aa0;
extern char* g_7746c0;

typedef struct {
	char pad0[0x8c];
	float pos[3];
	int pad98;
	float rot[3];
} Save;

typedef struct {
	char pad0[0x21c];
} House;

#pragma pack(push, 1)
typedef struct {
	char pad0[0x61];
	char* obj;
} Ent;
#pragma pack(pop)

int __cdecl fcn_004133e0(char* e, float* lo, float* hi);
float* __stdcall fcn_005ebbb9(float* out, const float* in);
void __cdecl fcn_00455350(char* e, char* pos, float* out);
float __cdecl fcn_00413d10(float* p);
void __cdecl fcn_00433780(char* cam);
void __cdecl fcn_00412cf0(char* cam, float* a, float* b, int d, int e);

/* ADDRESS: GOLDTL 0x0052cbb0 */
void __cdecl fcn_0052cbb0(Ent* e)
{
	float n;
	float q[4];
	float rot[3];
	float lo;
	float hi;
	float off[4];
	float p[4];
	float m[16];
	float d[4];
	float h;
	float dx;
	float dz;
	float dy;
	float len;
	float a;
	float b;
	float c;
	char* obj;
	char* cam;
	Save* s;

	obj = e->obj;
	fcn_004133e0(obj, &lo, &hi);
	fcn_005ebbb9(m, (float*) ((char*) g_6b8014 + 0x18c));
	a = g_662d40[0] * -600.0f;
	b = g_662d40[1] * -600.0f;
	c = g_662d40[2] * -600.0f;
	off[0] = m[8] * c + m[4] * b + m[0] * a;
	off[1] = m[9] * c + m[5] * b + m[1] * a;
	off[2] = m[10] * c + m[6] * b + m[2] * a;
	fcn_00455350(obj, obj + 0x4c, p);
	q[0] = p[0] + off[0];
	q[1] = p[1] + off[1];
	q[2] = p[2] + off[2];
	h = fcn_00413d10(q);
	q[1] = ((g_6a2560 - g_6a2558) * g_774690 + g_6a2558) + h;
	d[1] = q[1] - p[1];
	fcn_004133e0(obj, &lo, &hi);
	n = off[1] / ((hi - lo) * 0.5f + d[1]);
	q[0] = (float) (q[0] - (n * off[0] - off[0] * 1.8));
	q[2] = (float) (q[2] - (n * off[2] - off[2] * 1.8));
	cam = (char*) g_6b8014;
	*(int*) &rot[0] = *(int*) (cam + 0x84);
	*(int*) &rot[1] = *(int*) (cam + 0x88);
	*(int*) &rot[2] = *(int*) (cam + 0x8c);
	fcn_00433780(cam);
	g_6b5cc0 = 0;
	g_6b5cbc = 0;
	h = fcn_00413d10(q);
	q[1] = ((g_6a2560 - g_6a2558) * g_774690 + g_6a2558) + h;
	cam = (char*) g_6b8014;
	dx = q[0] - *(float*) (cam + 0x4c);
	dy = q[1] - *(float*) (cam + 0x50);
	dz = q[2] - *(float*) (cam + 0x54);
	n = (float) g_6a256c;
	len = (float) sqrt(dz * dz + dy * dy + dx * dx) * n * 0.0005f;
	fcn_00412cf0(cam, q, rot, (int) MINV(MAXV(n, len), (float) (g_6a256c * 3)), 0x68);
	g_7e3a50[0] = rot[0];
	g_7e3a50[1] = rot[1];
	g_7e3a50[2] = rot[2];
	g_7e3a40[0] = q[0];
	g_7e3a40[1] = q[1];
	g_7e3a40[2] = q[2];
	s = (Save*) gm_GetEntityTableEntry((char*) (&((House*) g_7f4ca0)[g_774970]));
	if (s != 0) {
		*(int*) &s->pos[0] = *(int*) &q[0];
		*(int*) &s->pos[1] = *(int*) &q[1];
		*(int*) &s->pos[2] = *(int*) &q[2];
		*(int*) &s->rot[0] = *(int*) &rot[0];
		*(int*) &s->rot[1] = *(int*) &rot[1];
		*(int*) &s->rot[2] = *(int*) &rot[2];
	}
	g_7e2aa0 = (char*) e;
	g_7746c0 = e->obj;
}
