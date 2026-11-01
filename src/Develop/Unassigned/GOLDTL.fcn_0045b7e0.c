#include <math.h>
#include <stdlib.h>

/* ADDRESS: GOLDTL 0x0045b7e0 */
char __cdecl fcn_0045b7e0(int a0, int a1, int a2, int* a3, int* a4)
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

	if (a0 == 0) {
		return 0;
	}
	base = *(int**) (a0 + 0x24);
	if (base == 0) {
		return 0;
	}
	if (a3 == 0) {
		return 0;
	}
	if (a4 == 0) {
		return 0;
	}
	n = *(int*) (a0 + 0x20);
	for (; i < n; i++) {
		rowEnd = (n - 1 < i + a2) ? n - 1 : i + a2;
		row = (a2 - i < 0) ? 0 : a2 - i;
		while (row <= rowEnd) {
			span = i - abs(a2 - row);
			colEnd = (n - 1 < a1 + span) ? n - 1 : a1 + span;
			col = (a1 - span < 0) ? 0 : a1 - span;
			while (col <= colEnd) {
				if (row >= 0 && row < n && col >= 0 && col < n) {
					type = base[(n * row + col) * 7];
					if (type != 0 && type != 0x0d) {
						*a3 = col;
						*a4 = row;
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
