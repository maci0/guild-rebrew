// FUNCTION: GOLDTL 0x455610

// SIZE 0xc
typedef struct Vec3 {
	float x;
	float y;
	float z;
} Vec3;

void __cdecl fcn_00455540(char*, Vec3*, Vec3*);

void __cdecl fcn_00455610(char* o, char* ref, Vec3* v, Vec3* out)
{
	float t[4];

	if ((o[0x214] & 0x20) == 0 && ref != 0) {
		fcn_00455540(o, v, (Vec3*) t);
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
		fcn_00455540(o, v, out);
	}
}
