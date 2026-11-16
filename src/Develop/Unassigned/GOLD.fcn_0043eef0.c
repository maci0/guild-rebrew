#include <mmintrin.h>

typedef void (__cdecl* BLIT_FN)(short* dst, int* src, int** corners, unsigned int n);

/* Blits the 4x4 terrain tile cells of desc into buffer: each cell blends the
 * four corner textures picked by the byte map at desc + 0x14 (row stride 5).
 * Globals have no Gold data rows yet (DATA TODO). */
/* ADDRESS: GOLD 0x0043eef0 */
void __cdecl fcn_0043eef0(char* buffer, char* desc)
{
	int* corners[4];
	int* src;
	unsigned int y;
	unsigned int x;
	unsigned int ratio;
	unsigned int s;
	int* lut;
	unsigned int off;
	unsigned char* m;

	corners[0] = (int*) 0xfbb900;
	corners[1] = (int*) 0xfbbd40;
	corners[2] = (int*) 0xfbcd40;
	ratio = *(unsigned int*) (desc + 0xc) / *(unsigned int*) (desc + 0x10);
	*(unsigned int*) 0xfbb870 = ratio;
	if (ratio >= 0x10) {
		if (ratio > 0x40) s = 0x40; else s = ratio;
	} else {
		s = 0x10;
	}
	src = corners[s >> 5];
	lut = (int*) (*(char**) desc + (2 - (s >> 5)) * 0x20);
	off = *(unsigned int*) (desc + 0x10) * s * 4 / *(unsigned int*) (desc + 0xc);
	y = 0;
	*(unsigned int*) 0xfc0d40 = off;
	*(unsigned int*) 0xfc2560 = off * s;
	*(unsigned int*) 0xfbbd10 = off << 6;
	*(unsigned int*) 0xfbb874 = *(unsigned int*) (desc + 0xc) * 2;
	for (; y < *(unsigned int*) (desc + 0x10); y++) {
		m = (unsigned char*) desc + 0x15 + y * 5;
		for (x = 0; x < *(unsigned int*) (desc + 0x10); x++) {
			off = (((((*(int*) (desc + 8) + y) * s) & 0x3f) << 6)
			    + (((*(int*) (desc + 4) + x) * s) & 0x3f)) << 2;
			corners[0] = (int*) (lut[m[x - 1]] + off);
			corners[1] = (int*) (lut[m[x]] + off);
			corners[2] = (int*) (lut[m[x + 4]] + off);
			corners[3] = (int*) (lut[m[x + 5]] + off);
			(*(BLIT_FN*) 0x5fb970)((short*) buffer
			    + (*(unsigned int*) (desc + 0xc) * y + x) * *(unsigned int*) 0xfbb870,
			    src, corners, *(unsigned int*) 0xfbb870);
		}
	}
	if (*(unsigned char*) 0x631220 != 0) {
		_mm_empty();
	}
}
