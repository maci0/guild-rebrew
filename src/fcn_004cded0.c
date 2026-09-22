// FUNCTION: GOLDTL 0x4cded0
// SIZE: 46

char* __cdecl fcn_004cded0(void)
{
	int i;
	int a;

	for (i = 0, a = 0x9baae0; a < 0x9bad98; a += 0x57, i++) {
		if (*(int*) a == 0) {
			return (char*) (0x9baae0 + i * 87);
		}
	}
	return 0;
}
