#include "Develop/DieGildeAddOn/game/spiel.h"



// SIZE 0x24
typedef struct {
	char pad0[0xc];
	int amount;
	char pad10[0x24 - 0x10];
} Offer;

// SIZE 0x18
#include "Develop/client_types.h"
typedef CRIME_GRID_CELL Cell;

extern CRIME_GRID_CELL gm_CrimeGrid[9][8];

void __cdecl gm_GetLawEntry(int kind, Offer* o);

unsigned short __cdecl gm_RandomMod(int n);
void __cdecl gm_PosToStatsGrid(char* pos, int* x, int* y);

void __cdecl cm_SubtractCrimeGrid(int key, unsigned char kind)
{
	int x;
	char* entity;
	Offer offer;
	int y;
	int xmax;
	int ymax;
	int i;
	int j;

	gm_GetLawEntry(kind, &offer);
	gm_ResolveEntityById((void**) (&entity), 0, 0, key);
	x = gm_RandomMod(8);
	y = gm_RandomMod(8);
	if (entity != 0 && *(char**) (entity + 0x61) != 0) {
		gm_PosToStatsGrid(*(char**) (entity + 0x61) + 0x4c, &x, &y);
		gm_CrimeGrid[x][y].supply -= offer.amount;
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
				gm_CrimeGrid[i][j].demand -= offer.amount;
			}
		}
	}
}
