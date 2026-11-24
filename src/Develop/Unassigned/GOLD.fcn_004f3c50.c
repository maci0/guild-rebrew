int __cdecl FindStraftatIndexById(int);
extern char g_7f4ca4[];

/* ADDRESS: GOLD 0x004f3c50 */
int __cdecl fcn_004f3c50(int* ids, int* counts, int id)
{
	int list[0x200];
	int* w;
	int* e;
	int key;
	int n;
	int i;
	int j;
	int c;
	int v;
	int k;
	int t;
	int t2;
	int* cp;
	int* ip;

	n = 0;
	for (i = 0; i < 0x20; i++) {
		ids[i] = -1;
		counts[i] = 0;
	}
	for (i = 0; i < 0x200; i++) {
		list[i] = -1;
	}
	w = list;
	key = *(int*) (g_7f4ca4 + (unsigned short) id * 0x21c);
	for (e = (int*) 0x91b6e4; (int) e < 0x91f6e4; e += 2) {
		if (e[-1] == key) {
			k = FindStraftatIndexById(e[0]);
			if (k != -1 && *(int*) (0x91f725 + k * 0x2d) == 1) {
				*w++ = *(int*) (0x91f716 + k * 0x2d);
			}
		}
	}
	for (i = 1, w = list; i - 1 < 0x200; i++, w++) {
		v = *w;
		if (v == -1) {
			continue;
		}
		*w = -1;
		n++;
		c = 1;
		for (j = i; j < 0x200; j++) {
			if (list[j] == v) {
				c++;
				list[j] = -1;
			}
		}
		if (c > counts[31]) {
			counts[31] = c;
			ids[31] = v;
		}
		for (k = 31, cp = counts + 30, ip = ids + 30; k > 0; k--, cp--, ip--) {
			if (cp[1] > cp[0]) {
				t = *ip;
				t2 = cp[1];
				*ip = ids[k];
				cp[1] = cp[0];
				ids[k] = t;
				cp[0] = t2;
			}
		}
	}
	if (n > 0x20) {
		n = 0x20;
	}
	return n;
}
