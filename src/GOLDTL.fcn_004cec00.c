#include <stdlib.h>

extern int g_67a370;

int __cdecl fcn_004ceba0(int x, int y);

/* ADDRESS: GOLDTL 0x004cec00 */
int __cdecl fcn_004cec00(int x, int y, int *out_x, int *out_y)
{
	int radius;
	int n;
	int y_cur;
	int limit;
	int row_hi;
	int row;
	int dx;
	int col_hi;
	int col;

	radius = 0;
	n = *(int *) (*(char **) (((char *) g_67a370) + 0xb0) + 0x20);
	y_cur = y;
	limit = n - 1;
	for (; radius < 0x40; radius++, y_cur--) {
		row_hi = (limit < y + radius) ? limit : y + radius;
		for (row = (y_cur < 0) ? 0 : y_cur; row <= row_hi; row++) {
			dx = radius - abs(y - row);
			col_hi = (limit < x + dx) ? limit : x + dx;
			for (col = (x - dx < 0) ? 0 : x - dx; col <= col_hi; col++) {
				if (fcn_004ceba0(col, row)) {
					*out_x = col;
					*out_y = row;
					return 1;
				}
			}
		}
	}
	return 0;
}
