#include "Develop/DieGildeAddOn/game/spiel.h"
#include "Develop/DieGildeAddOn/game/game_data.h"

/* g_100b0c0: 0x40-byte building records.
 * g_100d0c0: 0x58-byte parent records (recursed into).
 * g_868c40: 0x18-byte client records scanned when a building has no parent. */
typedef struct {
	int type;             /* 0x00 */
	int parent;           /* 0x04 */
	char* name;           /* 0x08 */
	int fc;               /* 0x0c */
	int f10;              /* 0x10 */
	int f14;              /* 0x14 */
	int f18;              /* 0x18 */
	float divisor;        /* 0x1c */
	int f20;              /* 0x20 */
	int used;             /* 0x24 */
	int stock;            /* 0x28 */
	int capacity;         /* 0x2c */
	int f30;              /* 0x30 */
	int f34;              /* 0x34 */
	int f38;              /* 0x38 */
	int flags;            /* 0x3c */
} Seg4868d0;

typedef struct {
	char* name;           /* 0x00 */
	int field4;           /* 0x04 */
	int field8;           /* 0x08 */
	int limit;            /* 0x0c */
	char pad10[8];
} Client4868d0;

typedef struct {
	int f00;              /* 0x00 */
	int f04;              /* 0x04 */
	int f08;              /* 0x08 */
	int f0c;              /* 0x0c */
	int f10;              /* 0x10 */
	int f14;              /* 0x14 */
	int f18;              /* 0x18 */
	float divisor;        /* 0x1c */
	int f20;              /* 0x20 */
	int f24;              /* 0x24 */
	int f28;              /* 0x28 */
	int f2c;              /* 0x2c */
	int f30;              /* 0x30 */
	int f34;              /* 0x34 */
	int f38;              /* 0x38 */
	int f3c;              /* 0x3c */
	int scale;            /* 0x40 */
	int f44;              /* 0x44 */
	int limit;            /* 0x48 */
	int f4c;              /* 0x4c */
	int f50;              /* 0x50 */
	int flags;            /* 0x54 */
} Rec4868d0;

extern Seg4868d0 g_100b0c0[];
extern char g_100d0c0[];
extern Client4868d0 g_868c40[];
extern int g_86805c;

int __cdecl fcn_00503a70(int type);
int __cdecl fcn_004868d0(char* a0, int* a1);

/* ADDRESS: GOLDTL 0x004868d0 */
int __cdecl fcn_004868d0(char* a0, int* a1)
{
	int* p;
	int off;
	int t;
	int idx;
	int n;
	int w;
	int limit;
	int scale;
	float fl;
	float ratio;
	Seg4868d0* seg;
	Client4868d0* rec;
	Rec4868d0* rp;

	off = 0x26;
	p = a1 + 1;
	do {
		if (*p < 0) {
			goto next;
		}
		seg = &g_100b0c0[*p];
		seg->f30 = seg->f30 < a1[18] ? seg->f30 : a1[18];
		seg->flags |= 2;
		if (seg->type == 0x1c7 || seg->type == 0x1c4
		    || seg->type == 0x1c5 || seg->type == 0x1c6
		    || seg->type == 0x2af || seg->type == 0x2b0
		    || seg->type == 0x1c1 || seg->type == 0x1c2
		    || seg->type == 0x1c3 || seg->type == 0x225
		    || seg->type == 0x226 || seg->type == 0x227
		    || seg->type == 0x293 || seg->type == 0x294
		    || seg->type == 0x295) {
			rp = (Rec4868d0*) (g_100d0c0 + seg->parent * 0x58);
			if ((rp->f38 + rp->f3c) * 4 < rp->scale) {
				w = *(unsigned short*) (g_item_def_table + a1[0] * 0x41 + off);
				if (seg->stock + seg->used < w * 4) {
					seg->flags |= 0x10;
				}
			}
		} else {
			if (seg->parent != -1) {
				rp = (Rec4868d0*) (g_100d0c0 + seg->parent * 0x58);
				rp->limit = rp->limit < a1[18] ? rp->limit : a1[18];
				rp->flags |= 2;
				if ((rp->f38 + rp->f3c) * 4 < rp->scale) {
					if (rp->scale > *(unsigned short*) (g_item_def_table + rp->f00 * 0x41 + 0x36)) {
						rp->flags |= 8;
					}
					fcn_004868d0(a0, (int*) rp);
				}
			} else {
				w = *(unsigned short*) (g_item_def_table + a1[0] * 0x41 + off);
				if (seg->stock + seg->used < w * 4) {
					fcn_00503a70(seg->type);
					idx = 0;
					rec = g_868c40;
					for (;;) {
						if (idx >= g_86805c) {
							break;
						}
						if (rec->name != *(char**) (a0 + 0x16c)
						    && gm_GetBuildingTypeCategory((unsigned char) *rec->name) != 2
						    && rec->field8 != 0) {
							limit = rec->limit;
							w = *(unsigned short*) (g_item_def_table + a1[0] * 0x41 + off);
							if (limit >= w) {
								seg->name = rec->name;
								if (*(short*) (rec->name + 0x27) == *(short*) (*(int*) (a0 + 0x16c) + 0x27)) {
									seg->f14 = seg->capacity;
									idx++;
									rec++;
									continue;
								}
								scale = *(int*) ((char*) a1 + 0x40) >> 1;
								if (scale < 1) {
									scale = 1;
								}
								t = w * scale - seg->used - seg->stock;
								n = (seg->capacity >> 1) - seg->used;
								if (t < n) {
									t = n;
								}
								n = seg->capacity - seg->used - 1;
								if (t > n) {
									t = n;
								}
								ratio = (float) *(int*) (a0 + 0x1b8) / seg->divisor;
								fl = (float) t;
								n = (int) (ratio < fl ? ratio : fl);
								if (n > limit) {
									n = limit;
								}
								if (n >= w) {
									seg->f14 = n >= seg->f14 ? n : seg->f14;
								}
							}
						}
						idx++;
						rec++;
					}
				}
			}
		}
next:
		p++;
		off += 2;
	} while (off < 0x2e);
	return 1;
}
