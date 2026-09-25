struct s_772500;

// SIZE 0x54
struct s_772500 {
	char pad[0x50];
	short x;
	short y;
};

extern struct s_772500* g_772500;

// SIZE 0x3cc
struct s_1015f4c {
	int x;
	int y;
	char pad[0x384];
	int idx;
	char pad2[0xc];
	int w;
	int h;
	int c;
	int d;
	char pad3[0x20];
};

extern struct s_1015f4c g_1015f4c[];

// FUNCTION: GOLDTL 0x5340f0
// SIZE: 100

void __cdecl fcn_005340f0(int i)
{
	struct s_772500* p;

	if (g_1015f4c[i].idx != -1) {
		p = &g_772500[g_1015f4c[i].idx];
		g_1015f4c[i].x = p->x;
		g_1015f4c[i].y = p->y;
		g_1015f4c[i].w = 0x18;
		g_1015f4c[i].h = 0x18;
		g_1015f4c[i].c = 0x1b;
		g_1015f4c[i].d = 0xb;
	}
}
