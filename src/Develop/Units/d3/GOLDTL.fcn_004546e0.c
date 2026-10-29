#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#include "Develop/Units/d3/d3_camera.h"

void __cdecl fcn_00438100(char* e, char* cam, int f);
char* __cdecl fcn_00455910(char* e, int h, char* p);

/* ADDRESS: GOLDTL 0x004546e0 */
char __cdecl fcn_004546e0(char* e, float* lo, float* hi)
{
	float* q;
	int i;
	int h;

	if (!(*(unsigned char*) (e + 0x216) & 0x20))
		fcn_00438100(e, *(char**) 0x6b8014, 0);
	h = *(int*) (e + 0x1ec);
	q = (float*) fcn_00455910(e, h + 0xf4, (char*) (h + 8));
	if (q != 0) {
		*lo = 1.0e10f;
		lo[1] = 1.0e10f;
		lo[2] = 1.0e10f;
		*hi = -1.0e10f;
		hi[1] = -1.0e10f;
		hi[2] = -1.0e10f;
		for (i = 8; i != 0; i--) {
			*lo = MIN(*lo, q[0]);
			lo[1] = MIN(lo[1], q[1]);
			lo[2] = MIN(lo[2], q[2]);
			*hi = MAX(*hi, q[0]);
			hi[1] = MAX(hi[1], q[1]);
			hi[2] = MAX(hi[2], q[2]);
			q += 20;
		}
		*(float*) (*(int*) (e + 0x1ec) + 0x90) = *lo;
		*(float*) (*(int*) (e + 0x1ec) + 0x94) = lo[1];
		*(float*) (*(int*) (e + 0x1ec) + 0x98) = lo[2];
		*(float*) (*(int*) (e + 0x1ec) + 0xa0) = *hi;
		*(float*) (*(int*) (e + 0x1ec) + 0xa4) = hi[1];
		*(float*) (*(int*) (e + 0x1ec) + 0xa8) = hi[2];
		return 1;
	}
	return 0;
}
