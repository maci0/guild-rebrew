#include "client_types.h"
typedef Group_102cbc4 Group;
// SIZE 0x8c

typedef struct Slot {
	char pad0[0x58];
	int dirty;
	char pad5c[0x1d0 - 0x5c];
	int flags;
	char pad1d4[0x2f4 - 0x1d4];
} Slot;
// SIZE 0x2f4

extern Group_102cbc4 g_102cbc4[8];
extern char* g_1015ea0;

void __cdecl fcn_004695a0(int g, int sel);

// FUNCTION: GOLDTL 0x469470
// SIZE: 146
void __cdecl fcn_00469470(int g, int id)
{
	g_102cbc4[g].ids[g_102cbc4[g].count] = id;
	((Slot*)g_1015ea0)[id].dirty = 1;
	((Slot*)g_1015ea0)[id].flags &= ~2;
	g_102cbc4[g].count++;
	if (g_102cbc4[g].sel == -1) {
		fcn_004695a0(g, 0);
	}
}
