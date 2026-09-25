// FUNCTION: GOLD 0x0040cda0
// SIZE: 240
// FUNCTION: GOLDTL 0x0040dcd0
// SIZE: 240

extern char* g_6b7e98;
float __cdecl fcn_00444700(int h, char* pos);
void __cdecl fcn_00451720(float* out, char* base, float* a, float* b);
char* __cdecl fcn_0040c120(char* e, int kind, ...);
void __cdecl fcn_00425bf0(char* g, int h, const char* msg);

int __cdecl fcn_0040dcd0(char** a, char** b)
{
	float d;
	float v[3];
	float w[3];
	float u[3];
	char* e;

	if (*a == 0 || *b == 0) {
		fcn_00425bf0(g_6b7e98, *(int*) (g_6b7e98 + 0x118), "invalid object");
		return 1;
	}
	d = fcn_00444700(*(int*) (*a + 0x34), *(char**) (*b + 0x34) + 0x4c);
	v[0] = 0.0f;
	v[1] = d;
	v[2] = 0.0f;
	fcn_00451720(v, *(char**) (*a + 0x34) + 0x84, u, w);
	e = *a;
	v[0] += *(float*) (*(char**) (e + 0x34) + 0x84);
	v[1] += *(float*) (*(char**) (e + 0x34) + 0x88);
	v[2] += *(float*) (*(char**) (e + 0x34) + 0x8c);
	fcn_0040c120(e, 7, (int) (d * 57.29578f), 0);
	return 0;
}
