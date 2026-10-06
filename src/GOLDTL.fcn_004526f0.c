void __cdecl fcn_00451500(int b, int c, float* m);
void __cdecl fcn_004519d0(float* m, float* v);
void __cdecl fcn_00438cb0(char* p, float* v);

// FUNCTION: GOLD 0x00455a30
// FUNCTION: GOLDTL 0x4526f0
void __cdecl fcn_004526f0(char* a, int b, int c)
{
	float m[16];
	float v[3];

	if (a != 0) {
		fcn_00451500(b, c, m);
		fcn_004519d0(m, v);
		fcn_00438cb0(a + 0xe8, v);
	}
}
