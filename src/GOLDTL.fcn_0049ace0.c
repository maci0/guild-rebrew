typedef struct Req {
	unsigned short* s;
	int id;
	int arg;
	int dir;
	int pad;
} Req;
// SIZE 0x14

extern float g_1009760;
extern float g_1009780;

unsigned short* __cdecl fcn_00502cd0(int a, int b, int c, int d);
float* __cdecl fcn_005c61e0(int id);
int __cdecl fcn_005dbf10(char* e, Req* r);

// FUNCTION: GOLD 0x0049b2a0
// SIZE: 195
// FUNCTION: GOLDTL 0x49ace0
// SIZE: 195
int __cdecl fcn_0049ace0(char* e, int* p)
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
				g_1009780 = g_1009760 * d[3];
				return 0x1f;
			}
			if (r.dir == -1) {
				g_1009780 = -(g_1009760 * d[3]);
			}
			return 0x1f;
		}
	}
	return 0;
}
