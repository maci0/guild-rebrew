unsigned int __cdecl fcn_004789e0(int x, unsigned int y, char* s, unsigned short* spr, unsigned int zoom)
{
	unsigned short* dst;
	unsigned int* line;
	unsigned int* q;
	unsigned int* end;
	unsigned int v2;
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

	h = *(unsigned short*) ((char*) spr + 6);
	v2 = *(unsigned short*) ((char*) spr + 0xa);
	line = (unsigned int*) ((char*) spr + 0x32);
	q = (unsigned int*) ((char*) spr + 0x36);
	dst = (unsigned short*) (*(int*) (s + 0x1c)
	 + (*(int*) (s + 0x10) * (int) y + x) * 2);
	if ((int) (v2 + y) < *(int*) 0x7725fc) {
		return 0;
	}
	if (*(int*) 0x67d964 < (int) ((int) h / (int) zoom) + x) {
		return 0;
	}
	if ((int) (h + x) < *(int*) 0x7725f8) {
		return 0;
	}
	if (*(int*) 0x67d968 < (int) ((int) (v2 / zoom) + (int) y)) {
		v2 = (*(int*) 0x67d968 - (int) y) * zoom;
	}
	off = 0;
	row = 0;
	if ((int) y < *(int*) 0x7725fc) {
		while ((int) v2 > 0) {
			first = (row % (int) zoom) == 0;
			end = q;
			d = dst;
			if (*line) {
				k = 0;
				do {
					r = off + (*q >> 1);
					off = r % zoom;
					d += r / zoom;
					if (first) {
						src = q + 2;
						r = 0;
						n = (q[1] + off) / zoom;
						if (n) {
							do {
								if (*(int*) 0x7725fc <= (int) (row / (int) zoom + (int) y)) {
									*d = *(unsigned short*) src;
								}
								src = (unsigned int*) ((char*) src + zoom * 2);
								d++;
								r++;
							} while (r < n);
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
			row++;
			line = end;
		}
		return 1;
	}
	while ((int) v2 > 0) {
		first = (row % (int) zoom) == 0;
		end = q;
		d = dst;
		if (*line) {
			k = 0;
			do {
				r = (*q >> 1) + off;
				off = r % zoom;
				d += r / zoom;
				if (first) {
					src = q + 2;
					r = 0;
					n = (q[1] + off) / zoom;
					if (n) {
						do {
							*d = *(unsigned short*) src;
							src = (unsigned int*) ((char*) src + zoom * 2);
							d++;
							r++;
						} while (r < n);
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
		row++;
		line = end;
	}
	return 1;
}
