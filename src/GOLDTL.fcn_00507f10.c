// FUNCTION: GOLDTL 0x00507f10

#define MIN(a, b) ((b) < (a) ? (b) : (a))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct {
	unsigned short id;
	char pad2[0x2c - 2];
	unsigned int skills;
	char pad30[0x80 - 0x30];
	unsigned char level[5];
	char pad85[0x1cc - 0x85];
	unsigned int flags;
} Unit;
// SIZE 0x1d0

typedef struct {
	char pad0[0xac];
	unsigned char slot_a;
	unsigned char slot_b;
	char padae[2];
	float bonus_a;
	float bonus_b;
} Mod;
// SIZE 0xb8

Mod* __cdecl fcn_005463a0(int, int, int, ...);
Mod* __cdecl fcn_005462a0(void);
int __cdecl fcn_005c6270(void*, int);
int __cdecl fcn_00577ab0(Unit*);

float __cdecl fcn_00507f10(Unit* u, int idx)
{
	float r;
	float add;
	float sub;
	Mod* m;

	sub = 0.0f;
	if (u == 0 || idx >= 5) {
		return -1.0f;
	}
	r = u->level[idx] * 0.003968254f;
	if (idx != 1) {
		add = 0.0f;
		for (m = fcn_005463a0(2, 2, u->id, 0, 0x82); m != 0; m = fcn_005462a0()) {
			if (m->slot_a == idx) {
				add += m->bonus_a;
			} else if (m->slot_b == idx) {
				add += m->bonus_b;
			}
		}
		if (fcn_005c6270(u, 0x2c4) == 1) {
			add *= 0.5f;
		}
		r += add;
	}
	if (idx == 3) {
		r += fcn_005c6270(u, 0x15a) * 0.16666667f;
	}
	switch (idx) {
	case 0:
		sub = ((u->skills >> 20) & 7) * 0.0555f + ((u->skills >> 4) & 0xf) * 0.03333333432674408;
		break;
	case 1:
		sub = ((u->skills >> 8) & 0xf) * 0.03333333432674408;
		sub += ((u->skills >> 20) & 7) * 0.0555f;
		break;
	case 2:
		sub = ((u->skills >> 17) & 7) * 0.055500001654028894;
		sub += ((u->skills >> 25) & 0xf) * 0.03333333432674408;
		break;
	case 3:
		sub = ((u->skills >> 8) & 0xf) * 0.03333333432674408;
		sub += ((u->skills >> 25) & 0xf) * 0.03333333432674408;
		break;
	case 4:
		sub = ((u->skills >> 12) & 3) * 0.16666667f + ((u->skills >> 4) & 0xf) * 0.03333333432674408;
		break;
	}
	r -= sub;
	if (idx == 4) {
		if (u->flags & 0x400) {
			r += 0.5f;
		}
	} else if (idx == 3) {
		if (u->flags & 0x200) {
			r += 0.5f;
		}
	} else if (idx == 2) {
		if (u->flags & 0x800) {
			r += 0.5f;
		}
	}
	r = MAX(MIN(r, 1.0f), 0.0f);
	if (fcn_00577ab0(u) == 0) {
		if (fcn_005c6270(u, 0x2c4) == 0) {
			return r * 0.5f;
		}
		return r * 0.75f;
	}
	return r;
}
