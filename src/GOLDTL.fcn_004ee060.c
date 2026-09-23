// GLOBAL: GOLDTL 0x772f90
extern char g_772f90[];
// GLOBAL: GOLD 0x6f0de0
extern char g_772f90[];
// FUNCTION: GOLD 0x004ec2d0
// SIZE: 32
// FUNCTION: GOLDTL 0x4ee060
// SIZE: 32

char* __cdecl fcn_004ee060(int i)
{
	if (i < 0 || i >= 3) {
		return 0;
	}
	return g_772f90 + i * 24;
}
