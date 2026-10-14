#include <stdio.h>

typedef struct BmpInfo {
	int size;
	int width;
	int height;
	unsigned short planes;
	unsigned short bits;
	int compression;
	int image_size;
	int xppm;
	int yppm;
	int clr_used;
	int clr_important;
} BmpInfo;
// SIZE 0x28

extern char s_6750e8[];

/* ADDRESS: GOLD 0x00478970 */
/* ADDRESS: GOLDTL 0x00475830 */
int __cdecl fcn_00475830(const char* name)
{
	BmpInfo bi;
	FILE* f;

	f = fopen(name, s_6750e8);
	if (f) {
		fseek(f, 14, SEEK_SET);
		fread(&bi, 1, 0x28, f);
		fclose(f);
		if (bi.planes == 1 && bi.bits == 0x18 && bi.compression == 0) {
			return (bi.height << 16) | bi.width;
		}
		return -2;
	}
	return -1;
}
