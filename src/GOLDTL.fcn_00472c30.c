void __cdecl fcn_00472960(int, int, int, int, int);

/* ADDRESS: GOLDTL 0x00472c30 */

/* Draws the line from (x0,y0) to (x1,y1) with the plot attributes a4, a5 and
 * a6. Axis-parallel segments become straight runs, the rest use the
 * Bresenham error accumulator. */
void __cdecl fcn_00472c30(int x0, int y0, int x1, int y1, int a4, int a5, int a6)
{
	int n;
	int sx;
	int sy;
	int dx;
	int dy;
	int e;
	int d2;
	int e2;

	if (y0 == y1) {
		if (x1 < x0) {
			n = x0 - x1;
			if (n > 0) {
				do {
					fcn_00472960(x1, y0, a4, a5, a6);
					x1++;
				} while (--n);
			}
			return;
		}
		n = x1 - x0;
		if (n > 0) {
			do {
				fcn_00472960(x0, y0, a4, a5, a6);
				x0++;
			} while (--n);
		}
		return;
	}
	if (x0 != x1) {
		if (x0 < x1) {
			sx = 1;
			dx = x1 - x0;
		} else {
			sx = -1;
			dx = x0 - x1;
		}
		if (y0 < y1) {
			sy = 1;
			dy = y1 - y0;
		} else {
			sy = -1;
			dy = y0 - y1;
		}
		fcn_00472960(x0, y0, a4, a5, a6);
		if (dx > dy) {
			d2 = dy * 2;
			e2 = (dy - dx) * 2;
			e = d2 - dx;
			do {
				x0 += sx;
				if (e < 0) {
					e += d2;
				} else {
					y0 += sy;
					e += e2;
				}
				fcn_00472960(x0, y0, a4, a5, a6);
			} while (x0 != x1);
			return;
		}
		d2 = dx * 2;
		e2 = (dx - dy) * 2;
		e = d2 - dy;
		do {
			y0 += sy;
			if (e < 0) {
				e += d2;
			} else {
				x0 += sx;
				e += e2;
			}
			fcn_00472960(x0, y0, a4, a5, a6);
		} while (y0 != y1);
		return;
	}
	if (y1 < y0) {
		n = y0 - y1;
		if (n > 0) {
			do {
				fcn_00472960(x1, y1, a4, a5, a6);
				y1++;
			} while (--n);
		}
		return;
	}
	n = y1 - y0;
	if (n > 0) {
		do {
			fcn_00472960(x1, y0, a4, a5, a6);
			y0++;
		} while (--n);
	}
}
