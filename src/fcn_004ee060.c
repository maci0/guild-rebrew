// FUNCTION: GOLDTL 0x4ee060
// SIZE: 32

char* __cdecl fcn_004ee060(int i)
{
	if (i < 0 || i >= 3) {
		return 0;
	}
	return (char*) 0x772f90 + i * 24;
}
