#include "Develop/DieGildeAddOn/game/game_data.h"

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x0047b340 */
int __cdecl d2_DrawScaledRleSprite(int x, int y, int* surface, char* sprite, int factor)
{
	unsigned int* line_count;
	unsigned int* run;
	unsigned short* row_output;
	unsigned short* output;
	unsigned short* pixels;
	unsigned int carry;
	unsigned int n;
	unsigned int i;
	int height, clipped_height;
	int width;
	int divisor;
	int row;
	int emit;
	int screen_y;
	line_count = (unsigned int*) (sprite + 0x32);
	run = (unsigned int*) (sprite + 0x36);
	row_output = (unsigned short*) surface[7] + surface[4] * y + x;
	height = *(unsigned short*) (sprite + 0xa);
	if (height + y < *(int*) 0x6f045c) {
		return 0;
	}
	divisor = factor & 0xff;
	width = *(unsigned short*) (sprite + 6);
	if (width / divisor + x > *(int*) 0x5fed5c) {
		return 0;
	}
	if (width + x < *(int*) 0x6f0458) {
		return 0;
	}
	if (height / divisor + y > *(int*) 0x5fed60) {
		clipped_height = (*(int*) 0x5fed60 - y) * divisor;
	} else { clipped_height = height; }
	carry = 0;
	if (y >= *(int*) 0x6f045c) {
		for (row = 0; row < clipped_height; row++) {
			emit = row % divisor == 0;
			output = row_output;
			for (i = 0; i < *line_count; i++) {
				output += ((run[0] >> 1) + carry) / (unsigned int) divisor;
				carry = (run[0] >> ((carry + 1) & 0x1f)) % (unsigned int) divisor;
				if (emit) {
					pixels = (unsigned short*) (run + 2);
					for (n = 0; n < (run[1] + carry) / (unsigned int) divisor; n++) {
						*output = *pixels;
						pixels += divisor;
						output++;
					}
					carry = (run[1] + carry) % (unsigned int) divisor;
				}
				run = (unsigned int*) ((char*) run + run[1] * 2 + 8);
			}
			if (emit) {
				row_output += surface[4];
			}
			line_count = run;
			run++;
		}
	} else {
		for (row = 0; row < clipped_height; row++) {
			emit = row % divisor == 0;
			output = row_output;
			for (i = 0; i < *line_count; i++) {
				output += ((run[0] >> 1) + carry) / (unsigned int) divisor;
				carry = (run[0] >> ((carry + 1) & 0x1f)) % (unsigned int) divisor;
				if (emit) {
					pixels = (unsigned short*) (run + 2);
					for (n = 0; n < (run[1] + carry) / (unsigned int) divisor; n++) {
						screen_y = row / divisor + y;
						if (screen_y >= *(int*) 0x6f045c) {
							*output = *pixels;
						}
						pixels += divisor;
						output++;
					}
					carry = (run[1] + carry) % (unsigned int) divisor;
				}
				run = (unsigned int*) ((char*) run + run[1] * 2 + 8);
			}
			if (emit) {
				row_output += surface[4];
			}
			line_count = run;
			run++;
		}
	}
	return 1;
}
#else
/* ADDRESS: GOLDTL 0x004789e0 */
unsigned int __cdecl d2_DrawScaledRleSprite(int x, unsigned int y, char* s, unsigned short* spr, unsigned int zoom)
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
#endif
