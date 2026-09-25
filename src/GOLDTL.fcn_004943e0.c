int __cdecl fcn_00508eb0(unsigned short id, int a2);
float __cdecl fcn_0050f980(int a, int b, int c);
float __cdecl gm_RandomFloat01(void);

// FUNCTION: GOLD 0x00494a20
// SIZE: 139
// FUNCTION: GOLDTL 0x4943e0
// SIZE: 139
int __cdecl fcn_004943e0(unsigned short* a, unsigned short* b)
{
	int x;
	float f;

	if (*(int*) ((char*) a + 4) == *(int*) ((char*) b + 0x210)) {
		return 0;
	}
	x = fcn_00508eb0(*a, 0);
	f = (fcn_00508eb0(*b, 0) - x) * 2.5f;
	f = fcn_0050f980(*a, *b, 1) + f;
	if (gm_RandomFloat01() * 75.0f > f) {
		return 0;
	}
	return 1;
}
