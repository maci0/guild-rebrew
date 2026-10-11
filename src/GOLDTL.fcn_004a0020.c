// SIZE 0x21c
typedef struct
{
	unsigned short id;
	char pad2[2];
	int h;
	char pad8[0x166 - 8];
	unsigned char x166;
	unsigned char x167;
	unsigned char x168;
	char pad169[0x21c - 0x169];
} fcn_004a0020_Ent;

typedef struct
{
	int x0;
	int id;
	unsigned char x8;
	char pad9[0xf];
} fcn_004a0020_Rec;
// SIZE 0x18

int __cdecl fcn_004e8b40(int idx, fcn_004a0020_Rec* out);
int __cdecl fcn_004e8c00(int k, int max, fcn_004a0020_Rec* out);
fcn_004a0020_Ent* __cdecl fcn_00508e40(int id);
float __cdecl fcn_0050f980(int a, int b, int c);
unsigned short __cdecl gm_RandomMod(int n);

// FUNCTION: GOLDTL 0x004a0020
int __cdecl fcn_004a0020(fcn_004a0020_Ent* e)
{
	float sum;
	int cnt;
	int i;
	int j;
	int n;
	int ord[6];
	fcn_004a0020_Rec q;
	fcn_004a0020_Rec list[6];
	fcn_004a0020_Ent* d;
	fcn_004a0020_Ent* d2;
	int k;
	int a;
	int b;
	int t;

	for (i = 0; i < 6; i++) {
		ord[i] = i + 1;
	}
	if (e->x168 != 0) {
		j = e->x168;
	} else if (e->x166 != 0) {
		j = e->x166;
	} else if (e->x167 != 0) {
		j = e->x167;
	}
	if (j != 0) {
		if (fcn_004e8b40(j, &q) == 0) {
			return 0;
		}
		j = (q.x8 - 1) / 3;
		if (j == 1) {
			for (i = 0; i < 6; i++) {
				ord[i] = (i + 4) % 6 + 1;
			}
		} else if (j == 2) {
			for (i = 0; i < 6; i++) {
				ord[i] = 6 - i;
			}
		}
	}
	for (i = 6; i != 0; i--) {
		a = gm_RandomMod(3);
		b = gm_RandomMod(3);
		t = ord[a];
		ord[a] = ord[b];
		ord[b] = t;
		a = gm_RandomMod(3) + 3;
		b = gm_RandomMod(3) + 3;
		t = ord[a];
		ord[a] = ord[b];
		ord[b] = t;
	}
	for (i = 0; i < 5; i++) {
		cnt = 0;
		sum = 0;
		n = fcn_004e8c00(ord[i], 6, list);
		if (n >= 3) {
			for (j = 0; j < n - 1; j++) {
				if (list[j].id != e->h && list[j].id != -1) {
					d = fcn_00508e40(list[j].id);
					for (k = j + 1; k < n; k++) {
						if (d == 0)
							break;
						if (list[k].id != e->h && list[k].id != -1) {
							d2 = fcn_00508e40(list[k].id);
							if (d2 != 0) {
								sum += fcn_0050f980(d->id, d2->id, 1);
								sum += fcn_0050f980(d2->id, d->id, 1);
								cnt += 2;
							}
						}
					}
				}
			}
			if (cnt != 0 && sum / cnt > 33.0f) {
				return ord[i];
			}
		}
	}
	return 0;
}
