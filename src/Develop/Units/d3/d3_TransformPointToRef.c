

// SIZE 0xc
typedef struct Vec3 {
	float x;
	float y;
	float z;
} Vec3;

void __cdecl d3_TransformPoint(char*, Vec3*, Vec3*);

void __cdecl d3_TransformPointToRef(char* node, char* ref, Vec3* point, Vec3* out)
{
	float t[4];

	if ((node[0x214] & 0x20) == 0 && ref != 0) {
		d3_TransformPoint(node, point, (Vec3*) t);
		t[0] -= *(float*) (ref + 0x4c);
		t[1] -= *(float*) (ref + 0x50);
		t[2] -= *(float*) (ref + 0x54);
		t[0] -= *(float*) (ref + 0x78);
		t[1] -= *(float*) (ref + 0x7c);
		t[2] -= *(float*) (ref + 0x80);
		out->x = t[0] * *(float*) (ref + 0x18c) + t[1] * *(float*) (ref + 0x19c) + t[2] * *(float*) (ref + 0x1ac);
		out->y = t[0] * *(float*) (ref + 0x190) + t[1] * *(float*) (ref + 0x1a0) + t[2] * *(float*) (ref + 0x1b0);
		out->z = t[0] * *(float*) (ref + 0x194) + t[1] * *(float*) (ref + 0x1a4) + t[2] * *(float*) (ref + 0x1b4);
	} else {
		d3_TransformPoint(node, point, out);
	}
}
