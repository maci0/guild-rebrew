


#include "Develop/DieGildeAddOn/game/spiel.h"
float __cdecl fcn_00507f10(char* e, int k);
unsigned char __cdecl fcn_004f97a0(int a);
int __cdecl fcn_004f4830(int idx, void* dst);

int __cdecl fcn_00491790(char* e, int unused, int* out)
{
	int info[9];
	float m;
	float x;
	float y;
	float z;
	int job;

	job = gm_MapEntityStatRange(*(unsigned char*) (e + 0x164));
	m = fcn_00507f10(e, 4);
	m = (m - (fcn_004f97a0(4) + 1.0f) * 0.003968254f) * 0.023809524f;
	y = (*(float*) (e + 0xf4) - 2.0) * *(float*) (e + 0xfc);
	z = (*(float*) (e + 0x10c) - 2.0) * *(float*) (e + 0x114);
	x = m * 0.8f;
	fcn_004f4830(0x13, info);
	if (x < 1.0f && info[6] == 0) {
		if (!(y > z)) {
			return 0;
		}
		*out = 1;
		return 1;
	}
	if (!(x > 1.0) || info[6] != 1 || !(z > y)) {
		return 0;
	}
	*out = 0;
	return info[6];
}
