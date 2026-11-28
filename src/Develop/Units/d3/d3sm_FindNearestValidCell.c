#include <math.h>
#include <stdlib.h>

/* ADDRESS: GOLDTL 0x0045b7e0 */
/* ADDRESS: GOLDDE 0x004508a0 */
char __cdecl d3sm_FindNearestValidCell(int grid, int startCol, int startRow, int* outCol, int* outRow)
{
	int* base;
	int n;
	int i = 0;
	int rowEnd;
	int row;
	int colEnd;
	int col;
	int span;
	int type;

	if (grid == 0) {
		return 0;
	}
	base = *(int**) (grid + 0x24);
	if (base == 0) {
		return 0;
	}
	if (outCol == 0) {
		return 0;
	}
	if (outRow == 0) {
		return 0;
	}
	n = *(int*) (grid + 0x20);
	for (; i < n; i++) {
		rowEnd = (n - 1 < i + startRow) ? n - 1 : i + startRow;
		row = (startRow - i < 0) ? 0 : startRow - i;
		while (row <= rowEnd) {
			span = i - abs(startRow - row);
			colEnd = (n - 1 < startCol + span) ? n - 1 : startCol + span;
			col = (startCol - span < 0) ? 0 : startCol - span;
			while (col <= colEnd) {
				if (row >= 0 && row < n && col >= 0 && col < n) {
					type = base[(*(int*) (grid + 0x20) * row + col) * 7];
					if (type != 0 && type != 0x0d) {
						*outCol = col;
						*outRow = row;
						return 1;
					}
				}
				col++;
			}
			row++;
		}
	}
	return 0;
}
