#include "client_types.h"

/* Panel table entry. The 0x58 entry stride comes from the entry addressing in
 * this body (index * 0x58). The named fields are the offsets this body reads
 * or writes; bytes that no access reaches stay padding. */
typedef struct
{
	int x0;
	int a[4];
	char pad14[0x24 - 0x14];
	int x24;
	int x28;
	int c[4];
	int d[4];
	int x4c;
	char pad50[0x58 - 0x50];
} Panel;

extern char g_779160[];
extern char* g_7746c4;
extern unsigned char* g_7746c8;
extern char* g_1015ea0;
extern char* g_99ec10;
extern int g_772514;
extern char g_7f4c00[];

int __cdecl fcn_004727a0(int k, int i);
int __cdecl fcn_0050cce0(char* o, void* out, int producers);
int __cdecl fcn_0046f100(int x, int y, int cx, int cy, int a5, int win);
int __cdecl fcn_0046f740(int x, int y, int a3, int win);
int __cdecl fcn_0046f7e0(int x, int y, int a3, int win, int a5);
void __cdecl fcn_0046b2b0(int id);
int __cdecl fcn_00500d20(void* a, void* b);
void* __cdecl fcn_005463a0(int n, ...);
void* __cdecl fcn_005462a0(void);
void __cdecl fcn_00519190(int a, ...);

/* ADDRESS: GOLDTL 0x00594de0 */
void __cdecl fcn_00594de0(int a0, int a1, int a2)
{
	Panel* p;
	unsigned char* st;
	int stock[0xb8 / 4];
	unsigned char* obj;
	void* row;
	int i;
	int k;
	int y;
	int n;
	int found;
	int status;
	int off;
	int span;
	int w;
	int t1;
	int t2;

	/* List record buffer: fcn_0050cce0 fills 0xb8 bytes. Only the count at
	 * +4, the item ids at +0x48 and the values at +0x68 are read here. */
	st = (unsigned char*) stock;
	obj = 0;
	if (g_7746c4 != 0) {
		obj = (unsigned char*) g_7746c4;
	} else if (g_7746c8 != 0) {
		obj = g_7746c8;
	}
	fcn_004727a0(a0, 0);
	fcn_004727a0(a0, a1);
	fcn_0050cce0((char*) obj, stock, 1);

	for (i = 0; i < a2; i++) {
		p = (Panel*) (g_779160 + i * 0x58);
		if (p->c[1] < 0) {
			w = fcn_0046f100(p->x24, p->x28, 0xcd, 0x57, 0x10, g_772514);
			p->c[1] = w;
			*(int*) (0x10161cc + w * 0x3cc) = 0x54;
			fcn_0046f740(0, 0, 0x749, w);
			if (i == 0) {
				p->c[2] = fcn_0046f740(0xd, 5, 0x74a, p->c[1]);
			} else {
				p->c[2] = fcn_0046f740(0xd, 5, p->x0 + 0xdf, p->c[1]);
			}
			*(int*) (g_1015ea0 + p->c[2] * 0x2f4 + 0x5c) = 1;
			*(int*) (g_1015ea0 + p->c[2] * 0x2f4 + 0x1e8) = -1;
			*(int*) (g_1015ea0 + p->c[2] * 0x2f4 + 0x1ec) = -1;
			for (y = 0x11, k = 0; y < 0xd5; y += 0x31, k++) {
				if (p->a[k] != 0) {
					w = fcn_0046f7e0(y, 0x3a, p->a[k] + 0xdf, p->c[1], -2);
					p->d[k] = w;
					*(int*) (g_1015ea0 + w * 0x2f4 + 0x5c) = 1;
					*(int*) (g_1015ea0 + w * 0x2f4 + 0x1e8) = -1;
					*(int*) (g_1015ea0 + w * 0x2f4 + 0x1ec) = -1;
				}
			}
			w = fcn_0046f100(0x43, 4, 0x88, 0x32, 0x10, p->c[1]);
			p->x4c = w;
			*(int*) (0x10161cc + w * 0x3cc) = 0x54;
		}

		status = 0;
		off = 0x26;
		for (k = 0; k < 4; k++, off += 2) {
			if (p->a[k] == 0) {
				continue;
			}
			found = -1;
			for (n = 0; n < *(int*) (st + 4); n++) {
				if ((int) *(unsigned short*) (st + 0x48 + n * 2) == p->a[k]) {
					found = n;
					break;
				}
			}
			if (found >= 0) {
				if ((int) *(unsigned short*) (g_99ec10 + p->x0 * 0x41 + off) <= *(int*) (st + 0x68 + found * 4)) {
					*(int*) (g_1015ea0 + p->d[k] * 0x2f4 + 0x1e4) = 0x74d;
				} else {
					*(int*) (g_1015ea0 + p->d[k] * 0x2f4 + 0x1e4) = 0x74e;
					if (status <= 1) {
						status = 1;
					}
				}
			} else {
				status = 2;
				*(int*) (g_1015ea0 + p->d[k] * 0x2f4 + 0x1e4) = 0x74f;
			}
		}
		*(int*) (g_1015ea0 + p->c[2] * 0x2f4 + 0x1e4) = status + 0x750;

		span = 0;
		if (i == 0) {
			row = fcn_005463a0(2, 0, 9, 3, *(int*) (obj + 1));
		} else {
			row = fcn_005463a0(2, 0, 8, 3, *(int*) (obj + 1));
			while (row != 0 && (int) *(unsigned short*) ((char*) row + 0xac) != p->x0) {
				row = fcn_005462a0();
			}
		}
		if (row != 0 && (*(int*) ((char*) row + 0x14) != 0 || *(int*) ((char*) row + 0x18) != 0)) {
			if (p->c[3] < 0) {
				p->c[3] = fcn_0046f740(0xd, 5, 0x4fd, p->c[1]);
			}
			span = *(int*) ((char*) row + 0x18) + *(int*) ((char*) row + 0x14);
			t1 = fcn_00500d20((void*) ((char*) row + 0x44), (void*) ((char*) row + 0x52));
			t2 = fcn_00500d20((void*) ((char*) row + 0x44), (void*) g_7f4c00);
			*(float*) (g_1015ea0 + p->c[2] * 0x2f4 + 0x1f4) = (float) t2 / (float) t1;
		} else {
			if (p->c[3] != -1) {
				fcn_0046b2b0(p->c[3]);
				p->c[3] = -1;
			}
			if (p->c[2] != -1) {
				*(float*) (g_1015ea0 + p->c[2] * 0x2f4 + 0x1f4) = 0.0f;
			}
		}

		if (i == 0) {
			g_772514 = p->x4c;
			fcn_00519190(0xc8, span, 0x51e);
		} else {
			g_772514 = p->x4c;
			fcn_00519190(0xc9, span, 0x51e, p->x0 * 2 + 0x9a8);
		}
		fcn_004727a0(a0, a1);
	}

	/* Tear down the remaining entries. The reference stops when the c[1]
	 * field address reaches 0x779710, which is 16 entries of 0x58 from
	 * 0x779160, so the index bound is 16. */
	if (i < 0x10) {
		for (k = i; k < 0x10; k++) {
			p = (Panel*) (g_779160 + k * 0x58);
			if (p->c[1] >= 0) {
				p->c[0] = -1;
				fcn_0046b2b0(p->c[1]);
				p->c[1] = -1;
				p->c[2] = -1;
				p->c[3] = -1;
				p->d[0] = -1;
				p->d[1] = -1;
				p->d[2] = -1;
				p->d[3] = -1;
				p->x4c = -1;
			}
		}
	}
}
