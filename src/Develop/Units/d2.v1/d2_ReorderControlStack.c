#include "d2_capacity.h"
#include <string.h>

#include "Develop/Units/d2.v1/d2_gui.h"

typedef struct D2_STACK_ELEMENT_SLOT {
	char pad0[0x2f4];
} D2_STACK_ELEMENT_SLOT;

extern void** d2_ZOrderStack;

#if defined(REBREW_GOLD)

extern GuiEnt** g_006ed964; /* 0x006ed964 */

/* ADDRESS: GOLD 0x00472f40 */
void __cdecl d2_ReorderControlStack(int slot)
{
	GuiEnt* s;
	int i;
	int free;

	free = -1;
	i = 0x2ff;
	s = &g_00f8f080[slot];
	do {
		if (g_006ed964[i] == s) {
			if (free != -1) {
				g_006ed964[free] = g_006ed964[i];
				memmove(&g_006ed964[i], &g_006ed964[i + 1], 0xbf8 - i * 4);
			}
			return;
		}
		if (g_006ed964[i] != 0 && free == -1) {
			free = i + 1;
		}
		i--;
	} while (i > 0);
}

#else

/* A do-while (not a for loop) gives the reference's register roles. */
/* ADDRESS: GOLDTL 0x0046f4c0 */
/* ADDRESS: GOLDDE 0x00462a20 */
void __cdecl d2_ReorderControlStack(int slot)
{
	D2_STACK_ELEMENT_SLOT* s;
	int i;
	int free;

	free = -1;
	i = d2_ELEMENT_CAPACITY - 1;
	s = (D2_STACK_ELEMENT_SLOT*)&((D2_CONTROL_TL*)d2_Controls)[slot];
	do {
		if (((D2_STACK_ELEMENT_SLOT**)d2_ZOrderStack)[i] == s) {
			if (free != -1) {
				((D2_STACK_ELEMENT_SLOT**)d2_ZOrderStack)[free] = ((D2_STACK_ELEMENT_SLOT**)d2_ZOrderStack)[i];
				memmove(&((D2_STACK_ELEMENT_SLOT**)d2_ZOrderStack)[i], &((D2_STACK_ELEMENT_SLOT**)d2_ZOrderStack)[i + 1], (d2_ELEMENT_CAPACITY - 2) * 4 - i * 4);
			}
			return;
		}
		if (((D2_STACK_ELEMENT_SLOT**)d2_ZOrderStack)[i] != 0 && free == -1) {
			free = i + 1;
		}
		i--;
	} while (i > 0);
}

#endif
