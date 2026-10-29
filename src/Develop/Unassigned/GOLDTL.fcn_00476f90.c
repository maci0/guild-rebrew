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

/* ADDRESS: GOLDTL 0x00476f90 */
void __cdecl fcn_00476f90(int x, int y, int w, int h, unsigned char r, unsigned char g, unsigned char b, Surf* s)
{
	int i;

	if (b >= 1 && h >= 1) {
		for (i = 0; i < h; i++) {
			fcn_00476b10(x, y + i, r, g, b, s);
			fcn_00476b10(x + w - 1, y + i, r, g, b, s);
		}
		for (i = 0; i < w; i++) {
			fcn_00476b10(x + i, y, r, g, b, s);
			fcn_00476b10(x + i, y + h - 1, r, g, b, s);
		}
	}
}
