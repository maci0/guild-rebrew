// FUNCTION: GOLD 0x004cd4c0
// SIZE: 60
// FUNCTION: GOLDTL 0x4ce040
// SIZE: 60

extern int g_772e8c;
extern int g_9ba9f4;
extern char g_9ba3a0[];

char* __cdecl fcn_004ce040(void)
{
	int n;
	int m;

	n = g_772e8c;
	m = g_9ba9f4;
	if (n == m) {
		return 0;
	}
	n++;
	g_772e8c = n;
	if (n == m) {
		return 0;
	}
	if (n == 0xf) {
		n = 0;
		g_772e8c = n;
	}
	return g_9ba3a0 + n * 108;
}
