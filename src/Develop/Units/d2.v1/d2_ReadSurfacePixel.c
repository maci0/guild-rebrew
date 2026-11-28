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
/* ADDRESS: GOLDDE 0x00468c20 */
void __cdecl d2_ReadSurfacePixel(int x, int y, Surf* s, unsigned char* dst)
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
		b = s->bits + off;
		c0 = b[0]; c1 = b[1]; c2 = b[2];

		break;
	case 32:
		off = s->pitch * y + x;
		b = s->bits + off * 4;
		c0 = b[2]; c1 = b[1]; c2 = b[0];

		break;
	default:
		c0 = (unsigned char) y;
		c1 = (unsigned char) y;
		c2 = (unsigned char) y;
		break;
	}
	dst[0] = c0; dst[1] = c1; dst[2] = c2;
}
