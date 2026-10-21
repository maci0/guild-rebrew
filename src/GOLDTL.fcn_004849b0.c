/*
 * Collects the goods a building needs into the object record table
 * (g_100d0c0), prices them, and ranks them.
 */
#include <string.h>

/* g_100d0c0: 0x58-byte object records. */
#pragma pack(push, 1)
typedef struct Ord {
	int f0;               /* 0x00 goods id */
	int bld[4];           /* 0x04 building slot indices */
	int f14;              /* 0x14 */
	int f18;              /* 0x18 */
	int f1c;              /* 0x1c */
	int f20;              /* 0x20 */
	float price;          /* 0x24 */
	int f28;              /* 0x28 */
	int f2c;              /* 0x2c */
	int f30;              /* 0x30 */
	float f34;            /* 0x34 sort key */
	int f38;              /* 0x38 summed amount */
	int f3c;              /* 0x3c */
	int f40;              /* 0x40 */
	int f44;              /* 0x44 */
	int f48;              /* 0x48 */
	int f4c;              /* 0x4c */
	int f50;              /* 0x50 */
	int flags;            /* 0x54 */
} Ord;

/* g_100b0c0: 0x40-byte building instances. */
typedef struct Seg {
	int type;             /* 0x00 goods id */
	int next;             /* 0x04 index into g_100d0c0 */
	int owner;            /* 0x08 */
	int f0c;              /* 0x0c */
	int f10;              /* 0x10 */
	int f14;              /* 0x14 */
	int f18;              /* 0x18 */
	float price;          /* 0x1c */
	int f20;              /* 0x20 */
	int want;             /* 0x24 summed amount */
	int stock;            /* 0x28 */
	int full;             /* 0x2c */
	int f30;              /* 0x30 */
	int f34;              /* 0x34 */
	int f38;              /* 0x38 */
	int flags;            /* 0x3c */
} Seg;

/* Statistics block filled by fcn_0050de80. */
typedef struct Stats {
	int x0;
	int n;
	int x8[16];
	unsigned short x48[16];
	int x68[16];
	int xa8;
	int xac;
	int xb0;
	char* xb4;
} Stats;

/* g_868050: 0x24d-byte level records. */
typedef struct Lvl {
	unsigned char kind;   /* 0x000 */
	char pad1[0x24c];
} Lvl;
#pragma pack(pop)

extern Ord g_100d0c0[];
extern Seg g_100b0c0[];
extern int g_100b0ac;
extern int g_100b0a8;
extern char* g_99ec10;
extern char* g_868050;
extern float g_662910;
extern float g_6628a0;
extern float g_664124;

char* __cdecl fcn_00502cd0(int, int, int, ...);
char* __cdecl fcn_00502850(void);
char* __cdecl fcn_005463a0(int, int, int, int, int);
char* __cdecl fcn_005462a0(void);
char* __cdecl fcn_00501510(int);
int __cdecl fcn_0050df70(char*, char*);
int __cdecl fcn_0050e000(char*, int, int);
int __cdecl fcn_0050de80(char*, Stats*);
int __cdecl fcn_0050c710(char*, int, int);
void __cdecl fcn_004c52d0(int, int);
void __cdecl fcn_00486500(Ord*);

