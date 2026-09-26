typedef struct Slot {
	char pad0[0x20];
	int type;
	char pad24[0x88 - 0x24];
	int result;
	char pad8c[0x2f4 - 0x8c];
} Slot;
// SIZE 0x2f4

#include "client_types.h"
typedef Anim_100e7a0 Anim;
// SIZE 0x14

extern char* g_1015ea0;
extern Anim_100e7a0 g_100e7a0[0x30];

// FUNCTION: GOLDTL 0x473030
// SIZE: 131
void __cdecl fcn_00473030(int slot, char mode)
{
	Slot* s;

	if (slot > 0x400) {
		return;
	}
	s = &((Slot*)g_1015ea0)[slot];
	if (s->type != 4) {
		return;
	}
	if (mode == 0) {
		g_100e7a0[s->result].frame = 0;
		g_100e7a0[s->result].running = 0;
	} else if (mode == 1) {
		g_100e7a0[s->result].frame = g_100e7a0[s->result].seq[0x16] - 1;
		g_100e7a0[s->result].running = 1;
	}
}
