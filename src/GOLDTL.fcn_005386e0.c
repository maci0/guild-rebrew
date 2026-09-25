// FUNCTION: GOLDTL 0x005386e0
// SIZE: 32

__declspec(dllimport) int __stdcall SystemParametersInfoA(unsigned int, unsigned int, void*, unsigned int);

int __cdecl fcn_005386e0(void)
{
	int v;

	v = 0;
	SystemParametersInfoA(0x10, 0, &v, 0);
	return v;
}
