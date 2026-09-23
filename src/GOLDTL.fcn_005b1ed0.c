// FUNCTION: GOLDTL 0x5b1ed0
// SIZE: 28

char* __cdecl fcn_005b1a80(int);

void __cdecl fcn_005b1ed0(char* a, int v)
{
	char* p;

	p = fcn_005b1a80(*(int*) (a + 1));
	if (p != 0) {
		*(int*) (p + 0x44) = v;
	}
}
