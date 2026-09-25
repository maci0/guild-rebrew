// FUNCTION: GOLD 0x005776b0
// SIZE: 93
// FUNCTION: GOLDTL 0x57fc80
// SIZE: 93

extern unsigned short* g_7746cc;
extern char* g_665f08;

int __cdecl fcn_0057fc80(void)
{
	unsigned short* p;
	unsigned short k;
	int v;
	int m;

	p = g_7746cc;
	if (p != 0) {
		k = *p;
		v = k;
		if (v >= 0x92 && v <= 0x97) {
			m = *(int*) (g_665f08 + 0x38);
			if (m == 0) {
				return k == 0x92 ? 0 : 3;
			}
			if (m == 1) {
				return k == 0x95 ? 1 : 4;
			}
			if (m == 2) {
				return m;
			}
		}
	}
	return -1;
}
