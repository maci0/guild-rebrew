// FUNCTION: GOLD 0x00491e70
// FUNCTION: GOLDTL 0x491440

#include "Develop/DieGildeAddOn/game/spiel.h"
int __cdecl fcn_004f4830(int idx, void* dst);

int __cdecl fcn_00491440(char* e, int unused, int* out)
{
	int info[9];
	double a;
	double b;
	float m;
	float x;
	float y;
	float z;
	int job;

	job = gm_MapEntityStatRange(*(unsigned char*) (e + 0x164));
	a = *(float*) (e + 0xd0) - 2.0;
	b = *(float*) (e + 0xdc) - 2.0;
	m = a > b ? a : b;
	y = (*(float*) (e + 0xf4) - 2.0) * *(float*) (e + 0xfc);
	z = (*(float*) (e + 0x10c) - 2.0) * *(float*) (e + 0x114);
	if (job == 11 || job == 12) {
		x = m * 1.2f;
	} else if (job == 7) {
		x = m * 0.8f;
	} else {
		x = m * 1.1f;
	}
	fcn_004f4830(0x10, info);
	if (x < 0.5f && info[6] == 0) {
		if (!(y > z)) {
			return 0;
		}
		*out = 1;
		return 1;
	}
	if (!(x > 0.5) || info[6] != 1 || !(z > y)) {
		return 0;
	}
	*out = 0;
	return info[6];
}
