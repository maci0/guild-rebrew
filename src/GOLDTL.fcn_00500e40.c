#include <string.h>

#pragma pack(push, 1)
typedef struct Rec500e {
	char kind;
	char pad1[0x20];
	unsigned char x21;
	char pad22[0x41 - 0x22];
} Rec500e;
/* SIZE 0x41 */

typedef struct Bld500e {
	unsigned char kind;
	char pad1[0x22 - 1];
	unsigned char n;
	unsigned short items[0x100];
} Bld500e;
/* SIZE 0x24d */
#pragma pack(pop)

extern unsigned char* g_868050;
extern char* g_99ec10;

/* ADDRESS: GOLDTL 0x00500e40 */
void __cdecl fcn_00500e40(void)
{
	int kind;
	int i;
	int k;
	int prev;
	unsigned char* bld;
	int count;
	int run;
	int type;
	int j;
	unsigned char* r;
	unsigned char* t;
	int id;
	int tgt;
	int cnt;
	int n;

	memset((void*) 0x8f9480, 0, 0x64);
	for (n = 0; n < 0x2dc; n++) {
		((int*) 0x99e0a0)[n] = 0x58;
	}
	((int*) 0x8f9480)[8] = 0x2f;
	((int*) 0x8f9480)[7] = 0x32;
	((int*) 0x8f9480)[6] = 0x29;
	((int*) 0x8f9480)[10] = 0x21;
	((int*) 0x8f9480)[14] = 0x1e;
	((int*) 0x8f9480)[15] = 0x1f;
	((int*) 0x8f9480)[16] = 0x20;
	((int*) 0x8f9480)[11] = 0x17;
	((int*) 0x8f9480)[12] = 0x35;
	((int*) 0x8f9480)[9] = 0x14;
	run = 0;
	count = 0;
	prev = 0x58;
	i = 0;
	bld = (unsigned char*) g_868050;
	do {
		type = bld[0];
		if (type == prev) {
			run++;
		}
		else {
			run = 0;
			count = 0;
			prev = type;
			if (i < 0x58) {
				j = i;
				r = bld;
				do {
					if (r[0] != type) {
						break;
					}
					count++;
					j++;
					r += 0x24d;
				} while (j < 0x58);
			}
		}
		k = 0;
		if (bld[0x22] != 0) {
			r = bld + 0x23;
			do {
				if (*(unsigned short*) r != 0xffff) {
					id = *(unsigned short*) r & 0x7fff;
					tgt = ((int*) 0x8f9480)[((Rec500e*) g_99ec10)[id].x21];
					t = (unsigned char*) g_868050 + tgt * 0x24d;
					kind = t[0];
					cnt = 0;
					j = tgt;
					if (tgt < 0x58) {
						do {
							if (t[0] != kind) {
								break;
							}
							cnt++;
							j++;
							t += 0x24d;
						} while (j < 0x58);
					}
					tgt += cnt * run / count;
					if (tgt < ((int*) 0x99e0a0)[id]) {
						((int*) 0x99e0a0)[id] = tgt;
					}
				}
				k++;
				r += 2;
			} while (k < (int) bld[0x22]);
		}
		bld += 0x24d;
		i++;
	} while (i < 0x58);
	r = (unsigned char*) 0x99e0a0;
	t = (unsigned char*) g_99ec10 + 0x21;
	do {
		if (*(int*) r == 0x58) {
			*(int*) r = ((int*) 0x8f9480)[*t];
		}
		r += 4;
		t += 0x41;
	} while (r < (unsigned char*) 0x99ec10);
}
