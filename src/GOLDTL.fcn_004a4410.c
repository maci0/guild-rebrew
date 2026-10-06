typedef struct Share {
	unsigned char kind;
	char pad[3];
	float val;
} Share;

typedef struct Deal {
	char pad0[0x30];
	Share a[4];
	char pad50[0x20];
	Share b[4];
	unsigned char flags;
	char pad91[3];
} Deal;
// SIZE 0x94

typedef struct Rate {
	float f;
	int x4;
	int x8;
} Rate;

typedef struct Actor {
	char pad0[0x90];
	Rate rate[13];
	char pad12c[4];
	unsigned char kind;
	char pad131[0x218 - 0x131];
	unsigned char flags;
} Actor;

extern char g_1008540[];

// FUNCTION: GOLD 0x004a49a0
// FUNCTION: GOLDTL 0x004a4410
int __cdecl fcn_004a4410(float* s1, float* s2, int idx, Actor* e)
{
	Deal* t;
	float k1;
	float k2;
	int found;
	int i;

	*s1 = 0;
	*s2 = 0;
	t = &((Deal*)g_1008540)[idx];
	if (t->flags & e->flags) {
		k1 = 40.0f;
		k2 = 50.0f;
		found = 1;
	} else {
		k1 = 50.0f;
		k2 = 100.0f;
		found = 0;
	}
	for (i = 0; !found && i < 4; i++) {
		if (t->a[i].kind == e->kind && t->a[i].val > 0.0f) {
			found = 1;
		}
	}
	for (i = 0; !found && i < 4; i++) {
		if (t->b[i].kind == e->kind && t->b[i].val > 0.0f) {
			found = 1;
		}
	}
	for (i = 0; i < 4; i++) {
		*s1 += t->a[i].kind == e->kind ? t->a[i].val / k1 * e->rate[t->a[i].kind].f : t->a[i].val / k2 * e->rate[t->a[i].kind].f;
		*s2 += t->b[i].kind == e->kind ? t->b[i].val / k1 * e->rate[t->b[i].kind].f : t->b[i].val / k2 * e->rate[t->b[i].kind].f;
	}
	return found;
}
