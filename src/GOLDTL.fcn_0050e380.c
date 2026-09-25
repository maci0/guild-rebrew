// FUNCTION: GOLD 0x0050af00
// SIZE: 260
// FUNCTION: GOLDTL 0x0050e380
// SIZE: 260

#include <string.h>

#pragma pack(1)
// SIZE 0xe
typedef struct {
	int a;
	int b;
	int c;
	short d;
} Blob;

// SIZE 0xa4
typedef struct {
	int id;
	int pad4;
	int has_amount;
	int owner;
	int amount;
	Blob blob;
	char tail[0xa4 - 0x22];
} Deal;

// SIZE 0x1e
typedef struct {
	int id;
	Deal* deal;
	char* tail;
	int amount;
	Blob blob;
} Entry;

// SIZE 0x21d
typedef struct {
	int width;
	char pad4[0x31 - 4];
	int height;
	Entry entries[16];
	int total;
	int count;
} Summary;
#pragma pack()

// SIZE 0x98
typedef struct {
	int count;
	int ids[36];
	int special;
} Sorted;

extern Deal g_7d2020[];

char* __cdecl gm_StartFilteredEntitySearch(int mode, int kind, int owner);
char* __cdecl gm_AddObjekt(void);
void __cdecl fcn_00505d00(char* obj, Sorted* out);

int __cdecl fcn_0050e380(int owner, Summary* out)
{
	Sorted sorted;
	int k;
	Deal* d;
	char* p;
	int i;

	memset(out, 0, sizeof(Summary));
	p = gm_StartFilteredEntitySearch(1, 4, owner);
	while (p != 0) {
		fcn_00505d00(p, &sorted);
		if (sorted.special != 0xffff && sorted.special == owner) {
			out->width += 0xe;
			out->height += 0xe;
			break;
		}
		p = gm_AddObjekt();
	}
	k = 0;
	for (i = 0; i < 256; i++) {
		d = &g_7d2020[i];
		if (d->id != 0 && d->owner == owner) {
			out->entries[k].id = d->id;
			if (d->has_amount != 0) {
				out->entries[k].amount = d->amount;
			}
			out->entries[k].blob = d->blob;
			out->entries[k].tail = d->tail;
			if (d->has_amount != 0) {
				out->total -= d->amount;
			}
			out->entries[k].deal = d;
			out->count++;
			k++;
		}
	}
	return 0;
}
