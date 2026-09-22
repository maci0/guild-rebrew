// FUNCTION: GOLDTL 0x4be320
// SIZE: 27

void __cdecl fcn_004be320(char* p, int a2)
{
	int i;

	i = 0;
	while (p != 0 && a2 != i) {
		p = *(char**) (p + 0x3c);
		i++;
	}
}
