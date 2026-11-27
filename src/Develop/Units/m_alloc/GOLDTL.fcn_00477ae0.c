#include <string.h>
#include "rgb.h"

extern RGB_COLOR g_100f1a0;

void* __cdecl m_alloc(unsigned int size, const char* tag);
void __cdecl m_FreeTracked(void*);
int __cdecl fcn_00475780(char*, char*);
void __cdecl d2_WritePixelRgb(char*, char, char, char);

/* Crop one 24-bit bitmap block: scan the cells against the hole colour for the
   used bounds, repaint both row markers, copy the bounding rows into the block
   header and return a right-sized copy. */
/* ADDRESS: GOLDTL 0x00477ae0 */
unsigned int* __cdecl fcn_00477ae0(int x, int y, int width,
                                   int height, char* pixels, char a5, int stride)
{
	unsigned int* v6;
	unsigned int* v8;
	int col;
	int row;
	char* v20;
	char black[3];
	unsigned short xmin;
	unsigned short ymin;
	unsigned short xmax;
	unsigned short ymax;

	black[0] = 0;
	black[1] = 0;
	black[2] = 0;
	xmax = 0;
	xmin = (unsigned short) width;
	ymax = 0;
	ymin = (unsigned short) height;
	v6 = (unsigned int*) m_alloc((width * 0xc + 4) * height + 0x32, (char*) 0x67d9a0);
	for (row = 0; row < height; row++) {
		for (col = 0; col < width; col++) {
			v20 = &pixels[((y + row) * stride + x + col) * 3];
			if (fcn_00475780(v20, (char*) &g_100f1a0) && col > (int) xmax) {
				xmax = (unsigned short) col;
			}
			if (fcn_00475780(v20, (char*) &g_100f1a0) && col < (int) xmin) {
				xmin = (unsigned short) col;
			}
			if (fcn_00475780(v20, (char*) &g_100f1a0) && row > (int) ymax) {
				ymax = (unsigned short) row;
			}
			if (fcn_00475780(v20, (char*) &g_100f1a0) && row < (int) ymin) {
				ymin = (unsigned short) row;
			}
		}
	}
	if (xmax < xmin || ymax < ymin) {
		xmax = 0;
		xmin = 0;
		ymax = 0;
		ymin = 0;
	}
	*(unsigned short*) ((char*) v6 + 4) = xmin;
	*(unsigned short*) ((char*) v6 + 6) = (unsigned short) (xmax + 1);
	*(unsigned short*) ((char*) v6 + 8) = ymin;
	*(unsigned short*) ((char*) v6 + 0xa) = (unsigned short) (ymax + 1);
	*(unsigned short*) ((char*) v6 + 0xe) = xmin;
	*(unsigned short*) ((char*) v6 + 0x10) = ymin;
	*(unsigned short*) ((char*) v6 + 0x12) = (unsigned short) (xmax + 1);
	*(unsigned short*) ((char*) v6 + 0x14) = (unsigned short) (ymax + 1);
	if (fcn_00475780((char*) 0x67d95c, black)) {
		for (row = 0; row < height; row++) {
			for (col = 0; col < width; col++) {
				v20 = &pixels[((y + row) * stride + x + col) * 3];
				if (!fcn_00475780(v20, (char*) 0x67d960)) {
					xmin = (unsigned short) col;
					ymin = (unsigned short) row;
					d2_WritePixelRgb(v20, g_100f1a0.r, g_100f1a0.g, g_100f1a0.b);
				}
				if (!fcn_00475780(v20, (char*) 0x67d95c)) {
					xmax = (unsigned short) col;
					ymax = (unsigned short) row;
					d2_WritePixelRgb(v20, g_100f1a0.r, g_100f1a0.g, g_100f1a0.b);
				}
			}
		}
	}
	*(unsigned short*) ((char*) v6 + 0x16) = xmin;
	*(unsigned short*) ((char*) v6 + 0x18) = ymin;
	*(unsigned short*) ((char*) v6 + 0x1a) = xmax;
	*(unsigned short*) ((char*) v6 + 0x1c) = ymax;
	*(unsigned int*) v6 = 0x32;
	v8 = (unsigned int*) ((char*) v6 + 0x32);
	for (row = 0; row < (int) *(unsigned short*) ((char*) v6 + 0xa); row++) {
		memcpy(v8, &pixels[((y + row) * stride + x) * 3], *(unsigned short*) ((char*) v6 + 6) * 3);
		*(unsigned int*) ((char*) v6 + 0x2e) += *(unsigned short*) ((char*) v6 + 6);
		v8 = (unsigned int*) ((char*) v8 + *(unsigned short*) ((char*) v6 + 6) * 3);
		*(unsigned int*) v6 += *(unsigned short*) ((char*) v6 + 6) * 3;
	}
	*(unsigned int*) ((char*) v6 + 0x2a) = 0;
	*(char*) ((char*) v6 + 0xd) = a5;
	*(unsigned int*) ((char*) v6 + 0x26) = 0xffffffff;
	v8 = (unsigned int*) m_alloc(*v6, (char*) 0x67d970);
	memcpy(v8, v6, *v6);
	m_FreeTracked(v6);
	return v8;
}
