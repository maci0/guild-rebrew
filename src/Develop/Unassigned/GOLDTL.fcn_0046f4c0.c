
// A do-while (not a for loop) gives the reference's register roles.

#include <string.h>

typedef struct D2_STACK_ELEMENT_SLOT {
	char pad0[0x2f4];
} D2_STACK_ELEMENT_SLOT;
// SIZE 0x2f4

#include "Develop/Units/d2.v1/d2_gui.h"
extern void** g_772540;

void __cdecl d2_ReorderControlStack(int slot)
{
	D2_STACK_ELEMENT_SLOT* s;
	int i;
	int free;

	free = -1;
	i = 0x3ff;
	s = (D2_STACK_ELEMENT_SLOT*)&((D2_CONTROL_TL*)g_1015ea0)[slot];
	do {
		if (((D2_STACK_ELEMENT_SLOT**)g_772540)[i] == s) {
			if (free != -1) {
				((D2_STACK_ELEMENT_SLOT**)g_772540)[free] = ((D2_STACK_ELEMENT_SLOT**)g_772540)[i];
				memmove(&((D2_STACK_ELEMENT_SLOT**)g_772540)[i], &((D2_STACK_ELEMENT_SLOT**)g_772540)[i + 1], 0xff8 - i * 4);
			}
			return;
		}
		if (((D2_STACK_ELEMENT_SLOT**)g_772540)[i] != 0 && free == -1) {
			free = i + 1;
		}
		i--;
	} while (i > 0);
}
