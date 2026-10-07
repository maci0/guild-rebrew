typedef struct Req {
	unsigned short* s;
	int id;
	int arg;
	int dir;
	int pad;
} Req;
// SIZE 0x14

extern float g_10097f4;
extern float g_1009814;

unsigned short* __cdecl fcn_00502cd0(int a, int b, int c, int d);
float* __cdecl fcn_005c61e0(int id);
int __cdecl fcn_005dbf10(char* e, Req* r);

// FUNCTION: GOLD 0x0049b6e0
// FUNCTION: GOLDTL 0x49b120
int __cdecl fcn_0049b120(char* e, int* p, int* q)
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
		r.arg = -1;
		if (fcn_005dbf10(e, &r) == 1) {
			if (r.dir == 1) {
				g_1009814 = g_10097f4 * d[3];
				return 0x20;
			}
			if (r.dir == -1) {
				g_1009814 = -(g_10097f4 * d[3] * 0.5f);
			}
			return 0x20;
		}
	}
	return 0;
}
