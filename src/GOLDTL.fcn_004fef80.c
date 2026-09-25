// FUNCTION: GOLD 0x004fc820
// SIZE: 104
// FUNCTION: GOLDTL 0x004fef80
// SIZE: 104

typedef struct
{
	unsigned short id;
	char pad2[6];
	unsigned char x8;
	char pad9;
	unsigned short xa;
	char padc[4];
	float f10;
	char pad14[8];
	float f1c;
	float f20;
	int x24;
} Obj28;
// SIZE 0x28

extern float g_662a94;
extern double g_662950;

float __cdecl fcn_004fef80(Obj28* p)
{
	float x;
	float v;

	if (p->id == 0xffff) {
		return g_662a94;
	}
	if (p->x8 == 0) {
		return g_662a94;
	}
	x = p->xa;
	if (x <= p->f20) {
		v = x * ((p->f1c - p->f10) / p->f20) + p->f10;
	} else {
		v = p->f1c;
	}
	v += p->x24;
	return v > g_662950 ? v : g_662950;
}

// FUNCTION: GOLD 0x004fc890
// SIZE: 77
// FUNCTION: GOLDTL 0x4feff0
// SIZE: 77

typedef struct
{
	unsigned short id;
	char p2[6];
	char active;
	char p9;
	unsigned short cur;
	char pc[4];
	float lo;
	char p14[8];
	float hi;
	float max;
} Bar24;
// SIZE 0x24


float __cdecl fcn_004feff0(Bar24* a1)
{
	float v;

	if (a1->id == 0xffff) {
		return g_662a94;
	}
	if (a1->active == 0) {
		return g_662a94;
	}
	v = a1->cur;
	if (v <= a1->max) {
		return (a1->hi - a1->lo) / a1->max * v + a1->lo;
	}
	return a1->hi;
}

extern float g_6628a8;

// FUNCTION: GOLD 0x4fc8e0
// SIZE: 64
// FUNCTION: GOLDTL 0x004ff040
// SIZE: 56

float __cdecl fcn_004ff040(Bar24* a1)
{
	if (a1->id == 0xffff) {
		return g_6628a8;
	}
	if (a1->active == 0) {
		return g_6628a8;
	}
	return fcn_004fef80((Obj28*) a1) / fcn_004feff0(a1);
}

extern char g_7f4ca0[];

// FUNCTION: GOLDTL 0x004ff080
// SIZE: 99

/* Named float addends: the two rounding stores die late and leave the
 * reference's fxch; fxch before faddp. */
float __cdecl fcn_004ff080(unsigned short id)
{
	Bar24* p;
	float v;
	float a;
	float b;

	p = (Bar24*) (g_7f4ca0 + id * 0x21c);
	if (p->active == 1 || p->active == 0) {
		return g_6628a8;
	}
	v = fcn_004feff0(p);
	a = fcn_004fef80((Obj28*) p) / v * 0.8;
	b = v * 0.001f * 0.2;
	return a + b;
}
