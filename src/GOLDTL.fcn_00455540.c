// FUNCTION: GOLDTL 0x455540
// SIZE: 194

// SIZE 0xc
typedef struct Vec3 {
	float x;
	float y;
	float z;
} Vec3;

void __cdecl fcn_00455350(char*, Vec3*, Vec3*);

void __cdecl fcn_00455540(char* o, Vec3* v, Vec3* out)
{
	float t[4];
	float a;
	float b;
	float c;

	a = v->x + *(float*) (o + 0x6c);
	b = v->y + *(float*) (o + 0x70);
	c = v->z + *(float*) (o + 0x74);
	t[0] = a * *(float*) (o + 0x18c) + b * *(float*) (o + 0x19c) + c * *(float*) (o + 0x1ac);
	t[1] = a * *(float*) (o + 0x190) + b * *(float*) (o + 0x1a0) + c * *(float*) (o + 0x1b0);
	t[2] = a * *(float*) (o + 0x194) + b * *(float*) (o + 0x1a4) + c * *(float*) (o + 0x1b4);
	t[0] -= *(float*) (o + 0x6c);
	t[1] -= *(float*) (o + 0x70);
	t[2] -= *(float*) (o + 0x74);
	t[0] += *(float*) (o + 0x4c);
	t[1] += *(float*) (o + 0x50);
	t[2] += *(float*) (o + 0x54);
	fcn_00455350(o, (Vec3*) t, out);
}
