#include <string.h>

/* g_100d0c0: 0x58-byte object records.  The four dwords at +4 select the
 * building instances; +0x54 carries the state flags. */
#pragma pack(push, 1)
typedef struct Ord {
	int f0;               /* 0x00 */
	int bld[4];           /* 0x04 */
	int f14;              /* 0x14 */
	int f18;              /* 0x18 */
	int f1c;              /* 0x1c */
	int f20;              /* 0x20 */
	int f24;              /* 0x24 */
	int f28;              /* 0x28 */
	int f2c;              /* 0x2c */
	int f30;              /* 0x30 */
	int f34;              /* 0x34 */
	int f38;              /* 0x38 */
	int f3c;              /* 0x3c */
	int f40;              /* 0x40 */
	int f44;              /* 0x44 */
	int f48;              /* 0x48 */
	int f4c;              /* 0x4c */
	int f50;              /* 0x50 */
	int flags;            /* 0x54 */
} Ord;

/* g_100b0c0: 0x40-byte building instances. */
typedef struct Bld {
	int type;             /* 0x00 */
	int parent;           /* 0x04 */
	int owner;            /* 0x08 */
	int f0c;              /* 0x0c */
	int f10;              /* 0x10 */
	char pad14[0x14];
	int busy;             /* 0x28 */
	char pad2c[0x10];
	int flags;            /* 0x3c */
} Bld;

/* g_7f4ca0: 0x21c-byte map records. */
typedef struct Ent {
	unsigned short id;    /* 0x000 */
	unsigned char f2;     /* 0x002 */
	char pad3[5];
	unsigned char f8;     /* 0x008 */
	char pad9[0x15c];
	unsigned char f165;   /* 0x165 */
	char pad166[6];
	int f16c;             /* 0x16c */
	char pad170[0xc];
	char* host;           /* 0x17c */
	char pad180[4];
	int f184;             /* 0x184 */
	char pad188[0x94];
} Ent;

/* g_868050: 0x24d-byte level records. */
typedef struct Lvl {
	unsigned char kind;   /* 0x000 */
	char pad1[0x246];
	unsigned char level;  /* 0x247 */
	char pad248[5];
} Lvl;

/* g_item_def_table: 0x41-byte item definitions. */
typedef struct ItemDef {
	unsigned char kind;   /* 0x00 */
	char pad1[0x25];
	unsigned short f26;   /* 0x26 */
	char pad28[0xe];
	unsigned short f36;   /* 0x36 */
	char pad38[9];
} ItemDef;

/* Scheduler state handed to fcn_00487f90. */
typedef struct Msg {
	int kind;             /* 0x00 */
	char* self;           /* 0x04 */
	char* rec;            /* 0x08 */
	char* p0c;            /* 0x0c */
	char* p10;            /* 0x10 */
	int want;             /* 0x14 */
	int avail;            /* 0x18 */
	int sent;             /* 0x1c */
	int total;            /* 0x20 */
} Msg;
#pragma pack(pop)

extern Ord g_100d0c0[];
extern Bld g_100b0c0[];
extern Ent g_7f4ca0[];
extern char g_868050[];
extern char* g_item_def_table;
extern char g_7f4ca4[];
extern char g_7f4c00[];
extern int g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern int g_100b0ac;
extern int g_100b0a8;

char* __cdecl fcn_00502cd0(int, int, int, ...);
char* __cdecl fcn_00502850(void);
char* __cdecl fcn_005463a0(int, int, int, int, int);
char* __cdecl find_zone_record(int);
void* __cdecl fcn_00503d10(int);
void __cdecl fcn_004849b0(char*, char*, char*);
int __cdecl fcn_00486640(char*, int*, int);
void __cdecl fcn_004868d0(char*, int*);
void __cdecl fcn_00487000(char*);
void __cdecl fcn_00484740(char*);
void __cdecl fcn_00487970(char*, char*, int);
void __cdecl fcn_00487c00(char*, char*, int);
void __cdecl fcn_00487e60(char*, int);
void __cdecl fcn_00487f90(int*);
void __cdecl fcn_00489250(char*);
void __cdecl fcn_00489a70(char*, char*);
void __cdecl fcn_0047e220(char*);
void __cdecl fcn_004c5530(char*);
void __cdecl fcn_00529160(char*, int, int, int);
void __cdecl fcn_004c5aa0(int, int, int, int, int, int);
void* __cdecl fcn_0050e000(char*, int, int);
int __cdecl fcn_005155e0(char*);
int __cdecl fcn_005b1e40(int);
int __cdecl plt_CheckZoneAvailability(int, int, int, int);
int __cdecl gm_RandomMod(int);
int __cdecl fcn_0064d470(char*, char*);

