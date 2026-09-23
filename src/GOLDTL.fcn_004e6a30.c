// FUNCTION: GOLDTL 0x4e6a30
// SIZE: 64

char* __cdecl fcn_004e6a30(int a1)
{
	int i;
	int a;

	for (i = 0, a = 0x9a9660; a < 0x9afde0; a += 0x114, i++) {
		if (*(char*) (a + 0x30) != 0 && *(int*) a == a1) {
			return (char*) (0x9a9660 + i * 276);
		}
	}
	return 0;
}
