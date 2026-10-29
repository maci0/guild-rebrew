#include <string.h>

#include "client_types.h"

typedef Rec2d_9a3800 Rec2d;
typedef Pair_99f800 Pair;

/* SIZE 0x21c */
typedef struct {
	unsigned short id;
	unsigned char type;
	char pad3;
	int owner;
	char pad8[0x21c - 8];
} Obj;

extern Rec2d g_9a3800[512];
extern Pair g_99f800[0x800];
extern char g_7f4ca0[];

int __cdecl fcn_004f36e0(int b);

/* ADDRESS: GOLDTL 0x004f6040 */
int __cdecl fcn_004f6040(int* ids, int* d, unsigned short k)
{
	int list[0x200];
	char* e;
	char* p;
	int key;
	int n;
	int m;
	int i;
	int j;
	int c;
	int v;
	int s;
	int t;

	n = 0;
	m = 0;
	for (i = 0; i < 0x20; i++) {
		ids[i] = -1;
		d[i] = 0;
	}
	memset(list, 0xff, 0x200 * 4);
	e = g_7f4ca0 + k * 0x21c;
	key = *(int*) (e + 4);
	for (i = 0; i < 0x800; i++) {
		if (g_99f800[i].owner == key) {
			s = fcn_004f36e0(g_99f800[i].key);
			if (s != -1 && g_9a3800[s].x25 == 1) {
				list[m] = g_9a3800[s].x16;
				m++;
			}
		}
	}
	p = list;
	for (i = 1; i <= 0x200; i++) {
		v = *(int*) p;
		if (v != -1) {
			*(int*) p = -1;
			n++;
			c = 1;
			for (j = i; j < 0x200; j++) {
				if (list[j] == v) {
					c++;
					list[j] = -1;
				}
			}
			if (d[0x1f] < c) {
				d[0x1f] = c;
				ids[0x1f] = v;
			}
			for (j = 0x1f; j > 0; j--) {
				if (d[j - 1] < d[j]) {
					t = ids[j - 1];
					ids[j - 1] = ids[j];
					ids[j] = t;
					t = d[j - 1];
					d[j - 1] = d[j];
					d[j] = t;
				}
			}
		}
		p += 4;
	}
	return n <= 0x20 ? n : 0x20;
}
