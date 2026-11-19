#include <stdlib.h>

extern int g_67a370;
#include "Develop/DieGildeAddOn/game/game_data.h"

float __cdecl fcn_004d3070(char* self, int x, int z, float range);

/* ADDRESS: GOLDTL 0x004d3330 */
int __cdecl fcn_004d3330(char* self, int a1, int a2, int a3,
	unsigned int* a4, unsigned int* a5)
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
	for (; i < a3; i++) {
		row_hi = __min(*(int*) (map + 0x20) - 1, i + a2);
		for (r = __max(0, a2 - i); r <= row_hi; r++) {
			d = i - abs(a2 - r);
			hi = __min(*(int*) (map + 0x20) - 1, a1 + d);
			for (c = __max(0, a1 - d); c <= hi; c++) {
				cell = *(int*) (*(char**) (map + 0x24)
					+ (*(int*) (map + 0x20) * r + c) * 0x1c);
				if (cell != 0 && cell != 0xd) {
					f = fcn_004d3070(self, c, r,
						(float) a3 * *(float*) (map + 0x10) * 2.0f);
					if (f > best) {
						best = f;
						*a4 = c;
						*a5 = r;
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
