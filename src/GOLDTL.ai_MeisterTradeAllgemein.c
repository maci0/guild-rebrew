/*
 * General master trade decisions: the master walks the producer records and
 * the town stock, prices the goods, fills a request message and sends it.
 *
 * Entire native body 0x48b220-0x48c5a0 transcribed (1446 instructions,
 * frame 0x694). Block boundaries in comments are offsets into that range.
 */

#include <stdio.h>
#include <string.h>

typedef struct {
	int x0;
	int n;
	int x8[16];
	unsigned short x48[16];
	int x68[16];
	int xa8;
	int xac;
	int xb0;
	char* xb4;
} Stats; /* 0xb8 */

typedef struct {
	int f00;              /* +0x00 */
	unsigned char type;   /* +0x04 */
	unsigned char f05;
	unsigned char flag;   /* +0x06 */
	unsigned char f07;
	int state;            /* +0x08 */
	int f0c;              /* +0x0c */
	int f10;
	int f14;
	int f18;
	char pad1c[0x28 - 0x1c];
	int p28;
	int p2c;
	int p30;
	unsigned short p34;
	unsigned char flag2;  /* +0x36 */
	char pad37[0x58 - 0x37];
	int f58;
	int f5c;
	int f60;              /* +0x60 */
	int slots[6];         /* +0x64 */
	unsigned short ids[6];/* +0x7c */
	int f88[4];           /* +0x88 */
	char pad98[0x9d - 0x98];
	unsigned char skip;   /* +0x9d */
	char pad9e[0xf8 - 0x9e];
} Msg; /* 0xf8 */

typedef struct {          /* producer record, 0x40 bytes */
	int id;               /* +0x00 */
	int f04;
	int f08;              /* +0x08 */
	int f0c;
	int f10;
	int f14;              /* +0x14 */
	int qty18;            /* +0x18 */
	int f1c;
	int f20;
	int f24;
	int qty28;            /* +0x28 */
	int f2c;
	int f30;              /* +0x30 */
	int f34;
	int f38;
	int flags;            /* +0x3c */
} Prod;

typedef struct {          /* town record, 0x58 bytes */
	int id;               /* +0x00 */
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
	int f38;              /* +0x38 */
	int qty3c;            /* +0x3c */
	int f40;              /* +0x40 */
	int qty44;            /* +0x44 */
	int f48;
	int f4c;
	int f50;
	int flags54;          /* +0x54 */
} Town;

extern unsigned char g_773d75;
extern char* g_773d78;
extern int g_7f4c00;
extern int g_7f4c04;
extern int g_7f4c08;
extern unsigned short g_7f4c0c;
extern int g_772620;
extern float g_6628a0;
extern float g_664144;

int __cdecl gm_RandomFloat01(void);
int __cdecl fcn_0047d1b0(void);
int __cdecl fcn_0047d1e0(void);
int __cdecl fcn_004c51f0(int, int, int, int, int, int);
int __cdecl fcn_004c52d0(int, int);
int __cdecl fcn_004c5530(void*);
int __cdecl fcn_00500bb0(void*, int, int, int);
char* __cdecl fcn_00502cd0(int, int, int, ...);
char* __cdecl fcn_00502850(void);
int __cdecl fcn_00503d10(int);
float __cdecl fcn_0050b980(int, int);
float __cdecl fcn_0050bb50(int, unsigned char);
int __cdecl fcn_0050cce0(char*, void*, int);
int __cdecl fcn_0050d2a0(void*);
int __cdecl fcn_0050de80(char*, Stats*);
int __cdecl fcn_0050dfd0(void*, int);
int __cdecl fcn_005462a0(void);
char* __cdecl fcn_005463a0(int, int, int, int, int);

