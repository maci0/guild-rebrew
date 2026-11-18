
extern char* g_entity_type_table;
extern char* g_item_def_table;
extern int g_85ab60;
extern int g_90e090;
extern unsigned short g_7f4c20[];

#include "Develop/Units/d2.v1/d2_dependency_node.h"



















int __cdecl fcn_0050e780(int i);

/* ADDRESS: GOLDTL 0x0050e830 */
int __cdecl fcn_0050e830(unsigned char* a0, unsigned short* a1, int a2, int a3)
{
	char* rec;
	DEPENDENCY_DIAGRAM_NODE tmp;

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

	i = 0;
	for (; i < *(unsigned char*) (rec + 0x22); i++) {
		if ((*(unsigned short*) (rec + 0x23 + i * 2) & 0x7fff) == *a1) {
			break;
		}
	}
	if (i >= *(unsigned char*) (rec + 0x22)) {
		return 1;
	}
	g_85ab60 = 0;

	i++;
	for (; i < *(unsigned char*) (rec + 0x22); i++) {
		j = *(unsigned short*) (rec + 0x23 + i * 2) & 0x7fff;
		if (g_item_def_table[j * 0x41] == 2 || g_item_def_table[j * 0x41] == 6) {
			break;
		}
		((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[g_85ab60].item_id = j;
		((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[g_85ab60].parent_a = *(unsigned short*) (rec + 0xa3 + i * 4);
		((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[g_85ab60].parent_b = *(unsigned short*) (rec + 0xa5 + i * 4);
		((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[g_85ab60].depth = 0xffff;
		((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[g_85ab60].x = 0;
		((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[g_85ab60].y = 0;
		((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[g_85ab60].unk_1c = -1;
		((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[g_85ab60].unk_20 = -1;
		((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[g_85ab60].unk_24 = -1;
		((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[g_85ab60].unk_28 = -1;
		((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[g_85ab60].unk_2c = -1;
		((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[g_85ab60].state = 0xff;
		g_85ab60++;

	}
	n = g_85ab60;
	if (n == 0) {
		return 1;
	}
	max = 0;
	for (i = 0; i < n; i++) {
		v = fcn_0050e780(i);
		((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].depth = (unsigned short) v;
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
				if (((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[j].depth < ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i - 1].depth) {
					tmp = ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i - 1];
					((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i - 1] = ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[j];
					v = 1;
					((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[j] = tmp;
				}
			}
		}
		i = 1;
	} while (v);
	g_7f4c20[0] = 0;
	if (n > 0) {
		k = 0;
		for (i = 0; i < n; i++) {
			if (((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].depth > k) {
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
		((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].x = v;
		v += span * 2;
	}
	for (k = 1; k < g_90e090; k++) {
		v = g_7f4c20[k];
		j = g_7f4c20[k + 1];
		for (i = v; i < j; i++) {
			sum = 0;
			num = 0;
			for (h = 0; h < v; h++) {
				if (((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[h].item_id == ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].parent_a
				    || ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[h].item_id == ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].parent_b) {
					sum += ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[h].x;
					num++;
				}
			}
			if (num != 0) {
				sum /= num;
			}
			((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].x = sum;
		}
		do {
			n = 0;
			for (i = v + 1; i < j; i++) {
				for (h = i; h < j; h++) {
					if (((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[h].x < ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i - 1].x) {
						tmp = ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i - 1];
						((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i - 1] = ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[h];
						((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[h] = tmp;
						n = 1;
					}
				}
			}
		} while (n);
		for (i = v; i < j; i++) {
			for (h = i; h < j; h++) {
				if (((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[h].x != ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].x) {
					break;
				}
			}
			len = h - i;
			if (len > 1) {
				d = (a2 / v0 >> (k - 1)) - (len * 3 + 3) * 8;
				half = d >> 1;
				acc = 0;
				for (h = i; h < i + len; h++) {
					((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[h].x += acc / (len - 1) - half;
					acc += d;
				}
			}
		}
		for (i = v; i < j; i++) {
			for (h = i + 1; h < j; h++) {
				if (((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[h].x - ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].x < 0x50) {
					d = (((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].x - ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[h].x + 0x50) >> 1;
					((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].x -= d;
					((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[h].x += d;
				}
			}
		}
	}
	min = a2 + 1;
	max = -1;
	for (k = 0; k < g_90e090; k++) {
		for (i = g_7f4c20[k]; i < g_7f4c20[k + 1]; i++) {
			if (((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].x <= min) {
				min = ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].x;
			}
			if (((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].x >= max) {
				max = ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].x;
			}
		}
	}
	if ((min - 0x18) < 0 || a2 <= max + 0x60) {
		scale = (float) a2 / ((max - min) + 0x78);
		base = (int) -((float) (min - 0x18) * scale);
		for (k = 0; k < g_90e090; k++) {
			for (i = g_7f4c20[k]; i < g_7f4c20[k + 1]; i++) {
				((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].x = (int) ((float) ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].x * scale) + base;
			}
		}
	}
	v = g_90e090 * 0x60;
	h = a3 - 0x10;
	if (v >= h) {
		v = h;
	}
	for (i = 0; i < g_85ab60; i++) {
		((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].y = ((DEPENDENCY_DIAGRAM_NODE*)g_7f3f00)[i].depth * v / g_90e090 + 0x10;
	}
	return 0;
}
