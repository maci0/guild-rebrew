#include <stdlib.h>

/* SIZE 0x1c */
typedef struct {
	int v;
	int pad[6];
} Cell;

typedef struct {
	char pad0[0x20];
	int n;
	Cell* cells;
} Grid;

extern char g_1043370[];
extern int g_67a370;
extern int g_675320;
extern int g_675324;
extern int g_6b5c4c;
extern int g_6b5c50;

/* ADDRESS: GOLDTL 0x00405a50 */
int __cdecl fcn_00405a50(int a, int b, int id, int value, int radius)
{
	Grid* g;
	int r;
	int row = 0;
	int rowend;
	int col;
	int colend;
	int dy;

	g = ((Grid**) g_1043370)[(id & 0xff) * 247];
	if (g != ((Grid**) g_1043370)[0] && g != *(Grid**) (g_67a370 + 0xb0)) {
		return 0;
	}
	if (g == 0) {
		return 0;
	}
	for (r = 0; r < g->n; r++) {
		if (r >= radius) {
			break;
		}
		rowend = g->n - 2;
		if (b + r < rowend) {
			rowend = b + r;
		}
		row = b - r;
		if (row < 1) {
			row = 1;
		}
		for (; row <= rowend; row++) {
			dy = abs(b - row);
			colend = g->n - 2;
			if (a + r - dy < colend) {
				colend = a + r - dy;
			}
			col = a - (r - dy);
			if (col < 1) {
				col = 1;
			}
			for (; col <= colend; col++) {
				if (row >= 1 && row < g->n - 1 && col >= 1 && col < g->n - 1) {
					g->cells[g->n * row + col].v = value;
				}
			}
		}
	}
	if (a - radius < g_675320) {
		g_675320 = a - radius;
	}
	if (a + radius > g_6b5c4c) {
		g_6b5c4c = a + radius + 1;
	}
	if (b - radius < g_675324) {
		g_675324 = b - radius;
	}
	if (b + radius > g_6b5c50) {
		g_6b5c50 = b + radius + 1;
	}
	return 1;
}
