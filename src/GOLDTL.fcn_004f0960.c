// FUNCTION: GOLD 0x4eeaa0
// SIZE: 96
// FUNCTION: GOLDTL 0x4f0960
// SIZE: 88

#include "client_types.h"
typedef Slot170_7731b8 Slot170;
// SIZE 0x170

extern Slot170_7731b8 g_7731b8[8];

int __cdecl fcn_004f0960(int id)
{
	int free;
	int i;
	int v;

	free = -1;
	if (id != -1) {
		for (i = 0; i < 8; i++) {
			v = g_7731b8[i].id;
			if (v == -1) {
				if (free == -1) {
					free = i;
				}
			} else if (v == id) {
				return 1;
			}
		}
		if (free >= -1) {
			g_7731b8[free].id = id;
			return 1;
		}
	}
	return 0;
}
