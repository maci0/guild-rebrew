unsigned short __cdecl fcn_00421350(void* path, char* map, int x0, int y0, int x1, int y1, int flags);

/* Picks the nearest walkable cell to (x, y) when no grid index was supplied. */
/* ADDRESS: GOLDTL 0x004bdbe0 */
int __cdecl fcn_004bdbe0(int obj, int x, int y, int i, int j)
{
	char* map;
	int* cell;
	int n;
	int row;
	int col;
	int dx;
	int dy;
	int d;
	float best;

	if (i < 0 || j < 0) {
		map = *(char**) (obj + 4);
		n = *(int*) (map + 0x20);
		best = (float) (n * n * 2);
		i = -1;
		j = -1;
		if (n <= 0)
			return 0;
		dy = -y;
		for (row = 0; row < n; row++) {
			col = 0;
			dx = -x;
			cell = (int*) (*(char**) (map + 0x24) + row * n * 0x1c);
			do {
				if (*cell == 6 || *cell == 0xb) {
					d = dy * dy + dx * dx;
					if ((float) d < best) {
						best = (float) d;
						i = col;
						j = row;
					}
				}
				col++;
				cell += 7;
				dx++;
			} while (col < n);
			dy++;
		}
	}
	if (i >= 0 && j >= 0) {
		*(int*) (obj + 0x1018) = 0x400;
		*(int*) (obj + 0x101c) = obj + 0x10;
		*(int*) (obj + 0x1014) = 0;
		return fcn_00421350((void*) (obj + 0x1014), *(char**) (obj + 4), x, y, i, j, 3) != 0xffff;
	}
	return 0;
}
