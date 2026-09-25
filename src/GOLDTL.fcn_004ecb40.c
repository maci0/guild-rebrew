// FUNCTION: GOLD 0x004eadc0
// SIZE: 150
// FUNCTION: GOLDTL 0x004ecb40
// SIZE: 150

typedef struct
{
	int a;
	int b;
	int c;
} V12;
// SIZE 0xc

extern int g_772fd8;
extern V12* g_772fdc;

unsigned short __cdecl fcn_0042e410(unsigned short n);

void __cdecl fcn_004ecb40(void)
{
	int n;
	int i;
	int a;
	int b;
	V12 tmp;

	n = g_772fd8 * 2;
	for (i = 0; i < n; i++) {
		a = fcn_0042e410((unsigned short) g_772fd8);
		b = fcn_0042e410((unsigned short) g_772fd8);
		if (a != b) {
			tmp = g_772fdc[a];
			g_772fdc[a] = g_772fdc[b];
			g_772fdc[b] = tmp;
		}
	}
}
