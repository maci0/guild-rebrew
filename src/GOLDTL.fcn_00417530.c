// FUNCTION: GOLDTL 0x00417530
// SIZE: 62

typedef struct {
	char pad0[0x51];
	unsigned char flags;
	char pad52[2];
} Item;
// SIZE 0x54

typedef struct {
	float f0;
	int i4;
	char pad8[0x20];
	Item *items;
	char pad2c[0xac];
	int count;
} Owner;
// SIZE 0xdc

void __cdecl fcn_00417530(Owner *o, float f, int v)
{
	int i;
	Item *p;

	o->f0 = f;
	o->i4 = v;
	p = o->items;
	for (i = 0; i < o->count; i++) {
		p->flags &= ~1;
		p++;
	}
}
