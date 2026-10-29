#include <math.h>
#include <stdlib.h>

/*
 * Nearest walkable cell search over the square map grid.
 *
 * map+0x20 is the grid size (row and column count), map+0x24 points at the
 * cell records. A record is 0x1c bytes and its first dword holds the cell
 * type; type 0 and 0x0d are not walkable.
 *
 * flags & 0x10 takes the world position of (x, y) from "to" instead of
 * converting it. flags & 1 asks for the nearest cell by world distance; without
 * either flag the first walkable cell found in the diamond around (x, y) wins.
 * The diamond is rescanned for every radius, rows from max(1, y - radius) to
 * min(size - 1, y + radius), so row 0 is never used as a start row.
 *
 * Returns 1 when a cell was stored through outX/outY.
 */

char __cdecl fcn_0045b920(char*, int, int, float*);

/* ADDRESS: GOLDTL 0x00407e30 */
char __cdecl fcn_00407e30(char* map, float* from, float* to, int x, int y, int* outX, int* outY, int maxRows, int flags)
{
	int i = 0;
	float best = 1e11f;
	float pts[12];
#define pa (pts)
#define pb (pts + 4)
#define p (pts + 8)
	int row;
	int rowEnd;
	int col;
	int colEnd;
	int dy;
	int span;
	int type;
	float d;
	float dx;
	float ey;
	float ez;
	float ex;

	if (map == 0 || *(int**) (map + 0x24) == 0 || outX == 0 || outY == 0) {
		return 0;
	}

	if (flags & 0x10) {
		type = ((int*) *(int**) (map + 0x24))[(*(int*) (map + 0x20) * y + x) * 7];
		if (type != 0 && type != 0x0d) {
			*outX = x;
			*outY = y;
			return 1;
		}
		pb[0] = to[0];
		pb[1] = to[1];
		pb[2] = to[2];
	} else {
		fcn_0045b920(map, x, y, pb);
	}
	pa[0] = from[0];
	pa[1] = from[1];
	pa[2] = from[2];
	*outX = -1;
	*outY = -1;

	if ((flags & 1) || (flags & 0x10)) {
		for (; i < *(int*) (map + 0x20) && i < maxRows; i++) {
			rowEnd = *(int*) (map + 0x20) - 1;
			if (rowEnd > i + y) {
				rowEnd = i + y;
			}
			row = y - i;
			if (row < 1) {
				row = 1;
			}
			dy = y - row;
			while (row <= rowEnd) {
				span = i - abs(dy);
				colEnd = *(int*) (map + 0x20) - 1;
				if (colEnd > x + span) {
					colEnd = x + span;
				}
				col = x - span;
				if (col < 0) {
					col = 0;
				}
				while (col <= colEnd) {
					if (row >= 0 && row < *(int*) (map + 0x20) && col >= 0 && col < *(int*) (map + 0x20)) {
						type = ((int*) *(int**) (map + 0x24))[(*(int*) (map + 0x20) * row + col) * 7];
						if (type != 0 && type != 0x0d) {
							if (fcn_0045b920(map, col, row, p)) {
								dx = pa[0] - p[0];
								ey = pa[1] - p[1];
								ez = pa[2] - p[2];
								d = (float) sqrt(ez * ez + ey * ey + dx * dx);
								ex = pb[0] - p[0];
								ey = pb[1] - p[1];
								ez = pb[2] - p[2];
								d = d + (float) sqrt(ez * ez + ey * ey + ex * ex);
								if (d < best) {
									*outX = col;
									*outY = row;
									best = d;
								}
							}
						}
					}
					col++;
				}
				row++;
				dy--;
			}
		}
	} else {
		for (; i < *(int*) (map + 0x20) && i < maxRows; i++) {
			rowEnd = *(int*) (map + 0x20) - 1;
			if (rowEnd > i + y) {
				rowEnd = i + y;
			}
			row = y - i;
			if (row < 1) {
				row = 1;
			}
			dy = y - row;
			while (row <= rowEnd) {
				span = i - abs(dy);
				colEnd = *(int*) (map + 0x20) - 1;
				if (colEnd > x + span) {
					colEnd = x + span;
				}
				col = x - span;
				if (col < 0) {
					col = 0;
				}
				while (col <= colEnd) {
					if (row >= 0 && row < *(int*) (map + 0x20) && col >= 0 && col < *(int*) (map + 0x20)) {
						type = ((int*) *(int**) (map + 0x24))[(*(int*) (map + 0x20) * row + col) * 7];
						if (type != 0 && type != 0x0d) {
							*outX = col;
							*outY = row;
							return 1;
						}
					}
					col++;
				}
				row++;
				dy--;
			}
		}
	}
	if (*outX != -1 || *outY != -1) {
		return 1;
	}
	*outX = x;
	*outY = y;
	return 0;
}
