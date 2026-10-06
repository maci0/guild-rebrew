typedef struct Req {
	unsigned short* s;
	int id;
	int arg;
	int dir;
	int pad;
} Req;
// SIZE 0x14

extern float g_10095a4;
extern float g_10095c4;

unsigned short* __cdecl fcn_00502cd0(int a, int b, int c, int d);
float* __cdecl fcn_005c61e0(int id);
int __cdecl fcn_005dbf10(char* e, Req* r);

// FUNCTION: GOLD 0x0049aa70
// FUNCTION: GOLDTL 0x49a4b0
int __cdecl fcn_0049a4b0(char* e, int* p, int* q)
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
		r.id = q[1];
		r.arg = q[2];
		r.dir = 0;
		r.pad = 0;
		if (fcn_005dbf10(e, &r) == 1) {
			if (r.dir == 1) {
				g_10095c4 = g_10095a4 * d[3];
				return 0x1c;
			}
			if (r.dir == -1) {
				g_10095c4 = g_10095a4 * d[3] * -0.5f;
			}
			return 0x1c;
		}
	}
	return 0;
}
