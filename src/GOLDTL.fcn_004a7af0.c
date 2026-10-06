#include "client_types.h"
typedef slot_1007ce8 fcn_004a7af0_slot;
// SIZE 0x10

typedef struct {
	char pad0[0x8];
	int slot[7];
	int last;
} fcn_004a7af0_obj;

extern slot_1007ce8 g_1007ce8[];

int __cdecl fcn_004a7880(int);

// FUNCTION: GOLD 0x004a79d0
// FUNCTION: GOLDTL 0x4a7af0

void __cdecl fcn_004a7af0(fcn_004a7af0_obj* o, int i)
{
	int old;

	if (i < 2) {
		old = g_1007ce8[o->slot[i]].state;
		g_1007ce8[o->slot[i]].state = 4;
		o->last = o->slot[i];
		o->slot[i] = fcn_004a7880(old);
		g_1007ce8[o->slot[i]].flag = 0;
	}
}
