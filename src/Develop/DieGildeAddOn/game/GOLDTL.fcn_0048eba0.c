#include <string.h>

typedef struct Slot {
	int id;
	int a;
	int b;
	char* item;
} Slot;
// SIZE 0x10

typedef struct Counts {
	int total;
	int blocked;
	int free;
} Counts;

typedef struct F8 {
	int mask;
	int b;
} F8;
// SIZE 0x8

typedef struct Msg {
	unsigned char type;
	char pad[3];
	int a;
	int b;
	int c;
	int d;
	float f;
} Msg;
// SIZE 0x18

#include "client_types.h"

extern pos14_7f4c00 g_7f4c00;
extern char g_7f4ca4[];
extern char* g_77261c;

unsigned short __cdecl gm_RandomMod(int n);
void __cdecl fcn_004a51d0(char* e, int n, Slot* slots, Counts* cnt);
int __cdecl fcn_004a5340(char* e, int a, int* b, int c, float r, int* out);
int __cdecl fcn_004a5e60(char* p, int kind, F8 f, int c, float r, int* out);

/* Slot chooser for the execution scene. A fifteen-entry slot table is matched
 * against the entity's inventory; the blocked counter and the first slot's
 * availability select either a pickup or a drop message, and one slot is
 * picked at random. */
/* ADDRESS: GOLDTL 0x0048eba0 */
int __cdecl fcn_0048eba0(int kind, char* e, int busy, Msg* a, Msg* b)
{
	Slot slot[0xf];
	Counts cnt;
	F8 f;
	int picked;
	register int idx;

	if (busy != 0) {
		return 0;
	}
	if (kind != 0x48 && kind != 0) {
		return 0;
	}
	memset(slot, 0, sizeof slot);
	slot[0].id = 0x2b8;
	slot[1].id = 0x2bb;
	slot[2].id = 0x2bc;
	slot[3].id = 0x2bf;
	slot[4].id = 0x2c2;
	slot[5].id = 0x2c3;
	slot[6].id = 0x2bd;
	slot[7].id = 0x2c1;
	slot[8].id = 0x2c4;
	slot[9].id = 0x2c5;
	slot[10].id = 0x2c6;
	slot[11].id = 0x2ba;
	slot[12].id = 0x2c0;
	slot[13].id = 0x2be;
	slot[14].id = 0x2b9;
	fcn_004a51d0(e, 0xf, slot, &cnt);
	if ((slot[0].a != 6 || slot[0].item != 0) && cnt.blocked != 0xf) {
		if (slot[0].a < 6) {
			if (slot[0].item == 0) {
				if (*(int*) &g_7f4c00 < 0x14) {
					return 0;
				}
				if (*(unsigned char*) (e + 0xd) <= 4) {
					return 0;
				}
				if (*(int*) &g_7f4c00 % 8 != (*(unsigned int*) (e + 4) & 7)) {
					return 0;
				}
				if (*(unsigned int*) (e + 0x1cc) & 0x40000000) {
					return 0;
				}
				idx = gm_RandomMod(0xf);
				while (slot[idx].a != 0) {
					idx = (idx + 1) % 0xf;
				}
				a->type = 2;
				a->b = 1;
				a->a = slot[idx].id;
				a->f = 0.05f;
				a->d = 1;
				b->type = 0;
				return 0x48;
			}
		} else if (slot[0].item == 0) {
			return 0;
		}
		idx = gm_RandomMod(0xf);
		while (slot[idx].a < 1) {
			idx = (idx + 1) % 0xf;
		}
		a->type = 1;
		a->b = 1;
		a->a = slot[idx].b;
		a->f = 0.05f;
		a->d = 3;
		b->type = 0;
		b->a = -1;
		b->b = -1;
		if (idx < 6) {
			int mask = 0xf00500;
			if (fcn_004a5340(e, 1, &mask, 0, (float) gm_RandomMod(0x20) + 10.0f, &picked)) {
				b->type = 7;
				b->b = -1;
				b->a = *(int*) (g_7f4ca4 + (picked & 0xffff) * 0x21c);
				b->d = 0x48;
				return 0x48;
			}
		} else {
			if (idx == 6) {
			cnt.total = -1;
			f.mask = 0xa0744380;
			f.b = 1;
			if (g_77261c != 0) {
				fcn_004a5e60(g_77261c, 4, f, 0, 100.0f, &cnt.total);
			}
			if (cnt.total != -1 || fcn_004a5e60(e, 6, f, 0, (float) gm_RandomMod(0x20) + 16.0f, &cnt.total)) {
				b->type = 4;
				b->a = cnt.total;
				b->b = -1;
				b->d = 0x48;
				return 0x48;
			}
			}
			if (idx == 7 && *(int*) (e + 0x194) < 3) {
				return 0;
			}
			b->d = 0x48;
			return 0x48;
		}
	}
	return 0;
}
