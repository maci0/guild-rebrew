#include "Develop/DieGildeAddOn/game/spiel.h"
// FUNCTION: GOLD 0x004f8590
// FUNCTION: GOLDTL 0x004fa980

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

unsigned short __cdecl gm_RandomMod(int n);
void __cdecl fcn_004fa6f0(char* pos, int* x, int* y);

void __cdecl fcn_004fa980(int key, unsigned char kind)
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
	gm_ResolveEntityById((void**) (&p), 0, 0, key);
	x = gm_RandomMod(8);
	y = gm_RandomMod(8);
	if (p != 0 && *(char**) (p + 0x61) != 0) {
		fcn_004fa6f0(*(char**) (p + 0x61) + 0x4c, &x, &y);
		g_99ef80[x][y].supply -= offer.amount;
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
				g_99ef80[i][j].demand -= offer.amount;
			}
		}
	}
}
