// FUNCTION: GOLD 0x004eaea0
// SIZE: 176
// FUNCTION: GOLDTL 0x004ecc20
// SIZE: 176

#include "g_772f90.h"

extern int g_772fe0;
extern Rec772fe4* g_772fe4;

unsigned short __cdecl fcn_0042e410(unsigned short n);
int __cdecl fcn_004ec9a0(int p);
int __cdecl fcn_004ec950(int p, int id);

Rec772fe4* __cdecl fcn_004ecc20(int p)
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
			if (!fcn_004ec950(p, g_772fe4[idx].key)) {
				return &g_772fe4[idx];
			}
			n--;
			idx = (idx + step) % g_772fe0;
		}
	}
	return 0;
}
