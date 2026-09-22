// FUNCTION: GOLDTL 0x420650
// SIZE: 49

char* __cdecl fcn_00420650(void)
{
	int i;
	int a;

	for (i = 0, a = 0x6b72b4; a < 0x6b7e44; a += 0x128, i++) {
		if (*(char*) (a + 2) == 0 && *(char*) a != 0) {
			return (char*) (0x6b71b0 + i * 296);
		}
	}
	return 0;
}
