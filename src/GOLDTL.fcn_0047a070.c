// FUNCTION: GOLDTL 0x47a070
// SIZE: 32

char* __cdecl fcn_0047a070(char* p, int i)
{
	if (p == 0) {
		return 0;
	}
	return p + *(int*) (p + i * 4 + 0x45);
}
