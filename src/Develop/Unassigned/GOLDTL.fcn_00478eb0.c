#pragma optimize("y", off)

/* ADDRESS: GOLDTL 0x00478eb0 */
void __cdecl fcn_00478eb0(int a0, int a1, char* a2, char* a3, int a4, int a5, int a6)
{
	short* dest;
	int stride;
	int width;
	char v2;
	char v3;
	int row;
	int col;
	char* src;
	short px;

	stride = *(int*) (a2 + 0x10);
	v2 = a3[6];
	v3 = a3[0xa];
	dest = (short*) (*(int*) (a2 + 0x1c) + (a0 + stride * a1) * 2);
	src = a3 + 0x32;
	width = *(unsigned short*) (a3 + 6) * 2;
	if (a6 == 0) {
		row = 0;
		do {
			col = 0;
			do {
				px = *(short*) (src + ((col >> 8) & 0xff) * 2);
				*dest++ = px;
				col += a4;
			} while ((char) (col >> 8) < v2);
			dest += stride;
			row += a5;
			src = a3 + 0x32 + ((row >> 8) & 0xff) * width;
		} while ((char) (row >> 8) < v3);
		return;
	}
	row = 0;
	do {
		col = 0;
		do {
			px = *(short*) (src + ((col >> 8) & 0xff) * 2);
			if (px != 0) {
				*dest = px;
			}
			dest++;
			col += a4;
		} while ((char) (col >> 8) < v2);
		dest += stride;
		row += a5;
		src = a3 + 0x32 + ((row >> 8) & 0xff) * width;
	} while ((char) (row >> 8) < v3);
}
