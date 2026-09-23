// FUNCTION: GOLDTL 0x5b3460
// SIZE: 48

char __cdecl fcn_005b3460(int a1)
{
	int n;

	n = *(int*) 0x775280;
	if (n < 0x80) {
		*(int*) (0x778b20 + n * 4) = a1;
		*(int*) 0x775280 = n + 1;
		return 1;
	}
	return 0;
}
