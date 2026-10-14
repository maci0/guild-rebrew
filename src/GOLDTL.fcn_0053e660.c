

// SIZE 0x10
struct vec4 {
	float x;
	float y;
	float z;
	float w;
};

char* __cdecl fcn_00445600(int, int, int, char*);
char* __cdecl fcn_00442910(int, struct vec4*, char*, char*);
void __cdecl fcn_00412f10(char*, char*, int);

char* __cdecl fcn_0053e660(float tx, float tz)
{
	struct vec4 v;
	char* p;
	char* q;
	char* r;

	v.x = 0.0f;
	v.y = 0.0f;
	v.z = 0.0f;
	v.w = 0.0f;
	p = fcn_00445600(0, 0x140, 0, "dummy_Kartentisch_LINKS_OBEN");
	q = fcn_00445600(0, 0x140, 0, "dummy_Kartentisch_RECHTS_UNTEN");
	if (p == 0 || q == 0) {
		return 0;
	}
	{
		double dx;
		double dz;
		double pz;

		dx = *(float*) (q + 0x4c) - *(float*) (p + 0x4c);
		dz = *(float*) (q + 0x54) - *(float*) (p + 0x54);
		v.x = 0.0f;
		v.y = 0.0f;
		v.z = 0.0f;
		v.w = 0.0f;
		v.x = *(float*) (p + 0x4c);
		v.y = *(float*) (p + 0x50);
		pz = *(float*) (p + 0x54);
		v.x += tx * (1.0f / 700.0f) * dx;
		v.z = tz * (1.0f / 750.0f) * dz + pz;
	}
	r = fcn_00442910(0, &v, p + 0x84, "sp_STADTTURM");
	r[0x215] |= 1;
	*(int*) (r + 0x220) = 4;
	r[0x216] = (r[0x216] & 0xfd) | 1;
	*(int*) (r + 0x224) = 1;
	fcn_00412f10(r, "sonstiges\\wimpel_STADTTURM.baf", 1);
	return r;
}
