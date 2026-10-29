#include "Develop/DieGildeAddOn/game/spiel.h"
#include "Develop/DieGildeAddOn/game/game_data.h"

/* g_100b0c0: 0x40-byte building records used by the filter.
 * g_868c40: 88 x 0x18 client records used when a building has no parent. */
typedef struct {
	int type;             /* 0x00 */
	int parent;           /* 0x04 */
	char pad8[0x14];
	float divisor;        /* 0x1c */
	char pad20[4];
	int used;             /* 0x24 */
	int stock;            /* 0x28 */
	int capacity;         /* 0x2c */
	char pad30[0x10];
} Seg486640;

typedef struct {
	char* name;           /* 0x00 */
	int field4;           /* 0x04 */
	int field8;           /* 0x08 */
	int limit;            /* 0x0c */
	char pad10[8];
} Client486640;

extern Seg486640 g_100b0c0[];
extern char g_100d0c0[];
#include "GOLDTL.fcn_00486640_gconf.h"
extern int g_86805c;

int __cdecl fcn_00503a70(int type);
int __cdecl fcn_00486640(char* a0, int* a1, int a2);

/* ADDRESS: GOLDTL 0x00486640 */
int __cdecl fcn_00486640(char* a0, int* a1, int a2)
{
	int* p;
	int off;
	int found;
	int idx;
	int i;
	int scale;
	int word;
	int clamp;
	int lim;
	int t;
	int sc;
	int w;
	int n;
	float fl;
	float ratio;
	Client486640* rec;
	Seg486640* seg;

	off = 0x26;
	p = a1 + 1;
	do {
		if (*p < 0) {
			goto next;
		}
		seg = &g_100b0c0[*p];
		word = *(unsigned short*) (g_item_def_table + a1[0] * 0x41 + off);
		if (seg->stock < word) {
			if (a2 != 0) {
				return 0;
			}
			if (seg->capacity == 0) {
				return 0;
			}
			if (seg->used == 0
			    && seg->type != 0x1c7 && seg->type != 0x1c4
			    && seg->type != 0x1c5 && seg->type != 0x1c6
			    && seg->type != 0x2af && seg->type != 0x2b0
			    && seg->type != 0x1c1 && seg->type != 0x1c2
			    && seg->type != 0x1c3) {
				if (seg->parent != -1) {
					if (!fcn_00486640(a0, (int*) (g_100d0c0 + seg->parent * 0x58), 0)) {
						return 0;
					}
				} else {
					fcn_00503a70(seg->type);
					found = 0;
					idx = 0;
					i = 0x26;
					rec = g_868c40;
					do {
						if (idx >= g_86805c) {
							return 0;
						}
						if (rec->name != *(char**) (a0 + 0x16c)
						    && gm_GetBuildingTypeCategory((unsigned char) *rec->name) != 2
						    && rec->field8 != 0) {
							lim = rec->limit;
							w = *(unsigned short*) (g_item_def_table + a1[0] * 0x41 + i);
							if (lim >= w) {
								if (*(short*) (rec->name + 0x27) == *(short*) (*(int*) (a0 + 0x16c) + 0x27)) {
									found = 1;
								} else {
									sc = *(int*) ((char*) a1 + 0x40) >> 1;
									if (sc < 1) {
										sc = 1;
									}
									t = w * sc - seg->stock - seg->used;
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
									if (n > lim) {
										n = lim;
									}
									if (n >= w) {
										found = 1;
									}
								}
							}
						}
						idx++;
						i += 2;
						rec++;
					} while (!found);
				}
			}
		}
next:
		p++;
		off += 2;
	} while (off < 0x2e);
	return 1;
}
