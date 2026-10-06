// FUNCTION: GOLD 0x004e5120
// FUNCTION: GOLDTL 0x4e6ab0

extern char g_9a9660[];

char* __cdecl fcn_004e6ab0(void)
{
	int a;
	int i;

	i = 0;
	for (a = (int) g_9a9660; a < (int) g_9a9660 + 0x6780; a += 0x114) {
		if (*(int*) a == -1) {
			return (char*) ((int) g_9a9660 + i * 0x114);
		}
		i++;
	}
	return 0;
}
