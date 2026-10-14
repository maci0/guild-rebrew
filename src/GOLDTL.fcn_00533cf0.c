

// SIZE 0x2f4
typedef struct {
	char pad0[0x20];
	int alive;
	char pad24[0x24];
	int marked;
	char pad4c[4];
	void* home;
	char pad54[0x2a0];
} Unit;

// SIZE 0x2bc
typedef struct {
	char pad0[0x190];
	int x190;
	char pad194[0xc];
	int x1a0;
	char pad1a4[0x118];
} Home;

extern char* g_1015ea0;
extern int g_7747a8;
extern unsigned short g_773e40[];
#include "client_types.h"
extern Obj_1038140 g_1038140[];

void __cdecl fcn_00533cf0(int mark)
{
	int i;
	int k;
	Home* h;

	if (mark != 0) {
		g_7747a8 = 0;
		for (i = 0; i < 48; i++) {
			if (((Home*)g_1038140)[i].x190 != 0 && ((Home*)g_1038140)[i].x1a0 != 0) {
				h = &((Home*)g_1038140)[i];
				for (k = 0; k < 0x400; k++) {
					if (((Unit*)g_1015ea0)[k].alive != 0 && ((Unit*)g_1015ea0)[k].home == h && ((Unit*)g_1015ea0)[k].marked == 0) {
						g_773e40[g_7747a8++] = (unsigned short) k;
						((Unit*)g_1015ea0)[k].marked = 1;
					}
				}
			}
		}
	} else {
		for (i = 0; i < g_7747a8; i++) {
			((Unit*)g_1015ea0)[g_773e40[i]].marked = 0;
		}
	}
}
