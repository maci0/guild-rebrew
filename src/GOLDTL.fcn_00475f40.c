typedef struct {
	char pad0[0x10];
	int pitch;
	char pad14[0x8];
	short* pixels;
} fcn_00475f40_image;
// SIZE 0x20

// FUNCTION: GOLDTL 0x475f40
// SIZE: 61

void __cdecl fcn_00475f40(int a1, int a2, int w, int h, int a5, int a6, int a7, fcn_00475f40_image* img)
{
	int y;
	int x;

	for (y = 0; y < h; y++) {
		for (x = 0; x < w; x++)
			img->pixels[img->pitch * y + x] = 0xff;
	}
}