/* ADDRESS: GOLDTL 0x0048b220 */
int __cdecl ai_MeisterTradeAllgemein(char* o, char* bld)
{
	int j;
	int i;
	float fr;
	char* q;
	int* p;
	int acc;
	int sent;
	char* r;
	Prod* pr;
	int price;
	int cnt;
	int tmp;
	int found;
	Town* t;
	unsigned short* ip;
	int n;
	struct {
		Msg m;
		int nslot[2];
		int a1[16];
		unsigned short ids[16];
		int a2[20];
		Stats st;
		char line[0x400];
	} v;

	/* 0x000-0x06e: producer records holding more than a third of demand */
	for (i = 0; i < *(int*) 0x100b0a8; i++) {
		if ((*(int*) (0x100b0c0 + i * 0x40 + 0x3c) & 6) != 0) {
			continue;
		}
		if ((*(int*) (0x100b0c0 + i * 0x40 + 0x3c) & 8) == 0) {
			continue;
		}
		tmp = *(int*) (0x100b0c0 + i * 0x40 + 0x28);
		if (tmp > fcn_0050dfd0(bld,
		    *(int*) (0x100b0c0 + i * 0x40)) / 3) {
			*(int*) (0x100b0c0 + i * 0x40 + 0x18) = tmp;
		}
	}

	/* 0x06f-0x0a0: own building busy flag */
	if ((*(int*) 0x7f4c04 & 0xffff) % 2) {
		if ((*(int*) (o + 0x1b4) & 0x200) == 0) {
			/* 0x0a0-0x198: town stock, selling on a good margin */
			for (i = 0; i < *(int*) 0x100b0ac; i++) {
				t = (Town*) 0x100d0c0 + i;
				if ((t->flags54 & 6) != 0) {
					continue;
				}
				if ((t->flags54 & 8) != 0) {
					tmp = t->qty3c;
					if (tmp <= fcn_0050dfd0(bld,
					    t->id) / 3) {
						continue;
					}
				}
				fr = fcn_0050b980(t->id, 100) /
				    fcn_0050bb50(t->id, g_773d75);
				if (fr >= g_6628a0) {
					continue;
				}
				if (gm_RandomFloat01() * g_664144 < fr) {
					continue;
				}
				t->qty44 = t->qty3c;
				if (o != (char*) 0x100e748) {
					continue;
				}
				sprintf(v.line, (char*) 0x67e6cc, t->qty44,
				    *(char**) 0x99ec10 + t->id * 0x40 +
				    t->id + 1);
			}

			/* 0x198-0x2a5: market stock of the own slot */
			{
				char* tp = *(char**) (o + 0x16c);
				unsigned short slot =
				    *(unsigned short*) (tp + 0x27);
				char* mp = (char*) 0x7f4ca0 + slot * 0x21c;

				if (*(int*) (o + 0x1b8) >= 0xc80) {
					if (fcn_0050d2a0(mp) >= 0x1f40) {
						goto clear_stack;
					}
				}
				acc = *(int*) (o + 0x1b8) <
				    fcn_0050d2a0(mp)
				    ? *(int*) (o + 0x1b8) :
				    fcn_0050d2a0(mp);
				if (acc >= 0x7d00) {
					goto clear_stack;
				}
				i = 0;
				/* 0x2a5-0x334: fill the market up to 32000 */
				for (; i < *(int*) 0x100b0ac && acc < 0x7d00;
				    i++) {
					t = (Town*) 0x100d0c0 + i;
					if ((t->flags54 & 6) != 0) {
						continue;
					}
					price = (int) fcn_0050bb50(t->id,
					    g_773d75);
					tmp = 0x7d00 / price;
					if (tmp < 1) {
						tmp = 1;
					}
					t->qty44 = tmp < t->qty3c ?
					    tmp : t->qty3c;
					acc += tmp * price;
					if (o == (char*) 0x100e748) {
						sprintf(v.line,
						    (char*) 0x67e6ac,
						    t->qty44,
						    *(char**) 0x99ec10 +
						    t->id * 0x40 +
						    t->id + 1);
					}
				}
			}

clear_stack:
			/* 0x334-0x3a7: dump full town stock */
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
					tmp = t->qty3c;
				}
				t->qty44 = tmp;
				if (o == (char*) 0x100e748) {
					sprintf(v.line, (char*) 0x67e674,
					    tmp, *(char**) 0x99ec10 +
					    t->id * 0x40 + t->id + 1);
				}
			}
		}
		*(int*) (o + 0x1b4) |= 0x200;
	} else {
		*(int*) (o + 0x1b4) &= ~0x200;
	}

	/* 0x3a7-0x572: request loop */
	do {
		{
			char* tp = *(char**) (o + 0x16c);

			fcn_0050cce0(tp, v.nslot, 0);
			r = fcn_00502cd0(*(int*) (tp + 0x5d), 3, 6, 4,
			    0x1d, 3, *(unsigned short*) (tp + 0x27));
		}
		if (r == 0) {
			return 1;
		}
next_request:
		if (*(int*) (r + 0x1c) !=
		    *(int*) (*(char**) (o + 0x16c) + 1)) {
			goto Tail;
		}
		if (*(unsigned char*) (r + 0x12) < 0x21) {
			/* 0x3bd-0x572: unload the cart */
			char* tp = *(char**) (o + 0x16c);
			unsigned short slot =
			    *(unsigned short*) (tp + 0x27);

			memset(&v.m, 0, sizeof(v.m));
			v.m.type = 0x10;
			v.m.state = *(int*) (0x7f4ca0 + slot * 0x21c + 4);
			v.m.f0c = *(int*) (tp + 1);
			v.m.p28 = g_7f4c00;
			v.m.p2c = g_7f4c04;
			v.m.p30 = g_7f4c08;
			v.m.p34 = g_7f4c0c;
			v.m.flag2 = 1;
			fcn_00500bb0(&v.m.p28, 0, 0, 0xa);
			v.m.f58 = *(int*) (r + 2);
			v.m.slots[0] = 5;
			*(int*) ((char*) &v.m + 0x84) = 0;
			v.m.f5c = 0x64 - *(unsigned char*) (r + 0x12);
			fcn_004c5530(&v.m);
			goto Tail;
		}
		/* 0x572-0x5f0: is the cart already unloaded? */
		{
			char* x = fcn_005463a0(
			    *(int*) (*(char**) (o + 0x16c) + 1),
			    2, 0, 0xb, 3);

			if (x != 0) {
				while (*(int*) (x + 0xac) !=
				    *(int*) (r + 2)) {
					if (!fcn_005462a0()) {
						break;
					}
				}
				if (*(int*) (x + 0xac) ==
				    *(int*) (r + 2)) {
					goto Tail;
				}
			}
		}
		/* 0x572-0x975: collect the cart's stock */
		memset(&v.m, 0, sizeof(v.m));
		cnt = 0;
		sent = 0;
		n = 0;
		if (fcn_0047d1e0() > fcn_0047d1b0()) {
			v.m.skip = 1;
		}
		for (i = 0; i < 3; i++) {
			v.m.ids[i] = 0;
			v.m.slots[i] = -1;
			v.m.ids[3 + i] = 0;
			v.m.slots[3 + i] = -1;
		}
		fcn_0050de80(r, &v.st);
		q = fcn_00502cd0(*(int*) (r + 0x14), 1, 0, 0x1dd);
		i = 0;
		if (v.st.x0 <= 0) {
			goto after_auto;
		}
		/* 0x5f0-0x975: unload every cart position */
		ip = v.st.x48;
		p = v.st.x68;
		for (; i < v.st.x0; i++, ip++, p++) {
			if (*ip == 0) {
				continue;
			}
			sprintf(v.line, (char*) 0x67e868,
			    *(char**) (o + 0x16c) + 5, *p,
			    *(char**) 0x99ec10 + *ip * 0x40 + *ip + 1);

			pr = 0;
			for (t = (Prod*) 0x100b0c0;
			    (char*) t < (char*) 0x100d0c0;
			    t = (Prod*) ((char*) t + 0x40)) {
				if (t->id == (int) *ip) {
					pr = t;
					break;
				}
			}
			if (pr == 0) {
				goto fake_auto;
			}
			if ((*(unsigned char*) ((char*) pr + 0x3c) & 2) == 0) {
				goto fake_auto;
			}

			found = 0;
			j = 0;
			/* 0x975-0x7a: amount already routed to this id */
			for (; j < v.nslot[0] && !found; j++) {
				if (v.ids[j] != *ip) {
					continue;
				}
				sprintf(v.line, (char*) 0x67e828,
				    *(char**) 0x99ec10 + *ip * 0x40 + *ip + 1,
				    *(char**) (o + 0x16c) + 5);
				tmp = v.a1[j] - v.a2[j];
				tmp = *p < tmp ? *p : tmp;
				if (tmp != 0) {
					sprintf(v.line, (char*) 0x67e358,
					    *(int*) (bld + 2),
					    *(int*) (q + 2), (int) *ip,
					    tmp, g_773d75, 0);
					fcn_004c51f0(*(int*) (bld + 2),
					    *(int*) (q + 2), (int) *ip,
					    tmp, g_773d75, 0);
				}
				*p -= tmp;
				if (*p == 0) {
					*ip = 0;
				}
				v.a2[j] += tmp;
				found = 1;
			}
			if (found) {
				goto after_slot;
			}
			j = 0;
			/* 0x7a-0x8b: amount that still fits a free slot */
			for (; j < v.nslot[0] && !found; j++) {
				if (v.ids[j] != 0) {
					continue;
				}
				sprintf(v.line, (char*) 0x67e7f0,
				    *(char**) (o + 0x16c) + 5,
				    *(char**) 0x99ec10 + *ip * 0x40 + *ip + 1);
				tmp = fcn_0050dfd0(bld, (int) *ip);
				tmp = *p < tmp ? *p : tmp;
				sprintf(v.line, (char*) 0x67e358,
				    *(int*) (bld + 2), *(int*) (q + 2),
				    (int) *ip, tmp, g_773d75, 0);
				fcn_004c51f0(*(int*) (bld + 2),
				    *(int*) (q + 2), (int) *ip, tmp,
				    g_773d75, 0);
				*p -= tmp;
				if (*p == 0) {
					*ip = 0;
				}
				v.ids[j] = *ip;
				v.a2[j] += tmp;
				found = 1;
			}
			if (found) {
				goto fake_auto;
			}
			j = 0;
			/* 0x8b-0xa7b: fake sale out of the store */
			for (; j < v.nslot[0]; j++) {
				Prod* w;

				found = 0;
				for (w = (Prod*) 0x100b0fc;
				    (char*) w < (char*) 0x100d0fc &&
				    !found;
				    w = (Prod*) ((char*) w + 0x40)) {
					if (*(int*) ((char*) w - 0x3c) !=
					    (int) v.ids[j]) {
						continue;
					}
					if (*(unsigned char*) w & 2) {
						if (*(int*) ((char*) w -
						    0xc) <= *(int*)
						    ((char*) pr + 0x30)) {
							continue;
						}
					}
					sprintf(v.line, (char*) 0x67e7a0,
					    *(char**) (o + 0x16c) + 5,
					    v.a2[j],
					    *(char**) 0x99ec10 +
					    (int) v.ids[j] * 0x40 +
					    (int) v.ids[j] + 1);
					tmp = (int) fcn_0050bb50(
					    (int) v.ids[j], g_773d75);
					price = tmp;
					sprintf(v.line, (char*) 0x67e358,
					    -1, *(int*) (bld + 2),
					    (int) v.ids[j], v.a2[j],
					    g_773d75, (double) price);
					tmp = (int) fcn_0050bb50(
					    (int) v.ids[j], g_773d75);
					fcn_004c51f0(-1,
					    *(int*) (bld + 2),
					    (int) v.ids[j], v.a2[j],
					    g_773d75, tmp);
					price = (int) (fcn_0050bb50(
					    (int) v.ids[j], g_773d75) +
					    *(int*) (o + 0x1b8));
					*(int*) (o + 0x1b8) = price;
					v.ids[j] = 0;
					v.a2[j] = 0;
					tmp = fcn_0050dfd0(bld,
					    (int) *ip);
					tmp = *p < tmp ? *p : tmp;
					sprintf(v.line, (char*) 0x67e358,
					    *(int*) (bld + 2),
					    *(int*) (q + 2), (int) *ip,
					    tmp, g_773d75, 0);
					fcn_004c51f0(*(int*) (bld + 2),
					    *(int*) (q + 2), (int) *ip,
					    tmp, g_773d75, 0);
					*p -= tmp;
					if (*p == 0) {
						*ip = 0;
					}
					v.ids[j] = *ip;
					v.a2[j] += tmp;
					found = 1;
				}
			}
after_slot:
			if (*p != 0) {
				goto fake_auto;
			}
fake_auto:
			/* 0xa7b-0xbe0: cart without a market place */
			if (*p != 0) {
				sprintf(v.line, (char*) 0x67e750,
				    *(char**) (o + 0x16c) + 5, *p,
				    *(char**) 0x99ec10 +
				    (int) *ip * 0x40 + (int) *ip + 1);
				price = (int) fcn_0050bb50((int) *ip,
				    g_773d75);
				sprintf(v.line, (char*) 0x67e358, -1,
				    *(int*) (bld + 2), (int) *ip, *p,
				    g_773d75, (double) price);
				tmp = (int) fcn_0050bb50((int) *ip,
				    g_773d75);
				fcn_004c51f0(-1, *(int*) (bld + 2),
				    (int) *ip, *p, g_773d75, tmp);
				price = (int) (fcn_0050bb50((int) *ip,
				    g_773d75) + *(int*) (o + 0x1b8));
				*ip = 0;
				*p = 0;
				*(int*) (o + 0x1b8) = price;
			}
		}
after_auto:
		i = 0;
		p = v.a2;
		ip = v.ids;
		/* 0xbe0-0x136f: route the amounts into request slots */
		for (; i < v.nslot[0]; i++, ip++, p++) {
			int id = *ip;
			if (id == 0) {
				goto next_collect;
			}
			found = 0;
			for (j = 0, t = (Town*) 0x100d0c0;
			    j < *(int*) 0x100b0ac && !found;
			    j++, t = (Town*) ((char*) t + 0x58)) {
				if (t->id == id) {
					found = 1;
				}
			}
			if (found) {
				goto next_collect;
			}
			found = 0;
			for (j = 0, pr = (Prod*) 0x100b0c0;
			    j < *(int*) 0x100b0a8 && !found;
			    j++, pr = (Prod*) ((char*) pr + 0x40)) {
				if (pr->id == id) {
					found = 1;
				}
			}
			if (found) {
				goto next_collect;
			}
			tmp = fcn_0050dfd0(q, id);
			j = 0;
			if (*p == 0) {
				goto clear_slot;
			}
			for (; j < v.st.x0; j++) {
				if (v.st.x48[j] != 0 && v.st.x48[j] != id) {
					continue;
				}
				tmp = *p < tmp ? *p : tmp;
				sprintf(v.line, (char*) 0x67e358,
				    *(int*) (bld + 2), *(int*) (q + 2),
				    id, tmp, g_773d75, 0);
				fcn_004c51f0(*(int*) (bld + 2),
				    *(int*) (q + 2), id, tmp,
				    g_773d75, 0);
				v.m.ids[cnt] = id;
				v.m.slots[cnt] = *(int*) (g_773d78 + 1);
				cnt++;
				*p -= tmp;
				v.st.x48[j] = id;
				if (*p == 0) {
					break;
				}
			}
			if (*p != 0) {
				continue;
			}
clear_slot:
			fcn_004c52d0(*(int*) (bld + 2), id);
			*ip = 0;
next_collect:
			;
		}

		/* 0x136f-0x1483: sell the collected slots */
		if (cnt < 3) {
			for (i = 0;
			    i < *(int*) 0x100b0ac && cnt < 3; i++) {
				Town* w = (Town*) 0x100d104 + i;

				if (w->qty44 == 0) {
					continue;
				}
				tmp = fcn_0050dfd0(q, w->id);
				j = 0;
				if (w->qty44 == 0) {
					continue;
				}
				for (; j < v.st.x0; j++) {
					if (v.st.x48[j] != 0 &&
					    v.st.x48[j] != w->id) {
						continue;
					}
					tmp = w->qty44 < tmp ?
					    w->qty44 : tmp;
					sprintf(v.line,
					    (char*) 0x67e358,
					    *(int*) (q + 2),
					    *(int*) (bld + 2),
					    (int) w->id, tmp,
					    g_773d75, 0);
					fcn_004c51f0(*(int*) (q + 2),
					    *(int*) (bld + 2),
					    (int) w->id, tmp,
					    g_773d75, 0);
					v.m.ids[cnt] = w->id;
					v.m.slots[cnt] =
					    *(int*) (g_773d78 + 1);
					cnt++;
					w->qty44 -= tmp;
					v.st.x48[j] = w->id;
					if (w->qty44 == 0) {
						break;
					}
				}
			}
		}
		if (cnt < 3) {
			for (i = 0;
			    i < *(int*) 0x100b0a8 && cnt < 3; i++) {
				Prod* w = (Prod*) 0x100b0c0 + i;

				if (w->qty18 == 0) {
					continue;
				}
				if (!fcn_00503d10(w->id)) {
					sprintf(v.line,
					    (char*) 0x67e4e8,
					    *(char**) (o + 0x16c) + 5,
					    w->qty18,
					    *(char**) 0x99ec10 +
					    w->id * 0x40 + w->id + 1);
					tmp = (int) fcn_0050bb50(w->id,
					    g_773d75);
					price = tmp;
					sprintf(v.line,
					    (char*) 0x67e358, -1,
					    *(int*) (bld + 2), w->id,
					    w->qty18, g_773d75, price);
					tmp = (int) fcn_0050bb50(w->id,
					    g_773d75);
					fcn_004c51f0(-1,
					    *(int*) (bld + 2), w->id,
					    w->qty18, g_773d75, tmp);
					w->qty18 = 0;
					continue;
				}
				tmp = fcn_0050dfd0(q, w->id);
				j = 0;
				if (w->qty18 == 0) {
					continue;
				}
				for (; j < v.st.x0; j++) {
					if (v.st.x48[j] != 0 &&
					    v.st.x48[j] != w->id) {
						continue;
					}
					tmp = w->qty18 < tmp ?
					    w->qty18 : tmp;
					sprintf(v.line,
					    (char*) 0x67e358,
					    *(int*) (bld + 2),
					    *(int*) (q + 2), w->id,
					    tmp, g_773d75, 0);
					fcn_004c51f0(*(int*) (bld + 2),
					    *(int*) (q + 2), w->id,
					    tmp, g_773d75, 0);
					v.m.ids[cnt] = w->id;
					v.m.slots[cnt] =
					    *(int*) (g_773d78 + 1);
					cnt++;
					w->qty18 -= tmp;
					v.st.x48[j] = w->id;
					if (w->qty18 == 0) {
						break;
					}
				}
			}
		}
		/* 0x1483-0x14ff: leftover producer stock becomes a request */
		cnt = 0;
		sent = 0;
		for (i = 0; i < *(int*) 0x100b0a8 && n < 3; i++) {
			Prod* w = (Prod*) 0x100b0d4 + i;

			if (*(int*) (char*) w == 0) {
				continue;
			}
			tmp = fcn_0050dfd0(q, *(int*) ((char*) w - 0x14));
			{
				int* x = *(int**) ((char*) w - 0xc);

				if (x == 0) {
					continue;
				}
				v.m.ids[3 + n] = *(unsigned short*)
				    ((char*) w - 0x14);
				v.m.slots[3 + n] = *(int*) ((char*) x + 1);
				if (tmp < *(int*) w) {
					v.m.f88[n] = tmp;
				} else {
					v.m.f88[n] = *(int*) w;
				}
				n++;
				*(int*) w = 0;
				sent = 1;
			}
		}
		/* 0x14ff-0x1550: log and send */
		if (sent) {
			if (o == (char*) 0x100e748) {
				for (i = 0; i < 3; i++) {
					if (v.m.ids[i] != 0) {
						sprintf(v.line,
						    (char*) 0x67e4d8,
						    *(char**) 0x99ec10 +
						    (int) v.m.ids[i] * 0x40 +
						    (int) v.m.ids[i] + 1);
					}
				}
				for (i = 0; i < 3; i++) {
					if (v.m.ids[3 + i] != 0) {
						sprintf(v.line,
						    (char*) 0x67e4b8,
						    v.m.f88[i],
						    *(char**) 0x99ec10 +
						    (int) v.m.ids[3 + i] *
						    0x40 +
						    (int) v.m.ids[3 + i] + 1);
					}
				}
			}
			{
				char* tp = *(char**) (o + 0x16c);
				unsigned short slot =
				    *(unsigned short*) (tp + 0x27);
				int x = v.m.slots[0];

				if (x == -1) {
					x = v.m.slots[3];
				}
				v.m.type = 0xb;
				v.m.state = *(int*) (0x7f4ca0 +
				    slot * 0x21c + 4);
				v.m.f0c = *(int*) (tp + 1);
				v.m.p28 = g_7f4c00;
				v.m.p2c = g_7f4c04;
				v.m.p30 = g_7f4c08;
				v.m.p34 = g_7f4c0c;
				v.m.flag2 = 1;
				v.m.f58 = *(int*) (r + 2);
				v.m.f5c = x;
				v.m.f60 = *(int*) (o + 4);
				if (*(int*) 0x100b0a4 == 0) {
					fcn_004c5530(&v.m);
					g_772620++;
				}
			}
		}
Tail:
		{
			char* tp = *(char**) (o + 0x16c);

			tmp = (int) fcn_00502cd0(*(int*) (tp + 0x5d),
			    3, 6, 4, 0x1d, 3,
			    *(unsigned short*) (tp + 0x27));
		}
		if ((char*) tmp != r) {
			while (fcn_00502850() != r) {
				;
			}
		}
		r = fcn_00502850();
	} while (r != 0);

	return 1;
}
