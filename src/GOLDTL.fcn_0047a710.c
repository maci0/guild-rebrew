#include <string.h>

#define MINR(a, b) ((b) < (a) ? (b) : (a))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define LEVEL(c) ((unsigned char) MAX(MINR((c) * 1.25, 255.0), 16.0))

typedef struct Surface {
	char pad0[0x10];
	int pitch;
	char pad14[0x1c - 0x14];
	unsigned int* bits;
} Surface;
// SIZE 0x20

typedef struct Run {
	unsigned int skip;
	unsigned int count;
	unsigned char rgb[1];
} Run;

// FUNCTION: GOLDTL 0x47a710
// SIZE: 636
int __cdecl fcn_0047a710(int x, int y, char* hdr, Surface* s)
{
	int* runs;
	int j;
	int k;
	unsigned int* out;
	unsigned char buf[0x1200];
	unsigned int* dst;
	Run* r;
	int n;
	int m;

	if (*(int*) (hdr + 0x26) != -1) {
		runs = (int*) (hdr + 0x32);
		r = (Run*) (hdr + 0x36);
		for (j = 0; j < *(unsigned short*) (hdr + 0xa); j++) {
			dst = s->bits + (j + y) * s->pitch + x;
			for (k = 0; k < *runs; k++) {
				for (m = 0; m < (int) (r->skip / 3); m++) {
					((unsigned char*) &dst[m])[3] = 0;
					buf[m * 4 + 2] = 0;
					buf[m * 4 + 1] = 0;
					buf[m * 4] = 0;
				}
				out = dst + r->skip / 3;
				n = r->count;
				for (m = 0; m < n; m++) {
					if ((r->count >= 4 && m == 0) || m == n - 1) {
						buf[m * 4 + 3] = 0xc0;
					} else {
						buf[m * 4 + 3] = 0xff;
					}
					{
						unsigned char* px;

						px = &r->rgb[m * 3];
						buf[m * 4 + 2] = LEVEL(px[0]);
						buf[m * 4 + 1] = LEVEL(px[1]);
						buf[m * 4] = LEVEL(px[2]);
					}
				}
				memcpy(out, buf, n * 4);
				dst = out + r->count;
				r = (Run*) ((unsigned char*) r + r->count * 3 + 8);
			}
			runs = (int*) r;
			r = (Run*) ((unsigned char*) r + 4);
		}
	}
	return 1;
}
