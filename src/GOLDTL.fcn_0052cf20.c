// FUNCTION: GOLDTL 0x0052cf20

// SIZE 0xc
typedef struct {
	float x;
	float y;
	float z;
} Vec3;

// SIZE 0x10
typedef struct {
	float x;
	float y;
	float z;
	float w;
} Vec4;

typedef struct View {
	char pad0[0x4c];
	Vec3 pos;
	char pad58[0x84 - 0x58];
	Vec3 rot;
	char pad90[0x18c - 0x90];
	float mat[16];
} View;

typedef struct Save {
	char pad0[0x8c];
	Vec3 pos;
	int pad98;
	Vec3 rot;
} Save;

#pragma pack(push, 1)
typedef struct Ent {
	char pad0[0x61];
	char* obj;
} Ent;
#pragma pack(pop)

typedef struct House {
	char pad0[0x21c];
} House;
// SIZE 0x21c

extern int g_6b8014;
extern float g_662d40[3];
extern float g_774690;
extern float g_6a2558;
extern float g_6a2560;
extern int g_6b5cbc;
extern int g_6b5cc0;
extern float g_7e3a40[3];
extern float g_7e3a50[3];
extern unsigned short g_774970;
extern char g_7f4ca0[];
extern char* g_7e2aa0;
extern char* g_7746c0;

int __cdecl fcn_004133e0(char* e, float* lo, float* hi);
float* __stdcall fcn_005ebbb9(float* out, float* in);
void __cdecl fcn_00455350(char* src, char* pos, Vec3* out);
float __cdecl fcn_00413d10(Vec3* p);
void __cdecl fcn_00433780(View* v);
void __cdecl fcn_00438b40(View* v, Vec3* p);
void __cdecl fcn_00438cb0(View* v, Vec3* r);
#include "Develop/DieGildeAddOn/game/spiel.h"

void __cdecl fcn_0052cf20(Ent* e)
{
	Vec4 q;
	Vec3 rot;
	float lo;
	float hi;
	Vec4 off;
	Vec4 p;
	float m[16];
	Vec4 d;
	float r;
	float h;
	float h2;
	float a;
	float b;
	float c;
	char* obj;
	Save* s;

	obj = e->obj;
	fcn_004133e0(obj, &lo, &hi);
	fcn_005ebbb9(m, ((View*)g_6b8014)->mat);
	a = g_662d40[0] * -600.0f;
	b = g_662d40[1] * -600.0f;
	c = g_662d40[2] * -600.0f;
	off.x = a * m[0] + b * m[4] + c * m[8];
	off.y = a * m[1] + b * m[5] + c * m[9];
	off.z = a * m[2] + b * m[6] + c * m[10];
	fcn_00455350(obj, obj + 0x4c, (Vec3*) &p);
	q.x = p.x + off.x;
	q.y = p.y + off.y;
	q.z = p.z + off.z;
	h = fcn_00413d10((Vec3*) &q);
	q.y = ((g_6a2560 - g_6a2558) * g_774690 + g_6a2558) + h;
	d.y = q.y - p.y;
	fcn_004133e0(obj, &lo, &hi);
	r = off.y / ((hi - lo) * 0.5f + d.y);
	q.x = q.x - (r * off.x - off.x * 1.8);
	q.z = q.z - (r * off.z - off.z * 1.8);
	*(int*) &rot.x = *(int*) &((View*)g_6b8014)->rot.x;
	*(int*) &rot.y = *(int*) &((View*)g_6b8014)->rot.y;
	*(int*) &rot.z = *(int*) &((View*)g_6b8014)->rot.z;
	fcn_00433780((View*)g_6b8014);
	g_6b5cc0 = 0;
	g_6b5cbc = 0;
	h2 = fcn_00413d10((Vec3*) &q);
	q.y = ((g_6a2560 - g_6a2558) * g_774690 + g_6a2558) + h2;
	g_7e3a50[0] = rot.x;
	g_7e3a50[1] = rot.y;
	g_7e3a50[2] = rot.z;
	g_7e3a40[0] = q.x;
	g_7e3a40[1] = q.y;
	g_7e3a40[2] = q.z;
	fcn_00438b40((View*)g_6b8014, (Vec3*) &q);
	fcn_00438cb0((View*)g_6b8014, &rot);
	s = (Save*) gm_GetEntityTableEntry((char*) (&((House*)g_7f4ca0)[g_774970]));
	if (s != 0) {
		*(int*) &s->pos.x = *(int*) &q.x;
		*(int*) &s->pos.y = *(int*) &q.y;
		*(int*) &s->pos.z = *(int*) &q.z;
		*(int*) &s->rot.x = *(int*) &rot.x;
		*(int*) &s->rot.y = *(int*) &rot.y;
		*(int*) &s->rot.z = *(int*) &rot.z;
	}
	g_7e2aa0 = (char*) e;
	g_7746c0 = e->obj;
}
