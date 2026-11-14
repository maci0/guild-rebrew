#include <string.h>
#include "rgb.h"

extern Rgb g_100f1a0;

char* __cdecl m_alloc(unsigned int size, char* file);
short __cdecl fcn_0041bac0(unsigned char r, unsigned char g, unsigned char b);
void __cdecl m_FreeTracked(void* p);

/* ADDRESS: GOLDTL 0x004781e0 */
unsigned int* __cdecl fcn_004781e0(int a0, int a1, int a2, int a3, int a4, char a5, int a6)
{
	char* v6;
	unsigned int* v18;
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
	unsigned int v4;

	x0 = 0;
	y0 = 0;
	y1 = (unsigned short) a3;
	x1 = (unsigned short) a2;
	v6 = m_alloc(a3 * (a2 * 8 + 4) + 0x32, (char*) 0x67d9c0);
	i = 0;
	if (a3 > 0) {
		p = (unsigned short*) (a4 + (a1 * a6 + a0) * 2);
		do {
			j = 0;
			if (a2 > 0) {
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
				} while (j < a2);
			}
			i++;
			p += a6;
		} while (i < a3);
	}
	if (x0 < x1 || y0 < y1) {
		y1 = 0;
		x0 = 0;
		x1 = 0;
		y0 = 0;
	}
	*(unsigned short*) (v6 + 4) = x1;
	*(unsigned short*) (v6 + 6) = x0 + 1;
	*(unsigned short*) (v6 + 8) = y1;
	*(unsigned short*) (v6 + 0xa) = y0 + 1;
	*(unsigned short*) (v6 + 0xe) = x1;
	*(unsigned short*) (v6 + 0x10) = y1;
	*(unsigned short*) (v6 + 0x12) = x0 + 1;
	*(unsigned short*) (v6 + 0x14) = y0 + 1;
	*(unsigned short*) (v6 + 0x16) = x1;
	*(unsigned short*) (v6 + 0x18) = y1;
	*(unsigned short*) (v6 + 0x1a) = x0;
	*(unsigned short*) (v6 + 0x1c) = y0;
	*(unsigned int*) v6 = 0x32;
	fcn_0041bac0(g_100f1a0.r, g_100f1a0.g, g_100f1a0.b);
	dst = v6 + *(unsigned int*) v6;
	i = 0;
	if (*(unsigned short*) (v6 + 0xa) > 0) {
		rowstride = a6 * 2;
		bytes = *(unsigned short*) (v6 + 6) * 2;
		row = (char*) (a4 + (a1 * a6 + a0) * 2);
		do {
			memcpy(dst, row, bytes);
			*(unsigned int*) (v6 + 0x2e) += *(unsigned short*) (v6 + 6);
			bytes = *(unsigned short*) (v6 + 6) * 2;
			*(unsigned int*) v6 += bytes;
			dst += bytes;
			row += rowstride;
			i++;
		} while (i < *(unsigned short*) (v6 + 0xa));
	}
	*(unsigned int*) (v6 + 0x2a) = 0;
	*(char*) (v6 + 0xd) = a5;
	*(unsigned int*) (v6 + 0x26) = 0xffffffff;
	v18 = (unsigned int*) m_alloc(*(unsigned int*) v6, (char*) 0x67d970);
	v4 = *(unsigned int*) v6;
	memcpy(v18, v6, v4);
	m_FreeTracked(v6);
	return v18;
}
