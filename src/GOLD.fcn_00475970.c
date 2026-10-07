// FUNCTION: GOLD 0x00475970

#include "gold_gui.h"

extern GuiEnt* g_00f8f080; /* 0x00f8f080 */

int __cdecl fcn_00475970(int slot)
{
	GuiEnt* s;
	char* d;

	s = &g_00f8f080[slot];
	if (s->kind == 0x41) {
		d = s->data;
		if (*(int*) (d + 0x28) & 0x10) {
			return *(int*) (d + 0x14c);
		}
		if (*(int*) (d + 0x28) & 1) {
			return (int) (d + 0x2c);
		}
		if (*(int*) (d + 0x28) & 2) {
			return *(int*) (d + 0x12c);
		}
	}
	if (s->dirty) {
		return s->f28;
	}
	if (s->kind == 0x45) {
		return (int) s->buf;
	}
	return -1;
}
