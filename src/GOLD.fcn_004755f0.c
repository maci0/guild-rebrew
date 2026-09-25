// FUNCTION: GOLD 0x004755f0
// SIZE: 165

typedef struct Win004755f0 {
	char pad0[0x8];
	short width;
	short height;
	char pad0c[0x26c - 0xc];
	int slot;
	char pad270[0x3c4 - 0x270];
} Win004755f0;
// SIZE 0x3c4

typedef struct Obj004755f0 {
	int pad0;
	int wins[0x60];
	int count;
	char pad188[0x2ac - 0x188];
} Obj004755f0;
// SIZE 0x2ac

typedef struct Slot004755f0 {
	char pad0[0x30];
	void* link;
	char pad34[0x2ec - 0x34];
} Slot004755f0;
// SIZE 0x2ec

extern Obj004755f0 g_00fb1020[]; /* 0x00fb1020 */
extern Win004755f0 g_00f8f120[]; /* 0x00f8f120 */
extern Slot004755f0* g_00f8f080; /* 0x00f8f080 */
extern int g_00f8f088; /* 0x00f8f088 */
extern int g_00f8f08c; /* 0x00f8f08c */

void __cdecl fcn_0046cd90(int x, int y, int slot);

void __cdecl fcn_004755f0(int k)
{
	Obj004755f0* o;
	Win004755f0* w;
	int i;

	o = &g_00fb1020[k];
	for (i = 0; i < o->count; i++) {
		w = &g_00f8f120[o->wins[i]];
		if (g_00f8f080[w->slot].link == 0) {
			fcn_0046cd90(g_00f8f08c - w->width / 2, g_00f8f088 - w->height / 2, w->slot);
		}
	}
}
