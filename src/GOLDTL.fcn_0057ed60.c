// FUNCTION: GOLDTL 0x0057ed60
// SIZE: 131

extern char* g_868050;
extern short* g_7746cc;

int __cdecl fcn_0057ed60(int* a)
{
	if (a[0] == 0x19 && a[1] != 0) {
		if (g_868050[*(unsigned char*) a[1] * 589] == 0xf && a[3] == 0x10e) {
			return 1;
		}
		return 0;
	}
	if (a[0] == 0x1a && a[1] != 0) {
		if (g_868050[*(unsigned char*) a[1] * 589] == 0xf && *g_7746cc == 0x10e) {
			return 0;
		}
		return 1;
	}
	return a[0] != 0x1b;
}
