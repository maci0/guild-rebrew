struct D2_RES_BOUNDS;

// SIZE 0x54
struct D2_RES_BOUNDS {
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

#include "Develop/client_types.h"
extern s_1015f4c g_1015f4c[];


/* ADDRESS: GOLDTL 0x005340f0 */
void __cdecl d2_InitWindowBounds(int i)
{
	struct D2_RES_BOUNDS* p;

	if (((struct s_1015f4c*)g_1015f4c)[i].idx != -1) {
		p = &((struct D2_RES_BOUNDS*)g_772500)[((struct s_1015f4c*)g_1015f4c)[i].idx];
		((struct s_1015f4c*)g_1015f4c)[i].x = p->x;
		((struct s_1015f4c*)g_1015f4c)[i].y = p->y;
		((struct s_1015f4c*)g_1015f4c)[i].w = 0x18;
		((struct s_1015f4c*)g_1015f4c)[i].h = 0x18;
		((struct s_1015f4c*)g_1015f4c)[i].c = 0x1b;
		((struct s_1015f4c*)g_1015f4c)[i].d = 0xb;
	}
}
