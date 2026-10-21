#include <string.h>

int __cdecl m_alloc(int size, char* tag);
void __cdecl m_FreeTracked(void* p);
unsigned int __cdecl fcn_0041bac0(int r, int g, unsigned char b);
void __cdecl fcn_00477560(const void* src, char* hdr);

/* Block-encodes the colour-keyed sprite rectangle found inside the plane at
 * a5 (stride a7, origin a1) and returns the packed block buffer. */
/* ADDRESS: GOLDTL 0x00477e70 */
char* __cdecl fcn_00477e70(int a1, int a2, int a3, int a4, int a5, int a6,
                           int a7, unsigned char a8)
{
	unsigned short minx;
	unsigned short maxx;
	unsigned short miny;
	unsigned short maxy;
	unsigned short color;
	int offs[865];
	char* b;
	char* block;
	char* g;
	char* p;
	char* q;
	char* out;
	int rowstride;
	int rb;
	int total;
	int bytes;
	int count;
	int i;
	int j;

	b = (char*) m_alloc((a3 * 8 + 4) * a4 + 0x32, (char*) 0x67d9c0);
	minx = a3;
	miny = a4;
	maxx = 0;
	maxy = 0;
	if (a4 > 0) {
		g = (char*) a5;
		p = (char*) (a5 + (a1 + a3 * a7) * 2);
		for (i = 0; i < a4; i++) {
			q = p;
			for (j = 0; j < a3; j++) {
				if (*(unsigned short*) q != 0) {
					if (j > maxx) {
						maxx = (unsigned short) j;
					}
					if (j < minx) {
						minx = (unsigned short) j;
					}
					if (i > maxy) {
						maxy = (unsigned short) i;
					}
					if (i < miny) {
						miny = (unsigned short) i;
					}
				}
				q += 2;
			}
			p += a7 * 2;
		}
	}
	if (maxx < minx) {
		minx = 0;
		maxx = 0;
		miny = 0;
		maxy = 0;
	} else if (maxy < miny) {
		minx = 0;
		maxx = 0;
		miny = 0;
		maxy = 0;
	}
	*(unsigned short*) (b + 4) = minx;
	*(unsigned short*) (b + 6) = (unsigned short) (maxx + 1);
	*(unsigned short*) (b + 8) = miny;
	*(unsigned short*) (b + 0xa) = (unsigned short) (maxy + 1);
	*(unsigned short*) (b + 0xe) = minx;
	*(unsigned short*) (b + 0x10) = miny;
	*(unsigned short*) (b + 0x12) = (unsigned short) (maxx + 1);
	*(unsigned short*) (b + 0x14) = (unsigned short) (maxy + 1);
	*(unsigned short*) (b + 0x16) = minx;
	*(unsigned short*) (b + 0x18) = miny;
	*(unsigned short*) (b + 0x1a) = maxx;
	*(unsigned short*) (b + 0x1c) = maxy;
	*(int*) b = 0x32;
	color = (unsigned short) fcn_0041bac0(*(unsigned char*) 0x100f1a0,
	                                      *(unsigned short*) 0x100f1a1,
	                                      *(unsigned char*) 0x100f1a2);
	g = (char*) a5;
	rowstride = a3 * a7;
	if (*(unsigned short*) (b + 0xa) != 0) {
		for (i = 0; i < *(unsigned short*) (b + 0xa); i++) {
			bytes = *(int*) b;
			block = b + bytes;
			total = 0;
			*(int*) b = bytes + 4;
			offs[i] = (int) (block - b);
			q = b + *(int*) b;
			if (*(unsigned short*) (b + 6) != 0) {
				rb = rowstride + a1;
				for (j = 0; j < *(unsigned short*) (b + 6); j++) {
					*(int*) q = 0;
					*(int*) (q + 4) = 0;
					count = 0;
					while (j < *(unsigned short*) (b + 6)
					       && *(unsigned short*) (g + (rb + j) * 2) == color) {
						count++;
						j++;
					}
					*(int*) q = count * 2;
					count = 0;
					while (j + count < *(unsigned short*) (b + 6)
					       && *(unsigned short*) (g + (rb + j + count) * 2) != color) {
						count++;
					}
					*(int*) (q + 4) = count;
					memcpy(q + 8, g + (rb + j) * 2, count * 2);
					if (count > 0) {
						j = j + count - 1;
					}
					*(int*) (b + 0x2e) = *(int*) (b + 0x2e) + count;
					total++;
					*(int*) b = *(int*) b + count * 2 + 8;
					q = b + *(int*) b;
				}
			}
			*(int*) block = total;
			rowstride = rowstride + a7;
		}
	}
	bytes = *(int*) b;
	*(int*) (b + 0x2a) = bytes;
	*(int*) b = bytes + *(unsigned short*) (b + 0xa) * 4;
	fcn_00477560(&offs[0], b);
	*(int*) (b + 0x26) = color;
	b[0xd] = a8;
	out = (char*) m_alloc(*(int*) b, (char*) 0x67d970);
	q = out;
	p = b;
	memcpy(q, p, *(int*) b);
	m_FreeTracked(b);
	return out;
}
