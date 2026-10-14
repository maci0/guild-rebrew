

float* __stdcall fcn_005eb970(float*, float*, float*);

void __cdecl fcn_00455700(char* o, char flag, float* m, float* out)
{
	float tmp[16];
	char* parent;

	parent = *(char**) (o + 0x1fc);
	if (flag != 0) {
		*(float*) (o + 0x1bc) = 0.0f;
		*(float*) (o + 0x1c0) = 0.0f;
		*(float*) (o + 0x1c4) = 0.0f;
	} else {
		m[12] += *(float*) (o + 0x6c);
		m[13] += *(float*) (o + 0x70);
		m[14] += *(float*) (o + 0x74);
		*(float*) (o + 0x1bc) = *(float*) (o + 0x4c) - *(float*) (o + 0x6c) + *(float*) (o + 0x78);
		*(float*) (o + 0x1c0) = *(float*) (o + 0x50) - *(float*) (o + 0x70) + *(float*) (o + 0x7c);
		*(float*) (o + 0x1c4) = *(float*) (o + 0x54) - *(float*) (o + 0x74) + *(float*) (o + 0x80);
	}
	if (parent != 0) {
		fcn_005eb970(tmp, m, (float*) (o + 0x18c));
		fcn_00455700(parent, flag, tmp, out);
	} else {
		fcn_005eb970(out, m, (float*) (o + 0x18c));
	}
}
