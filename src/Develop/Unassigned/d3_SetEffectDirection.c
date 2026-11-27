void __cdecl d3_BuildBasisMatrixFromDir(int b, int c, float* m);
void __cdecl d3_MatrixToEulerAngles(float* m, float* v);
void __cdecl d3_SetObjectRotation(char* p, float* v);

/* ADDRESS: GOLDTL 0x004526f0 */
void __cdecl d3_SetEffectDirection(char* effect, int dir, int angle)
{
	float m[16];
	float v[3];

	if (effect != 0) {
		d3_BuildBasisMatrixFromDir(dir, angle, m);
		d3_MatrixToEulerAngles(m, v);
		d3_SetObjectRotation(effect + 0xe8, v);
	}
}
