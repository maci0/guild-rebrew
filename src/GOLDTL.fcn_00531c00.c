// GLOBAL: GOLDTL 0x7e6068
extern char g_7e6068[];
// GLOBAL: GOLD 0x761fc8
extern char g_7e6068[];
// FUNCTION: GOLD 0x0052c4d0
// SIZE: 51
// FUNCTION: GOLDTL 0x531c00
// SIZE: 51

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
