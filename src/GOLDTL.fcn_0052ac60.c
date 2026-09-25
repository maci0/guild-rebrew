// FUNCTION: GOLDTL 0x0052ac60
// SIZE: 266

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

// SIZE 0x90
typedef struct {
	char pad0[0x4c];
	Vec3 pos;
	char pad58[0x84 - 0x58];
	Vec3 rot;
} View;

extern int g_6b8010;
extern View* g_6b8014;
extern float g_774690;
extern float g_774694;
extern float g_6a2558;
extern float g_6a255c;
extern float g_6a2560;
extern float g_6a2564;
extern float g_7e3a40;
extern float g_7e3a44;
extern float g_7e3a48;
extern float g_7e3a50;
extern float g_7e3a54;
extern float g_7e3a58;

float __cdecl fcn_00413d10(Vec3* p);
void __cdecl fcn_00438b40(View* v, Vec4* p);
void __cdecl fcn_00438cb0(View* v, Vec3* r);

void __cdecl fcn_0052ac60(float t)
{
	float h;
	Vec4 p;
	Vec3 r;

	if (g_6b8010 == 0) {
		g_774690 = t;
		g_774694 = t;
		h = fcn_00413d10(&g_6b8014->pos);
		p.x = g_6b8014->pos.x;
		p.y = g_6b8014->pos.y;
		p.z = g_6b8014->pos.z;
		p.y = (g_6a2560 - g_6a2558) * g_774690 + g_6a2558 + h;
		fcn_00438b40(g_6b8014, &p);
		r.x = g_6b8014->rot.x;
		r.y = g_6b8014->rot.y;
		r.z = g_6b8014->rot.z;
		r.x = (g_6a2564 - g_6a255c) * g_774694 + g_6a255c;
		fcn_00438cb0(g_6b8014, &r);
		g_7e3a50 = g_6b8014->rot.x;
		g_7e3a54 = g_6b8014->rot.y;
		g_7e3a58 = g_6b8014->rot.z;
		g_7e3a40 = g_6b8014->pos.x;
		g_7e3a44 = g_6b8014->pos.y;
		g_7e3a48 = g_6b8014->pos.z;
	}
}
