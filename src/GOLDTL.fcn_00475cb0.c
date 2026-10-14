#include <stdio.h>
#include <string.h>

#pragma pack(push, 2)
typedef struct BmpFileHeader {
	unsigned short type;
	unsigned int size;
	unsigned short reserved1;
	unsigned short reserved2;
	unsigned int off_bits;
} BmpFileHeader;
// SIZE 0xe
#pragma pack(pop)

typedef struct BmpInfo {
	unsigned int size;
	int width;
	int height;
	unsigned short planes;
	unsigned short bit_count;
	unsigned int compression;
	unsigned int size_image;
	int x_pels_per_meter;
	int y_pels_per_meter;
	unsigned int clr_used;
	unsigned int clr_important;
	unsigned char blue;
	unsigned char green;
	unsigned char red;
	unsigned char reserved;
} BmpInfo;
// SIZE 0x2c

typedef struct Rgb {
	unsigned char r;
	unsigned char g;
	unsigned char b;
} Rgb;
// SIZE 0x3

/* ADDRESS: GOLDTL 0x00475cb0 */

/* Writes a top-down 24-bit BMP from w*h RGB pixels (rows of at most 1024).
 * The inventory entry also holds a second function at 0x475e20 (279 bytes). */
int __cdecl fcn_00475cb0(const char* name, int w, int h, unsigned char* pixels)
{
	FILE* fp;
	int y;
	BmpFileHeader bfh;
	BmpInfo bmi;
	Rgb row[0x400];
	int i;
	unsigned char t;
	unsigned char u;

	bfh.type = 0x4d42;
	bfh.size = w * h * 3 + 0x3a;
	bfh.reserved2 = 0;
	bfh.reserved1 = 0;
	bfh.off_bits = 0x3a;
	bmi.red = 0;
	bmi.green = 0;
	bmi.blue = 0;
	bmi.size = 0x28;
	bmi.width = w;
	bmi.height = -h;
	bmi.planes = 1;
	bmi.bit_count = 0x18;
	bmi.compression = 0;
	bmi.size_image = 0;
	bmi.y_pels_per_meter = 1;
	bmi.x_pels_per_meter = 1;
	bmi.clr_used = 0;
	bmi.clr_important = 0;
	fp = fopen(name, "wb");
	if (fp != 0) {
		fwrite(&bfh, 0xe, 1, fp);
		fwrite(&bmi, 0x2c, 1, fp);
		for (y = 0; y < h; y++) {
			memcpy(row, pixels + y * w * 3, w * 3);
			for (i = 0; i < w; i++) {
				t = row[i].r;
				u = row[i].g;
				row[i].r = row[i].b;
				row[i].g = u;
				row[i].b = t;
			}
			fwrite(row, w * 3, 1, fp);
		}
		fclose(fp);
		return 1;
	}
	return 0;
}
