

typedef struct Blk24 {
	unsigned char kind;
	char pad1[3];
	int a;
	int b;
	int c;
	int d;
	float f;
} Blk24;
// SIZE 0x18

#include "client_types.h"

extern pos14_7f4c00 g_7f4c00;
extern unsigned char g_773d75;
extern unsigned char* lpGebaeudeINST;
extern unsigned char* lpGebaeudePROT;

unsigned short __cdecl gm_RandomMod(int n);
char* __cdecl fcn_0050e4a0(int n);
char* __cdecl fcn_00502cd0(int, int, int, int, int);
int __cdecl fcn_0050b810(int a, unsigned char b);
int __cdecl fcn_00495400(int kind, int id, int n, Blk24* b1, Blk24* b2);
int __cdecl fcn_004a4bb0(char* a1, char* e, int a3, Blk24* b1, Blk24* b2, int want);

/* The fallback's b1.kind is never written (as in the reference). The
 * pair structs are block-scoped: at function scope the b1.kind store is
 * scheduled ahead of the b1.a load. */
int __cdecl fcn_0049e1e0(char* a1, char* e, int a3, Blk24* o1, Blk24* o2)
{
	unsigned char* rec;
	unsigned char* fr[3];
	int n[3];
	int val;
	int r;
	char* q;
	char lvl;

	fr[0] = 0;
	fr[1] = 0;
	n[0] = 0;
	n[1] = 0;
	if (g_7f4c00.a < 4 || a3 != 0 || e[0x166] != 0xa || a1 != 0) {
		return 0;
	}
	q = fcn_0050e4a0(1);
	if (q == 0) {
		return 0;
	}
	a1 = fcn_00502cd0(*(int*) (q + 0x5d), 2, 6, 0, 0x115);
	val = fcn_0050b810(*(int*) (a1 + 0x14), g_773d75);
	if (val < (gm_RandomMod(3000) + 1000) * 32) {
		return 0;
	}
	rec = lpGebaeudeINST;
	for (a3 = 0; a3 < 0x100; a3++) {
		if (rec[0] != 0 && lpGebaeudePROT[rec[0] * 0x24d] == 3 && !(rec[0x5a] & 4)) {
			lvl = rec[0x5c];
			if (lvl < gm_RandomMod(0x40) + 0x25) {
				Blk24 b1;
				Blk24 b2;

				b1.kind = 4;
				b1.a = *(int*) (rec + 1);
				b1.b = 1;
				if (lvl < 0x21) {
					b1.d = 50;
				} else {
					b1.d = lvl < 0x42 ? 30 : 10;
				}
				b2.a = *(int*) (a1 + 2);
				b2.b = val;
				b2.kind = 1;
				b2.d = 1;
				r = fcn_00495400(0xf, *(unsigned short*) e, 0, &b1, &b2);
				if (r != 0) {
					*o1 = b1;
					*o2 = b2;
					return r;
				}
			}
			if (rec[0] != 10) {
				if (rec[0] == 9) {
					n[1]++;
					if (!(rec[0x5a] & 0x41)) {
						fr[1] = rec;
					}
				} else {
					n[0]++;
					if (!(rec[0x5a] & 0x41)) {
						fr[0] = rec;
					}
				}
			}
		}
		rec += 0xa9;
	}
	if (gm_RandomMod(8) != 0) {
		return 0;
	}
	if (n[0] != 0 && fr[0] != 0) {
		o1->kind = 4;
		o1->a = 9;
		o1->b = 1;
		o2->kind = 4;
		o2->a = *(int*) (fr[0] + 1);
		o2->b = 1;
		return 0x2f;
	}
	if (n[1] != 0 && fr[1] != 0) {
		o1->kind = 4;
		o1->a = 10;
		o1->b = 1;
		o2->kind = 4;
		o2->a = *(int*) (fr[1] + 1);
		o2->b = 1;
		return 0x2f;
	}
	{
		Blk24 b1;
		Blk24 b2;

		b1.a = 8;
		b1.b = 1;
		b2.kind = 0;
		b2.a = 0;
		b2.b = 0;
		if (fcn_004a4bb0(0, e, 1, &b1, &b2, 1) != 0) {
			*o1 = b1;
			*o2 = b2;
			return 0x2f;
		}
	}
	return 0;
}
