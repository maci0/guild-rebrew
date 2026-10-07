/* GOLD twin of GOLDTL fcn_00455280: the flag byte is 0x210 and the bit is 0x80
 * (GOLDTL: 0x214, bit 0x20). */

// FUNCTION: GOLD 0x458940

// SIZE 0xc
typedef struct Vec3 {
	float x;
	float y;
	float z;
} Vec3;

void __cdecl fcn_00458800(char*, Vec3*, Vec3*);

void __cdecl fcn_00458940(char* o, char* ref, Vec3* v, Vec3* out)
{
	float t[4];

	if ((o[0x210] & 0x80) == 0 && ref != 0) {
		fcn_00458800(o, v, (Vec3*) t);
		out->x = t[0] * *(float*) (ref + 0x18c) + t[1] * *(float*) (ref + 0x19c) + t[2] * *(float*) (ref + 0x1ac);
		out->y = t[0] * *(float*) (ref + 0x190) + t[1] * *(float*) (ref + 0x1a0) + t[2] * *(float*) (ref + 0x1b0);
		out->z = t[0] * *(float*) (ref + 0x194) + t[1] * *(float*) (ref + 0x1a4) + t[2] * *(float*) (ref + 0x1b4);
	} else {
		fcn_00458800(o, v, out);
	}
}
