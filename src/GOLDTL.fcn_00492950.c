/* ADDRESS: GOLDTL 0x006641a4 */
extern char g_6641a4[];
/* ADDRESS: GOLD 0x005ecf1c */
extern char g_6641a4[];
/* ADDRESS: GOLD 0x00493380 */
/* ADDRESS: GOLDTL 0x00492950 */

int __cdecl fcn_00492950(char* p, int a2, int a3)
{
	int v;
	int e;

	if (a2 == *(int*) (p + 0xc)) {
		v = *(int*) (p + 0x28);
	} else if (a2 == *(int*) (p + 0x30)) {
		v = *(int*) (p + 0x4c);
	} else {
		return 0;
	}
	for (e = (int) g_6641a4; e < (int) g_6641a4 + 0x48; e += 8) {
		if (*(int*) (e - 4) == v && *(int*) e == a3) {
			return 1;
		}
	}
	return 0;
}
