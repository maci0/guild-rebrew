// SIZE 0x20
typedef struct Plan {
	int x0;
	float level;
	char pad8[0xc];
	int c;
	int a;
	int b;
} Plan;

// SIZE 0x110
typedef struct Unit {
	unsigned short id;
	char pad2[0x1a];
	float bonus;
	char pad20[4];
	int base;
	char pad28[0xe4];
	float mood;
} Unit;

unsigned int __cdecl fcn_004938c0(Plan* p);
Unit* __cdecl fcn_00508e40(int id);
float __cdecl fcn_0050f980(int a, int b, int c);
unsigned short __cdecl gm_RandomMod(int n);

/* ADDRESS: GOLD 0x00494010 */
/* ADDRESS: GOLDTL 0x00493640 */
int __cdecl fcn_00493640(Plan* p)
{
	unsigned int n;
	Unit* a;
	Unit* b;
	Unit* c;
	float v;
	float r;
	float t;
	float d1;
	float d2;

	if (p->level <= 3.0f) {
		return 0;
	}
	if (p->level >= 18.0f) {
		return 1;
	}
	n = fcn_004938c0(p);
	a = fcn_00508e40(p->a);
	b = fcn_00508e40(p->b);
	c = fcn_00508e40(p->c);
	v = a->base + a->bonus;
	r = a->mood - 2.0f;
	if (r > 0.66f) {
		t = n * 190;
	} else if (r > 0.33f) {
		t = n * 90;
	} else {
		t = n * 70;
	}
	if (t > v) {
		return 1;
	}
	d1 = fcn_0050f980(a->id, b->id, 1) * 0.01f;
	d2 = fcn_0050f980(c->id, b->id, 1) * 0.01f;
	if (d1 * 1.1f > d2 * 0.9f && d1 < d2) {
		return 0;
	}
	return gm_RandomMod(2);
}
