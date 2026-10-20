extern int g_100f888;
extern char* g_1015ea0;
extern char g_1043370[];
extern int g_14ce8e8;
extern char g_14cf7c8;
extern char g_14cf7cb;
extern char g_14cf7cd;
extern char g_14cf7d0;
extern int g_67d370;
extern int g_6a99e8;
extern int g_6ab3dc;
extern int g_6b7fac;
extern int g_772514;
extern char* g_77255c;
extern unsigned char g_773d75;
extern int g_778d20;
extern int g_778d24;
extern char g_7f4ca0[];

int __cdecl fcn_005b0f00(char*);
int __cdecl fcn_005b10e0(char*);
void __cdecl fcn_005918f0(char*);
void __cdecl fcn_00455350(char*, char*, float*);
int __cdecl fcn_00469c30(int, int, int);
void __cdecl fcn_00469c40(int, int, int);
void __cdecl fcn_0046b2b0(int);
void __cdecl fcn_0046ed00(int, int, int);
char* __cdecl fcn_0050d490(char*);

/* ADDRESS: GOLDTL 0x005b11f0 */
void __cdecl fcn_005b11f0(int* a0)
{
	char* view;
	char* t;
	char* e;
	char* p;
	float pos[4];
	float x;
	float y;
	float q;
	int i;
	int n;
	int ox;
	int oy;
	int id;
	int sx;
	int sy;
	int* slot;
	int* list;
	int obj;
	unsigned char kind;

	view = *(char**) g_1043370;
	ox = *(int*) (g_773d75 * 0x2f4 + 0x86834c);
	oy = *(int*) (g_773d75 * 0x2f4 + 0x868350);
	g_772514 = a0[2];
	g_77255c = (char*) (a0[2] * 0x3cc + 0x1015f40);
	if (g_6ab3dc) {
		a0[0x9e7] = 0;
		a0[0x9e7] = fcn_005b0f00((char*) (a0[2] * 0x3cc + 0x1015f40));
		a0[0x9e7] |= fcn_005b10e0((char*) (a0[2] * 0x3cc + 0x1015f40));
		if (a0[0x9e7] != 0) {
			a0[0x9e8] = g_6b7fac;
		}
	}
	if (g_100f888 != -1 && (unsigned int) (a0[0x9e8] + 0x4b) < (unsigned int) g_6b7fac
	    && g_14ce8e8 && g_6a99e8 == -1 && a0[0x9e9] >= 1) {
		n = 0;
		p = (char*) (a0 + 0x38);
		i = g_67d370;
		do {
			if (i != -1 && i == *(int*) (p - 4)) {
				id = *(unsigned short*) (*(int*) p + 0x27);
				if (id != 0xffff
				    && *(unsigned char*) (id * 0x2f4 + 0x7f4ca2) < 10) {
					fcn_005918f0((char*) (id * 0x2f4 + 0x7f4ca0));
					i = g_67d370;
				}
			}
			n += 1;
			p += 6 * 4;
		} while (n < a0[0x9e9]);
	}
	g_772514 = a0[2];
	list = (int*) 0x14d0020;
	slot = a0 + 0x637;
	for (;;) {
		obj = *list;
		if (obj == 0) {
			goto next;
		}
		if (*(int*) (obj + 0x88) != 0x10432c0) {
			goto check;
		}
		e = *(char**) (obj + 0x34);
		fcn_00455350(e, e + 0x4c, pos);
		t = g_77255c;
		view = *(char**) g_1043370;
		x = (float) (((double) pos[0] - *(int*) t) / *(float*) (t + 0x10)
		    - *(int*) (view + 0x20) * 0.5);
		x = x * 5.33f;
		y = (float) (((double) pos[2] - *(int*) (t + 8)) / *(float*) (t + 0x18)
		    - *(int*) (view + 0x20) * 0.5);
		y = y * 5.33f;
		q = (float) ((double) fabs(x) / ((double) g_778d24 * 0.5));
		if (x < 0) {
			x = x - q * 51.0f;
		} else {
			x = q * 51.0f + x;
		}
		q = (float) ((double) fabs(y) / ((double) g_778d20 * 0.5));
		if (y < 0) {
			y = y - q * 51.0f;
		} else {
			y = q * 51.0f + y;
		}
		sx = (int) ((float) (g_778d24 / 2) + (float) ox + x);
		sy = (int) ((float) (g_778d20 / 2) + (float) oy + y);
		if (*slot == -1) {
			e = *(char**) (obj + 0x34);
			id = *(int*) (e + 0x204);
			if (*(int*) (e + 0x218) == 1 && *(int*) (obj + 0x124) == 0) {
				goto check;
			}
			if (id == 0) {
				goto check;
			}
			if (*(int*) (obj + 0x124) == 0) {
				if (*(int*) (id + 0x16c) == 0) {
					goto check;
				}
				id = *(unsigned short*) (*(int*) (id + 0x16c) + 0x27);
				if (id == 0xffff) {
					goto check;
				}
				kind = *(unsigned char*) (id * 0x2f4 + 0x7f4ca2);
				if (kind == 5 || kind == 6 || kind == 7) {
					n = fcn_00469c30(*(int*) (t + 4) + sx, *(int*) (t + 8) + sy,
					    *(int*) (id * 0x2f4 + 0x7f4cf4) - 0x53);
					*slot = n;
					if (n == -1) {
						goto next;
					}
					goto store;
				}
				goto check;
			}
			p = fcn_0050d490((char*) id);
			if (p == 0) {
				goto check;
			}
			kind = p[2];
			if (kind != 5 && kind != 6 && kind != 7) {
				goto check;
			}
			n = fcn_00469c30(*(int*) (t + 4) + sx, *(int*) (t + 8) + sy,
			    *(int*) (p + 0x54) - 0x53);
			*slot = n;
			if (n == -1) {
				goto next;
			}
		} else {
			e = *(char**) (obj + 0x34);
			if (*(int*) (e + 0x218) == 1 && *(int*) (obj + 0x124) == 0) {
				goto check;
			}
			fcn_00469c40(*(int*) (g_77255c + 4) - *(int*) (g_77255c + 0x268) + sx,
			    *(int*) (g_77255c + 8) - *(int*) (g_77255c + 0x258) + sy, *slot);
		}
store:
		n = *slot * 0x2f4;
		*(int*) (g_1015ea0 + 0x28 + n) = *(int*) (g_77255c + 4);
		*(int*) (g_1015ea0 + 0x2c + n) = *(int*) (g_77255c + 0xc)
		    + *(int*) (g_77255c + 4);
		*(int*) (g_1015ea0 + 0x30 + n) = *(int*) (g_77255c + 8);
		*(int*) (g_1015ea0 + 0x34 + n) = *(int*) (g_77255c + 0x10)
		    + *(int*) (g_77255c + 8);
		*(char**) (g_1015ea0 + 0x50 + n) = (char*) (a0[0] * 700 + 0x1038140);
check:
		if (*slot != -1
		    && (*(int*) (*(int*) (obj + 0x34) + 0x218) == 1
		        || *(int*) (obj + 0x88) != 0x10432c0)
		    && *(int*) (obj + 0x124) == 0) {
			fcn_0046b2b0(*slot);
			*slot = -1;
		}
next:
		slot += 1;
		list += 1;
		if (list >= (int*) 0x14d0c20) {
			break;
		}
	}
	if (*(char*) 0x14cf7c8) {
		fcn_0046ed00(0, -4, g_772514);
		return;
	}
	if (g_14cf7d0) {
		fcn_0046ed00(0, 4, g_772514);
		return;
	}
	if (g_14cf7cb) {
		fcn_0046ed00(-4, 0, g_772514);
		return;
	}
	if (g_14cf7cd) {
		fcn_0046ed00(4, 0, g_772514);
	}
}
