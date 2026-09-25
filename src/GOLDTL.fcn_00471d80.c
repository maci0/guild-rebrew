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

extern Obj g_1038140[];

void __cdecl fcn_00471c80(int win, int flags);

// FUNCTION: GOLDTL 0x471d80
// SIZE: 35
void __cdecl fcn_00471d80(int k, int flags)
{
	fcn_00471c80(g_1038140[k].wins[0], flags);
}
