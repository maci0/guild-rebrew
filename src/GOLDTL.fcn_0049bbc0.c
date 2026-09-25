typedef struct Req {
	unsigned short* s;
	int id;
	int arg;
	int dir;
	int pad;
} Req;
// SIZE 0x14

extern float g_1008574[];
extern float g_10099d0[8];

unsigned short* __cdecl fcn_00502cd0(int a, int b, int c, int d);
float* __cdecl fcn_005c61e0(int id);
int __cdecl fcn_005dbf10(char* e, Req* r);

// FUNCTION: GOLD 0x49c180
// SIZE: 399
// FUNCTION: GOLDTL 0x49bbc0
// SIZE: 399
int __cdecl fcn_0049bbc0(char* e, int* p, int* q)
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
		if (fcn_005dbf10(e, &r) == 1) {
			if (r.dir == 1) {
				g_10099d0[0] = g_1008574[q[4] * 37 + 0] * d[3];
				g_10099d0[2] = g_1008574[q[4] * 37 + 2] * d[3];
				g_10099d0[4] = g_1008574[q[4] * 37 + 4] * d[3];
				g_10099d0[6] = g_1008574[q[4] * 37 + 6] * d[3];
				return 0x23;
			}
			if (r.dir == -1) {
				g_10099d0[0] = -(g_1008574[q[4] * 37 + 0] * d[3] * 0.5f);
				g_10099d0[2] = -(g_1008574[q[4] * 37 + 2] * d[3] * 0.5f);
				g_10099d0[4] = -(g_1008574[q[4] * 37 + 4] * d[3] * 0.5f);
				g_10099d0[6] = -(g_1008574[q[4] * 37 + 6] * d[3] * 0.5f);
			}
			return 0x23;
		}
	}
	return 0;
}
