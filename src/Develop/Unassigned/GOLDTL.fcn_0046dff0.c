extern char* g_1015ea0;
extern char* g_772500;
extern int g_1040490;
extern int g_1040494;

void __cdecl fcn_0046c5a0(int, int);
void __cdecl fcn_0046c310(int);
void __cdecl fcn_0046dd60(int, int);
void __cdecl fcn_00472640(int, int);
void __cdecl fcn_0046f940(int, char*);
void __cdecl fcn_0047c560(int, int, int);
void __cdecl fcn_0047a040(int, int, int, int);
void __cdecl fcn_0047cba0(int, int, int, int, int);
int __cdecl d2_GetResourceData(int);
char* __cdecl itoa(int, char*, int);

/* Draw one window slot: sync the item states, size the frame, then blit the
 * border and the hatch pattern for the selected building. */
/* ADDRESS: GOLDTL 0x0046dff0 */
void __cdecl fcn_0046dff0(int a0, int a1)
{
	char* b;
	int saved;
	int n;
	int i;
	int id;
	int rec;
	int x;
	int y;
	int w;
	int h;
	int vert;
	int horiz;
	int step;
	int off;
	int count;
	int mode;
	int surf;
	char buf[32];

	b = (char*) (0x1015f40 + a0 * 0x3cc);
	if (!*(int*) (b + 0x290)) {
		return;
	}
	saved = *(int*) 0x772554;
	*(int*) 0x772554 = 1;
	n = *(int*) (b + 0x2c);
	if (n >= 1) {
		i = 0;
		do {
			id = *(int*) (*(int*) (b + 0x28) + i * 4);
			if (*(int*) (g_1015ea0 + 0x20 + id * 0x2f4) == 0x40) {
				rec = *(int*) (g_1015ea0 + id * 0x2f4 + 0x88);
				if (*(unsigned int*) (0x1015f54 + rec * 0x3cc) & 0x4000) {
					fcn_0046c5a0(0, rec);
				}
			}
			i++;
		} while (i < *(int*) (b + 0x2c));
	}
	if (*(unsigned int*) (b + 0x14) & 0x4000) {
		fcn_0046c5a0(0, a0);
	}
	rec = *(int*) (b + 0x274);
	if (rec) {
		if (rec % 8 == 0) {
			*(char*) (b + 0x270) = 8;
		} else if (rec % 6 == 0) {
			*(char*) (b + 0x270) = 6;
		} else if (rec % 4 == 0) {
			*(char*) (b + 0x270) = 4;
		} else if (rec % 2 == 0) {
			*(char*) (b + 0x270) = 2;
		}
	}
	*(int*) 0x772554 = saved;
	if (*(int*) (b + 0x3b8) != -1 || *(int*) (b + 0x3bc) != -1) {
		rec = *(int*) (b + 0x3bc);
		x = *(int*) (g_1015ea0 + 0x1f0 + rec * 0x2f4) * 0x3cc;
		if (rec != -1) {
			fcn_00472640(rec, *(int*) (x + 0x10161b4) + *(int*) (x + 0x1015f50) <= *(int*) (x + 0x1016194));
			fcn_00472640(rec, *(int*) (x + 0x10161a0) + *(int*) (x + 0x1016198) + *(int*) (x + 0x1015f50) < *(int*) (x + 0x1016194));
		}
		if (*(int*) (b + 0x3b8) != -1) {
			fcn_00472640(*(int*) (b + 0x3b8), *(int*) (x + 0x1016198) != 0);
		}
		if (*(int*) (b + 0x3c0) != -1) {
			itoa((int) ((float) *(int*) (x + 0x1016194) / (float) *(int*) (x + 0x10161b4) + 0.5f), buf, 10);
			fcn_0046f940(*(unsigned int*) (b + 0x3c0), buf);
		}
	}
	fcn_0046c310(a0);
	vert = a1;
	if (!*(int*) 0x772554) {
		if ((*(unsigned char*) (b + 0x14) & 1) || *(int*) (b + 0x3a0)) {
			fcn_0047c560(0, 0, 0);
		}
		fcn_0046dd60((int) b, vert);
	}
	if (*(unsigned char*) (b + 0x14) & 0x10) {
		fcn_0046c5a0(vert, a0);
	}
	fcn_0047a040(*(int*) (b + 4), *(int*) (b + 8), *(int*) (b + 0xc) + *(int*) (b + 4), *(int*) (b + 0x10) + *(int*) (b + 8));
	if ((*(unsigned char*) (b + 0x14) & 4) && !*(int*) 0x772554) {
		surf = d2_GetResourceData(*(unsigned int*) (b + 0x288));
		rec = *(int*) (b + 0x288);
		x = *(int*) (b + 4);
		y = *(int*) (b + 8);
		w = *(int*) (b + 0xc);
		h = *(int*) (b + 0x10);
		if (rec != 0x67d3a0 && rec != 0x67d3a4) {
			horiz = *(short*) (g_772500 + 0x50 + rec * 0x54);
			vert = *(short*) (g_772500 + 0x52 + rec * 0x54);
			fcn_0047cba0(x, y, a1, surf, 0);
			fcn_0047cba0(x - horiz + w, y, a1, surf, 1);
			fcn_0047cba0(x, y - vert + h, a1, surf, 2);
			fcn_0047cba0(x - horiz + w, y - vert + h, a1, surf, 3);
			step = *(short*) (g_772500 + 0x1a0 + rec * 0x54);
			h = *(short*) (g_772500 + 0x1a2 + rec * 0x54);
			count = (*(int*) (b + 0xc) - horiz * 2) / step;
			off = 0;
			i = 0;
			if (count >= 1) {
				do {
					fcn_0047cba0(x + off + horiz, y + 10, a1, surf, i % 4 + 4);
					fcn_0047cba0(x + off + horiz, (y - h) - 0xb + *(int*) (b + 0x10), a1, surf, i % 4 + 4);
					off += step;
					i++;
				} while (i < count);
			}
			step = *(short*) (g_772500 + 0x398 + rec * 0x54);
			vert = *(short*) (g_772500 + 0x39a + rec * 0x54);
			count = (*(int*) (b + 0x10) - horiz * 2) / vert;
			i = 0;
			if (count >= 1) {
				while (1) {
					if (i) {
						if (i != count - 1) {
							fcn_0047cba0(x + 10, y + step * i + horiz, a1, surf, i % 4 + 10);
							fcn_0047cba0((x - step) - 10 + *(int*) (b + 0xc), y + step * i + horiz, a1, surf, (i - 1) % 4 + 10);
						} else {
							fcn_0047cba0(x + 10, y + step * i + horiz, a1, surf, 9);
							fcn_0047cba0((x - step) - 10 + *(int*) (b + 0xc), y + step * i + horiz, a1, surf, 9);
						}
					} else {
						fcn_0047cba0(x + 10, y + horiz, a1, surf, 8);
						fcn_0047cba0((x - step) - 10 + *(int*) (b + 0xc), y + horiz, a1, surf, 8);
					}
					i++;
					if (i >= count) {
						break;
					}
				}
			}
		} else {
			fcn_0047cba0(x, y, a1, surf, 0);
			fcn_0047cba0(x - 8 + w, y, a1, surf, 1);
			fcn_0047cba0(x, y - 8 + h, a1, surf, 2);
			fcn_0047cba0(x - 8 + w, y - 8 + h, a1, surf, 3);
			count = (w - 0x10) >> 3;
			i = 0;
			if (count >= 1) {
				do {
					fcn_0047cba0(x + 8 + i * 8, y, a1, surf, 5);
					fcn_0047cba0(x + 8 + i * 8, y - 8 + h, a1, surf, 8);
					i++;
				} while (i < count);
			}
			count = (h - 0x10) >> 3;
			i = 0;
			if (count >= 1) {
				do {
					fcn_0047cba0(x, y + 8 + i * 8, a1, surf, 0xb);
					fcn_0047cba0(x - 8 + w, y + 8 + i * 8, a1, surf, 0xd);
					i++;
				} while (i < count);
			}
			if ((char) (*(unsigned int*) (b + 0x14) >> 8) < 0) {
				fcn_0047cba0(x - 2, y - 2, a1, surf, 0x10);
				fcn_0047cba0(x - 6 + w, y - 2, a1, surf, 0x10);
				fcn_0047cba0(x - 2, y - 6 + h, a1, surf, 0x10);
				fcn_0047cba0(x - 6 + w, y - 6 + h, a1, surf, 0x10);
			}
		}
	}
	if (*(int*) (b + 0x280)) {
		*(int*) (b + 0x280) = *(int*) (b + 0x280) - 1;
	}
	fcn_0047a040(0, 0, g_1040494, g_1040490);
}
