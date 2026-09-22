// FUNCTION: GOLDTL 0x4e6ab0
// SIZE: 48

char* __cdecl fcn_004e6ab0(void)
{
	int a;
	int i;

	i = 0;
	for (a = 0x9a9660; a < 0x9afde0; a += 0x114) {
		if (*(int*) a == -1) {
			return (char*) (0x9a9660 + i * 0x114);
		}
		i++;
	}
	return 0;
}
