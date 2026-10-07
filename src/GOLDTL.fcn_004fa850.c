// FUNCTION: GOLD 0x004f8460
// FUNCTION: GOLDTL 0x004fa850

// SIZE 0x24
typedef struct {
	char pad0[0xc];
	int amount;
	char pad10[0x24 - 0x10];
} Offer;

// SIZE 0x18
#include "client_types.h"
typedef Cell_99ef80 Cell;

extern Cell_99ef80 g_99ef80[9][8];

void __cdecl fcn_004f4830(int kind, Offer* o);
void __cdecl fcn_005015e0(char** out, int a, int b, int key);
unsigned short __cdecl fcn_0042e410(int n);
void __cdecl fcn_004fa6f0(char* pos, int* x, int* y);

void __cdecl fcn_004fa850(int key, unsigned char kind, int* ox, int* oy)
{
	int x;
	char* p;
	Offer offer;
	int y;
	int xmax;
	int ymax;
	int i;
	int j;

	fcn_004f4830(kind, &offer);
	fcn_005015e0(&p, 0, 0, key);
	x = fcn_0042e410(8);
	y = fcn_0042e410(8);
	if (p != 0 && *(char**) (p + 0x61) != 0) {
		fcn_004fa6f0(*(char**) (p + 0x61) + 0x4c, &x, &y);
		g_99ef80[x][y].supply += offer.amount;
		if (x + 1 > 8) {
			xmax = 8;
		} else {
			xmax = x + 1;
		}
		ymax = y + 1;
		if (ymax > 8) {
			ymax = 8;
		}
		for (i = x - 1 < 0 ? 0 : x - 1; i <= xmax; i++) {
			for (j = y - 1 < 0 ? 0 : y - 1; j <= ymax; j++) {
				g_99ef80[i][j].demand += offer.amount;
			}
		}
		*ox = x;
		*oy = y;
	}
}
