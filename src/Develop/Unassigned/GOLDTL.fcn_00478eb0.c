#pragma optimize("y", off)

/* ADDRESS: GOLDTL 0x00478eb0 */
void __cdecl d2_DrawScaledSprite16(int x, int y, char* surface, char* sprite, int xStep, int yStep, int transparent)
{
	short* dest;
	int stride;
	int width;
	char sprW;
	char sprH;
	int row;
	int col;
	char* src;
	short px;
	short* out;

	stride = *(int*) (surface + 0x10);
	sprW = sprite[6];
	sprH = sprite[0xa];
	dest = (short*) (*(int*) (surface + 0x1c) + (x + stride * y) * 2);
	src = sprite + 0x32;
	width = *(unsigned short*) (sprite + 6) * 2;
	if (transparent == 0) {
		row = 0;
		do {
			col = 0;
			out = dest;
			do {
				px = *(short*) (src + ((col >> 8) & 0xff) * 2);
				*out = px;
				col += xStep;
				out++;
			} while ((char) (col >> 8) < sprW);
			dest += stride;
			row += yStep;
			src = sprite + 0x32 + ((row >> 8) & 0xff) * width;
		} while ((char) (row >> 8) < sprH);
		return;
	}
	row = 0;
	do {
		col = 0;
		out = dest;
		do {
			px = *(short*) (src + ((col >> 8) & 0xff) * 2);
			if (px != 0) {
				*out = px;
			}
			col += xStep;
			out++;
		} while ((char) (col >> 8) < sprW);
		dest += stride;
		row += yStep;
		src = sprite + 0x32 + ((row >> 8) & 0xff) * width;
	} while ((char) (row >> 8) < sprH);
}
