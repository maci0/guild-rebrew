// SIZE 0x21c
typedef struct {
	unsigned short slot;
	unsigned char type;
	char pad3;
	int id;
	char pad8[0x214];
} Ent494470;

// SIZE 0x8
typedef struct {
	Ent494470* ent;
	int value;
} Member494470;

// SIZE 0x34
typedef struct {
	Ent494470* ent;
	Member494470 members[4];
	unsigned a;
	unsigned b;
	int text;
	unsigned char count;
} Party494470;

extern float g_662a2c;
extern unsigned char g_773d75;

unsigned short __cdecl gm_RandomMod(unsigned short range);
int __cdecl fcn_00508eb0(unsigned short id, int a2);
int __cdecl fcn_0050dac0(unsigned short id);
void __cdecl fcn_004c54c0(int a1, int a2, int a3, int a4);
void __cdecl fcn_004c5150(int a1, int a2, char a3, int a4);

/* ADDRESS: GOLDTL 0x00494470 */
int __cdecl fcn_00494470(Party494470* p, int flag)
{
	int i;
	int n;
	int q;
	int sum;
	int x;
	int value;
	int ya;
	int yb;

	if (p == 0) {
		return -1;
	}
	if (p->ent == 0) {
		return -2;
	}
	if (p->a > 5) {
		return -3;
	}
	if (p->b > 5) {
		return -4;
	}
	if (p->count == 0 || p->count > 4) {
		return -5;
	}
	yb = 5 - p->b;
	ya = 5 - p->a;
	n = fcn_00508eb0(p->ent->slot, 0);
	sum = n / -3 - n / 4 + n + ya + yb;
	for (i = 0; i < p->count; i++) {
		if (p->members[i].ent == 0) {
			return -6;
		}
		value = sum - fcn_00508eb0(p->members[i].ent->slot, 0);
		if (value >= 2) {
			value = 2;
		}
		else if (value <= -2) {
			value = -2;
		}
		p->members[i].value = value < 2 ? value : 2;
	}
	x = flag;
	for (i = 0; i < p->count; i++) {
			switch (p->members[i].value) {
		case -2:
			x = -0x10 - gm_RandomMod(0x10);
			break;
		case -1:
			x = -8 - gm_RandomMod(8);
			break;
		case 0:
			x = gm_RandomMod(8) + 8;
			break;
		case 1:
			x = gm_RandomMod(0x10) + 0x10;
			break;
		case 2:
			x = gm_RandomMod(0x10) + 0x18;
			break;
		}
		if (flag) {
			fcn_004c54c0(p->ent->id, p->members[i].ent->id, x, 1);
		}
	}
	q = fcn_0050dac0(p->ent->slot);
	p->text = (int) ((float) (10 - p->b - p->a) * q * p->count * 0.001f);
	if (flag) {
		fcn_004c5150(-1, p->ent->id, *(char*) &g_773d75, p->text);
	}
	return 0;
}
