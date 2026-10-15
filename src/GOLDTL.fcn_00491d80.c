


#include "Develop/DieGildeAddOn/game/spiel.h"
unsigned char __cdecl fcn_004f97a0(int a);
int __cdecl fcn_004f4830(int idx, void* dst);

int __cdecl fcn_00491d80(char* e, int unused, int* out)
{
	int info[9];
	float m;
	float x;
	float y;
	float z;
	float w;
	int job;

	job = gm_MapEntityStatRange(*(unsigned char*) (e + 0x164));
	m = fcn_00507f10(e, 2);
	x = (m - (fcn_004f97a0(2) + 1.0f) * 0.003968254f) * 0.023809524f;
	y = (*(float*) (e + 0xf4) - 2.0) * *(float*) (e + 0xfc);
	w = (*(float*) (e + 0x100) - 2.0) * *(float*) (e + 0x108);
	z = (*(float*) (e + 0x10c) - 2.0) * *(float*) (e + 0x114);
	if (job == 11 || job == 12) {
		x *= 1.1f;
	}
	fcn_004f4830(0x18, info);
	if (x < 1.0f && info[6] == 0) {
		if (!(z > y)) {
			return 0;
		}
		*out = 1;
		return 1;
	}
	if (!(x > 1.0) || info[6] != 1 || !(w > y)) {
		return 0;
	}
	*out = 0;
	return info[6];
}
