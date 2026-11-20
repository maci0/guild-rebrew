void __cdecl fcn_00451500(int b, int c, float* m);
void __cdecl d3_MatrixToEulerAngles(float* m, float* v);
void __cdecl d3_SetObjectRotation(char* p, float* v);

/* ADDRESS: GOLDTL 0x004526f0 */
void __cdecl fcn_004526f0(char* a, int b, int c)
{
	float m[16];
	float v[3];

	if (a != 0) {
		fcn_00451500(b, c, m);
		d3_MatrixToEulerAngles(m, v);
		d3_SetObjectRotation(a + 0xe8, v);
	}
}
