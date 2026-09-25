// GLOBAL: GOLDTL 0x680bd0
extern char g_680bd0[];
// GLOBAL: GOLD 0x601f68
extern char g_680bd0[];
// FUNCTION: GOLD 0x004b3ae0
// SIZE: 46
// FUNCTION: GOLDTL 0x4b3c50
// SIZE: 46

char* __cdecl fcn_004b3c50(int a1)
{
	int i;
	int p;

	for (i = 0, p = (int) g_680bd0; p < (int) g_680bd0 + 0x540; p += 0x1c, i++) {
		if (*(int*) p == a1) {
			return (char*) ((int) g_680bd0 + i * 0x1c);
		}
	}
	return 0;
}
