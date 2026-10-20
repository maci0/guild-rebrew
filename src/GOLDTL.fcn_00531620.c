#include <string.h>

// SIZE 0x2c
typedef struct {
	float ox;
	float oy;
	float oz;
	int pad0c;
	float sx;
	float sy;
	float sz;
	int pad1c;
	int n;
	int* cells;
	unsigned char* data;
} Map_531620;

// SIZE 0x1c
typedef struct {
	int id;
	char pad4[0x18];
} Cell_531620;

extern int g_67a370;
extern char* g_7746c4;
extern unsigned char* g_7746c8;
extern char* g_7746cc;
extern int g_7746a0;
extern int g_7746b8;
extern int g_7746f0;
extern int g_7ea360;
extern char g_7e2760[];
extern char* g_7e4260[32];
extern char g_7f4ca0[];
extern int g_7e4300;
extern int g_7e4318;
extern int g_7e431c;
extern int g_6772c4;
extern int g_100f894;
extern unsigned short g_774970;
extern short g_14ce8c0;
extern short g_14ce8c2;
extern int g_14ce8cc;
extern int g_14ce8d4;
extern int g_14ce8e4;
extern int g_14ce8e0;
extern int g_6b8010;

void __cdecl fcn_00414c30(int, int);
void* __cdecl fcn_00426cc0(int);
int __cdecl fcn_00428720(char*);
int __cdecl fcn_00445600(char*, int, char*, char*);
char __cdecl fcn_0045bad0(int, int, int, int*, int*);
void __cdecl fcn_00473690(int, int);
void __cdecl fcn_004737c0(void);
void __cdecl fcn_004c35b0(void);
void __cdecl fcn_004c5b50(int, int, int, int);
void __cdecl fcn_004c5c80(int);
void __cdecl fcn_004c5f20(int, int, int);
int __cdecl fcn_00506380(int, unsigned char*, unsigned short*, int);
void __cdecl fcn_00529160(int, int, int, int);
void __cdecl fcn_0052ae70(void);
void __cdecl fcn_00531320(void);
int __cdecl fcn_00515540(char*);
int __cdecl fcn_005155e0(unsigned char*);
void __cdecl fcn_00534520(void);
void __cdecl fcn_005345a0(void);
int __cdecl fcn_0064d41a(char*, char*, ...);

