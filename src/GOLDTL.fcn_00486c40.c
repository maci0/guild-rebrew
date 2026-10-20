typedef struct Seg {
	int id;              /* 0x00 */
	int next;            /* 0x04 */
	int x8;              /* 0x08 */
	int xc;              /* 0x0c */
	int x10;             /* 0x10 */
	int x14;             /* 0x14 */
	int x18;             /* 0x18 */
	float price;         /* 0x1c */
	int x20;             /* 0x20 */
	int stock;           /* 0x24 */
	int buy;             /* 0x28 */
	int full;            /* 0x2c */
	int flags;           /* 0x30 */
	int x34;             /* 0x34 */
	int x38;             /* 0x38 */
	int x3c;             /* 0x3c */
} Seg;
// SIZE 0x40

typedef struct ClientRec {
	int v0;              /* 0x00 */
	int v4;              /* 0x04 */
	int v8;              /* 0x08 */
	int vc;              /* 0x0c */
	char pad10[8];
} ClientRec;
// SIZE 0x18

extern int g_100b0a8;
extern Seg g_100b0c0[];
extern int g_100e720[];
extern int g_100e760[];
extern int g_86805c;
extern ClientRec g_868c40[];

/* 768 building records of 540 bytes; g_7f4ca4 points four bytes into the first. */
extern char g_7f4ca4[];
#define PROP_COUNT 768
#define PROP(n) (g_7f4ca4 + (n) * 540)

char* __cdecl fcn_00502cd0(int id, int a, int b, int c);
int __cdecl fcn_00503a70(int id);

/* ADDRESS: GOLDTL 0x00486c40 */
void __cdecl fcn_00486c40(char* a0, unsigned int a1, int a2)
{
	Seg* seg;
	ClientRec* rec;
	int* lp;
	char* p;
	char* q;
	int n;
	int i;
	int k;
	int found;
	int sum;
	int v;

	(void) a1;
	for (i = 0; i < PROP_COUNT; i++) {
		p = PROP(i);
		if (*(unsigned short*) (p - 4) == 0xffff) {
			continue;
		}
		if (*(int*) (p + 0x168) != *(int*) (a0 + 0x16c)) {
			continue;
		}
		if (*(char*) (p + 0x161) == 0) {
			continue;
		}
		q = fcn_00502cd0(*(int*) (p + 0x174), 1, 4, 0xc);
		n = g_100b0a8;
		if (q != 0) {
			found = 0;
			for (lp = &g_100e760[1]; lp[-1] != 0 && lp[0] != 0 && found == 0; lp++) {
				lp[-1] = *(unsigned short*) q;
				if (lp[-1] != 0) {
					for (k = 0; k < n; k++) {
						if (g_100b0c0[k].id == lp[0]) {
							g_100b0c0[k].x14++;
							g_100b0c0[k].x3c |= 2;
							found = 1;
							break;
						}
					}
				}
			}
			if (found == 0) {
				for (lp = &g_100e720[1]; lp[-1] != 0 && lp[0] != 0 && found == 0; lp++) {
					lp[-1] = *(unsigned short*) q;
					if (lp[-1] != 0) {
						for (k = 0; k < n; k++) {
							if (g_100b0c0[k].id == lp[0]) {
								g_100b0c0[k].x14++;
								g_100b0c0[k].x3c |= 2;
								found = 1;
								break;
							}
						}
					}
				}
			}
		} else if (n >= 1) {
			for (k = 0; k < n; k++) {
				if (g_100b0c0[k].id == g_100e760[0]) {
					g_100b0c0[k].x14++;
					g_100b0c0[k].x3c |= 2;
					break;
				}
			}
		}
	}
	n = g_100b0a8;
	for (i = 0; i < n; i++) {
		seg = &g_100b0c0[i];
		if (seg->x14 != 0) {
			found = 0;
			for (k = 0; g_100e760[k] != 0; k++) {
				if (seg->id == g_100e760[k]) {
					v = seg->x14 - (seg->stock + seg->buy);
					seg->x14 = v;
					if (seg->x14 < 0) {
						seg->x14 = 0;
					}
					found = 1;
					break;
				}
			}
			if (found == 0) {
				for (k = 0; g_100e720[k] != 0; k++) {
					if (seg->id == g_100e720[k]) {
						v = seg->x14 - (seg->stock + seg->buy);
						seg->x14 = v;
						if (seg->x14 < 0) {
							seg->x14 = 0;
						}
						found = 1;
						break;
					}
				}
			}
			if (seg->x14 != 0) {
				fcn_00503a70(seg->id);
				for (k = 0; k < g_86805c; k++) {
					rec = &g_868c40[k];
					if (rec->v8 != 0 && rec->vc >= 1) {
						seg->x8 = rec->v0;
					}
				}
				n = g_100b0a8;
			}
		}
		if (seg->x8 == 0) {
			seg->x14 = 0;
		}
	}
	sum = 0;
	if (g_100e760[0] != 0) {
		for (k = 0; g_100e760[k] != 0; k++) {
			for (i = 0; i < g_100b0a8; i++) {
				seg = &g_100b0c0[i];
				if (g_100e760[k] == seg->id && seg->x14 != 0) {
					while (seg->x14 > 0) {
						if ((float) seg->x14 * seg->price + (float) sum <= (float) a2) {
							break;
						}
						seg->x14--;
					}
					sum = (int) ((float) seg->x14 * seg->price + (float) sum);
				}
			}
		}
	}
	if (g_100e720[0] == 0) {
		return;
	}
	for (k = 0; g_100e720[k] != 0; k++) {
		for (i = 0; i < g_100b0a8; i++) {
			seg = &g_100b0c0[i];
			if (g_100e720[k] == seg->id && seg->x14 != 0) {
				while (seg->x14 > 0) {
					if ((float) seg->x14 * seg->price + (float) sum <= (float) a2) {
						break;
					}
					seg->x14--;
				}
				sum = (int) ((float) seg->x14 * seg->price + (float) sum);
			}
		}
	}
}
