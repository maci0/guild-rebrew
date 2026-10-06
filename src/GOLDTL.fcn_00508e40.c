extern char g_7f4ca4[];
// FUNCTION: GOLDTL 0x508e40
// FUNCTION: GOLD 0x505df0

char* __cdecl fcn_00508e40(int a1)
{
	int i;
	int a;

	for (i = 0, a = (int) g_7f4ca4; a < (int) (g_7f4ca4 + 0x65400); a += 0x21c, i++) {
		if (*(unsigned short*) (a - 4) != 0xffff && *(int*) a == a1) {
			return (char*) ((int) (g_7f4ca4 - 4) + i * 540);
		}
	}
	return 0;
}
