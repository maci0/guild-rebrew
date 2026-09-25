typedef struct Win {
	char pad0[0x28];
	int* children;
	int count;
	char pad30[0x3cc - 0x30];
} Win;
// SIZE 0x3cc

typedef struct Slot {
	char pad0[0x18];
	int w;
	char pad1c[0x20 - 0x1c];
	int type;
	char pad24[0x6c - 0x24];
	int visible;
	char pad70[0x2f4 - 0x70];
} Slot;
// SIZE 0x2f4

extern Win g_1015f40[];
extern Slot* g_1015ea0;

void __cdecl fcn_00469110(int slot, int w);

// FUNCTION: GOLDTL 0x46c4e0
// SIZE: 184
void __cdecl fcn_0046c4e0(int win)
{
	Win* w;
	int maxw;
	int i;

	w = &g_1015f40[win];
	maxw = 0;
	for (i = 0; i < w->count; i++) {
		if (g_1015ea0[w->children[i]].type == 9 && g_1015ea0[w->children[i]].w > maxw) {
			maxw = g_1015ea0[w->children[i]].w;
		}
	}
	maxw += 8;
	if (maxw < 0x80) {
		maxw = 0x80;
	}
	for (i = 0; i < w->count; i++) {
		if (g_1015ea0[w->children[i]].type == 9) {
			g_1015ea0[w->children[i]].visible = 1;
			fcn_00469110(w->children[i], maxw);
		}
	}
}
