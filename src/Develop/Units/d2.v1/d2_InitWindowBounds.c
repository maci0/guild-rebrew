struct D2_RES_BOUNDS;

// SIZE 0x54
struct D2_RES_BOUNDS {
	char pad[0x50];
	short x;
	short y;
};

extern char* d2_FileObjTable;

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
extern s_1015f4c d2_WindowMetricsView[];


/* ADDRESS: GOLDTL 0x005340f0 */
void __cdecl d2_InitWindowBounds(int i)
{
	struct D2_RES_BOUNDS* p;

	if (((struct s_1015f4c*)d2_WindowMetricsView)[i].idx != -1) {
		p = &((struct D2_RES_BOUNDS*)d2_FileObjTable)[((struct s_1015f4c*)d2_WindowMetricsView)[i].idx];
		((struct s_1015f4c*)d2_WindowMetricsView)[i].x = p->x;
		((struct s_1015f4c*)d2_WindowMetricsView)[i].y = p->y;
		((struct s_1015f4c*)d2_WindowMetricsView)[i].w = 0x18;
		((struct s_1015f4c*)d2_WindowMetricsView)[i].h = 0x18;
		((struct s_1015f4c*)d2_WindowMetricsView)[i].c = 0x1b;
		((struct s_1015f4c*)d2_WindowMetricsView)[i].d = 0xb;
	}
}
