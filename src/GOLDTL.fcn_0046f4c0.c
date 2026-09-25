// FUNCTION: GOLDTL 0x46f4c0
// SIZE: 128
// A do-while (not a for loop) gives the reference's register roles.

#include <string.h>

typedef struct Slot046f4c0 {
	char pad0[0x2f4];
} Slot046f4c0;
// SIZE 0x2f4

extern Slot046f4c0* g_1015ea0;
extern Slot046f4c0** g_772540;

void __cdecl fcn_0046f4c0(int slot)
{
	Slot046f4c0* s;
	int i;
	int free;

	free = -1;
	i = 0x3ff;
	s = &g_1015ea0[slot];
	do {
		if (g_772540[i] == s) {
			if (free != -1) {
				g_772540[free] = g_772540[i];
				memmove(&g_772540[i], &g_772540[i + 1], 0xff8 - i * 4);
			}
			return;
		}
		if (g_772540[i] != 0 && free == -1) {
			free = i + 1;
		}
		i--;
	} while (i > 0);
}
