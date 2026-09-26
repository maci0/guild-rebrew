// FUNCTION: GOLD 0x00589d70
// SIZE: 142
// FUNCTION: GOLDTL 0x005922e0
// SIZE: 142

// SIZE 0xc
#include "client_types.h"
typedef Slot_779d00 Slot;

extern Slot_779d00 g_779d00[];

unsigned int __cdecl fcn_00430910(void*, int, int, int);

int __cdecl fcn_005922e0(int fh)
{
	int n;
	int i;

	n = 0xb;
	if (fcn_00430910(&n, 4, 1, fh) <= 0) {
		return 0;
	}
	for (i = 0; i < n; i++) {
		if (fcn_00430910(&g_779d00[i].a, 1, 1, fh) <= 0) {
			return 0;
		}
		if (fcn_00430910(&g_779d00[i].b, 4, 1, fh) <= 0) {
			return 0;
		}
		if (fcn_00430910(&g_779d00[i].c, 4, 1, fh) <= 0) {
			return 0;
		}
	}
	return 1;
}
