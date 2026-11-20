#include <stdlib.h>
extern int g_67a370;
float __cdecl fcn_004d3070(char* self, int x, int z, float range);

/* ADDRESS: GOLDTL 0x004d31d0 */
int __cdecl fcn_004d31d0(char* self, int centerColumn, int centerRow, int searchRadius,
	unsigned int* resultColumn, unsigned int* resultRow)
{
	char* map;
	float best;
	float f;
	int i;
	int k;
	int r;
	int c;
	int n;
	int d;
	int lo;
	int hi; int row_hi;

	map = *(char**) (((char*) g_67a370) + 0xb0);
	best = 1e9f;
	i = 0;
	if (searchRadius > 0) {
		k = centerRow;
		do {
			row_hi = *(int*) (map + 0x20) - 1 > i + centerRow ? i + centerRow : *(int*) (map + 0x20) - 1;
			lo = k < 0 ? 0 : k;
			n = centerRow - lo;
			for (r = lo; r <= row_hi; r++, n--) {
				d = i - abs(n);
				lo = centerColumn - d;
				hi = centerColumn + d;
				if (lo < 0) lo = 0;
				if (hi > *(int*) (map + 0x20) - 1) {
					hi = *(int*) (map + 0x20) - 1;
				}
				for (c = lo; c <= hi; c++) {
					int cell = *(int*) (*(char**) (map + 0x24) + (*(int*) (map + 0x20) * r + c) * 0x1c);
					if (cell != 0 && cell != 0xd) {
						f = fcn_004d3070(self, c, r,
							(float) searchRadius * *(float*) (map + 0x10) * 2.0f);
						if (f < best) {
							best = f;
							*resultColumn = c;
							*resultRow = r;
						}
					}
				}
			}
			i++;
			k--;
		} while (i < searchRadius);
	}
	if (best != 1e9f) {
		return 1;
	}
	return 0;
}
