#pragma optimize("s", on)

typedef struct ITEM_605233 ITEM_605233;
struct ITEM_605233 {
	int id;
	unsigned short f4;
	unsigned short f6;
};

typedef struct SELF_605233 SELF_605233;
struct SELF_605233 {
	char pad_0fc[0xfc];
	ITEM_605233* f0fc;
	char* f100;
	unsigned int f104;
	unsigned int f108;
	int* f10c;
	unsigned int* f110;
};

/* ADDRESS: GOLDTL 0x00605233 */
int __fastcall fcn_00605233(SELF_605233* self)
{
	unsigned int i;
	ITEM_605233* item;
	unsigned int f;

	for (i = self->f108 + 1; i < self->f104; i++) {
		item = &self->f0fc[i];
		if (self->f10c[item->id] != -1) {
			f = item->f6;
			item->f6 = (f & ~3) | ((self->f110[item->id] + (f & 3)) % 3);
			item->id = self->f10c[item->id];
			self->f100[i] = 1;
		}
	}
	return 0;
}
