// FUNCTION: GOLD 0x55f130
// SIZE: 373
// FUNCTION: GOLDTL 0x567410
// SIZE: 373

#include <math.h>

char* __cdecl fcn_00502cd0(int, int, ...);
int __cdecl fcn_0050c710(char*, int, int);

int __cdecl fcn_00567410(char* h, int n, char** list, int* out1, int* out2)
{
	float dist[0x20];
	float hi;
	float best;
	float inv;
	float dx;
	float dy;
	float dz;
	char* a;
	char* b;
	char* q;
	int i;
	int bi;
	int r;

	bi = 0;
	hi = 0.01f;
	best = -1.0f;
	for (i = 0; i < n; i++) {
		if ((list[i][0x5a] & 1) == 0 && (a = *(char**) (list[i] + 0x61)) != 0 && *(char**) (h + 0x170) != 0
		    && (b = *(char**) (*(char**) (h + 0x170) + 0x61)) != 0) {
			dx = *(float*) (a + 0x4c) - *(float*) (b + 0x4c);
			dy = *(float*) (a + 0x50) - *(float*) (b + 0x50);
			dz = *(float*) (a + 0x54) - *(float*) (b + 0x54);
			dist[i] = (float) sqrt(dz * dz + dy * dy + dx * dx);
			if (dist[i] > hi) {
				hi = dist[i];
			}
		}
	}
	for (i = 0; i < n; i++) {
		inv = 1.0f / hi;
		r = fcn_0050c710(list[i], 9, 1);
		dist[i] = r * 0.0125 + (1.0f - inv * dist[i]);
		if (best < dist[i]) {
			best = dist[i];
			bi = i;
		}
	}
	q = fcn_00502cd0(*(int*) (list[bi] + 0x5d), 1, 0, 0x120);
	*out1 = *(int*) (list[bi] + 1);
	*out2 = *(int*) (q + 2);
	return *(int*) (list[bi] + 0x61) != 0;
}
