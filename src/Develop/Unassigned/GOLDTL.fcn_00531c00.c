extern char g_7e6068[];
extern char g_7e6068[];

/* ADDRESS: GOLD 0x0052c4d0 */
/* ADDRESS: GOLDTL 0x00531c00 */
void __cdecl fcn_00531c00(int a1)
{
	int i;
	int a;

	for (i = 0, a = (int) g_7e6068; a < (int) g_7e6068 + 0x4300; a += 0x10c, i++) {
		if (*(int*) a == a1) {
			*(int*) ((int) g_7e6068 + i * 268) = 0;
			return;
		}
	}
}
