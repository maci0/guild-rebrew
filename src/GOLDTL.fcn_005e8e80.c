#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

// SIZE 0xc
typedef struct {
	float x;
	float y;
	float z;
} V3;

// SIZE 0x10
typedef struct {
	float x;
	float y;
	float z;
	float w;
} V4;

// SIZE 0x68
typedef struct {
	V4 cur;
	V4 start;
	V3 pos;
	float pad2c;
	V3 origin;
	float pad3c;
	V4 color;
	float area;
	float mass;
	int pad58;
	int active;
	int time;
	int age;
} Particle;

extern float g_6660fc;
extern float g_666100;
extern float g_6628a8;
extern int g_6b7fac;

V4* __cdecl fcn_005e8850(void);

// FUNCTION: GOLD 0x005dc2f0
// SIZE: 99
// FUNCTION: GOLDTL 0x005e8de0
// SIZE: 99

int __cdecl fcn_005e8de0(float a, float b, float* out)
{
	float b2;

	if (a < 0.0f || b < 0.0f) {
		return 0;
	}
	out[0] = a;
	out[1] = b;
	b2 = b * b;
	out[2] = 6.2831855f * b2;
	out[3] = b2 * b * 4.1887903f;
	out[4] = out[3] * a;
	return 1;
}

// FUNCTION: GOLDTL 0x005e8e80
// SIZE: 341

int __cdecl fcn_005e8e80(Particle* o, V3* pos, V3* dir, float speed, float b, float a)
{
	float info[5];
	V4* c;
	float v;

	c = fcn_005e8850();
	fcn_005e8de0(a, b, info);
	*(V3*) &o->cur = *dir;
	o->cur.w = speed / info[4] * g_6660fc;
	o->cur.x *= o->cur.w;
	o->cur.y *= o->cur.w;
	o->cur.z *= o->cur.w;
	o->start = o->cur;
	o->color = *c;
	v = MAX(MIN(o->color.w, g_666100), g_6628a8);
	o->color.w = v;
	o->color.x *= v;
	o->color.y *= v;
	o->color.z *= v;
	o->pos = *pos;
	o->origin = *pos;
	o->mass = info[4];
	o->area = info[2];
	o->active = 1;
	o->time = g_6b7fac;
	o->age = 0;
	return 1;
}
