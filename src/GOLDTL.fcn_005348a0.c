// FUNCTION: GOLDTL 0x005348a0
// SIZE: 745

#define MAXV(a, b) (((a) > (b)) ? (a) : (b))
#define MINV(a, b) (((a) < (b)) ? (a) : (b))

typedef struct {
	float x;
	float y;
	float z;
} Vec3;
// SIZE 0xc

typedef struct {
	float x;
	float y;
	float z;
	float w;
} Vec4;
// SIZE 0x10

typedef struct {
	float m[16];
} Mat4;
// SIZE 0x40

extern int g_7e4300;
extern int g_7e4304;
extern int g_7e4308;
extern int g_7e430c;
extern int g_7e4310;
extern char* g_7e4260[32];
extern short g_14ce8c0;
extern short g_14ce8c2;
extern int g_1042570;
extern int g_1042574;
extern int g_1042578;
extern int g_104257c;
extern unsigned short g_774970;
extern int g_67a370;
extern int g_6b8014;
extern char g_1052be0[];
extern float g_1052c00[16];

int __cdecl fcn_004cef70(int who, char* obj);
void __cdecl fcn_00438100(char* obj, int cam, int flag);
Vec3* __stdcall fcn_005eb2e4(Vec3* out, Vec3* v, void* vp, Mat4* proj, Mat4* view, Mat4* world);

typedef Vec3* (__cdecl *BoxFn)(char* obj, char* mesh, int arg);

/* Flags every selectable object whose box centre projects into the
 * drag rectangle. */
void __cdecl fcn_005348a0(void)
{
	int x0;
	int x1;
	int y0;
	int y1;
	Vec3 v;
	Vec4 s;
	Mat4 m;
	int k;
	char* obj;
	char* p;
	char* e;
	Vec3* b;
	int i;

	if (g_7e4300 == 0) {
		return;
	}
	g_7e430c = MINV(MAXV(g_1042570, g_14ce8c0), g_1042578 - 1);
	g_7e4310 = MINV(MAXV(g_1042574, g_14ce8c2), g_104257c - 1);
	x0 = MINV(g_7e4304, g_7e430c);
	y0 = MINV(g_7e4308, g_7e4310);
	x1 = MAXV(g_7e4304, g_7e430c);
	y1 = MAXV(g_7e4308, g_7e4310);
	for (k = 0; k < 32; k++) {
		obj = g_7e4260[k];
		if (obj == 0 || obj[8] == 0) {
			continue;
		}
		i = fcn_004cef70(g_774970, obj);
		obj[0x188] = 0;
		if ((i & 0x800) == 0) {
			continue;
		}
		p = *(char**) (obj + 0x184);
		if (p == 0 || *(int*) (p + 0x88) != g_67a370) {
			continue;
		}
		e = *(char**) (p + 0x34);
		if (*(char**) (e + 0x1cc) == 0) {
			continue;
		}
		fcn_00438100(e, g_6b8014, 0);
		b = (*(BoxFn*) (*(char**) (*(char**) (e + 0x1cc) + 0x318) + 0x1f0))(e, *(char**) (e + 0x1cc), *(int*) (e + 0x1ec) + 0x48);
		if (b == 0) {
			continue;
		}
		s.x = 0.0f;
		s.y = 0.0f;
		s.z = 0.0f;
		m.m[1] = m.m[2] = m.m[3] = m.m[4] = m.m[6] = m.m[7] = m.m[8] = m.m[9] = m.m[11] = m.m[12] =
			m.m[13] = m.m[14] = 0.0f;
		m.m[0] = m.m[5] = m.m[10] = m.m[15] = 1.0f;
		/* the reference adds the first corner eight times: b never advances */
		for (i = 0; i < 8; i++) {
			s.x += b->x;
			s.y += b->y;
			s.z += b->z;
		}
		s.x *= 0.125f;
		s.y *= 0.125f;
		s.z *= 0.125f;
		v.x = s.x;
		v.y = s.y;
		v.z = s.z;
		if (v.z >= 0.0f) {
			fcn_005eb2e4(&v, &v, g_1052be0, (Mat4*) g_1052c00, &m, &m);
			if (v.z >= 0.0f && v.z <= 1.0f && x0 <= v.x && x1 >= v.x && y0 <= v.y && y1 >= v.y) {
				obj[0x188] = 1;
			}
		}
	}
}
