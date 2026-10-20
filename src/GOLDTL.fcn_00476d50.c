typedef struct Surf {
	char pad0[0x10];
	int pitch;
	unsigned char bpp;
	char pad15[0x1c - 0x15];
	char* bits;
	char pad20[0x2c - 0x20];
	int x0;
	int y0;
	int x1;
	int y1;
} Surf;

void __cdecl fcn_00476b10(int x, int y, unsigned char r, unsigned char g, unsigned char b, Surf* s);

/* ADDRESS: GOLDTL 0x00476d50 */
void __cdecl fcn_00476d50(int x0, int y0, int x1, int y1, int r, int g, int b, Surf* s)
{
	int n, x, y, dx, dy, sx, sy, d, inc1, inc2;

	if (y0 == y1) {
		if (x1 < x0) {
			n = x0 - x1;
			while (n-- > 0)
				fcn_00476b10(x1++, y0, r, g, b, s);
			return;
		}
		n = x1 - x0;
		while (n-- > 0)
			fcn_00476b10(x0++, y0, r, g, b, s);
		return;
	}
	if (x0 == x1) {
		if (y1 < y0) {
			n = y0 - y1;
			while (n-- > 0)
				fcn_00476b10(x0, y1++, r, g, b, s);
			return;
		}
		n = y1 - y0;
		while (n-- > 0)
			fcn_00476b10(x0, y0++, r, g, b, s);
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
	x = x0;
	y = y0;
	fcn_00476b10(x, y, r, g, b, s);
	if (dx > dy) {
		inc1 = 2 * (dy - dx);
		inc2 = 2 * dy;
		d = 2 * dy - dx;
		while (x != x1) {
			x += sx;
			if (d >= 0) {
				y += sy;
				d += inc1;
			} else {
				d += inc2;
			}
			fcn_00476b10(x, y, r, g, b, s);
		}
		return;
	}
	inc1 = 2 * (dx - dy);
	inc2 = 2 * dx;
	d = 2 * dx - dy;
	while (y != y1) {
		y += sy;
		if (d >= 0) {
			x += sx;
			d += inc1;
		} else {
			d += inc2;
		}
		fcn_00476b10(x, y, r, g, b, s);
	}
}
