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
extern int g_772534;
extern int g_772514;
extern Win* g_77255c;
extern char s_67d7d0[];

void __cdecl fcn_0041d9e0(const char* msg);

// FUNCTION: GOLDTL 0x4727a0
// SIZE: 130
int __cdecl fcn_004727a0(int k, int i)
{
	if (k) {
		g_772534 = k;
	} else {
		k = g_772534;
	}
	if (i > g_1038140[k].count || i < 0) {
		fcn_0041d9e0(s_67d7d0);
		return 0;
	}
	g_772514 = g_1038140[k].wins[i];
	g_77255c = &g_1015f40[g_772514];
	return 1;
}