/* ADDRESS: GOLDTL 0x0047f6b0 */
int __cdecl fcn_0047f6b0(char* a)
{
	char m[0xf8];
	Msg st;
	char* t1;
	int* p2;
	int i;
	char* t3;
	int t;
	int flag;
	char* h;
	char* q;
	int j;
	int n;
	int v;
	char* t2;

	t1 = fcn_00502cd0(*(int*) (*(char**) (a + 0x16c) + 0x5d), 2, 6, 0, 0xff);
	if (t1 == 0) {
		return 0;
	}
	t2 = fcn_00502cd0(*(int*) (*(char**) (a + 0x16c) + 0x5d), 2, 6, 0, 0x2a);
	if (t2 == 0) {
		return 0;
	}
	t3 = fcn_00502cd0(*(int*) (*(char**) (a + 0x16c) + 0x5d), 1, 0, 0xfe);
	if (t3 == 0) {
		return 0;
	}
	fcn_004849b0(a, t1, t2);

	if (g_100b0ac > 0) {
		p2 = (int*) &g_100d0c0[0].bld[0];
		for (n = g_100b0ac; n != 0; n--) {
			q = (char*) p2;
			for (i = 4; i != 0; i--) {
				if (*(int*) q >= 0 && g_100b0c0[*(int*) q].parent >= 0) {
					g_100d0c0[g_100b0c0[*(int*) q].parent].flags |= 4;
					for (j = 0; j < g_100b0a8; j++) {
						if (g_100d0c0[g_100b0c0[*(int*) q].parent].f0
						    == g_100b0c0[j].type) {
							g_100b0c0[j].flags |= 4;
						}
					}
				}
				q += 4;
			}
			p2 += 0x16;
		}
	}

	h = *(char**) (a + 0x16c);
	fcn_00487000(a);
	fcn_00487970(t2, a, 0xa);
	fcn_00487c00(t2, a, 0x19);
	fcn_00484740(a);
	q = 0;
	if ((*(unsigned char*) (a + 0x1c8) & 0x10) == 0) {
		if (((Lvl*) g_868050)[*(unsigned char*) h].kind != 0xb) {
			q = fcn_00502cd0(*(int*) (t1 + 0x14), 1, 4, 0x17);
			if (q == 0) {
				*(int*) (a + 0x1c8) |= 0x10;
			} else {
				while (*(int*) (q + 0xe) != 1) {
					q = fcn_00502850();
					if (q == 0) {
						break;
					}
				}
				if (q == 0) {
					*(int*) (a + 0x1c8) |= 0x10;
				} else {
					memset(m, 0, sizeof(m));
					m[4] = 9;
					*(int*) (m + 8) = *(int*) (g_7f4ca4 +
					                           *(unsigned short*) (h + 0x27) * 0x21c);
					*(int*) (m + 0xc) = *(int*) (h + 1);
					*(int*) (m + 0x10) = 0;
					*(int*) (m + 0x14) = 0;
					*(int*) (m + 0x28) = *(int*) &g_7f4c00;
					*(int*) (m + 0x2c) = g_7f4c04;
					*(int*) (m + 0x30) = g_7f4c08;
					*(short*) (m + 0x34) = g_7f4c0c;
					m[0x36] = 1;
					*(int*) (m + 0x58) = *(int*) (h + 1);
					*(int*) (m + 0x5c) = *(int*) (t1 + 2);
					*(int*) (m + 0x60) = *(int*) (t3 + 2);
					fcn_004c5530(m);
					*(int*) (a + 0x1c8) |= 0x10;
				}
			}
		}
	}

	flag = 0;
	q = fcn_005463a0(2, 0, 9, 3, *(int*) (h + 1));
	if (q != 0) {
		if (*(int*) (a + 0x17c) != (int) q) {
			fcn_00529160(h, 0, *(unsigned short*) a, (int) q);
		}
		flag = 1;
	}
	if (g_7f4ca0[*(unsigned short*) (h + 0x27)].f2 == 6 && q != 0) {
		v = fcn_005b1e40((int) h);
		for (i = 0; i < 0x20; i++) {
			if (g_100d0c0[i].f0 == v) {
				goto found;
			}
		}
	}
	goto scan;

found:
	if ((int) *(unsigned char*) (t2 + 0x1c) < g_100d0c0[i].f1c) {
		goto scan;
	}
	if ((int) *(unsigned char*) (t2 + 0x1d) < g_100d0c0[i].f20) {
		goto scan;
	}
	if (g_100d0c0[i].f40 < (int) ((ItemDef*) g_item_def_table)[g_100d0c0[i].f0].f36) {
		goto scan;
	}
	v = (int) fcn_00503d10(g_100d0c0[i].f0);
	if (v == 0) {
		goto scan;
	}
	t = (int) fcn_0050e000((char*) v, g_100d0c0[i].f0, 0xf4240);
	if (t < (int) ((ItemDef*) g_item_def_table)[g_100d0c0[i].f0].f36 + g_100d0c0[i].f3c) {
		goto scan;
	}
	if (((ItemDef*) g_item_def_table)[g_100d0c0[i].f0].kind == 0x17) {
		q = fcn_00502cd0(*(int*) (t3 + 0x14), 1, 0, g_100d0c0[i].f0);
		if (q == 0) {
			goto scan;
		}
		if (*(int*) (q + 0xe) < (int) ((ItemDef*) g_item_def_table)[g_100d0c0[i].f0].f36) {
			goto scan;
		}
		g_100d0c0[i].flags |= 8;
		fcn_004868d0(a, (int*) &g_100d0c0[i]);
	} else if (fcn_00486640(a, (int*) &g_100d0c0[i], 1)) {
		g_100d0c0[i].flags |= 8;
		fcn_004868d0(a, (int*) &g_100d0c0[i]);
	} else if (fcn_00486640(a, (int*) &g_100d0c0[i], 0)) {
		fcn_004868d0(a, (int*) &g_100d0c0[i]);
	} else {
		goto scan;
	}
	goto after;

scan:
	for (i = 0; i < g_100b0ac; i++) {
		if (g_100d0c0[i].flags & 4) {
			continue;
		}
		if ((int) *(unsigned char*) (t2 + 0x1c) < g_100d0c0[i].f1c) {
			continue;
		}
		if ((int) *(unsigned char*) (t2 + 0x1d) < g_100d0c0[i].f20) {
			continue;
		}
		if (g_100d0c0[i].f40 < (int) ((ItemDef*) g_item_def_table)[g_100d0c0[i].f0].f36) {
			continue;
		}
		v = (int) fcn_00503d10(g_100d0c0[i].f0);
		if (v == 0) {
			continue;
		}
		t = (int) fcn_0050e000((char*) v, g_100d0c0[i].f0, 0xf4240);
		if (t < (int) ((ItemDef*) g_item_def_table)[g_100d0c0[i].f0].f36 + g_100d0c0[i].f3c) {
			continue;
		}
		if (((ItemDef*) g_item_def_table)[g_100d0c0[i].f0].kind != 0x17) {
			if (fcn_00486640(a, (int*) &g_100d0c0[i], 1)) {
				g_100d0c0[i].flags |= 8;
				fcn_004868d0(a, (int*) &g_100d0c0[i]);
				goto after;
			}
			if (fcn_00486640(a, (int*) &g_100d0c0[i], 0)) {
				fcn_004868d0(a, (int*) &g_100d0c0[i]);
				goto after;
			}
			continue;
		}
		q = fcn_00502cd0(*(int*) (t3 + 0x14), 1, 0, g_100d0c0[i].f0);
		if (q == 0) {
			continue;
		}
		if (*(int*) (q + 0xe) < (int) ((ItemDef*) g_item_def_table)[g_100d0c0[i].f0].f36) {
			continue;
		}
		g_100d0c0[i].flags |= 8;
		fcn_004868d0(a, (int*) &g_100d0c0[i]);
		goto after;
	}

after:
	for (i = 0; i < g_100b0ac; i++) {
		if (g_100d0c0[i].flags & 8) {
			break;
		}
		if (g_100d0c0[i].flags & 4) {
			continue;
		}
		if ((int) *(unsigned char*) (t2 + 0x1c) < g_100d0c0[i].f1c) {
			continue;
		}
		if ((int) *(unsigned char*) (t2 + 0x1d) < g_100d0c0[i].f20) {
			continue;
		}
		if (g_100d0c0[i].f40 < (int) ((ItemDef*) g_item_def_table)[g_100d0c0[i].f0].f36) {
			continue;
		}
		v = (int) fcn_00503d10(g_100d0c0[i].f0);
		if (v == 0) {
			continue;
		}
		t = (int) fcn_0050e000((char*) v, g_100d0c0[i].f0, 0xf4240);
		if (t < (int) ((ItemDef*) g_item_def_table)[g_100d0c0[i].f0].f36 + g_100d0c0[i].f3c) {
			continue;
		}
		if (((ItemDef*) g_item_def_table)[g_100d0c0[i].f0].kind == 0x17) {
			g_100d0c0[i].flags |= 0x10;
			break;
		}
		if (fcn_00486640(a, (int*) &g_100d0c0[i], 0)) {
			fcn_004868d0(a, (int*) &g_100d0c0[i]);
			break;
		}
	}

	for (i = 0; i < g_100b0ac; i++) {
		if ((g_100d0c0[i].flags & 8) == 0) {
			continue;
		}
		if (((ItemDef*) g_item_def_table)[g_100d0c0[i].f0].kind == 0x17) {
			if (((Lvl*) g_868050)[*(unsigned char*) h].kind == 0xb) {
				g_100d0c0[i].flags |= 0x10;
			} else {
				q = fcn_00502cd0(*(int*) (t3 + 0x14), 1, 0, g_100d0c0[i].f0);
				if (q == 0
				    || *(int*) (q + 0xe) < (int) ((ItemDef*) g_item_def_table)[g_100d0c0[i].f0].f36) {
					g_100d0c0[i].flags =
					    (g_100d0c0[i].flags & ~8) | 0x10;
				}
			}
		} else {
			for (j = 0; j != 4; j++) {
				if (g_100b0c0[g_100d0c0[i].bld[j]].busy
				    < (int) ((ItemDef*) g_item_def_table)[g_100d0c0[i].f0].f26) {
					g_100d0c0[i].flags &= ~8;
				}
			}
		}
	}

	fcn_00487e60(a, 4);
	fcn_00487e60(a, 8);
	fcn_00487e60(a, 3);

	st.total = 0;
	st.sent = 0;
	for (j = 0; j < 0x300; j++) {
		if (g_7f4ca0[j].f8 != 0 && g_7f4ca0[j].id != 0xffff
		    && g_7f4ca0[j].f2 != 0xa
		    && g_7f4ca0[j].f16c == *(int*) h
		    && g_7f4ca0[j].f165 != 0
		    && g_7f4ca0[j].f184 != 0
		    && *(int*) (*(char**) (g_7f4ca0[j].f184) + 0x2c) == *(int*) (h + 1)
		    && (g_7f4ca0[j].host == 0 || *(unsigned char*) g_7f4ca0[j].host != 0x28)
		    && !(flag != 0 && (char*) a == (char*) &g_7f4ca0[j])) {
			fcn_00529160(h, 0, g_7f4ca0[j].id, 0);
			st.total++;
		}
	}
	if (*(char**) 0x100dc20 == h) {
		*(int*) 0x100dc34 = st.total;
	}
	st.want = 0;
	{
		int* f;

		f = &g_100d0c0[0].flags;
		for (i = 0; i < g_100b0ac; i++) {
			if (*f & 8) {
				st.want++;
			}
			if (*f & 0x10) {
				if (((Lvl*) g_868050)[*(unsigned char*) h].kind != 0xb) {
					st.want++;
				}
			}
			f = (int*) ((char*) f + 0x58);
		}
	}
	if (st.want > st.total) {
		st.want = st.total;
	}
	if (st.total == 0 || st.want == 0) {
		fcn_00489250(a);
		fcn_00489a70(a, t2);
		return 0;
	}

	st.self = a;
	st.p0c = t2;
	st.p10 = t3;
	st.sent = 0;
	st.total = 0;
	if (((Lvl*) g_868050)[*(unsigned char*) h].kind != 0xb) {
		goto ltail;
	}
	if ((unsigned short) g_7f4c04 % 2 != 0) {
		if ((*(int*) (a + 0x1b4) & 0x20) != 0) {
			goto ltail;
		}
	} else {
		*(int*) (a + 0x1b4) &= ~0x20;
		goto ltail;
	}
	v = fcn_005155e0(h);
	p2 = *(char**) (0x104336c + v * 0x3dc);
	if (p2 == 0) {
		return 0;
	}
	n = *(int*) (h + 0x71);
	{
		int ch;
		char* g;

		ch = -1;
		for (i = 0; i < 8; i++) {
			if (fcn_0064d470(p2 + 0x7e24 + i * 0x40, (char*) 0x67dd10) != 0) {
				ch = i;
			}
		}
		for (i = 0; i < g_100b0ac * 4; i++) {
			j = gm_RandomMod(g_100b0ac) & 0xffff;
			if (((ItemDef*) g_item_def_table)[g_100d0c0[j].f0].kind == 0x17) {
				break;
			}
		}
		if (((ItemDef*) g_item_def_table)[g_100d0c0[j].f0].kind != 0x17) {
			goto lflag;
		}
		g = find_zone_record(g_100d0c0[j].f0);
		v = 0;
		for (i = 0; i < *(int*) p2 && v < 4; i++) {
			for (j = 0; j < *(int*) p2 && v < 4; j++) {
				if ((int) *(unsigned char*) (*(int*) (p2 + 0x14)
				                             + i * *(int*) p2 + j) != ch) {
					continue;
				}
				if (plt_CheckZoneAvailability(n, j, i, *(unsigned char*) (g + 0x42)) == 0) {
					continue;
				}
				fcn_004c5aa0(*(int*) (h + 1), j, i, *(unsigned short*) g, 0, -1);
				v++;
			}
		}
	}
lflag:
	*(int*) (a + 0x1b4) |= 0x20;

ltail:
	{
		char* rec;

		rec = (char*) &g_100d0c0[0];
		for (i = 0; i < g_100b0ac; i++) {
			if (((Ord*) rec)->flags & 0x10) {
				if (((Lvl*) g_868050)[*(unsigned char*) h].kind != 0xb) {
					st.kind = 8;
					st.rec = rec;
					fcn_00487f90((int*) &st);
				}
				if (((Ord*) rec)->flags & 8) {
					if (((ItemDef*) g_item_def_table)[((Ord*) rec)->f0].kind == 0x17) {
						st.rec = rec;
						if (((Lvl*) g_868050)[*(unsigned char*) h].kind == 0xb) {
							st.kind = 0x28;
							fcn_00487f90((int*) &st);
						} else {
							st.kind = 3;
							fcn_00487f90((int*) &st);
						}
					} else {
						st.kind = 4;
						st.rec = rec;
						fcn_00487f90((int*) &st);
					}
					if (*(char**) 0x100dc20 == h && *(int*) 0x100dc3c < 4) {
						*(Ord*) (0x100ddc0 + *(int*) 0x100dc3c * 0x58) =
						    *(Ord*) st.rec;
						*(int*) 0x100dc3c = *(int*) 0x100dc3c + 1;
					}
				}
			}
			rec += 0x58;
		}
	}

	fcn_0047e220(t2);
	fcn_00489250(a);
	fcn_00489a70(a, t2);
	return 0;
}
