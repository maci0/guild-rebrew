#pragma optimize("y", off)

/* Remap-shaped method: rewrites entry identifiers in a 12-byte record table
   (+0xbc), then rebuilds the byte map at +0x138 from the identifier lists.
   Native ABI is thiscall with four stack arguments and callee cleanup
   (ret 0x10). */

typedef struct Entry605ccf {
	int f0;
	int f4;
	int f8;
} Entry605ccf;

typedef struct Map605ccf {
	char pad0[0xc];
	int start;
	int count;
} Map605ccf;

typedef struct Obj605ccf {
	char pad0[0x78];
	int size78;
	char pad7c[0xc];
	int words88;
	char pad8c[0x30];
	int entriesbc;
	char padc0[0x18];
	int charmapd4;
	char padc8[0x70];
	int mapcount9c;
	char pad98[0x8c];
	int maphead128;
	char pad12c[0xc];
	int bytemap138;
} Obj605ccf;

/* ADDRESS: GOLDTL 0x00605ccf */
int __fastcall fcn_00605ccf(Obj605ccf* self, int ignored, int* list, unsigned int nlist, int* order, unsigned int norder)
{
	Entry605ccf* dst;
	Entry605ccf* src;
	unsigned short* ids;
	unsigned short* p;
	int i;
	int k;
	int v;
	Map605ccf* map;

	ids = (unsigned short*) self->words88;
	for (i = 0; i < norder; i++) {
		v = order[i];
		if (v != 0xffff && ids[v * 3] != 0xffff) {
			dst = (Entry605ccf*) ((char*) self->entriesbc + v * 12);
			src = (Entry605ccf*) ((char*) self->entriesbc + i * 12);
			dst->f0 = src->f0;
			dst->f4 = src->f4;
			dst->f8 = src->f8;
			if (v != i) {
				for (k = 0; k < 3; k++) {
					p = (unsigned short*) ((int*) dst)[k];
					((int*) src)[k] = 0;
					p[1] = 0;
					p[0] = (unsigned short) v;
				}
			}
		} else {
			src = (Entry605ccf*) ((char*) self->entriesbc + i * 12);
			for (k = 0; k < 3; k++) {
				((int*) src)[k] = 0;
			}
		}
	}
	for (i = 0; i < nlist; i++) {
		v = list[i];
		if (v != 0xffff && ((char*) self->bytemap138)[i] == 0) {
			((char*) self->charmapd4)[v] = ((char*) self->charmapd4)[i];
		}
	}
	memset((char*) self->bytemap138, 1, self->size78);
	for (i = 0; i < self->mapcount9c; i++) {
		map = (Map605ccf*) ((char*) self->maphead128 + i * 0x14);
		for (k = map->start; k < map->start + map->count; k++) {
			((char*) self->bytemap138)[k] = 0;
		}
	}
	return 0;
}
