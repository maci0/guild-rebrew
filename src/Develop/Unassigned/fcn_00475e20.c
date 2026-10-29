#include <windows.h>

void* __cdecl fopen(char* path, char* mode);
int __cdecl fwrite(void* buf, unsigned int size, unsigned int count, void* fp);
int __cdecl fclose(void* fp);

/* ADDRESS: GOLDTL 0x00475e20 */
int __cdecl fcn_00475e20(char* path, int width, int height, unsigned char* pixels,
	unsigned char* palette)
{
	BITMAPFILEHEADER header;
	BITMAPINFOHEADER info;
	unsigned char colors[1024];
	void* fp;
	int i;

	header.bfType = 0x4d42;
	header.bfSize = height * width + 0x436;
	header.bfReserved2 = 0;
	header.bfReserved1 = 0;
	header.bfOffBits = 0x436;
	for (i = 0; i < 255; i++) {
		colors[i * 4] = palette[i * 3 + 2];
		colors[i * 4 + 1] = palette[i * 3 + 1];
		colors[i * 4 + 2] = palette[i * 3];
		colors[i * 4 + 3] = 0;
	}
	info.biWidth = width;
	info.biSize = sizeof(info);
	info.biHeight = -height;
	info.biPlanes = 1;
	info.biBitCount = 8;
	info.biCompression = 0;
	info.biSizeImage = 0;
	info.biYPelsPerMeter = 1;
	info.biXPelsPerMeter = 1;
	info.biClrUsed = 0;
	info.biClrImportant = 0;
	fp = fopen(path, "wb");
	if (fp != 0) {
		fwrite(&header, 14, 1, fp);
		fwrite(&info, 0x428, 1, fp);
		fwrite(pixels, width * height, 1, fp);
		fclose(fp);
		return 1;
	}
	return 0;
}
