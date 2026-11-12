/* ADDRESS: GOLD 0x0041ec50 */
void __cdecl fcn_0041ec50(unsigned int* destination, unsigned int* source)
{
	unsigned int mask;
	unsigned int rshift;
	unsigned int gshift;
	unsigned int bshift;
	unsigned int row;
	unsigned int column;
	unsigned int first_row;
	unsigned int end_row;
	unsigned int first_column;
	unsigned int end_column;
	unsigned int y;
	unsigned int x;
	unsigned int span;
	unsigned int line;
	unsigned int red;
	unsigned int green;
	unsigned int blue;
	unsigned int samples;
	unsigned short* input;
	unsigned short* output;
	unsigned short pixel;
	rshift = 0;
	mask = source[0x16];
	while (!(mask & 1)) {
		rshift++;
		mask >>= 1;
	}
	while (mask) {
		mask >>= 1;
	}
	gshift = 0;
	mask = source[0x17];
	while (!(mask & 1)) {
		gshift++;
		mask >>= 1;
	}
	while (mask) {
		mask >>= 1;
	}
	bshift = 0;
	mask = source[0x18];
	while (!(mask & 1)) {
		bshift++;
		mask >>= 1;
	}
	while (mask) {
		mask >>= 1;
	}
	first_row = 0;
	for (row = 0; row < destination[2]; row++) {
		end_row = source[2] * (row + 1) / destination[2];
		output = (unsigned short*) (destination[9] + destination[4] * row);
		first_column = 0;
		for (column = 0; column < destination[3]; column++) {
			end_column = source[3] * (column + 1) / destination[3];
			red = 0;
			green = 0;
			blue = 0;
			samples = 0;
			y = end_row - first_row;
			span = end_column - first_column;
			line = source[9] + source[4] * first_row;
			while (y != 0) {
				input = (unsigned short*) line + first_column;
				x = span;
				if (x != 0) {
					samples += x;
					do {
						pixel = *input++;
						red += (pixel & source[0x16]) >> rshift;
						green += (pixel & source[0x17]) >> gshift;
						blue += (pixel & source[0x18]) >> bshift;
					} while (--x != 0);
				}
				line += source[4];
				y--;
			}
			*output++ = (unsigned short) ((blue / samples << bshift)
				| (green / samples << gshift) | (red / samples << rshift));
			first_column = end_column;
		}
		first_row = end_row;
	}
}
