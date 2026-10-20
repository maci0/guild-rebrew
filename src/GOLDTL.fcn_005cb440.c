#include <string.h>

/* One 0x21c-byte record of the 0x7f4ca0 entity table. Only the fields this
 * body reads are named; the rest stays padding. */
typedef struct Ent {
	unsigned short id;        /* 0x00 */
	unsigned char kind;       /* 0x02 */
	char pad3;                /* 0x03 */
	int key;                  /* 0x04 */
	char pad8;                /* 0x08 */
	unsigned char b9;         /* 0x09 */
	char padA[0x50 - 0xa];
	unsigned short w50;       /* 0x50 */
	char pad52[0x58 - 0x52];
	unsigned char b58;        /* 0x58 */
	char pad59[0x5c - 0x59];
	int sel[8];               /* 0x5c */
	char pad7c[0x21c - 0x7c];
} Ent;
// SIZE 0x21c

/* One 0x38-byte result row. */
typedef struct Row {
	Ent* ent;                 /* 0x00 */
	char pad4[0x2c - 4];
	int cls;                  /* 0x2c */
	int val;                  /* 0x30 */
	char pad34[4];            /* 0x34 */
} Row;
// SIZE 0x38

/* Iterator node returned by fcn_005463a0 / fcn_005462a0. */
typedef struct Node {
	char pad0[0xac];
	int keyac;                /* 0xac */
	int b0;                   /* 0xb0 */
} Node;
// SIZE 0xb4

int __cdecl fcn_00508e40(int);
void __cdecl fcn_005ca560(Row*);
int __cdecl fcn_005cf720(int, int, int, int);
Node* __cdecl fcn_005462a0(void);
Node* __cdecl fcn_005463a0(int, int, int);

extern unsigned char g_slot_table[];

/* ADDRESS: GOLDTL 0x005cb440 */
int __cdecl fcn_005cb440(Ent* a0, int a1, Row* a2, int a3)
{
	Ent* e;
	Node* p;
	Row* o;
	int n;
	int i;

	n = 0;
	if (a1 == 0) {
		for (e = (Ent*) g_slot_table; (int) e < 0x85a0a0;
		     e = (Ent*) ((char*) e + 0x21c)) {
			if (e == a0) {
				continue;
			}
			if (e->id == 0xffff) {
				continue;
			}
			if (e->kind >= 0xa) {
				continue;
			}
			for (i = 0; i < 8; i++) {
				if (a0->sel[i] == e->key) {
					goto matched1;
				}
			}
			if (e->w50 != a0->w50) {
				continue;
			}
			if (e->b58 != a0->b58) {
				continue;
			}
matched1:
			n++;
		}
		p = fcn_005463a0(1, 0, 0x41);
		while (p != 0) {
			if (p->keyac == a0->key) {
				return n + 1;
			}
			p = fcn_005462a0();
		}
		return n;
	}
	memset(a2, 0, a1 * 0x38);
	o = a2;
	e = (Ent*) g_slot_table;
	while (n < a1 && (int) e < 0x85a0a0) {
		if (e == a0) {
			goto next;
		}
		if (e->id == 0xffff) {
			goto next;
		}
		if (e->kind >= 0xa) {
			goto next;
		}
		for (i = 0; i < 8; i++) {
			if (a0->sel[i] == e->key) {
				goto matched2;
			}
		}
		if (e->w50 != a0->w50) {
			goto next;
		}
		if (e->b58 != a0->b58) {
			goto next;
		}
		o->ent = e;
		o->cls = 2 + (e->b9 != 0);
		goto accept2;
matched2:
		o->ent = e;
		switch (i) {
		case 0:
			o->cls = 4 + (e->b9 != 0);
			break;
		case 1:
			o->cls = 0;
			break;
		case 2:
			o->cls = 1;
			break;
		default:
			o->cls = 6 + (e->b9 != 0);
			break;
		}
accept2:
		n++;
		o = (Row*) ((char*) o + 0x38);
next:
		e = (Ent*) ((char*) e + 0x21c);
	}
	if (n < a1) {
		p = fcn_005463a0(1, 0, 0x41);
		while (p != 0) {
			if (p->keyac == a0->key) {
				e = (Ent*) fcn_00508e40(p->b0);
				if (e != 0 && e->key != a0->sel[0]) {
					o = &a2[n];
					o->ent = e;
					o->cls = 8 + (e->b9 != 0);
					n++;
				}
				break;
			}
			p = fcn_005462a0();
		}
	}
	o = a2;
	for (i = 0; i < n; i++) {
		fcn_005ca560(o);
		o->val = fcn_005cf720(a0->id, o->ent->id, a3, 0);
		o = (Row*) ((char*) o + 0x38);
	}
	return n;
}
