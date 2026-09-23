// FUNCTION: GOLDTL 0x5b1b10
// SIZE: 31

char* __cdecl fcn_005b1b10(int a1)
{
	char* p;

	p = *(char**) 0x774a78;
	while (p != 0) {
		if (*(int*) p == a1) {
			return p + 0xc;
		}
		p = *(char**) (p + 0x48);
	}
	return 0;
}
