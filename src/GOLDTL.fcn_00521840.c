// FUNCTION: GOLD 0x51c8a0
// FUNCTION: GOLDTL 0x00521840

// SIZE 0x188
#include "client_types.h"
typedef Tabs_7e43a8 Tabs;

extern int g_7e4530;
extern Tabs_7e43a8 g_7e43a8;

unsigned int __cdecl fcn_00430910(void* p, int size, int n, int f);
int __cdecl fcn_005e8c00(int f);
int __cdecl fcn_004ef2e0(int f);

int __cdecl fcn_00521840(int f)
{
	int i;

	if (fcn_00430910(&g_7e4530, 4, 1, f) <= 0) {
		return 0;
	}
	for (i = 0; i < 24; i++) {
		if (fcn_00430910(&g_7e43a8.a[i], 4, 1, f) <= 0) {
			return 0;
		}
		if (fcn_00430910(&g_7e43a8.b[i], 4, 1, f) <= 0) {
			return 0;
		}
		if (fcn_00430910(&g_7e43a8.c[i], 4, 1, f) <= 0) {
			return 0;
		}
		if (fcn_00430910(&g_7e43a8.d[i], 4, 1, f) <= 0) {
			return 0;
		}
	}
	if (fcn_005e8c00(f) == 0) {
		return 0;
	}
	if (fcn_004ef2e0(f) == 0) {
		return 0;
	}
	return 1;
}