/* ADDRESS: GOLDTL 0x004849b0 */
void __cdecl fcn_004849b0(char* a, char* prod, char* craft)
{
	Stats st;
	Ord tmp;
	char* p;
	char* e;
	char* r;
	Seg* segp;
	int i;
	int j;
	int k;
	int type;
	int found;
	int x;
	unsigned short id;
	unsigned char kind;

	g_100b0ac = 0;
	p = fcn_00502cd0(*(int*) (prod + 0x14), 1, 5);
	while (p != 0) {
		if (*(int*) (p + 0xe)  > 1 && g_100b0ac < 0x20) {
			g_100d0c0[g_100b0ac].f0 = *(unsigned short*) p;
			for (j = 0; j != 4; j++) {
				g_100d0c0[g_100b0ac].bld[j] = -1;
			}
			g_100d0c0[g_100b0ac].f1c = 0;
			g_100d0c0[g_100b0ac].f20 = 0;
			g_100d0c0[g_100b0ac].price = -1.0e10f;
			g_100d0c0[g_100b0ac].f38 = 0;
			g_100d0c0[g_100b0ac].f3c = 0;
			g_100d0c0[g_100b0ac].f40 = 0;
			g_100d0c0[g_100b0ac].f44 = 0;
			g_100d0c0[g_100b0ac].f48 = 0x21;
			g_100d0c0[g_100b0ac].flags = 0;
			g_100b0ac++;
		}
		p = fcn_00502850();
	}

	g_100b0a8 = 0;
	for (k = 0; k < g_100b0ac; k++) {
		for (j = 0; j != 4; j++) {
			id = *(unsigned short*) (g_99ec10 +
			                         g_100d0c0[k].f0 * 0x41 + 0x2e +
			                         j * 2);
			if (id == 0) {
				continue;
			}
			if (g_100b0a8 >= 1) {
				for (i = 0; i < g_100b0a8; i++) {
					if (g_100b0c0[i].type == id) {
						g_100d0c0[k].bld[j] = i;
						break;
					}
				}
			}
			if (g_100d0c0[k].bld[j] != -1) {
				continue;
			}
			if (g_100b0a8 >= 0x80) {
				return;
			}
			segp = &g_100b0c0[g_100b0a8];
			segp->type = id;
			segp->next = -1;
			segp->owner = 0;
			segp->f10 = 0;
			segp->f14 = 0;
			segp->f18 = 0;
			segp->price = -1.0e10f;
			segp->want = 0;
			g_100d0c0[k].bld[j] = g_100b0a8;
			segp->stock = 0;
			g_100b0a8++;
			segp->f30 = 0x21;
			segp->flags = 0;
		}
	}

	kind = ((Lvl*) g_868050)[*(unsigned char*) *(char**) (a + 0x16c)].kind;
	if (kind == 0xe || kind == 8 || kind == 0x20) {
		if (g_100b0a8 > 0) {
			for (k = 0; k < g_100b0a8; k++) {
				type = g_100b0c0[k].type;
				if (type == 0x1c7 || type == 0x1c4 ||
				    type == 0x1c5 || type == 0x1c6 ||
				    type == 0x2af || type == 0x2b0) {
					g_100b0c0[k].flags |= 0x24;
					for (i = 0; i < g_100b0ac; i++) {
						if (g_100d0c0[i].f0 == type) {
							g_100d0c0[i].flags |= 0x24;
							break;
						}
					}
					if (i >= g_100b0ac) {
						g_100d0c0[g_100b0ac].f0 = type;
						for (j = 0; j != 4; j++) {
							g_100d0c0[g_100b0ac].bld[j] = -1;
						}
						g_100d0c0[g_100b0ac].f1c = 0;
						g_100d0c0[g_100b0ac].f20 = 0;
						g_100d0c0[g_100b0ac].price = -1.0e10f;
						g_100d0c0[g_100b0ac].f38 = 0;
						g_100d0c0[g_100b0ac].f3c = 0;
						g_100d0c0[g_100b0ac].f40 = 0;
						g_100d0c0[g_100b0ac].f44 = 0;
						g_100d0c0[g_100b0ac].f48 = 0x21;
						g_100d0c0[g_100b0ac].flags = 0x24;
						g_100b0ac = g_100b0ac + 1;
					}
				} else if (type == 0x1c1 || type == 0x1c2 ||
				           type == 0x1c3) {
					g_100b0c0[k].flags |= 0x204;
					for (i = 0; i < g_100b0ac; i++) {
						if (g_100d0c0[i].f0 == type) {
							g_100d0c0[i].flags |= 0x204;
							break;
						}
					}
					if (i >= g_100b0ac) {
						g_100d0c0[g_100b0ac].f0 = type;
						for (j = 0; j != 4; j++) {
							g_100d0c0[g_100b0ac].bld[j] = -1;
						}
						g_100d0c0[g_100b0ac].f1c = 0;
						g_100d0c0[g_100b0ac].f20 = 0;
						g_100d0c0[g_100b0ac].price = -1.0e10f;
						g_100d0c0[g_100b0ac].f38 = 0;
						g_100d0c0[g_100b0ac].f3c = 0;
						g_100d0c0[g_100b0ac].f40 = 0;
						g_100d0c0[g_100b0ac].f44 = 0;
						g_100d0c0[g_100b0ac].f48 = 0x21;
						g_100d0c0[g_100b0ac].flags = 0x204;
						g_100b0ac = g_100b0ac + 1;
					}
				}
			}
		}
	}

	kind = ((Lvl*) g_868050)[*(unsigned char*) *(char**) (a + 0x16c)].kind;
	if ((kind == 0x1d || kind == 0x1f) && g_100b0a8 > 0) {
		for (k = 0; k < g_100b0a8; k++) {
			type = g_100b0c0[k].type;
			if (type == 0x225 || type == 0x226 || type == 0x227 ||
			    type == 0x293 || type == 0x294 || type == 0x295) {
				g_100b0c0[k].flags |= 0x404;
				for (i = 0; i < g_100b0ac; i++) {
					if (g_100d0c0[i].f0 == type) {
						g_100d0c0[i].flags |= 0x404;
						break;
					}
				}
				if (i >= g_100b0ac) {
					g_100d0c0[g_100b0ac].f0 = type;
					for (j = 0; j != 4; j++) {
						g_100d0c0[g_100b0ac].bld[j] = -1;
					}
					g_100d0c0[g_100b0ac].f1c = 0;
					g_100d0c0[g_100b0ac].f20 = 0;
					g_100d0c0[g_100b0ac].price = -1.0e10f;
					g_100d0c0[g_100b0ac].f38 = 0;
					g_100d0c0[g_100b0ac].f3c = 0;
					g_100d0c0[g_100b0ac].f40 = 0;
					g_100d0c0[g_100b0ac].f44 = 0;
					g_100d0c0[g_100b0ac].f48 = 0x21;
					g_100d0c0[g_100b0ac].flags = 0x404;
					g_100b0ac = g_100b0ac + 1;
				}
			}
		}
	}

	for (k = 0; k < g_100b0a8; k++) {
		if (g_100b0ac > 0) {
			for (i = 0; i < g_100b0ac; i++) {
				if (g_100d0c0[i].f0 == g_100b0c0[k].type) {
					break;
				}
			}
			if (i < g_100b0ac) {
				g_100b0c0[k].next = i;
			}
		}
	}

	for (i = 0; i < g_100b0ac; i++) {
		p = fcn_00502cd0(*(int*) (craft + 0x14), 1, 0, g_100d0c0[i].f0);
		if (p == 0) {
			g_100d0c0[i].f3c = 0;
		} else {
			g_100d0c0[i].f3c = fcn_0050df70(craft, p);
		}
		g_100d0c0[i].f40 =
		    fcn_0050e000(craft, g_100d0c0[i].f0, 0xf4240);
	}

	for (k = 0; k < g_100b0a8; k++) {
		p = fcn_00502cd0(*(int*) (craft + 0x14), 1, 0, g_100b0c0[k].type);
		if (p == 0) {
			g_100b0c0[k].stock = 0;
		} else {
			g_100b0c0[k].stock = fcn_0050df70(craft, p);
			if (g_100b0c0[k].stock == 0) {
				fcn_004c52d0(*(int*) (craft + 2), g_100b0c0[k].type);
			}
		}
		g_100b0c0[k].full =
		    fcn_0050e000(craft, g_100b0c0[k].type, 0xf4240);
	}

	for (e = fcn_005463a0(2, 0, 0xb, 3,
	                     *(int*) (*(char**) (a + 0x16c) + 1));
	     e != 0;
	     e = fcn_005462a0()) {
		r = fcn_00501510(*(int*) (e + 0xac));
		if (r == 0) {
			continue;
		}
		fcn_0050de80(r, &st);
		for (i = 0; i < st.x0; i++) {
			id = st.x48[i];
			if (id == 0) {
				continue;
			}
			found = 0;
			for (j = 0; found == 0 && j < 3; j++) {
				if (((unsigned short*) (e + 0xd0))[j] == id) {
					found = 1;
				}
			}
			if (found != 0) {
				continue;
			}
			for (j = 0; j < g_100b0ac; j++) {
				if (id == g_100d0c0[j].f0) {
					g_100d0c0[j].f38 += st.x68[i];
				}
			}
			for (j = 0; j < g_100b0a8; j++) {
				if (id == g_100b0c0[j].type) {
					g_100b0c0[j].want += st.x68[i];
				}
			}
		}
		for (j = 0; j < 3; j++) {
			id = ((unsigned short*) (e + 0xd6))[j];
			if (id == 0) {
				continue;
			}
			for (i = 0; i < g_100b0ac; i++) {
				if (id == g_100d0c0[i].f0) {
					g_100d0c0[i].f38 += ((int*) (e + 0xdc))[j];
				}
			}
			for (i = 0; i < g_100b0a8; i++) {
				if (id == g_100b0c0[i].type) {
					g_100b0c0[i].want += ((int*) (e + 0xdc))[j];
				}
			}
		}
	}

	kind = ((Lvl*) g_868050)[*(unsigned char*) *(char**) (a + 0x16c)].kind;
	if (kind == 8 || kind == 0xe) {
		for (e = fcn_005463a0(2, 0, 0x14, 3,
		                     *(int*) (*(char**) (a + 0x16c) + 1));
		     e != 0;
		     e = fcn_005462a0()) {
			for (k = 0; k < g_100b0a8; k++) {
				if (g_100b0c0[k].type !=
				    (int) *(unsigned short*) (e + 0xae)) {
					continue;
				}
				x = fcn_0050c710(*(char**) (a + 0x16c), 0xb, 1);
				g_100b0c0[k].want =
				    (int) (((float) x * g_662910 + g_6628a0) *
				               g_664124 +
				           (float) g_100b0c0[k].want);
			}
		}
	}

	kind = ((Lvl*) g_868050)[*(unsigned char*) *(char**) (a + 0x16c)].kind;
	if (kind == 8) {
		for (e = fcn_005463a0(2, 0, 0x15, 3,
		                     *(int*) (*(char**) (a + 0x16c) + 1));
		     e != 0;
		     e = fcn_005462a0()) {
			for (k = 0; k < g_100b0a8; k++) {
				if (g_100b0c0[k].type !=
				    (int) *(unsigned short*) (e + 0xae)) {
					continue;
				}
				x = fcn_0050c710(*(char**) (a + 0x16c), 0xb, 1);
				g_100b0c0[k].want =
				    (int) (((float) x * g_662910 + g_6628a0) *
				               g_664124 +
				           (float) g_100b0c0[k].want);
			}
		}
	}

	kind = ((Lvl*) g_868050)[*(unsigned char*) *(char**) (a + 0x16c)].kind;
	if (kind == 0x1d || kind == 0x1f) {
		for (e = fcn_005463a0(2, 0, 0x8c, 3,
		                     *(int*) (*(char**) (a + 0x16c) + 1));
		     e != 0;
		     e = fcn_005462a0()) {
			for (k = 0; k < g_100b0a8; k++) {
				if (g_100b0c0[k].type !=
				    (int) *(unsigned short*) (e + 0xac)) {
					continue;
				}
				x = fcn_0050c710(*(char**) (a + 0x16c), 0xb, 1);
				g_100b0c0[k].want =
				    (int) (((float) x * g_662910 + g_6628a0) *
				               g_664124 +
				           (float) g_100b0c0[k].want);
			}
		}
	}

	for (i = 0; i < g_100b0ac; i++) {
		fcn_00486500(&g_100d0c0[i]);
	}

	for (i = 0; i < g_100b0ac; i++) {
		for (j = i; j < g_100b0ac; j++) {
			if (g_100d0c0[i].f34 < g_100d0c0[j].f34) {
				tmp = g_100d0c0[i];
				g_100d0c0[i] = g_100d0c0[j];
				g_100d0c0[j] = tmp;
			}
		}
	}

	for (k = 0; k < g_100b0a8; k++) {
		if (g_100b0c0[k].next != -1) {
			for (j = 0; j < g_100b0ac; j++) {
				if (g_100b0c0[k].type == g_100d0c0[j].f0) {
					g_100b0c0[k].flags |= 0x40;
					g_100d0c0[j].flags |= 0x40;
					g_100b0c0[k].next = j;
				}
			}
		}
	}

	for (i = 0; i < g_100b0ac; i++) {
		g_100d0c0[i].f48 = i;
	}
}
