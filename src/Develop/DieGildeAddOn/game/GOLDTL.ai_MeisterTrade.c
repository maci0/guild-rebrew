/*
 * ai_MeisterTrade - master trade decisions for one building: prices and sells
 * town stock, fills the cart requests, unloads carts, routes stock into the
 * request message and sells leftovers.
 *
 * Native body 0x489a70-0x48b1f4 (1785 instructions, frame 0x74c, kept EBP
 * frame with 8-byte stack alignment). Block comments use native offsets.
 * Special request type 0x116 delegates to ai_MeisterTradeAllgemein.
 */

#include <stdio.h>
#include <string.h>

/* Request message, 0xf8 bytes. */
typedef struct {
	int f00;			/* +0x00 */
	unsigned char type;		/* +0x04 */
	unsigned char f05;
	unsigned char flag;		/* +0x06 */
	unsigned char f07;
	int state;			/* +0x08 */
	int f0c;			/* +0x0c */
	int f10;
	int f14;
	int f18;
	char pad1c[0x28 - 0x1c];
	int p28;			/* +0x28 */
	int p2c;
	int p30;
	unsigned short p34;		/* +0x34 */
	unsigned char flag2;		/* +0x36 */
	char pad37[0x58 - 0x37];
	int f58;			/* +0x58 */
	int f5c;			/* +0x5c */
	int f60;			/* +0x60 */
	int slots[6];			/* +0x64 */
	unsigned short ids[6];		/* +0x7c */
	int f88[4];			/* +0x88 */
	char pad98[0xf8 - 0x98];
} Msg;

/* Producer record, 0x40 bytes. */
typedef struct {
	int id;				/* +0x00 */
	int f04;
	int f08;
	int f0c;
	int f10;
	int f14;
	int qty18;			/* +0x18 */
	int f1c;
	int f20;
	int f24;
	int qty28;			/* +0x28 */
	int f2c;
	int f30;
	int f34;
	int f38;
	int flags;			/* +0x3c */
} Prod;

/* Town stock record, 0x58 bytes. */
typedef struct {
	int id;				/* +0x00 */
	int f04;
	int f08;
	int f0c;
	int f10;
	int f14;
	int f18;
	int f1c;
	int f20;
	int f24;
	int f28;
	int f2c;
	int f30;
	int f34;
	int f38;
	int qty3c;			/* +0x3c */
	int f40;
	int qty44;			/* +0x44 */
	int f48;
	int f4c;
	int f50;
	int flags54;			/* +0x54 */
} Town;

/* Stock/Stats record filled by fcn_0050cce0 and fcn_0050de80, 0xb8 bytes. */
typedef struct {
	int cap;			/* +0x00 */
	int n;				/* +0x04 */
	int caps[16];			/* +0x08 */
	unsigned short ids[16];		/* +0x48 */
	int vals[16];			/* +0x68 */
	int xa8;
	int xac;
	int xb0;
	char* xb4;
} Stock;

extern unsigned char g_773d75;
extern char* g_773d78;
extern float g_6628a0;
extern float g_664144;

int __cdecl ai_MeisterTradeAllgemein(char* o, char* bld);
int __cdecl fcn_0050dfd0(char* pkt, int item_id);
float __cdecl eval_ObjektPreis2Credits(int id, int n);
float __cdecl fcn_0050bb50(int id, unsigned char a);
float __cdecl fcn_005a8a30(char* a);
int __cdecl gm_AccumulateTyped2(void* m);
void* __cdecl fcn_00502cd0(int list, int mode, ...);
char* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl fcn_0050cce0(char* o, Stock* out, int producers);
int __cdecl fcn_0050de80(char* e, Stock* s);
char* __cdecl fcn_005463a0(int, int, int, int, int);
char* __cdecl he_fn_Handlung(void);
int __cdecl fcn_0047d1b0(void);
int __cdecl fcn_0047d1e0(void);
void __cdecl fcn_00500bb0(void*, int, int, int);
void __cdecl fcn_004c4510(char* a, int b);
int __cdecl fcn_004c4570(unsigned char size, unsigned char count,
	unsigned short off, char* src);
void __cdecl fcn_004c5360(void);
int __cdecl fcn_004c51f0(int a1, int a2, short a3, int a4, char a5, int a6);
void __cdecl fcn_004c52d0(int a1, unsigned short a2);
void __cdecl fcn_004c5530(int a1);
char* __cdecl fcn_00503d10(int who);
double __cdecl gm_RandomFloat01(void);

