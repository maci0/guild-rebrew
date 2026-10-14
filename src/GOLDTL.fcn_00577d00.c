#include "Develop/DieGildeAddOn/game/spiel.h"
// FUNCTION: GOLD 0x56f890
// FUNCTION: GOLDTL 0x00577d00

#include <math.h>
#pragma intrinsic(sqrt)

char* __cdecl fcn_005463a0(int, int, int);
char* __cdecl fcn_005462a0(void);


char* __cdecl fcn_00577d00(char* who, char* self, int skip)
{
	char* best_e;
	float best;
	char* q;
	char* m;
	char* e;
	char* r;
	float p[4];
	float dv[4];
	float d;
	float t;

	best_e = 0;
	best = 1e7f;
	q = *(char**) (self + 0x184);
	if (q == 0) {
		return 0;
	}
	m = *(char**) (q + 0x34);
	t = *(float*) (m + 0x4c);
	p[0] = t;
	t = *(float*) (m + 0x50);
	p[1] = t;
	t = *(float*) (m + 0x54);
	p[2] = t;
	fcn_005463a0(1, 0, 0x18);
	e = fcn_005463a0(1, 0, 0x18);
	while (e != 0) {
		if (*(int*) (e + 0x70) != -1 && *(int*) (e + 0x70) != -2 && skip != *(int*) (e + 4) && *(int*) (e + 0xc4) == *(int*) (who + 4)) {
			gm_ResolveEntityById((void**) (&r), 0, 0, *(int*) (e + 0xb4));
			if (r != 0) {
				m = *(char**) (r + 0x61);
				t = *(float*) (m + 0x4c);
				dv[0] = t;
				t = *(float*) (m + 0x50);
				dv[1] = t;
				t = *(float*) (m + 0x54);
				dv[2] = t;
				dv[0] -= p[0];
				dv[1] -= p[1];
				dv[2] -= p[2];
				d = (float) sqrt(dv[2] * dv[2] + dv[1] * dv[1] + dv[0] * dv[0]);
				if (best_e == 0) {
					best = d;
					best_e = e;
				} else if (best > d) {
					best = d;
					best_e = e;
				}
			}
		}
		e = fcn_005462a0();
	}
	return best_e;
}
