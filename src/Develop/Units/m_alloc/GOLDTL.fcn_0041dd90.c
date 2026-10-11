// FUNCTION: GOLD 0x4225e0
// FUNCTION: GOLDTL 0x41dd90

#include "memtrack.h"

extern int g_6b6f64;
extern MemBlock* g_6b6f80;

int __cdecl fcn_0041dd90(int id)
{
	int i;
	MemBlock* t;

	if (id != 0) {
		t = g_6b6f80;
		for (i = 0; i < g_6b6f64; i++) {
			if ((int) t->ptr == id) {
				break;
			}
			t++;
		}
		return i != g_6b6f64;
	}
	return 1;
}
