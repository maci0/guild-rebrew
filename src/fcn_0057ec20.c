// FUNCTION: GOLDTL 0x57ec20
// SIZE: 73

int __cdecl fcn_0057ec20(int a1)
{
	int* p;

	if (*(int*) 0x774a14 == 0) {
		return 1;
	}
	p = *(int**) 0x665f08;
	if (*(int*) ((char*) p + 0x3c) == 2 || *p == 5) {
		return 0;
	}
	p = (int*) p[6];
	if (p == 0) {
		return 1;
	}
	if (*(int*) 0x6b7fc0 != 0) {
		return 0;
	}
	return (*(int*) ((char*) p + 0x68) & a1) != 0;
}
