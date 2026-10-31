

#include "Develop/DieGildeAddOn/game/spiel.h"
unsigned char __cdecl fcn_004f97a0(int a);
int __cdecl fcn_004f4830(int idx, void* dst);

int __cdecl fcn_004908a0(char* e, int unused, int* out)
{
	int info[9];
	float m;
	float t;
	float y;
	float z;
	float w;
	int job;

	job = gm_MapEntityStatRange(*(unsigned char*) (e + 0x164));
	t = gm_GetEntitySkill(e, 4);
	m = (t - (fcn_004f97a0(4) + 1.0f) * 0.003968254f) * 0.023809524f;
	y = (float)((*(float*) (e + 0xf4) - 2.0) * *(float*) (e + 0xfc));
	w = (float)((*(float*) (e + 0x100) - 2.0) * *(float*) (e + 0x108));
	z = (float)((*(float*) (e + 0x10c) - 2.0) * *(float*) (e + 0x114));
	if (job == 7) {
		m = m * 1.1f;
	} else if (job == 11 || job == 12) {
		m = m * 0.9f;
	}
	fcn_004f4830(3, info);
	if (m < 1.0f && info[6] == 0) {
		if (!(z > y)) {
			return 0;
		}
		*out = 1;
		return 1;
	}
	if (!(m > 1.0) || info[6] != 1 || !(w > y)) {
		return 0;
	}
	*out = 0;
	return info[6];
}
