typedef struct Slot {
	int id;
	int used;
	int value;
	char* data;
	int x;
	int y;
	int w;
	int h;
	int type;
	char pad24[0x38 - 0x24];
	int text;
	char pad3c[0x48 - 0x3c];
	int hidden;
	char pad4c[0x58 - 0x4c];
	int dirty;
	char pad5c[0x88 - 0x5c];
	int result;
	char* buf;
	char pad90[0x2f4 - 0x90];
} Slot;
// SIZE 0x2f4
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

extern Slot* g_1015ea0;
extern Win g_1015f40[];
extern Obj g_1038140[];
extern int g_772534;

// FUNCTION: GOLDTL 0x472100
// SIZE: 103
char* __cdecl fcn_00472100(int j, int i)
{
	Win* w;
	Slot* s;

	w = &g_1015f40[g_1038140[g_772534].wins[i]];
	if (j > w->count) {
		return 0;
	}
	s = &g_1015ea0[w->children[j]];
	if (s->type == 0x41) {
		return s->data;
	}
	return 0;
}
