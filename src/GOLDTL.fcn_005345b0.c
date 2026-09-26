// FUNCTION: GOLDTL 0x005345b0
// SIZE: 749

typedef struct {
	float x;
	float y;
	float z;
} Vec3;
// SIZE 0xc

/* the centre accumulator is a 4-float vector; only x, y and z are summed */
typedef struct {
	float x;
	float y;
	float z;
	float w;
} Vec4;
// SIZE 0x10

typedef struct {
	float m[4][4];
} Mat4;
// SIZE 0x40

typedef float* (__cdecl* BoundsFn)(char*, char*, int);

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

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

int __cdecl fcn_00506380(int, int, int, char*);
void __cdecl fcn_00438100(char*, int, int);
Vec3* __stdcall fcn_005eb2e4(Vec3*, Vec3*, char*, Mat4*, Mat4*, Mat4*);

void __cdecl fcn_005345b0(void)
{
	int x0;
	int x1;
	int y0;
	int y1;
	Vec3 v;
	Vec4 c;
	Mat4 m;
	int k;
	char* e;
	char* o;
	char* s;
	char* sub;
	float* p;
	int i;

	if (g_7e4300 != 0) {
		g_7e430c = MIN(MAX(g_1042570, g_14ce8c0), g_1042578 - 1);
		g_7e4310 = MIN(MAX(g_1042574, g_14ce8c2), g_104257c - 1);
		x0 = MIN(g_7e4304, g_7e430c);
		y0 = MIN(g_7e4308, g_7e4310);
		x1 = MAX(g_7e4304, g_7e430c);
		y1 = MAX(g_7e4308, g_7e4310);
		for (k = 0; k < 32; k++) {
			e = g_7e4260[k];
			if (e == 0 || e[8] == 0) {
				continue;
			}
			i = fcn_00506380(g_774970, 0, 0, e);
			e[0x188] = 0;
			if ((i & 0x800) == 0) {
				continue;
			}
			o = *(char**) (e + 0x184);
			if (o == 0 || *(int*) (o + 0x88) != g_67a370) {
				continue;
			}
			s = *(char**) (o + 0x34);
			if (*(char**) (s + 0x1cc) == 0) {
				continue;
			}
			fcn_00438100(s, g_6b8014, 0);
			sub = *(char**) (s + 0x1cc);
			p = (*(BoundsFn*) (*(char**) (sub + 0x318) + 0x1f0))(s, sub, *(int*) (s + 0x1ec) + 0x48);
			if (p == 0) {
				continue;
			}
			c.x = 0.0f;
			c.y = 0.0f;
			c.z = 0.0f;
			m.m[0][1] = m.m[0][2] = m.m[0][3] = m.m[1][0] = m.m[1][2] = m.m[1][3] = m.m[2][0] = m.m[2][1] =
			    m.m[2][3] = m.m[3][0] = m.m[3][1] = m.m[3][2] = 0.0f;
			m.m[0][0] = m.m[1][1] = m.m[2][2] = m.m[3][3] = 1.0f;
			for (i = 0; i < 8; i++) {
				c.x += p[0];
				c.y += p[1];
				c.z += p[2];
			}
			c.x *= 0.125f;
			c.y *= 0.125f;
			c.z *= 0.125f;
			v.x = c.x;
			v.y = c.y;
			v.z = c.z;
			if (v.z >= 0.0f) {
				fcn_005eb2e4(&v, &v, g_1052be0, (Mat4*) g_1052c00, &m, &m);
				if (v.z >= 0.0f && v.z <= 1.0f && x0 <= v.x && x1 >= v.x && y0 <= v.y && y1 >= v.y) {
					e[0x188] = 1;
				}
			}
		}
	}
}
