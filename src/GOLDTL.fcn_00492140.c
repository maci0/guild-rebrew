


extern unsigned char* g_90e094;

#include "Develop/DieGildeAddOn/game/spiel.h"
unsigned char __cdecl fcn_004f97a0(int a);
int __cdecl fcn_004f4830(int idx, void* dst);

int __cdecl fcn_00492140(char* e, int unused, int* out)
{
	int info[9];
	float m;
	float s;
	float x;
	float y;
	float z;
	float w;
	int cnt;
	int owned;
	int i;
	unsigned char* rec;

	s = fcn_00507f10(e, 2);
	m = (s - (fcn_004f97a0(2) + 1.0f) * 0.003968254f) * 0.023809524f;
	y = (float)((*(float*) (e + 0xf4) - 2.0) * *(float*) (e + 0xfc));
	w = (float)((*(float*) (e + 0x100) - 2.0) * *(float*) (e + 0x108));
	z = (float)((*(float*) (e + 0x10c) - 2.0) * *(float*) (e + 0x114));
	cnt = 0;
	owned = 0;
	rec = g_90e094;
	for (i = 0; i < 0x100; i++, rec += 0xa9) {
		if (rec[0] == 0x4b || rec[0] == 0x4c || rec[0] == 0x4d) {
			cnt++;
			if (e[2] != 5) {
				break;
			}
			if (*(unsigned short*) (rec + 0x27) == *(unsigned short*) e) {
				owned = 1;
				break;
			}
		}
	}
	if (cnt == 0) {
		return 0;
	}
	fcn_004f4830(8, info);
	if (e[2] == 5) {
		if (owned) {
			if (info[6] != 1) {
				return 0;
			}
			*out = 0;
			return 1;
		}
		if (info[6] != 0) {
			return 0;
		}
		*out = 1;
		return 1;
	}
	if (e[2] == 3) {
		x = m * 1.2f;
	} else {
		x = m * 0.8f;
	}
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
