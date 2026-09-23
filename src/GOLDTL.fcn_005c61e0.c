// FUNCTION: GOLDTL 0x5c61e0
// SIZE: 58

char* __cdecl fcn_005c61e0(int a1)
{
	int n;
	int v;

	v = *(int*) 0x6abb08;
	n = 0;
	while (v != 0) {
		if (v == a1) {
			return (char*) (0x6abb08 + n * 0x1c);
		}
		n++;
		v = *(int*) (0x6abb08 + n * 0x1c);
	}
	return 0;
}
