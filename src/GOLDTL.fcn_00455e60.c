// FUNCTION: GOLDTL 0x455e60

#include <stdlib.h>

typedef struct Cell0455e60 {
	int kind;
	char pad4[0x1c - 4];
} Cell0455e60;
// SIZE 0x1c

void __cdecl fcn_00455e60(int fixed, int unused, int kind, int n, unsigned char* heights, Cell0455e60* grid, int cx, int cy, int size, int r)
{
	unsigned char h;
	int y;
	int x;
	int dx;
	int i;

	if (n <= 0) {
		return;
	}
	h = (unsigned char)(fixed >> 16);
	i = n;
	do {
		if (h >= *heights) {
			*heights = h;
			for (y = (cy - r < 0) ? 0 : cy - r; y <= ((size - 1 < cy + r) ? size - 1 : cy + r); y++) {
				dx = r - abs(cy - y);
				for (x = (cx - dx < 0) ? 0 : cx - dx; x <= ((size - 1 < cx + dx) ? size - 1 : cx + dx); x++) {
					grid[y * size + x].kind = kind;
				}
			}
		}
		heights++;
	} while (--i != 0);
}
