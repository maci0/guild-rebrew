#include <stdlib.h>

extern int g_67a370;
#include "Develop/DieGildeAddOn/game/game_data.h"

float __cdecl gm_ScorePositionBalance(char* self, int x, int z, float range);

/* ADDRESS: GOLDTL 0x004d3330 */
int __cdecl gm_FindBestCombatCell(char* self, int centerCol, int centerRow, int searchRadius,
	unsigned int* outCol, unsigned int* outRow)
{
	char* map;
	float best;
	float f;
	int i;
	int r;
	int c;
	int d;
	int hi;
	int row_hi;
	int cell;

	map = *(char**) (((char*) g_67a370) + 0xb0);
	i = 0;
	best = 0.0f;
	for (; i < searchRadius; i++) {
		row_hi = __min(*(int*) (map + 0x20) - 1, i + centerRow);
		for (r = __max(0, centerRow - i); r <= row_hi; r++) {
			d = i - abs(centerRow - r);
			hi = __min(*(int*) (map + 0x20) - 1, centerCol + d);
			for (c = __max(0, centerCol - d); c <= hi; c++) {
				cell = *(int*) (*(char**) (map + 0x24)
					+ (*(int*) (map + 0x20) * r + c) * 0x1c);
				if (cell != 0 && cell != 0xd) {
					f = gm_ScorePositionBalance(self, c, r,
						(float) searchRadius * *(float*) (map + 0x10) * 2.0f);
					if (f > best) {
						best = f;
						*outCol = c;
						*outRow = r;
					}
				}
			}
		}
	}
	if (best != 0.0f && best > 5.0f) {
		return 1;
	}
	return 0;
}
