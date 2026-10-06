void __cdecl fcn_00455540(int, int, float*);

// FUNCTION: GOLDTL 0x4bdfb0

void __cdecl fcn_004bdfb0(float* ox, float* oy, int x, int y, char** ctx)
{
	float v[4];

	fcn_00455540(y, x, v);
	*ox = (v[0] - *(float*) (*ctx + 0x50)) / *(float*) (*ctx + 0x60);
	*oy = (v[2] - *(float*) (*ctx + 0x58)) / *(float*) (*ctx + 0x78);
}
