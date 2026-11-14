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

/* ADDRESS: GOLDTL 0x00476a50 */
void __cdecl fcn_00476a50(int x, int y, Surf* s, unsigned char* dst)
{
	char* b;
	int off;
	int n; unsigned char c0, c1, c2;

	n = s->bpp >> 3;
	switch (s->bpp) {
	case 15:
	case 16:
		c0 = (unsigned char) y;
		c1 = (unsigned char) y;
		c2 = (unsigned char) y;
		break;
	case 24:
		off = (s->pitch * y + x) * n;
		b = s->bits;
		c0 = b[off]; c1 = b[off + 1]; c2 = b[off + 2];

		break;
	case 32:
		off = s->pitch * y + x;
		b = s->bits;
		c0 = b[off * 4 + 2]; c1 = b[off * 4 + 1]; c2 = b[off * 4];

		break;
	default:
		c0 = (unsigned char) y;
		c1 = (unsigned char) y;
		c2 = (unsigned char) y;
		break;
	}
	dst[0] = c0; dst[1] = c1; dst[2] = c2;
}
