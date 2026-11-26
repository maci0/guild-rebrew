typedef struct Ent {
	unsigned short id;
	char pad2[0x164];
	unsigned char x166;
	unsigned char x167;
	unsigned char x168;
	char pad169[0x21c - 0x169];
} Ent;
// SIZE 0x21c

typedef struct Rec18 {
	int x0;
	int id;
	unsigned char x8;
	char pad9[0xf];
} Rec18;
// SIZE 0x18

int __cdecl amt_GetRoleTemplate(int idx, Rec18* out);
int __cdecl amt_CollectOfficeSlotsByGroup(int k, int max, Rec18* out);
Ent* __cdecl gm_LookupEntityRecordById(int id);
float __cdecl gm_CalcEntityFavor(unsigned int a0, unsigned int a1, unsigned int a2);
unsigned short __cdecl gm_RandomMod(int n);

/* ADDRESS: GOLDTL 0x0049fe50 */
int __cdecl fcn_0049fe50(Ent* e)
{
	float sum;
	int n;
	int ord[6];
	Rec18 q;
	Rec18 list[6];
	int i;
	int j;
	int a;
	int b;
	int t;

	for (i = 0; i < 6; i++) {
		ord[i] = i + 1;
	}
	if (e->x168 != 0) {
		n = e->x168;
	} else if (e->x166 != 0) {
		n = e->x166;
	} else if (e->x167 != 0) {
		n = e->x167;
	}
	if (n != 0) {
		if (amt_GetRoleTemplate(n, &q) == 0) {
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
		n = amt_CollectOfficeSlotsByGroup(ord[i], 6, list);
		if (n >= 3) {
			sum = 0;
			for (j = 0; j < n; j++) {
				sum += gm_CalcEntityFavor(e->id, gm_LookupEntityRecordById(list[j].id)->id, 1);
			}
			if (sum / n < 66.0f) {
				return ord[i];
			}
		}
	}
	return 0;
}
