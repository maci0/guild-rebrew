#include "client_dialog_helpers.h"

#pragma optimize("y", off)

extern float g_664178;
extern float g_66414c;

int __cdecl fcn_00507910(int);
int __cdecl gm_CheckStatLevel(int, int);
int __cdecl gm_GetOppositeStatIndex(int);
int __cdecl fcn_0050d170(int);
int __cdecl fcn_005072c0(int);
int __cdecl gm_MapEntityStatRange(int);
int __cdecl fcn_00507080(int);
int __cdecl fcn_0050cf50(unsigned char *, int);
int __cdecl fcn_0050d200(short *, int);
int __cdecl gm_StartFilteredEntitySearch(int, int, int);
int __cdecl gm_FindNextFilteredEntity(void);
int __cdecl fcn_005463a0(int, int, int);
int __cdecl he_fn_Handlung(void);

/* ADDRESS: GOLDTL 0x00498670 */
int __cdecl fcn_00498670(int a1, short *ent, int mode, Cmd *out1, Cmd *out2)
{
	Cmd o1;
	Cmd o2;
	Cmd c1;
	Cmd c2;
	unsigned char *p;
	int sum;
	int count;
	int ones;
	int slot;
	int idx;
	int ratio;
	int cap;
	int tmp;
	int modev;
	int act;
	int type;
	int v;
	int t;

	sum = 0;
	count = 0;
	ones = 0;
	slot = 0;
	idx = 0;
	cap = (*(char *) ((char *) ent + 2) == 5) + 2;
	if (*(char *) ((char *) ent + 2) == 3) {
		return 0;
	}
	if (a1 != 0) {
		return 0;
	}
	if (mode == 0) {
		if (out1->kind != 0) {
			return 0;
		}
	} else if (mode == 1 && out1->kind != 5) {
		return 0;
	}
	v = fcn_0050d320(ent, g_773d75);
	ratio = (int) ((float) v * g_664178);
	o1.kind = 0;
	o1.f1 = 0;
	o1.f2 = 0;
	o2.kind = 0;
	o2.f1 = 0;
	o2.f2 = 0;
	idx = 0;
	while (idx < 0xa900) {
		if (lpGebaeudeINST[idx] != 0 && *(short *) (lpGebaeudeINST + idx + 0x27) == *ent) {
			p = lpGebaeudePROT + (int) lpGebaeudeINST[idx] * 0x24d;
			type = fcn_00507910(*p);
			if (type > 0 && type < 0x10) {
				sum += p[0x247];
				count++;
				if (p[0x247] == 1) {
					ones++;
				}
			}
		}
		idx += 0xa9;
	}
	if (sum != 0) {
		int diff;
		unsigned char *other;

		other = *(unsigned char **) ((char *) ent + 0x170);
		if (other == 0) {
			diff = 0;
		} else if (*other != 7) {
			diff = (int) lpGebaeudePROT[*other * 0x24d + 0x247] -
				(int) lpGebaeudePROT[0xb7b] + 1;
		} else {
			diff = -1;
		}
		if (diff >= 0 && (float) diff / (float) sum < 0.33f) {
			o1.kind = 0;
			o1.f1 = 0;
			o1.f2 = 0;
			o2.kind = 0;
			o2.f1 = 0;
			o2.f2 = 0;
			if (fcn_00497ec0(0x13, ent, 0, &o1, &o2) != 0) {
				*out1 = o1;
				*out2 = o2;
				return 0x13;
			}
		}
	}
	if (out1->kind != 0) {
		return 0;
	}
	idx = 0;
	while (idx < 0xa900) {
		p = lpGebaeudeINST + idx;
		if (*p != 0 && *(short *) (p + 0x27) == *ent && (p[0x5a] & 0x41) == 0) {
			t = *p;
			type = lpGebaeudePROT[t * 0x24d + 0x247];
			if (type < lpGebaeudePROT[t * 0x24d + 0x248]) {
				v = fcn_00507910(lpGebaeudePROT[t * 0x24d]);
				t = gm_CheckStatLevel(*ent, v);
				if (t != 0) {
					t = gm_GetOppositeStatIndex(t);
					type = lpGebaeudePROT[(int) *p * 0x24d + 0x247];
					t = t / 2 + t % 2;
					if (type < t) {
						if (v != 7) {
							tmp = fcn_0050d170(*p + 1);
							tmp = (int) ((float) tmp * g_66414c);
							if (tmp <= ratio) {
								out1->kind = 5;
								out1->f1 = *p + 1;
								out1->f2 = 1;
								out2->kind = 4;
								out2->f1 = *(int *) (p + 1);
								out2->f2 = 1;
								return 0x13;
							}
							ratio = tmp - ratio;
							if ((float) ratio / (float) tmp < 0.25f) {
								return 0;
							}
							out1->f2 = ratio;
							out1->kind = 0x12;
							return fcn_0049e900(0x13, ent, mode, out1, out2);
						}
					} else if (v != 7) {
						idx += 0xa9;
						continue;
					}
					if (type < t) {
						slot = *p + 1;
					}
				}
			}
		}
		idx += 0xa9;
	}
	if ((*(unsigned int *) ((char *) ent + 0x1c8) & 0x1000000) != 0) {
		return 0;
	}
	if (count > 3) {
		return 0;
	}
	if (ones < 1) {
		if (slot == 0) {
			goto use_slot;
		}
	} else if (slot == 0) {
		unsigned int flags;

		if (cap < ones) {
			return 0;
		}
		flags = (unsigned int) g_7f4c00 & 0x80000007u;
		if ((int) flags < 0) {
			flags = (flags - 1 | 0xfffffff8u) + 1;
		}
		if (flags != (*(unsigned int *) ((char *) ent + 4) & 7)) {
			return 0;
		}
use_slot:
		slot = fcn_005072c0(*(unsigned char *) ((char *) ent + 0x164));
		if (slot == 0) {
			return 0;
		}
	}
	modev = slot;
	c1.kind = 5;
	c1.f1 = 1;
	c1.f2 = 0;
	c2.kind = 0;
	c2.f1 = 0;
	c2.f2 = 0;
	act = fcn_004a4bb0(0, ent, mode, &c1, &c2, 1);
	if (act == 0) {
		int limit;
		int type2;
		int e;

		v = gm_MapEntityStatRange(*(unsigned char *) ((char *) ent + 0x164));
		t = fcn_00507080(v);
		type2 = gm_GetOppositeStatIndex(*(unsigned char *) ((char *) ent + 0x164));
		limit = type2 % 2 + type2 / 2;
		if (t == 0x10) {
			limit = 3;
		}
		c1.kind = 0;
		c2.kind = 0;
		p = (unsigned char *) gm_StartFilteredEntitySearch(1, 5, t);
		while (c1.kind == 0 && p != 0) {
			if ((int) lpGebaeudePROT[(int) *p * 0x24d + 0x247] <= limit && (p[0x5a] & 2) != 0) {
				e = fcn_005463a0(1, 0, 0x1b);
				while (e != 0) {
					if (*(int *) (e + 0xac) == *(int *) (p + 1)) {
						type = *(int *) (e + 0xb0);
						cap = type;
						if (ratio < type) {
							v = fcn_0050cf50(p, (char) p[0x5c]);
							ratio = type - ratio;
							if (((float) (type - v) / (float) v) * -0.5f + 0.25f <=
							    (float) ratio / (float) cap) {
								return 0;
							}
							out1->f2 = ratio;
							out1->kind = 0x12;
							return fcn_0049e900(0x13, ent, mode, out1, out2);
						}
						c1.kind = 4;
						c1.f1 = *(int *) (p + 1);
						c1.f2 = 1;
						c2.kind = 8;
						c2.f1 = *(int *) (e + 4);
						break;
					}
					e = he_fn_Handlung();
				}
			}
			p = (unsigned char *) gm_FindNextFilteredEntity();
		}
		if (c1.kind == 4 && c2.kind == 8) {
			goto accept;
		}
	} else {
		v = fcn_0050d200(ent, modev);
		if (v <= ratio) {
accept:
			*out1 = c1;
			*out2 = c2;
			return 0x13;
		}
		if ((float) (v - ratio) / (float) v < 0.25f) {
			out1->f2 = v - ratio;
			out1->kind = 0x12;
			return fcn_0049e900(0, ent, mode, out1, out2);
		}
	}
	return 0;
}
unsigned char _dpad_85ab90[54464];
