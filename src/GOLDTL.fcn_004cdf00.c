// FUNCTION: GOLDTL 0x4cdf00
// SIZE: 58

char* __cdecl fcn_004cded0(void);

char* __cdecl fcn_004cdf00(int a1)
{
	int i;
	int a;

	if (a1 == 0) {
		return 0;
	}
	for (i = 0, a = 0x9baae0; a < 0x9bad98; a += 0x57, i++) {
		if (*(int*) a == a1) {
			return (char*) (0x9baae0 + i * 87);
		}
	}
	return fcn_004cded0();
}