/* ADDRESS: GOLDTL 0x00489a70 */
int __cdecl ai_MeisterTrade(char* o, char* bld)
{
	char* q;
	char* r;
	char* x;
	char* tp;
	Prod* pr;
	Town* t;
	unsigned short id;
	int i;
	int j;
	int n;
	int cnt;
	int sent;
	int found;
	int tmp;
	int price;
	int type;
	int slot;
	float fr;
	struct {
		Msg m;
		Stock s1;
		Stock s2;
		Stock s3;
		char line[0x404];
	} v;

	/* 0x0000: general trade for special request type 0x116 */
	if (*(unsigned short*) bld == 0x116) {
		return ai_MeisterTradeAllgemein(o, bld);
	}

	/* 0x002d-0x00b0: producer records holding more than a third of demand */
	for (i = 0; i < *(int*) 0x100b0a8; i++) {
		pr = (Prod*) 0x100b0c0 + i;
		if ((pr->flags & 6) != 0) {
			continue;
		}
		if ((pr->flags & 8) == 0) {
			continue;
		}
		tmp = pr->qty28;
		if (tmp > fcn_0050dfd0(bld, pr->id) / 3) {
			tp = *(char**) (o + 0x16c);
			if (*(unsigned char*) (0x868050 +
			    (unsigned char) *tp * 0x24d) == 0x16) {
				pr->qty18 = tmp / 2;
			} else {
				pr->qty18 = tmp;
			}
		}
	}

	/* 0x00b0-0x00c0: building busy flag; the pricing pass runs once */
	if ((*(int*) 0x7f4c04 & 1) == 0) {
		*(int*) (o + 0x1b4) &= ~0x200;
	} else {
		if ((*(int*) (o + 0x1b4) & 0x200) == 0) {
			/* 0x00c0-0x0198: sell town stock on a good price */
			for (i = 0; i < *(int*) 0x100b0ac; i++) {
				t = (Town*) 0x100d0c0 + i;
				if ((t->flags54 & 6) != 0) {
					continue;
				}
				if ((t->flags54 & 8) != 0 && t->qty3c <= 3) {
					continue;
				}
				tp = *(char**) (o + 0x16c);
				if (*(unsigned char*) (0x7f4ca2 +
				    *(unsigned short*) (tp + 0x27) *
				    0x21c) == 6) {
					fr = (float) (int) fcn_005a8a30(tp);
					price = (int) eval_ObjektPreis2Credits(t->id, 100);
					tmp = (int) fcn_0050bb50(t->id,
					    g_773d75);
					if (fr <= (float) tmp / (float) price) {
						t->qty44 = t->qty3c;
						if (o == (char*) 0x100e748) {
							sprintf(v.line,
							    (char*) 0x67e708,
							    t->qty44,
							    *(char**) 0x99ec10 +
							    t->id * 0x41 + 1);
						}
					}
				} else {
					price = (int) eval_ObjektPreis2Credits(t->id, 100);
					fr = (float) price /
					    fcn_0050bb50(t->id, g_773d75);
					if (fr < g_6628a0
					    && fr < (float) (gm_RandomFloat01() *
					    g_664144 + 0.25)) {
						t->qty44 = t->qty3c;
						if (o == (char*) 0x100e748) {
							sprintf(v.line,
							    (char*) 0x67e6cc,
							    t->qty44,
							    *(char**) 0x99ec10 +
							    t->id * 0x41 + 1);
						}
					}
				}
			}

			/* 0x0198-0x02a5: fill the own market stall to 32000 */
			if (*(int*) (o + 0x1b8) >= 0xc80) {
				tp = *(char**) (o + 0x16c);
				if (gm_AccumulateTyped2((void*) (0x7f4ca0 +
				    *(unsigned short*) (tp + 0x27) * 0x21c))
				    >= 0x1f40) {
					goto dump_stock;
				}
			}
			tp = *(char**) (o + 0x16c);
			fr = (float) gm_AccumulateTyped2((void*) (0x7f4ca0 +
			    *(unsigned short*) (tp + 0x27) * 0x21c));
			tmp = *(int*) (o + 0x1b8);
			if (tmp > (int) fr) {
				tmp = (int) fr;
			}
			if (tmp >= 0x7d00) {
				goto dump_stock;
			}
			i = 0;
			for (; i < *(int*) 0x100b0ac && tmp < 0x7d00; i++) {
				t = (Town*) 0x100d0c0 + i;
				if ((t->flags54 & 6) != 0) {
					continue;
				}
				price = (int) fcn_0050bb50(t->id, g_773d75);
				j = 0x7d00 / price;
				if (j < 1) {
					j = 1;
				}
				t->qty44 = j < t->qty3c ? j : t->qty3c;
				tmp += j * price;
				if (o == (char*) 0x100e748) {
					sprintf(v.line, (char*) 0x67e6ac,
					    t->qty44,
					    *(char**) 0x99ec10 +
					    t->id * 0x41 + 1);
				}
			}

dump_stock:
			/* 0x02a5-0x0334: dump full town stock */
			for (i = 0; i < *(int*) 0x100b0ac; i++) {
				t = (Town*) 0x100d0c0 + i;
				if ((t->flags54 & 6) != 0) {
					continue;
				}
				tmp = fcn_0050dfd0(bld, t->id) / 4;
				if (t->qty3c <= tmp) {
					continue;
				}
				tmp = t->qty3c / 4;
				if (tmp < 5) {
					tmp = 5;
				}
				t->qty44 = tmp;
				if (tmp >= t->qty3c) {
					t->qty44 = t->qty3c;
				}
				if (o == (char*) 0x100e748) {
					sprintf(v.line, (char*) 0x67e674,
					    t->qty44,
					    *(char**) 0x99ec10 +
					    t->id * 0x41 + 1);
				}
			}
		}
		*(int*) (o + 0x1b4) |= 0x200;
	}

	/* 0x0334-0x03a7: collect the own stock lanes */
	fcn_0050cce0(*(char**) (o + 0x16c), &v.s1, 1);
	fcn_0050cce0(*(char**) (o + 0x16c), &v.s3, 0);

	/* 0x03a7-0x0420: drop producer requests already being handled */
	for (i = 0; i < *(int*) 0x100b0a8; i++) {
		pr = (Prod*) 0x100b0c0 + i;
		if ((pr->flags & 6) == 0) {
			continue;
		}
		r = (char*) fcn_00502cd0(*(int*) (bld + 0x14), 1, 0, pr->id);
		if (r == 0) {
			continue;
		}
		tmp = 4;
		if (*(int*) (r + 0x1c) == 4) {
			continue;
		}
		fcn_004c4510(r, *(int*) (r + 2));
		fcn_004c4570(4, 1,
		    (unsigned short) ((r - *(char**) 0xaed32c) + 0x1c),
		    (char*) &tmp);
		fcn_004c5360();
	}

	tp = *(char**) (o + 0x16c);
	type = *(unsigned char*) (0x868050 + (unsigned char) *tp * 0x24d);
	if (type == 0xd || type == 0xb || type == 0xc) {
		/* 0x0420-0x04b7: drop town requests already being handled */
		for (i = 0; i < *(int*) 0x100b0ac; i++) {
			t = (Town*) 0x100d0c0 + i;
			if ((t->flags54 & 6) != 0) {
				continue;
			}
			r = (char*) fcn_00502cd0(*(int*) (bld + 0x14), 1, 0,
			    t->id);
			if (r == 0) {
				continue;
			}
			if (*(int*) (r + 0x1c) == 0) {
				continue;
			}
			tmp = 0;
			fcn_004c4510(r, *(int*) (r + 2));
			fcn_004c4570(4, 1,
			    (unsigned short) ((r - *(char**) 0xaed32c) + 0x1c),
			    (char*) &tmp);
			fcn_004c5360();
		}
	}

	/* 0x04b7: request loop head */
	tp = *(char**) (o + 0x16c);
	r = (char*) fcn_00502cd0(*(int*) (tp + 0x5d), 3, 6, 4, 0x1d, 3,
	    *(unsigned short*) (tp + 0x27));
next_request:
	if (r == 0) {
		return 1;
	}
	tp = *(char**) (o + 0x16c);
	if (*(int*) (r + 0x1c) != *(int*) (tp + 1)) {
		goto tail;
	}
	if (*(unsigned char*) (r + 0x12) < 0x21) {
		/* 0x0520-0x0572: unload the cart into the store */
		slot = *(unsigned short*) (tp + 0x27);
		memset(&v.m, 0, sizeof(v.m));
		v.m.type = 0x10;
		v.m.state = *(int*) (0x7f4ca4 + slot * 0x21c);
		v.m.f0c = *(int*) (tp + 1);
		v.m.p28 = *(int*) 0x7f4c00;
		v.m.p2c = *(int*) 0x7f4c04;
		v.m.p30 = *(int*) 0x7f4c08;
		v.m.p34 = *(unsigned short*) 0x7f4c0c;
		v.m.flag2 = 1;
		fcn_00500bb0(&v.m.p28, 0, 0, 0xa);
		v.m.f58 = *(int*) (r + 2);
		v.m.slots[0] = 5;
		*(int*) ((char*) &v.m + 0x84) = 0;
		v.m.f5c = 0x64 - *(unsigned char*) (r + 0x12);
		fcn_004c5530((int) &v.m);
		goto tail;
	}

	/* 0x0572-0x05f0: is the cart already unloaded? */
	x = fcn_005463a0(*(int*) (*(char**) (o + 0x16c) + 1), 2, 0, 0xb, 3);
	if (x != 0) {
		while (*(int*) (x + 0xac) != *(int*) (r + 2)) {
			if (he_fn_Handlung() == 0) {
				break;
			}
		}
		if (*(int*) (x + 0xac) == *(int*) (r + 2)) {
			goto tail;
		}
	}

	/* 0x05f0-0x0630: prepare the cart stock and message */
	memset(&v.m, 0, sizeof(v.m));
	cnt = 0;
	sent = 0;
	n = 0;
	*(unsigned char*) ((char*) &v.m + 0x9d) = 0;
	if (fcn_0047d1e0() > fcn_0047d1b0()) {
		*(unsigned char*) ((char*) &v.m + 0x9d) = 1;
	}
	for (i = 0; i < 3; i++) {
		v.m.ids[i] = 0;
		v.m.slots[i] = -1;
		v.m.ids[3 + i] = 0;
		v.m.slots[3 + i] = -1;
	}
	fcn_0050de80(r, &v.s2);
	q = (char*) fcn_00502cd0(*(int*) (r + 0x14), 1, 0, 0x1dd);
	if (q == 0) {
		q = (char*) fcn_00502cd0(*(int*) (r + 0x14), 1, 0, 0x1dd);
	}

	/* 0x0630-0x0970: unload every cart position */
	i = 0;
	for (; i < v.s2.cap; i++) {
		if (v.s2.ids[i] == 0) {
			continue;
		}
		id = v.s2.ids[i];
		sprintf(v.line, (char*) 0x67e634, *(char**) (o + 0x16c) + 5,
		    v.s2.vals[i], *(char**) 0x99ec10 + id * 0x41 + 1);
		pr = 0;
		for (tmp = 0; tmp < *(int*) 0x100b0a8; tmp++) {
			if (((Prod*) 0x100b0c0 + tmp)->id == id) {
				pr = (Prod*) 0x100b0c0 + tmp;
				break;
			}
		}
		if (pr == 0) {
			goto no_market;
		}
		if ((pr->flags & 2) == 0) {
			goto no_market;
		}
		found = 0;
		for (j = 0; j < v.s1.cap; j++) {
			if (v.s1.ids[j] != id) {
				continue;
			}
			/* tracking arrays start four ints in */
			sprintf(v.line, (char*) 0x67e600,
			    *(char**) (o + 0x16c) + 5,
			    *(char**) 0x99ec10 + id * 0x41 + 1);
			tmp = v.s1.caps[4 + j] - v.s1.vals[4 + j];
			if (v.s2.vals[i] < tmp) {
				tmp = v.s2.vals[i];
			}
			if (tmp != 0) {
				sprintf(v.line, (char*) 0x67e358,
				    *(int*) (bld + 2), *(int*) (q + 2), id,
				    tmp, g_773d75, 0);
				fcn_004c51f0(*(int*) (bld + 2),
				    *(int*) (q + 2), id, tmp, g_773d75, 0);
			}
			v.s2.vals[i] -= tmp;
			if (v.s2.vals[i] == 0) {
				v.s2.ids[i] = 0;
			}
			v.s1.vals[4 + j] += tmp;
			found = 1;
			break;
		}
		if (found) {
			goto next_auto;
		}
		found = 0;
		for (j = 0; j < v.s1.cap; j++) {
			if (v.s1.ids[j] != 0) {
				continue;
			}
			sprintf(v.line, (char*) 0x67e5d0,
			    *(char**) (o + 0x16c) + 5,
			    *(char**) 0x99ec10 + id * 0x41 + 1);
			tmp = fcn_0050dfd0(bld, id);
			if (v.s2.vals[i] < tmp) {
				tmp = v.s2.vals[i];
			}
			sprintf(v.line, (char*) 0x67e358,
			    *(int*) (bld + 2), *(int*) (q + 2), id, tmp,
			    g_773d75, 0);
			fcn_004c51f0(*(int*) (bld + 2), *(int*) (q + 2), id,
			    tmp, g_773d75, 0);
			v.s2.vals[i] -= tmp;
			if (v.s2.vals[i] == 0) {
				v.s2.ids[i] = 0;
			}
			v.s1.ids[j] = id;
			v.s1.vals[4 + j] += tmp;
			found = 1;
			break;
		}
		if (found) {
			goto no_market;
		}
		/* 0x08b0-0x0970: fake sale out of the store */
		for (j = 0; j < v.s1.cap; j++) {
			if (v.s1.ids[j] != id) {
				continue;
			}
			if (v.s2.vals[i] < v.s1.vals[4 + j]) {
				continue;
			}
			sprintf(v.line, (char*) 0x67e588,
			    *(char**) (o + 0x16c) + 5,
			    v.s1.vals[4 + j],
			    *(char**) 0x99ec10 + id * 0x41 + 1);
			price = (int) fcn_0050bb50(id, g_773d75);
			sprintf(v.line, (char*) 0x67e358, -1,
			    *(int*) (bld + 2), id, v.s1.vals[4 + j],
			    g_773d75, (double) price);
			tmp = (int) fcn_0050bb50(id, g_773d75);
			fcn_004c51f0(-1, *(int*) (bld + 2), id,
			    v.s1.vals[4 + j], g_773d75, tmp);
			price = (int) fcn_0050bb50(id, g_773d75) +
			    *(int*) (o + 0x1b8);
			*(int*) (o + 0x1b8) = price;
			v.s1.ids[j] = 0;
			v.s1.vals[4 + j] = 0;
			break;
		}
no_market:
		/* 0x0970-0x0aa0: cart item without a market place */
		if (v.s2.vals[i] != 0) {
			sprintf(v.line, (char*) 0x67e540,
			    *(char**) (o + 0x16c) + 5, v.s2.vals[i],
			    *(char**) 0x99ec10 + id * 0x41 + 1);
			price = (int) fcn_0050bb50(id, g_773d75);
			sprintf(v.line, (char*) 0x67e358, -1,
			    *(int*) (bld + 2), id, v.s2.vals[i], g_773d75,
			    (double) price);
			tmp = (int) fcn_0050bb50(id, g_773d75);
			fcn_004c51f0(-1, *(int*) (bld + 2), id,
			    v.s2.vals[i], g_773d75, tmp);
			price = (int) fcn_0050bb50(id, g_773d75) +
			    *(int*) (o + 0x1b8);
			*(int*) (o + 0x1b8) = price;
			v.s2.ids[i] = 0;
			v.s2.vals[i] = 0;
		}
next_auto:
		;
	}

	/* 0x0aa0-0x0bf0: route the cart amounts into the request */
	for (i = 0; i < v.s2.cap && cnt < 3; i++) {
		id = v.s2.ids[i];
		if (id == 0) {
			continue;
		}
		found = 0;
		for (j = 0; j < *(int*) 0x100b0ac; j++) {
			if (((Town*) 0x100d0c0 + j)->id == id) {
				found = 1;
				break;
			}
		}
		if (found) {
			continue;
		}
		found = 0;
		for (j = 0; j < *(int*) 0x100b0a8; j++) {
			if (((Prod*) 0x100b0c0 + j)->id == id) {
				found = 1;
				break;
			}
		}
		if (found) {
			continue;
		}
		tmp = fcn_0050dfd0(q, id);
		for (j = 0; j < v.s3.cap; j++) {
			if (v.s3.ids[j] != 0 && v.s3.ids[j] != id) {
				continue;
			}
			tmp = v.s2.vals[i] < tmp ? v.s2.vals[i] : tmp;
			if (tmp == 0) {
				break;
			}
			sprintf(v.line, (char*) 0x67e358, *(int*) (bld + 2),
			    *(int*) (q + 2), id, tmp, g_773d75, 0);
			fcn_004c51f0(*(int*) (bld + 2), *(int*) (q + 2), id,
			    tmp, g_773d75, 0);
			v.m.ids[cnt] = id;
			v.m.slots[cnt] = *(int*) (g_773d78 + 1);
			cnt++;
			v.s2.vals[i] -= tmp;
			v.s3.ids[j] = id;
			if (v.s2.vals[i] == 0) {
				break;
			}
		}
		if (v.s2.vals[i] != 0) {
			continue;
		}
		fcn_004c52d0(*(int*) (bld + 2), id);
		v.s2.ids[i] = 0;
	}

	/* 0x0bf0-0x0d30: route the cart ids reserved for the request */
	if (cnt < 3) {
		for (i = 0; i < v.s3.cap && cnt < 3; i++) {
			id = v.s3.ids[i];
			if (id == 0 || v.s3.vals[i] == 0) {
				continue;
			}
			tmp = fcn_0050dfd0(q, id);
			for (j = 0; j < v.s2.cap; j++) {
				if (v.s2.ids[j] != 0 && v.s2.ids[j] != id) {
					continue;
				}
				tmp = v.s3.vals[i] < tmp ? v.s3.vals[i] : tmp;
				if (tmp == 0) {
					break;
				}
				sprintf(v.line, (char*) 0x67e358,
				    *(int*) (bld + 2), *(int*) (q + 2), id,
				    tmp, g_773d75, 0);
				fcn_004c51f0(*(int*) (bld + 2),
				    *(int*) (q + 2), id, tmp, g_773d75, 0);
				v.m.ids[cnt] = id;
				v.m.slots[cnt] = *(int*) (g_773d78 + 1);
				cnt++;
				v.s3.vals[i] -= tmp;
				v.s2.ids[j] = id;
				if (v.s3.vals[i] == 0) {
					break;
				}
			}
		}
	}

	/* 0x0d30-0x0f60: sell collected stock, town first */
	if (cnt < 3) {
		for (i = 0; i < *(int*) 0x100b0ac && cnt < 3; i++) {
			t = (Town*) 0x100d104 + i - 0x11;
			if (t->qty44 == 0) {
				continue;
			}
			tmp = fcn_0050dfd0(q, t->id);
			if (t->qty44 == 0) {
				continue;
			}
			for (j = 0; j < v.s3.cap; j++) {
				if (v.s3.ids[j] != 0 && v.s3.ids[j] != t->id) {
					continue;
				}
				tmp = t->qty44 < tmp ? t->qty44 : tmp;
				if (tmp == 0) {
					break;
				}
				sprintf(v.line, (char*) 0x67e358,
				    *(int*) (bld + 2), *(int*) (q + 2),
				    t->id, tmp, g_773d75, 0);
				fcn_004c51f0(*(int*) (bld + 2),
				    *(int*) (q + 2), t->id, tmp, g_773d75, 0);
				v.m.ids[cnt] = t->id;
				v.m.slots[cnt] = *(int*) (g_773d78 + 1);
				cnt++;
				t->qty44 -= tmp;
				v.s3.ids[j] = t->id;
				if (t->qty44 == 0) {
					break;
				}
			}
		}
	}
	if (cnt < 3) {
		for (i = 0; i < *(int*) 0x100b0a8 && cnt < 3; i++) {
			pr = (Prod*) 0x100b0c0 + i;
			if (pr->qty18 == 0) {
				continue;
			}
			if (!fcn_00503d10(pr->id)) {
				sprintf(v.line, (char*) 0x67e4e8,
				    *(char**) (o + 0x16c) + 5, pr->qty18,
				    *(char**) 0x99ec10 +
				    pr->id * 0x41 + 1);
				price = (int) fcn_0050bb50(pr->id,
				    g_773d75);
				sprintf(v.line, (char*) 0x67e358, -1,
				    *(int*) (bld + 2), pr->id, pr->qty18,
				    g_773d75, (double) price);
				tmp = (int) fcn_0050bb50(pr->id,
				    g_773d75);
				fcn_004c51f0(-1, *(int*) (bld + 2),
				    pr->id, pr->qty18, g_773d75, tmp);
				pr->qty18 = 0;
				continue;
			}
			tmp = fcn_0050dfd0(q, pr->id);
			if (pr->qty18 == 0) {
				continue;
			}
			for (j = 0; j < v.s3.cap; j++) {
				if (v.s3.ids[j] != 0 &&
				    v.s3.ids[j] != pr->id) {
					continue;
				}
				tmp = pr->qty18 < tmp ? pr->qty18 : tmp;
				if (tmp == 0) {
					break;
				}
				sprintf(v.line, (char*) 0x67e358,
				    *(int*) (bld + 2), *(int*) (q + 2),
				    pr->id, tmp, g_773d75, 0);
				fcn_004c51f0(*(int*) (bld + 2),
				    *(int*) (q + 2), pr->id, tmp,
				    g_773d75, 0);
				v.m.ids[cnt] = pr->id;
				v.m.slots[cnt] = *(int*) (g_773d78 + 1);
				cnt++;
				pr->qty18 -= tmp;
				v.s3.ids[j] = pr->id;
				if (pr->qty18 == 0) {
					break;
				}
			}
		}
	}

	/* 0x0f60-0x136f: leftover producer stock becomes a request */
	cnt = 0;
	sent = 0;
	n = 0;
	for (i = 0; i < *(int*) 0x100b0a8 && n < 3; i++) {
		int* w = (int*) ((char*) 0x100b0d4 + i * 0x40);

		if (*w == 0) {
			continue;
		}
		{
			char* z = *(char**) ((char*) w - 0xc);

			if (z == 0) {
				continue;
			}
			v.m.ids[3 + n] =
			    *(unsigned short*) ((char*) w - 0x14);
			v.m.slots[3 + n] = *(int*) (z + 1);
			tmp = fcn_0050dfd0(q,
			    *(unsigned short*) ((char*) w - 0x14));
			if (tmp < *w) {
				v.m.f88[n] = tmp;
			} else {
				v.m.f88[n] = *w;
			}
			n++;
			*w = 0;
			sent = 1;
		}
	}

	/* 0x136f-0x1483: log and send the request */
	if (sent) {
		if (o == (char*) 0x100e748) {
			for (i = 0; i < 3; i++) {
				if (v.m.ids[i] != 0) {
					sprintf(v.line, (char*) 0x67e4d8,
					    *(char**) 0x99ec10 +
					    v.m.ids[i] * 0x41 + 1);
				}
			}
			for (i = 0; i < 3; i++) {
				if (v.m.ids[3 + i] != 0) {
					sprintf(v.line, (char*) 0x67e4b8,
					    v.m.f88[i],
					    *(char**) 0x99ec10 +
					    v.m.ids[3 + i] * 0x41 + 1);
				}
			}
		}
		{
			char* tpx = *(char**) (o + 0x16c);
			int s = v.m.slots[0];

			if (s == -1) {
				s = v.m.slots[3];
			}
			v.m.type = 0xb;
			v.m.state = *(int*) (0x7f4ca0 +
			    *(unsigned short*) (tpx + 0x27) * 0x21c + 4);
			v.m.f0c = *(int*) (tpx + 1);
			v.m.p28 = *(int*) 0x7f4c00;
			v.m.p2c = *(int*) 0x7f4c04;
			v.m.p30 = *(int*) 0x7f4c08;
			v.m.p34 = *(unsigned short*) 0x7f4c0c;
			v.m.flag2 = 1;
			v.m.f58 = *(int*) (r + 2);
			v.m.f5c = s;
			v.m.f60 = *(int*) (o + 4);
			if (*(int*) 0x100b0a4 == 0) {
				fcn_004c5530((int) &v.m);
				*(int*) 0x772620 = *(int*) 0x772620 + 1;
			}
		}
	}

tail:
	{
		char* tpx = *(char**) (o + 0x16c);
		char* nx = (char*) fcn_00502cd0(*(int*) (tpx + 0x5d), 3, 6,
		    4, 0x1d, 3, *(unsigned short*) (tpx + 0x27));

		if (nx != r) {
			while (gm_NextEntityQueryMatch() != r) {
				;
			}
		}
		r = gm_NextEntityQueryMatch();
	}
	goto next_request;
}
