#include "Develop/DieGildeAddOn/game/game_data.h"

unsigned int __cdecl fcn_004789e0(int x, unsigned int y, char* s, unsigned short* spr, unsigned int zoom)
{
	unsigned short* dst;
	unsigned int* line;
	unsigned int* q;
	unsigned int* end;
	unsigned int height;
	unsigned int off;
	int row;
	unsigned int i;
	unsigned int k;
	unsigned int n;
	unsigned int r;
	unsigned short* d;
	unsigned int* src;
	unsigned int first;
	unsigned int h;

	q = (unsigned int*) ((char*) spr + 0x36);
	line = (unsigned int*) ((char*) spr + 0x32);
	dst = (unsigned short*) (*(int*) (s + 0x1c)
	 + (*(int*) (s + 0x10) * (int) y + x) * 2);
	height = *(unsigned short*) ((char*) spr + 0xa);
	if ((int) (height + y) < g_7725fc) {
		return 0;
	}
	h = *(unsigned short*) ((char*) spr + 6);
	if ((int) x + (int) h / (int) zoom > d2_ClipRight) {
		return 0;
	}
	if ((int) x + (int) h < d2_ClipLeft) {
		return 0;
	}
	if (d2_ClipBottom < (int) ((int) height / (int) zoom + (int) y)) {
		height = (d2_ClipBottom - (int) y) * zoom;
	}
	off = 0;
	row = 0;
	if ((int) y >= g_7725fc) {
		while (row < (int) height) {
			first = (row % (int) zoom) == 0;
			end = q;
			d = dst;
			if (*line > 0) {
				k = 0;
				do {
					r = (*q >> 1) + off;
					off = r % zoom;
					d += r / zoom;
					if (first) {
						src = q + 2;
						r = 0;
						n = (q[1] + off) / zoom;
						if (n > 0) {
							do {
								*d = *(unsigned short*) src;
								src = (unsigned int*) ((char*) src + zoom * 2);
								d++;
								r++;
							} while (r < (q[1] + off) / zoom);
						}
						off = (q[1] + off) % zoom;
					}
					k++;
					q = (unsigned int*) ((char*) q + q[1] * 2 + 8);
					end = q;
				} while (k < *line);
			}
			if (first) {
				dst += *(int*) (s + 0x10);
			}
			q = end + 1;
			line = end;
			row++;
		}
		return 1;
	}
	while (row < (int) height) {
		first = (row % (int) zoom) == 0;
		end = q;
		d = dst;
		if (*line > 0) {
			k = 0;
			do {
				r = off + (*q >> 1);
				off = r % zoom;
				d += r / zoom;
				if (first) {
					src = q + 2;
					r = 0;
					n = (q[1] + off) / zoom;
					if (n > 0) {
						do {
							if (g_7725fc <= (int) (row / (int) zoom + (int) y)) {
								*d = *(unsigned short*) src;
							}
							src = (unsigned int*) ((char*) src + zoom * 2);
							d++;
							r++;
						} while (r < (q[1] + off) / zoom);
					}
					off = (q[1] + off) % zoom;
				}
				k++;
				q = (unsigned int*) ((char*) q + q[1] * 2 + 8);
				end = q;
			} while (k < *line);
		}
		if (first) {
			dst += *(int*) (s + 0x10);
		}
		q = end + 1;
		line = end;
		row++;
	}

	return 1;
}
