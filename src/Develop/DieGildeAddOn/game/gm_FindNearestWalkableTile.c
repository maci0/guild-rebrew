#include <stdlib.h>

extern int d3_ActiveScene;

int __cdecl gm_IsMapTileWalkable(int x, int y);

/* ADDRESS: GOLDTL 0x004cec00 */
/* ADDRESS: GOLDDE 0x004bc3a0 */
int __cdecl gm_FindNearestWalkableTile(int x, int y, int *out_x, int *out_y)
{
	int radius;
	char* m;
	int y_cur;
	int max;
	int row_hi;
	int row;
	int dx;
	int col_hi;
	int col;

	m = *(char **) (((char *) d3_ActiveScene) + 0xb0);
	radius = 0;
	y_cur = y;
	max = *(int *) (m + 0x20);
	for (; radius < 0x40; radius++, y_cur--) {
		row_hi = (max - 1 < y + radius) ? max - 1 : y + radius;
		for (row = (y_cur < 0) ? 0 : y_cur; row <= row_hi; row++) {
			dx = radius - abs(y - row);
			col_hi = (max - 1 < x + dx) ? max - 1 : x + dx;
			for (col = (x - dx < 0) ? 0 : x - dx; col <= col_hi; col++) {
				if (gm_IsMapTileWalkable(col, row)) {
					*out_x = col;
					*out_y = row;
					return 1;
				}
			}
		}
	}
	return 0;
}
