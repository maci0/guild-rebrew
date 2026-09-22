// FUNCTION: GOLDTL 0x4b3bc0
// SIZE: 58

char* __cdecl fcn_004b3bc0(int* a1)
{
	int i;

	for (i = 0; i < 128; i++) {
		if (*(int*) (0x10069a0 + i * 0x24) != 0 && *(int*) (0x10069a4 + i * 0x24) == a1[1]) {
			return (char*) (0x10069a0 + i * 0x24);
		}
	}
	return 0;
}
