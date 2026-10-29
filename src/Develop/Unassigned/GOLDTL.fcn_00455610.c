

#include "client_scene_transform.h"

void __cdecl fcn_00455610(char* o, char* ref, float* v, float* out)
{
	float t[4];

	if ((o[0x214] & 0x20) == 0 && ref != 0) {
		fcn_00455540(o, v, t);
		t[0] -= *(float*) (ref + 0x4c);
		t[1] -= *(float*) (ref + 0x50);
		t[2] -= *(float*) (ref + 0x54);
		t[0] -= *(float*) (ref + 0x78);
		t[1] -= *(float*) (ref + 0x7c);
		t[2] -= *(float*) (ref + 0x80);
		out[0] = t[0] * *(float*) (ref + 0x18c) + t[1] * *(float*) (ref + 0x19c) + t[2] * *(float*) (ref + 0x1ac);
		out[1] = t[0] * *(float*) (ref + 0x190) + t[1] * *(float*) (ref + 0x1a0) + t[2] * *(float*) (ref + 0x1b0);
		out[2] = t[0] * *(float*) (ref + 0x194) + t[1] * *(float*) (ref + 0x1a4) + t[2] * *(float*) (ref + 0x1b4);
	} else {
		fcn_00455540(o, v, out);
	}
}
