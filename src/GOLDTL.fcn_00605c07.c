#pragma optimize("s", on)

typedef struct ITEM_605c07 ITEM_605c07;
struct ITEM_605c07 {
	int id;
	unsigned short f4;
	unsigned short f6;
};

typedef struct SELF_605c07 SELF_605c07;
struct SELF_605c07 {
	char pad_0fc[0xfc];
	ITEM_605c07* f0fc;
	char* f100;
	unsigned int f104;
	unsigned int f108;
	int* f10c;
	unsigned short* f110;
};

/* ADDRESS: GOLDTL 0x00605c07 */
int __fastcall fcn_00605c07(SELF_605c07* self)
{
	unsigned int i;
	ITEM_605c07* item;
	unsigned int f;
	int v;
	int n;

	for (i = self->f108 + 1; i < self->f104; i++) {
		item = &self->f0fc[i];
		if (self->f10c[item->id] != 0xffff) {
			f = item->f6;
			v = self->f110[item->id];
			n = v + (int) (f & 3);
			item->f6 = (f & ~3) | (n % 3);
			item->id = self->f10c[item->id];
			self->f100[i] = 1;
		}
	}
	return 0;
}
