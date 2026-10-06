// GLOBAL: GOLDTL 0x68b400
extern char g_68b400[];
// GLOBAL: GOLD 0x60c7a0
extern char g_68b400[];
// FUNCTION: GOLD 0x004cd9d0
// FUNCTION: GOLDTL 0x4ce590

int __cdecl fcn_004ce590(int a1)
{
	int i;
	int a;

	for (i = 0, a = (int) g_68b400; a < (int) g_68b400 + 0x398; a += 0x5c, i++) {
		if (*(int*) a == a1) {
			return (int) ((int) g_68b400 + i * 92);
		}
	}
	return 0;
}
