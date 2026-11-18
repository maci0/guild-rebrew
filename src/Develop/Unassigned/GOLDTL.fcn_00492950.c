extern char g_6641a4[];
extern char g_6641a4[];

/* ADDRESS: GOLD 0x00493380 */
/* ADDRESS: GOLDTL 0x00492950 */
int __cdecl fcn_00492950(char* p, int a2, int a3)
{
	int value;
	int e;

	if (a2 == *(int*) (p + 0xc)) {
		value = *(int*) (p + 0x28);
	} else if (a2 == *(int*) (p + 0x30)) {
		value = *(int*) (p + 0x4c);
	} else {
		return 0;
	}
	for (e = (int) g_6641a4; e < (int) g_6641a4 + 0x48; e += 8) {
		if (*(int*) (e - 4) == value && *(int*) e == a3) {
			return 1;
		}
	}
	return 0;
}
