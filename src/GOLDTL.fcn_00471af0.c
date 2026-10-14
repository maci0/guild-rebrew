typedef struct Obj {
	int pad0;
	int wins[0x60];
	int count;
	char pad188[0x190 - 0x188];
	int used;
	char pad194[0x19c - 0x194];
	int shown;
	int active;
	char pad1a4[0x2bc - 0x1a4];
} Obj;
// SIZE 0x2bc

typedef struct Slot {
	char pad0[0x20];
	int type;
	char pad24[0x48 - 0x24];
	int hidden;
	int pad4c;
	Obj* owner;
	char pad54[0x2f4 - 0x54];
} Slot;
// SIZE 0x2f4

#include "client_types.h"
extern Obj_1038140 g_1038140[];
extern char* g_1015ea0;

/* ADDRESS: GOLDTL 0x00471af0 */
void __cdecl fcn_00471af0(int k, int flag)
{
	Obj* o;
	int i;

	o = &((Obj*)g_1038140)[k];
	if (o->used) {
		for (i = 0; i < 0x400; i++) {
			if (((Slot*)g_1015ea0)[i].type && ((Slot*)g_1015ea0)[i].owner == o) {
				((Slot*)g_1015ea0)[i].hidden = (flag == 0);
			}
		}
		o->active = flag;
	}
}
