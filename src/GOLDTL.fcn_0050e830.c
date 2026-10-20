
extern char* g_entity_type_table;
extern char* g_item_def_table;
extern int g_85ab60;
extern int g_90e090;
extern unsigned short g_7f4c20[];

typedef struct {
	int x0;
	int x4;
	int x8;
	unsigned short xc;
	unsigned short xd;
	int x10;
	int x14;
	int x18;
	int x1c;
	int x20;
	int x24;
	int x28;
	int x2c;
	unsigned char x30;
	char pad[3];
} Rec34;

extern Rec34 g_7f3f00[];

int __cdecl fcn_0050e780(int i);

/* ADDRESS: GOLDTL 0x0050e830 */
int __cdecl fcn_0050e830(unsigned char* a0, unsigned short* a1, int a2, int a3)
{
	char* rec;
	Rec34 tmp;
	int count;
	int i;
	int j;
	int k;
	int n;
	int num;
	int sum;
	int max;
	int min;
	int v;
	int v0;
	int span;
	int h;
	int len;
	int acc;
	int half;
	int d;
	int base;
	float scale;

	rec = g_entity_type_table + (int) *a0 * 0x24d;
	count = *(unsigned char*) (rec + 0x22);
	i = 0;
	for (; i < count; i++) {
		if ((*(unsigned short*) (rec + 0x23 + i * 2) & 0x7fff) == *a1) {
			break;
		}
	}
	if (i >= count) {
		return 1;
	}
	g_85ab60 = 0;
	n = 0;
	i++;
	for (; i < *(unsigned char*) (rec + 0x22); i++) {
		j = *(unsigned short*) (rec + 0x23 + i * 2) & 0x7fff;
		if (g_item_def_table[j * 0x41] == 2 || g_item_def_table[j * 0x41] == 6) {
			break;
		}
		g_7f3f00[n].x0 = j;
		g_7f3f00[n].x4 = *(unsigned short*) (rec + 0xa3 + i * 4);
		g_7f3f00[n].x8 = *(unsigned short*) (rec + 0xa5 + i * 4);
		g_7f3f00[n].xc = 0xffff;
		g_7f3f00[n].x10 = 0;
		g_7f3f00[n].x14 = 0;
		g_7f3f00[n].x1c = -1;
		g_7f3f00[n].x20 = -1;
		g_7f3f00[n].x24 = -1;
		g_7f3f00[n].x28 = -1;
		g_7f3f00[n].x2c = -1;
		g_7f3f00[n].x30 = 0xff;
		n++;
		g_85ab60 = n;
	}
	if (n == 0) {
		return 1;
	}
	max = 0;
	for (i = 0; i < n; i++) {
		v = fcn_0050e780(i);
		g_7f3f00[i].xc = (unsigned short) v;
		if (max <= (v & 0xffff)) {
			max = v & 0xffff;
		}
	}
	max++;
	g_90e090 = max;
	i = 1;
	do {
		v = 0;
		for (; i < n; i++) {
			for (j = i; j < n; j++) {
				if (g_7f3f00[j].xc < g_7f3f00[i - 1].xc) {
					tmp = g_7f3f00[i - 1];
					g_7f3f00[i - 1] = g_7f3f00[j];
					g_7f3f00[j] = tmp;
					v = 1;
				}
			}
		}
		i = 1;
	} while (v);
	g_7f4c20[0] = 0;
	if (n > 0) {
		k = 0;
		for (i = 0; i < n; i++) {
			if (g_7f3f00[i].xc > k) {
				k++;
				g_7f4c20[k] = (unsigned short) i;
			}
		}
	}
	g_7f4c20[g_90e090] = (unsigned short) n;
	v0 = g_7f4c20[1];
	span = a2 / (v0 * 2);
	v = span - 0x18;
	for (i = 0; i < v0; i++) {
		g_7f3f00[i].x10 = v;
		v += span * 2;
	}
	for (k = 1; k < g_90e090; k++) {
		v = g_7f4c20[k];
		j = g_7f4c20[k + 1];
		for (i = v; i < j; i++) {
			sum = 0;
			num = 0;
			for (h = 0; h < v; h++) {
				if (g_7f3f00[h].x0 == g_7f3f00[i].x4
				    || g_7f3f00[h].x0 == g_7f3f00[i].x8) {
					sum += g_7f3f00[h].x10;
					num++;
				}
			}
			if (num != 0) {
				sum /= num;
			}
			g_7f3f00[i].x10 = sum;
		}
		do {
			n = 0;
			for (i = v + 1; i < j; i++) {
				for (h = i; h < j; h++) {
					if (g_7f3f00[h].x10 < g_7f3f00[i - 1].x10) {
						tmp = g_7f3f00[i - 1];
						g_7f3f00[i - 1] = g_7f3f00[h];
						g_7f3f00[h] = tmp;
						n = 1;
					}
				}
			}
		} while (n);
		for (i = v; i < j; i++) {
			for (h = i; h < j; h++) {
				if (g_7f3f00[h].x10 != g_7f3f00[h].x10) {
					break;
				}
			}
			len = h - i;
			if (len > 1) {
				d = (a2 / v0 >> (k - 1)) - (len * 3 + 3) * 8;
				half = d >> 1;
				acc = 0;
				for (h = i; h < i + len; h++) {
					g_7f3f00[h].x10 += acc / (len - 1) - half;
					acc += d;
				}
			}
		}
		for (i = v; i < j; i++) {
			for (h = i + 1; h < j; h++) {
				if (g_7f3f00[h].x10 - g_7f3f00[i].x10 < 0x50) {
					d = (g_7f3f00[i].x10 - g_7f3f00[h].x10 + 0x50) >> 1;
					g_7f3f00[i].x10 -= d;
					g_7f3f00[h].x10 += d;
				}
			}
		}
	}
	min = a2 + 1;
	max = -1;
	for (k = 0; k < g_90e090; k++) {
		for (i = g_7f4c20[k]; i < g_7f4c20[k + 1]; i++) {
			if (g_7f3f00[i].x10 <= min) {
				min = g_7f3f00[i].x10;
			}
			if (g_7f3f00[i].x10 >= max) {
				max = g_7f3f00[i].x10;
			}
		}
	}
	if ((min - 0x18) < 0 || a2 <= max + 0x60) {
		scale = (float) a2 / ((max - min) + 0x78);
		base = (int) -((float) (min - 0x18) * scale);
		for (k = 0; k < g_90e090; k++) {
			for (i = g_7f4c20[k]; i < g_7f4c20[k + 1]; i++) {
				g_7f3f00[i].x10 = (int) ((float) g_7f3f00[i].x10 * scale) + base;
			}
		}
	}
	v = g_90e090 * 0x60;
	h = a3 - 0x10;
	if (v >= h) {
		v = h;
	}
	for (i = 0; i < g_85ab60; i++) {
		g_7f3f00[i].x14 = g_7f3f00[i].xc * v / g_90e090 + 0x10;
	}
	return 0;
}