/* ADDRESS: GOLDTL 0x00531620 */
void __cdecl fcn_00531620(void)
{
	Map_531620* map;
	char* ent;
	char* p;
	char* q;
	char* e;
	char* f;
	union {
		char buf[0x80];
		int offs[9][2];
	} u;
	int v16;
	int a;
	int b;
	int ix;
	int iy;
	int k;
	int idx;
	int c;
	int cell;
	int ei;
	int w;

	v16 = *(int*) ((char*) g_67a370 + 0xb0);
	map = (Map_531620*) v16;
	ent = 0;
	a = -1;
	b = -1;
	if (g_7746c4 != 0) {
		ent = g_7746c4;
	} else if (g_7746c8 != 0) {
		ent = (char*) g_7746c8;
	}
	if (g_14ce8d4 != 0) {
		goto L684;
	}
	if (g_7e4300 != 0) {
		fcn_004c35b0();
		fcn_005345a0();
		if (g_14ce8d4 != 0) {
			goto L684;
		}
	}
	goto L6d3;

L684:
	if (g_14ce8e4 == 0) {
		if (g_7e4300 == 0 && g_6772c4 != 0 && *(int*) 0x100f894 == -1
		    && ent != 0 && *(unsigned short*) (ent + 0x27) == g_774970) {
			fcn_00534520();
		}
		goto La5d;
	}

L6d3:
	if (g_7746f0 == 0) {
		goto La5d;
	}
	if (g_7746b8 != 0) {
		goto L192f;
	}
	if (g_7746a0 != 0) {
		goto La50;
	}
	if (g_7e431c != 0) {
		goto La50;
	}
	if (g_7e4318 != 0) {
		fcn_00531320();
		goto La5d;
	}
	if (v16 == 0 || ent == 0 || g_14ce8cc == 0 || *(int*) 0x100f894 != -1) {
		goto La5d;
	}
	for (p = g_7f4ca0; p < (char*) 0x85a0a0; p += 0x21c) {
		if (p[0x188] == 0) {
			continue;
		}
		if (p[8] == 0) {
			continue;
		}
		if ((fcn_00506380(g_774970, 0, 0, (int) p) & 0x800) == 0) {
			continue;
		}
		if (*(int*) (p + 0x184) == 0) {
			continue;
		}
		u.offs[0][0] = 0;
		u.offs[0][1] = 0;
		u.offs[1][0] = -1;
		u.offs[1][1] = 0;
		u.offs[2][0] = -1;
		u.offs[2][1] = -1;
		u.offs[3][0] = 0;
		u.offs[3][1] = -1;
		u.offs[4][0] = 1;
		u.offs[4][1] = -1;
		u.offs[5][0] = 1;
		u.offs[5][1] = 0;
		u.offs[6][0] = 1;
		u.offs[6][1] = 1;
		u.offs[7][0] = 0;
		u.offs[7][1] = 1;
		u.offs[8][0] = -1;
		u.offs[8][1] = 1;
		if (fcn_0045bad0(v16, g_14ce8c0, g_14ce8c2, &b, &a) == 0) {
			continue;
		}
		cell = 0;
		for (k = 0;; ) {
			ix = (int) (u.offs[k][0] * (50.0 / map->sx) + b);
			iy = (int) (u.offs[k][1] * (50.0 / map->sz) + a);
			if (ix < map->n && iy < map->n) {
				cell = ((Cell_531620*) map->cells)[map->n * iy + ix].id;
			}
			k++;
			if (k >= 8) {
				ix = b;
				iy = a;
				break;
			}
			if (ix < 0 || ix >= map->n || iy < 0 || iy >= map->n
			    || cell == 0 || cell == 0xd) {
				continue;
			}
			break;
		}
		if (*(int*) (p + 0x16c) != 0) {
			fcn_00529160(*(int*) (p + 0x16c), 0, *(unsigned short*) p, 0);
		}
		f = (char*) (*(int*) (p + 0x184));
		w = *(int*) (f + 0x28);
		if (w != -1) {
			f = (char*) fcn_00426cc0(w);
			if (f != 0) {
				fcn_00428720(f);
			}
		}
		fcn_004c5b50(*(int*) (p + 4), ix, iy, g_6b8010);
	}
	if (g_7746b8 == 0) {
		goto La50;
	}

L192f:
	if (v16 == 0 || g_14ce8cc == 0 || *(int*) 0x100f894 != -1) {
		goto La50;
	}
	fcn_0064d41a(u.buf, (char*) 0x68143c, (char*) g_7746a0 + 8);
	if (fcn_00445600((char*) g_7746a0, 0x100, 0, u.buf) == 0) {
		strcpy(u.buf, (char*) g_7746a0);
	}
	ei = -1;
	for (idx = 0, q = (char*) 0x7e4260; q < (char*) 0x7e42e0; q += 4, idx++) {
		e = *(char**) q;
		if (e == 0) {
			continue;
		}
		if (e[0x188] == 0) {
			continue;
		}
		fcn_004c5c80(*(int*) (e + 4));
		if (*(int*) (e + 0x16c) != 0) {
			fcn_00529160(*(int*) (e + 0x16c), 0, *(unsigned short*) e, 0);
		}
		if (*(unsigned short*) g_7746b8 == 0xfd) {
			if (g_7746c8 != 0) {
				ei = fcn_005155e0(g_7746c8);
			} else if (g_7746c4 != 0) {
				ei = 0;
				p = g_7746c4;
				goto L1a0d;
			} else {
				goto L1a0d;
			}
		} else {
			ei = fcn_00515540((char*) g_7746b8);
		}
		if (g_7746c8 != 0) {
			p = (char*) g_7746c8;
		} else if (g_7746c4 != 0) {
			p = g_7746c4;
		}
L1a0d:
		if (ei >= 0) {
			fcn_004c5f20(*(int*) (e + 4), *(int*) (p + 1), *(int*) ((char*) g_7746b8 + 2));
		}
	}
	fcn_0052ae70();
	g_7746b8 = 0;

La50:
	if (g_7e4318 != 0) {
		fcn_00531320();
	}

La5d:
	g_7746f0 = 0;
	fcn_004737c0();
	c = 0;
	for (idx = 0, q = (char*) 0x7f4e24; q < (char*) 0x85a224; q += 0x21c, idx++) {
		e = *(char**) q;
		if (e != 0) {
			c = q[4];
			if (c != g_7e2760[idx] && (*(unsigned char*) (e + 0x8c) & 0x40) == 0) {
				if (c == 0) {
					fcn_00414c30(*(int*) (e + 0x34), 0);
				} else {
					fcn_00414c30(*(int*) (e + 0x34), 1);
				}
			}
			if (c != 0) {
				if (g_7746f0 == 0) {
					g_7ea360 = (int) (q - 0x184);
				}
				g_7746f0 = g_7746f0 + 1;
				f = *(char**) (q - 0x18);
				if (f != 0 && *(int*) (f + 1) == *(int*) (e + 0x2c)
				    && !(g_7746c8 == 0
				         && (g_7746cc == 0 || *(unsigned short*) g_7746cc == 0x120))) {
					fcn_00473690(*(int*) (q + 8), 1);
				}
			}
		}
		g_7e2760[idx] = c;
	}
	if (g_14ce8e0 != 0 && g_7746f0 != 0) {
		fcn_0052ae70();
	}
}
