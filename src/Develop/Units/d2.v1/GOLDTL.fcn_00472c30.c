void __cdecl d2_Plot(int, int, unsigned char, unsigned char, unsigned char);


/* Draws the line from (x0,y0) to (x1,y1) with the plot attributes a4, a5 and
 * a6. Axis-parallel segments become straight runs, the rest use the
 * Bresenham error accumulator. */
/* ADDRESS: GOLDTL 0x00472c30 */
void __cdecl d2_DrawLine(int x0, int y0, int x1, int y1, unsigned char a4, unsigned char a5, unsigned char a6)
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
			for (; n > 0; n--) {
				d2_Plot(x1++, y0, a4, a5, a6);
			}
			return;
		}
		n = x1 - x0;
		for (; n > 0; n--) {
			d2_Plot(x0++, y0, a4, a5, a6);
		}
		return;
	}
	if (x0 == x1) {
		if (y1 < y0) {
			n = y0 - y1;
			for (; n > 0; n--) {
				d2_Plot(x1, y1++, a4, a5, a6);
			}
			return;
		}
		n = y1 - y0;
		for (; n > 0; n--) {
			d2_Plot(x1, y0++, a4, a5, a6);
		}
		return;
	}
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
	d2_Plot(x0, y0, a4, a5, a6);
	if (dx > dy) {
		e2 = (dy - dx) * 2;
		d2 = dy * 2;
		e = d2 - dx;
		do {
			x0 += sx;
			if (e >= 0) {
				y0 += sy;
				e += e2;
			} else {
				e += d2;
			}
			d2_Plot(x0, y0, a4, a5, a6);
		} while (x0 != x1);
		return;
	}
	e2 = (dx - dy) * 2;
	d2 = dx * 2;
	e = d2 - dy;
	do {
		y0 += sy;
		if (e >= 0) {
			x0 += sx;
			e += e2;
		} else {
			e += d2;
		}
		d2_Plot(x0, y0, a4, a5, a6);
	} while (y0 != y1);
}
