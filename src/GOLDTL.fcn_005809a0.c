// FUNCTION: GOLDTL 0x5809a0
// SIZE: 44

int __cdecl fcn_005809a0(int a1)
{
	int* p;

	if (*(int*) 0x774a14 == 0) {
		return -4;
	}
	p = *(int**) 0x665f08;
	*(int*) ((char*) p + 0x1c) = a1;
	*(int*) ((char*) *(int**) 0x665f08 + 0x20) = -1;
	return 0;
}
