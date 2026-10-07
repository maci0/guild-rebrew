struct s_772500;

// SIZE 0x54
struct s_772500 {
	char pad[0x50];
	short x;
	short y;
};

extern char* g_772500;

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

#include "client_types.h"
extern s_1015f4c g_1015f4c[];

// FUNCTION: GOLDTL 0x5340f0

void __cdecl fcn_005340f0(int i)
{
	struct s_772500* p;

	if (((struct s_1015f4c*)g_1015f4c)[i].idx != -1) {
		p = &((struct s_772500*)g_772500)[((struct s_1015f4c*)g_1015f4c)[i].idx];
		((struct s_1015f4c*)g_1015f4c)[i].x = p->x;
		((struct s_1015f4c*)g_1015f4c)[i].y = p->y;
		((struct s_1015f4c*)g_1015f4c)[i].w = 0x18;
		((struct s_1015f4c*)g_1015f4c)[i].h = 0x18;
		((struct s_1015f4c*)g_1015f4c)[i].c = 0x1b;
		((struct s_1015f4c*)g_1015f4c)[i].d = 0xb;
	}
}
