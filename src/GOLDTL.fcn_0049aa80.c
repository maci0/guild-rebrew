typedef struct Req {
	unsigned short* s;
	int id;
	int arg;
	int dir;
	int pad;
} Req;
// SIZE 0x14

extern float g_10096cc;
extern float g_10096ec;

unsigned short* __cdecl fcn_00502cd0(int a, int b, int c, int d);
float* __cdecl fcn_005c61e0(int id);
int __cdecl fcn_005dbf10(char* e, Req* r);

// FUNCTION: GOLDTL 0x49aa80
// SIZE: 195
int __cdecl fcn_0049aa80(char* e, int* p)
{
	float* d;
	unsigned short* s;
	Req r;

	s = fcn_00502cd0(*(int*) (e + 0x178), 1, 1, p[1]);
	if (!s) {
		return 0;
	}
	d = fcn_005c61e0(*s);
	if (d) {
		r.s = s;
		r.id = -1;
		r.arg = -1;
		r.dir = 0;
		r.pad = 0;
		if (fcn_005dbf10(e, &r) == 1) {
			if (r.dir == 1) {
				g_10096ec = g_10096cc * d[3];
				return 0x1e;
			}
			if (r.dir == -1) {
				g_10096ec = -(g_10096cc * d[3]);
			}
			return 0x1e;
		}
	}
	return 0;
}
