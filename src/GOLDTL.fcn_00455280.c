// FUNCTION: GOLDTL 0x455280
// SIZE: 197

// SIZE 0xc
typedef struct Vec3 {
	float x;
	float y;
	float z;
} Vec3;

void __cdecl fcn_00455140(char*, Vec3*, Vec3*);

void __cdecl fcn_00455280(char* o, char* ref, Vec3* v, Vec3* out)
{
	float t[4];

	if ((o[0x214] & 0x20) == 0 && ref != 0) {
		fcn_00455140(o, v, (Vec3*) t);
		out->x = t[0] * *(float*) (ref + 0x18c) + t[1] * *(float*) (ref + 0x19c) + t[2] * *(float*) (ref + 0x1ac);
		out->y = t[0] * *(float*) (ref + 0x190) + t[1] * *(float*) (ref + 0x1a0) + t[2] * *(float*) (ref + 0x1b0);
		out->z = t[0] * *(float*) (ref + 0x194) + t[1] * *(float*) (ref + 0x1a4) + t[2] * *(float*) (ref + 0x1b4);
	} else {
		fcn_00455140(o, v, out);
	}
}
