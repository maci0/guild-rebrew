

#include "Develop/Units/d3/client_scene_transform.h"

void __cdecl d3_TransformWorldPointToRef(char* node, char* ref, float* point, float* out)
{
	float t[4];

	if ((node[0x214] & 0x20) == 0 && ref != 0) {
		d3_TransformToObjectSpace(node, point, t);
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
		d3_TransformToObjectSpace(node, point, out);
	}
}
