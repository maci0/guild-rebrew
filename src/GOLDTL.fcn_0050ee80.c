typedef struct {
	int x0;
	int x4;
	int x8;
	unsigned short xc;
	unsigned short pad_e;
	int x10;
	int x14;
	int pad18;
	int x1c;
	int x20;
	int x24;
	int x28;
	int x2c;
	unsigned char x30;
	unsigned char pad31[3];
} Rec_7f3f00;

extern Rec_7f3f00 g_7f3f00[];

int __cdecl fcn_00502cd0(int, int, ...);
char* __cdecl fcn_005463a0(int, int, int, int, int);
char* __cdecl fcn_005462a0(void);
int __cdecl fcn_0046f100(int, int, int, int, int, int);
int __cdecl fcn_0046f740(int, int, int, int);
int __cdecl fcn_0046f280(int);
int __cdecl fcn_00519190();
int __cdecl fcn_00500d20(void*, void*);

/* ADDRESS: GOLDTL 0x0050ee80 */
void __cdecl fcn_0050ee80(unsigned char* a, unsigned short* b)
{
	Rec_7f3f00* p;
	char* q;
	int i;
	int st;
	int n;
	int found;
	int v1;
	int v2;
	int h;
	int y;
	int k;

	i = 0;
	v1 = *(int*) (0x1038150 + *(int*) 0x7f4c10 * 0x2bc);
	for (; i < *(int*) 0x85ab60; i++) {
		st = 0;
		if (*(unsigned char*) (*(int*) 0x99ec10 + g_7f3f00[i].x0 * 0x40 + g_7f3f00[i].x0) == 6) {
			if (fcn_00502cd0(*(int*) (a + 0x5d), 1, 0, g_7f3f00[i].x0) != 0) {
				st = 1;
				for (q = fcn_005463a0(2, 0, 0xc, 3, *(int*) (a + 1)); q != 0;
				     q = fcn_005462a0()) {
					if (*(int*) (q + 0xb4) == g_7f3f00[i].x0) {
						st = 3;
						break;
					}
				}
			} else {
				n = 0;
				if (i > 0) {
					p = g_7f3f00;
					for (k = i; k != 0; p++, k--) {
						if (p->x0 == g_7f3f00[i].x4 &&
						    (fcn_00502cd0(*(int*) (a + 0x5d), 1, 0, p->x0) != 0 ||
						     fcn_00502cd0(*(int*) ((char*) b + 0x14), 1, 0, p->x0) != 0) &&
						    *(int*) (*(int*) 0x1015ea0 + p->x24 * 0x2f4 + 0x60) == 0) {
							n++;
						} else if (p->x0 == g_7f3f00[i].x8 &&
							   (fcn_00502cd0(*(int*) (a + 0x5d), 1, 0, p->x0) != 0 ||
							    fcn_00502cd0(*(int*) ((char*) b + 0x14), 1, 0, p->x0) != 0) &&
							   *(int*) (*(int*) 0x1015ea0 + p->x24 * 0x2f4 + 0x60) == 0) {
							n++;
						}
					}
				}
				if ((n == 0 && g_7f3f00[i].x4 == 0) ||
				    (n == 1 && g_7f3f00[i].x8 == 0) ||
				    n == 2) {
					st = 2;
				}
			}
		} else {
			if (fcn_00502cd0(*(int*) ((char*) b + 0x14), 1, 0, g_7f3f00[i].x0) != 0) {
				st = 1;
			} else if (*(unsigned short*) b != 0xfd ||
				   fcn_00502cd0(*(int*) (a + 0x5d), 1, 0, g_7f3f00[i].x0) == 0) {
				found = 0;
				if (i > 0) {
					p = g_7f3f00;
					for (k = i; k != 0; p++, k--) {
						if (p->x0 == g_7f3f00[i].x4 &&
						    (fcn_00502cd0(*(int*) (a + 0x5d), 1, 0, p->x0) != 0 ||
						     fcn_00502cd0(*(int*) ((char*) b + 0x14), 1, 0, p->x0) != 0)) {
							found++;
						} else if (p->x0 == g_7f3f00[i].x8 &&
							   (fcn_00502cd0(*(int*) (a + 0x5d), 1, 0, p->x0) != 0 ||
							    fcn_00502cd0(*(int*) ((char*) b + 0x14), 1, 0, p->x0) != 0)) {
							found++;
						}
					}
				}
				if ((found == 0 && g_7f3f00[i].x4 == 0) ||
				    (found == 1 && g_7f3f00[i].x8 == 0) ||
				    found == 2) {
					st = 2;
					for (q = fcn_005463a0(2, 0, 2, 3, *(int*) (a + 1)); q != 0;
					     q = fcn_005462a0()) {
						if (*(int*) (q + 0xb0) == *(int*) ((char*) b + 2) &&
						    *(unsigned short*) (q + 0xac) == g_7f3f00[i].x0) {
							st = 3;
							break;
						}
					}
				}
			} else {
				st = 1;
			}
		}
		if (st != g_7f3f00[i].x30) {
			if (g_7f3f00[i].x1c != -1) {
				fcn_0046f280(g_7f3f00[i].x1c);
				g_7f3f00[i].x1c = -1;
				g_7f3f00[i].x20 = -1;
				g_7f3f00[i].x24 = -1;
				g_7f3f00[i].x28 = -1;
			}
			if (g_7f3f00[i].x2c != -1) {
				fcn_0046f280(g_7f3f00[i].x2c);
				g_7f3f00[i].x2c = -1;
			}
			h = *(int*) 0x772514;
			if (st == 0) {
				v2 = fcn_0046f100(g_7f3f00[i].x10 - 4, g_7f3f00[i].x14 - 4, 0x36, 0x36, 0x400, v1);
				g_7f3f00[i].x1c = v2;
				g_7f3f00[i].x20 = fcn_0046f740(0, 0, 0x52b, v2);
				g_7f3f00[i].x24 = fcn_0046f740(3, 3, 0x4fb, g_7f3f00[i].x1c);
			} else if (st == 1) {
				v2 = fcn_0046f100(g_7f3f00[i].x10 - 4, g_7f3f00[i].x14 - 4, 0x36, 0x36, 0x400, v1);
				g_7f3f00[i].x1c = v2;
				g_7f3f00[i].x20 = fcn_0046f740(0, 0, 0x529, v2);
				if (g_7f3f00[i].x0 < 0x2dc) {
					y = g_7f3f00[i].x0 + 0xdf;
				} else {
					y = 0xdf;
				}
				g_7f3f00[i].x24 = fcn_0046f740(3, 3, y, g_7f3f00[i].x1c);
				*(int*) (*(int*) 0x1015ea0 + g_7f3f00[i].x24 * 0x2f4 + 0x64) = 1;
				*(int*) (*(int*) 0x1015ea0 + g_7f3f00[i].x24 * 0x2f4 + 0x5c) = 1;
				*(int*) 0x772514 = h;
				v2 = fcn_0046f100(g_7f3f00[i].x10 - 0x18, g_7f3f00[i].x14 + 0x32, 0x60, 0x11, 0x4510, v1);
				g_7f3f00[i].x2c = v2;
				*(int*) (0x1015f40 + v2 * 0x3cc + 0x28c) = 0x54;
				*(int*) (0x1015f40 + v2 * 0x3cc + 0x20) = 1;
				*(int*) (0x1015f40 + v2 * 0x3cc + 0x24) = 1;
				if (g_7f3f00[i].x0 < 0x2dc) {
					fcn_00519190(g_7f3f00[i].x0 * 2 + 0x9a8);
				}
			} else if (st == 2) {
				v2 = fcn_0046f100(g_7f3f00[i].x10 - 4, g_7f3f00[i].x14 - 4, 0x36, 0x36, 0x400, v1);
				g_7f3f00[i].x1c = v2;
				g_7f3f00[i].x20 = fcn_0046f740(0, 0, 0x52a, v2);
				if (g_7f3f00[i].x0 < 0x2dc) {
					y = g_7f3f00[i].x0 + 0xdf;
				} else {
					y = 0xdf;
				}
				g_7f3f00[i].x24 = fcn_0046f740(3, 3, y, g_7f3f00[i].x1c);
				*(int*) (*(int*) 0x1015ea0 + g_7f3f00[i].x24 * 0x2f4 + 0x5c) = 1;
				*(int*) 0x772514 = h;
				v2 = fcn_0046f100(g_7f3f00[i].x10 - 0x18, g_7f3f00[i].x14 + 0x32, 0x60, 0x11, 0x4510, v1);
				g_7f3f00[i].x2c = v2;
				*(int*) (0x1015f40 + v2 * 0x3cc + 0x28c) = 0x54;
				*(int*) (0x1015f40 + v2 * 0x3cc + 0x20) = 1;
				*(int*) (0x1015f40 + v2 * 0x3cc + 0x24) = 1;
				if (g_7f3f00[i].x0 < 0x2dc) {
					fcn_00519190(g_7f3f00[i].x0 * 2 + 0x9a8);
				}
				*(int*) (*(int*) 0x1015ea0 + g_7f3f00[i].x24 * 0x2f4 + 0x64) = 1;
			} else {
				v2 = fcn_0046f100(g_7f3f00[i].x10 - 4, g_7f3f00[i].x14 - 4, 0x36, 0x36, 0x400, v1);
				g_7f3f00[i].x1c = v2;
				g_7f3f00[i].x20 = fcn_0046f740(0, 0, 0x529, v2);
				if (g_7f3f00[i].x0 < 0x2dc) {
					y = g_7f3f00[i].x0 + 0xdf;
				} else {
					y = 0xdf;
				}
				g_7f3f00[i].x24 = fcn_0046f740(3, 3, y, g_7f3f00[i].x1c);
				g_7f3f00[i].x28 = fcn_0046f740(3, 3, 0x4fc, g_7f3f00[i].x1c);
				*(int*) 0x772514 = h;
				v2 = fcn_0046f100(g_7f3f00[i].x10 - 0x18, g_7f3f00[i].x14 + 0x32, 0x60, 0x11, 0x4510, v1);
				g_7f3f00[i].x2c = v2;
				*(int*) (0x1015f40 + v2 * 0x3cc + 0x28c) = 0x54;
				*(int*) (0x1015f40 + v2 * 0x3cc + 0x20) = 1;
				*(int*) (0x1015f40 + v2 * 0x3cc + 0x24) = 1;
				if (g_7f3f00[i].x0 < 0x2dc) {
					fcn_00519190(g_7f3f00[i].x0 * 2 + 0x9a8);
				}
				*(int*) (*(int*) 0x1015ea0 + g_7f3f00[i].x24 * 0x2f4 + 0x64) = 1;
			}
			*(int*) 0x772514 = h;
			g_7f3f00[i].x30 = st;
		}
		if (g_7f3f00[i].x30 == 3) {
			if (*(unsigned char*) (*(int*) 0x99ec10 + g_7f3f00[i].x0 * 0x40 + g_7f3f00[i].x0) == 6) {
				if (fcn_00502cd0(*(int*) (a + 0x5d), 1, 0, g_7f3f00[i].x0) != 0) {
					for (q = fcn_005463a0(2, 0, 0xc, 3, *(int*) (a + 1)); q != 0;
					     q = fcn_005462a0()) {
						if (*(int*) (q + 0xb4) == g_7f3f00[i].x0) {
							goto fnd;
						}
					}
				}
			} else {
				for (q = fcn_005463a0(2, 0, 2, 3, *(int*) (a + 1)); q != 0;
				     q = fcn_005462a0()) {
					if (*(int*) (q + 0xb0) == *(int*) ((char*) b + 2) &&
					    *(unsigned short*) (q + 0xac) == g_7f3f00[i].x0) {
						goto fnd;
					}
				}
			}
			*(int*) (*(int*) 0x1015ea0 + g_7f3f00[i].x24 * 0x2f4 + 0x1f4) = 0;
			goto next;
fnd:
			*(float*) (*(int*) 0x1015ea0 + g_7f3f00[i].x24 * 0x2f4 + 0x1f4) =
				(float) fcn_00500d20(q + 0x44, (void*) 0x7f4c00) /
				(float) fcn_00500d20(q + 0x44, q + 0x52);
next:			;
		}
	}
}
