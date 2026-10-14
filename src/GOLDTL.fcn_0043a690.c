

extern int g_67a370;

void __cdecl fcn_004379a0(int, int, int, void*, void*);
char __cdecl fcn_0043a5d0(char*, float*);

void __cdecl fcn_0043a690(float* mn, float* mx)
{
	float bb[8];

	bb[0] = 1.0e10f;
	bb[1] = 1.0e10f;
	bb[2] = 1.0e10f;
	bb[4] = -1.0e10f;
	bb[5] = -1.0e10f;
	bb[6] = -1.0e10f;
	fcn_004379a0(g_67a370, 0, 0x40, fcn_0043a5d0, bb);
	mn[0] = bb[0];
	mn[1] = bb[1];
	mn[2] = bb[2];
	mx[0] = bb[4];
	mx[1] = bb[5];
	mx[2] = bb[6];
}
