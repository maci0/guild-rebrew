#include "Develop/Units/d2.v1/d2_gui.h"
extern GuiEnt** g_006ed964;
int __cdecl d2_FindFreeElementSlot(void);

/* ADDRESS: GOLD 0x0046c9e0 */
int __cdecl fcn_0046c9e0(void)
{
	int index;
	int i;
	GuiEnt* element;

	index = d2_FindFreeElementSlot();
	if (index == -1) {
		return index;
	}
	element = &g_00f8f080[index];
	for (i = 0x2ff; i >= 0; i--) {
		if (g_006ed964[i] != 0) {
			i++;
			break;
		}
	}
	if (i < 0) {
		i = 0;
	}
	g_006ed964[i] = element;
	if (index > *(int*) 0x6ed94c) {
		*(int*) 0x6ed94c = index;
	}
	*(int*) ((char*) &g_00f8f080[index] + 4) = 1;
	return index;
}
