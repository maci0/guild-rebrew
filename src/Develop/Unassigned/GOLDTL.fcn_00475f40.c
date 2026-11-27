typedef struct {
	char pad0[0x10];
	int pitch;
	char pad14[0x8];
	short* pixels;
} D2_IMAGE_16;
// SIZE 0x20


/* ADDRESS: GOLDTL 0x00475f40 */
void __cdecl d2_FillSurfaceConst(int dst_x, int dst_y, int w, int h, int src, int src_x, int src_y, D2_IMAGE_16* img)
{
	int y;
	int x;

	for (y = 0; y < h; y++) {
		for (x = 0; x < w; x++)
			img->pixels[img->pitch * y + x] = 0xff;
	}
}
