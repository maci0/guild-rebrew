#include <string.h>
#include "rgb.h"

extern RGB_COLOR g_100f1a0;

char* __cdecl m_alloc(unsigned int size, char* file);
short __cdecl d2_PackColorForPixelFormat(unsigned char r, unsigned char g, unsigned char b);
void __cdecl m_FreeTracked(void* p);

/* ADDRESS: GOLDTL 0x004781e0 */
unsigned int* __cdecl shp_GrabBit16(int x, int y, int width, int height, int srcBuf, char flags, int srcPitch)
{
	char* shapeBuf;
	unsigned int* result;
	unsigned short y0;
	unsigned short* q;
	unsigned short* p;
	unsigned short x0;
	unsigned short x1;
	unsigned short y1;
	int j;
	char* dst;
	char* row;
	int i;
	int rowstride;
	int bytes;
	unsigned int totalBytes;

	x0 = 0;
	y0 = 0;
	y1 = (unsigned short) height;
	x1 = (unsigned short) width;
	shapeBuf = m_alloc(height * (width * 8 + 4) + 0x32, (char*) 0x67d9c0);
	i = 0;
	if (height > 0) {
		p = (unsigned short*) (srcBuf + (y * srcPitch + x) * 2);
		do {
			j = 0;
			if (width > 0) {
				q = p;
				do {
					if (*q != 0) {
						if (j > x0) {
							x0 = (unsigned short) j;
						}
						if (j < x1) {
							x1 = (unsigned short) j;
						}
						if (i > y0) {
							y0 = (unsigned short) i;
						}
						if (i < y1) {
							y1 = (unsigned short) i;
						}
					}
					j++;
					q++;
				} while (j < width);
			}
			i++;
			p += srcPitch;
		} while (i < height);
	}
	if (x0 < x1 || y0 < y1) {
		x0 = 0;
		x1 = 0;
		y1 = 0;
		y0 = 0;
	}
	*(unsigned short*) (shapeBuf + 4) = x1;
	*(unsigned short*) (shapeBuf + 6) = x0 + 1;
	*(unsigned short*) (shapeBuf + 8) = y1;
	*(unsigned short*) (shapeBuf + 0xa) = y0 + 1;
	*(unsigned short*) (shapeBuf + 0xe) = x1;
	*(unsigned short*) (shapeBuf + 0x10) = y1;
	*(unsigned short*) (shapeBuf + 0x12) = x0 + 1;
	*(unsigned short*) (shapeBuf + 0x14) = y0 + 1;
	*(unsigned short*) (shapeBuf + 0x16) = x1;
	*(unsigned short*) (shapeBuf + 0x18) = y1;
	*(unsigned short*) (shapeBuf + 0x1a) = x0;
	*(unsigned short*) (shapeBuf + 0x1c) = y0;
	*(unsigned int*) shapeBuf = 0x32;
	d2_PackColorForPixelFormat(g_100f1a0.r, g_100f1a0.g, g_100f1a0.b);
	dst = shapeBuf + *(unsigned int*) shapeBuf;
	i = 0;
	if (*(unsigned short*) (shapeBuf + 0xa) > 0) {
		rowstride = srcPitch * 2;
		bytes = *(unsigned short*) (shapeBuf + 6) * 2;
		row = (char*) (srcBuf + (y * srcPitch + x) * 2);
		do {
			memcpy(dst, row, bytes);
			*(unsigned int*) shapeBuf += *(unsigned short*) (shapeBuf + 6) * 2;
			*(unsigned int*) (shapeBuf + 0x2e) += *(unsigned short*) (shapeBuf + 6);
			bytes = *(unsigned short*) (shapeBuf + 6) * 2;
			dst += bytes;
			i++;
			row += rowstride;
		} while (i < *(unsigned short*) (shapeBuf + 0xa));
	}
	*(unsigned int*) (shapeBuf + 0x2a) = 0;
	*(char*) (shapeBuf + 0xd) = flags;
	*(unsigned int*) (shapeBuf + 0x26) = 0xffffffff;
	result = (unsigned int*) m_alloc(*(unsigned int*) shapeBuf, (char*) 0x67d970);
	totalBytes = *(unsigned int*) shapeBuf;
	memcpy(result, shapeBuf, totalBytes);
	m_FreeTracked(shapeBuf);
	return result;
}
