// FUNCTION: GOLD 0x004b3a50
// FUNCTION: GOLDTL 0x4b3bc0

extern char g_10069a0[];

char* __cdecl fcn_004b3bc0(int* a1)
{
	int i;

	for (i = 0; i < 128; i++) {
		if (*(int*) ((int) g_10069a0 + i * 0x24) != 0 && *(int*) ((int) g_10069a0 + 4 + i * 0x24) == a1[1]) {
			return (char*) ((int) g_10069a0 + i * 0x24);
		}
	}
	return 0;
}
