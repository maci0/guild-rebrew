/* ADDRESS: GOLD 0x0041f2b0 */
void __cdecl fcn_0041f2b0(unsigned int* destination, unsigned int* source)
{
	unsigned int bits;
	unsigned int rs;
	unsigned int gs;
	unsigned int bs;
	unsigned int row;
	unsigned int column;
	unsigned int first_y;
	unsigned int end_y;
	unsigned int first_x;
	unsigned int end_x;
	unsigned int width;
	unsigned int height;
	unsigned int next_row;
	unsigned int next_column;
	unsigned short* input;
	unsigned short* output;
	unsigned short a;
	unsigned short b;
	unsigned short c;
	unsigned short d;
	unsigned int ar, ag, ab, br, bg, bb, cr, cg, cb, dr, dg, db;
	unsigned int lr, lg, lb, rr, rg, rb;
	unsigned int left_r, left_g, left_b, right_r, right_g, right_b;
	unsigned int xr, xg, xb;
	unsigned int dlr, dlg, dlb, drr, drg, drb;
	unsigned int dxr, dxg, dxb;
	unsigned int y;
	unsigned int x;
	rs = 0;
	bits = source[0x16];
	while (!(bits & 1)) { rs++; bits >>= 1; }
	while (bits) { bits >>= 1; }
	gs = 0;
	bits = source[0x17];
	while (!(bits & 1)) { gs++; bits >>= 1; }
	while (bits) { bits >>= 1; }
	bs = 0;
	bits = source[0x18];
	while (!(bits & 1)) { bs++; bits >>= 1; }
	while (bits) { bits >>= 1; }
	first_y = 0;
	for (row = 0; row < source[2]; row++) {
		end_y = destination[2] * (row + 1) / source[2];
		height = end_y - first_y;
		input = (unsigned short*) (source[9] + source[4] * row);
		first_x = 0;
		for (column = 0; column < source[3]; column++) {
			end_x = destination[3] * (column + 1) / source[3];
			width = end_x - first_x;
			next_row = row + 1 < source[2] ? (int) source[4] >> 1 : 0;
			next_column = column + (column + 1 < source[3]);
			a = input[column];
			b = input[next_column];
			c = input[next_row + column];
			d = input[next_row + next_column];
			ar = (a & source[0x16]) >> rs;
			ag = (a & source[0x17]) >> gs;
			ab = (a & source[0x18]) >> bs;
			br = (b & source[0x16]) >> rs;
			bg = (b & source[0x17]) >> gs;
			bb = (b & source[0x18]) >> bs;
			cr = (c & source[0x16]) >> rs;
			cg = (c & source[0x17]) >> gs;
			cb = (c & source[0x18]) >> bs;
			dr = (d & source[0x16]) >> rs;
			dg = (d & source[0x17]) >> gs;
			db = (d & source[0x18]) >> bs;
			dlr = cr - ar; dlg = cg - ag; dlb = cb - ab;
			drr = dr - br; drg = dg - bg; drb = db - bb;
			lr = 0; lg = 0; lb = 0;
			rr = 0; rg = 0; rb = 0;
			for (y = 0; y < height; y++) {
				left_r = ar + lr / height;
				left_g = ag + lg / height;
				left_b = ab + lb / height;
				right_r = br + rr / height;
				right_g = bg + rg / height;
				right_b = bb + rb / height;
				dxr = right_r - left_r; dxg = right_g - left_g; dxb = right_b - left_b;
				xr = 0; xg = 0; xb = 0;
				output = (unsigned short*) (destination[9]
					+ destination[4] * (first_y + y)) + first_x;
				x = width;
				if (x != 0) {
					do {
						*output++ = (unsigned short) (((left_b + xb / width) << bs)
							| ((left_g + xg / width) << gs) | ((left_r + xr / width) << rs));
						xr += dxr; xg += dxg; xb += dxb;
					} while (--x != 0);
				}
				lr += dlr; lg += dlg; lb += dlb;
				rr += drr; rg += drg; rb += drb;
			}
			first_x = end_x;
		}
		first_y = end_y;
	}
}
