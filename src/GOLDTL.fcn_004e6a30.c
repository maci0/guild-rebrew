// GLOBAL: GOLDTL 0x9a9660
extern char g_9a9660[];
// GLOBAL: GOLD 0x925520
extern char g_9a9660[];
// FUNCTION: GOLD 0x004e50a0
// FUNCTION: GOLDTL 0x4e6a30

char* __cdecl fcn_004e6a30(int a1)
{
	int i;
	int a;

	for (i = 0, a = (int) g_9a9660; a < (int) g_9a9660 + 0x6780; a += 0x114, i++) {
		if (*(char*) (a + 0x30) != 0 && *(int*) a == a1) {
			return (char*) ((int) g_9a9660 + i * 276);
		}
	}
	return 0;
}
