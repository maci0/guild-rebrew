// FUNCTION: GOLD 0x004754c0
// SIZE: 187

typedef struct Win004754c0 {
	char pad0[0x18];
	int* children;
	short count;
	char pad1e[0x3c4 - 0x1e];
} Win004754c0;
// SIZE 0x3c4

typedef struct Obj004754c0 {
	int pad0;
	int wins[0x60];
	int count;
	char pad188[0x190 - 0x188];
	int used;
	char pad194[0x19c - 0x194];
	int shown;
	char pad1a0[0x2ac - 0x1a0];
} Obj004754c0;
// SIZE 0x2ac

typedef struct Slot004754c0 {
	char pad0[0x3c];
	int hidden;
	char pad40[0x2ec - 0x40];
} Slot004754c0;
// SIZE 0x2ec

extern Obj004754c0 g_00fb1020[]; /* 0x00fb1020 */
extern Win004754c0 g_00f8f120[]; /* 0x00f8f120 */
extern Slot004754c0* g_00f8f080; /* 0x00f8f080 */

void __cdecl fcn_004754c0(int k, int flag)
{
	Obj004754c0* o;
	Win004754c0* w;
	int i;
	int j;

	o = &g_00fb1020[k];
	if (o->used) {
		for (i = 0; i < o->count; i++) {
			w = &g_00f8f120[o->wins[i]];
			for (j = 0; j < w->count; j++) {
				g_00f8f080[w->children[j]].hidden = (flag == 0);
			}
		}
		o->shown = flag;
	}
}
