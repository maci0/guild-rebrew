// FUNCTION: GOLDTL 0x004ecc20
// SIZE: 176

typedef struct
{
	int a;
	int b;
	int c;
} V12;

extern int g_772fe0;
extern V12* g_772fe4;

unsigned short __cdecl fcn_0042e410(unsigned short n);
int __cdecl fcn_004ec9a0(int p);
int __cdecl fcn_004ec950(int p, int id);

V12* __cdecl fcn_004ecc20(int p)
{
	int step;
	int idx;
	int n;

	if (fcn_004ec9a0(p)) {
		step = fcn_0042e410((unsigned short) g_772fe0) + 1;
		while (step % g_772fe0 == 0) {
			step++;
		}
		idx = fcn_0042e410((unsigned short) g_772fe0);
		n = g_772fe0;
		while (n != 0) {
			if (!fcn_004ec950(p, g_772fe4[idx].a)) {
				return &g_772fe4[idx];
			}
			n--;
			idx = (idx + step) % g_772fe0;
		}
	}
	return 0;
}
