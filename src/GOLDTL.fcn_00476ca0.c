typedef struct {
	char pad0[0x4];
	int width;
	int height;
	char padc[0x4];
	int pitch;
	char pad14[0x8];
	short* pixels;
	char pad20[0xc];
	int clip_left;
	int clip_top;
	int clip_right;
	int clip_bottom;
} fcn_00476ca0_image;
// SIZE 0x3c

/* ADDRESS: GOLDTL 0x00476ca0 */

int __cdecl fcn_00476ca0(int x, int y, short value, fcn_00476ca0_image* img)
{
	if (x >= 0 && x < img->width && y >= 0 && y < img->height && x >= img->clip_left &&
	    x < img->clip_right && y >= img->clip_top && y < img->clip_bottom) {
		img->pixels[img->pitch * y + x] = value;
		return 1;
	}
	return 0;
}
