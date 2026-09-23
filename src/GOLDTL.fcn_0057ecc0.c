// FUNCTION: GOLDTL 0x57ecc0
// SIZE: 40

int __cdecl fcn_0057ecc0(void)
{
	int* p;

	if (*(int*) 0x774a14 == 0) {
		return 1;
	}
	p = *(int**) 0x665f08;
	if (*(int*) ((char*) p + 0x3c) == 2 || *p == 5) {
		return 0;
	}
	return 1;
}
