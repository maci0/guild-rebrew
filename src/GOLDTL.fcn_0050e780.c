// FUNCTION: GOLD 0x0050b2f0
// FUNCTION: GOLDTL 0x0050e780

#include "client_types.h"
typedef Rec34_7f3f00 Rec34;
// SIZE 0x34

extern Rec34_7f3f00 g_7f3f00[];
extern int g_85ab60;

int __cdecl fcn_0050e780(int i)
{
	int a;
	int b;
	int k;
	int n;
	int p;

	a = 0;
	b = 0;
	if (g_7f3f00[i].xc != 0xffff) {
		return g_7f3f00[i].xc;
	}
	if (g_7f3f00[i].x4 == 0) {
		return 0;
	}
	n = g_85ab60;
	for (k = 0; k < n; k++) {
		if (g_7f3f00[i].x4 == g_7f3f00[k].x0) {
			a = fcn_0050e780(k) + 1;
			break;
		}
	}
	p = g_7f3f00[i].x8;
	if (p == 0) {
		return a;
	}
	for (k = 0; k < n; k++) {
		if (p == g_7f3f00[k].x0) {
			b = fcn_0050e780(k) + 1;
			break;
		}
	}
	return a > b ? a : b;
}
