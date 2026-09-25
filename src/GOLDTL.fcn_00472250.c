typedef struct Win {
	int pad0;
	int left;
	int top;
	int width;
	int height;
	char pad14[0x28 - 0x14];
	int* children;
	int count;
	char pad30[0x27c - 0x30];
	int slot;
	char pad280[0x3cc - 0x280];
} Win;
// SIZE 0x3cc
typedef struct Obj {
	int pad0;
	int wins[0x60];
	int count;
	char pad188[0x190 - 0x188];
	int used;
	char pad194[0x1a4 - 0x194];
	void* fx[2];
	void* h[2];
	char pad1b4[0x2bc - 0x1b4];
} Obj;
// SIZE 0x2bc

extern Win g_1015f40[];
extern Obj g_1038140[];

// FUNCTION: GOLDTL 0x472250
// SIZE: 97
int __cdecl fcn_00472250(int k, int i, int j)
{
	Win* w;

	if (k != -1) {
		w = &g_1015f40[g_1038140[k].wins[i]];
	} else {
		w = &g_1015f40[i];
	}
	if (j > w->count) {
		return -1;
	}
	return w->children[j];
}
