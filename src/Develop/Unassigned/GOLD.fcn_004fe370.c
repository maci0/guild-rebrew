#include <string.h>

/* DATA TODO: native .data tables 0x875360 (25 dwords, item kind to building
 * index), 0x919f80 (732 dwords, per item best building index). 0x7e3f30 is the
 * building-prototype pointer (88 records, stride 0x24d), 0x91aaf0 the item
 * prototype pointer (stride 0x41). */
#define KIND_BUILDING ((int*) 0x875360)
#define ITEM_BEST ((int*) 0x919f80)
#define BUILDING_COUNT 0x58
#define BUILDING_STRIDE 0x24d
#define ITEM_STRIDE 0x41
#define ITEM_COUNT 0x2dc

/* Builds the item to building assignment tables. */
/* ADDRESS: GOLD 0x004fe370 */
void __cdecl gm_InitItemBuildingMap(void)
{
	unsigned char* p;
	unsigned char* q;
	unsigned char* r;
	unsigned short* ids;
	int* best;
	int i;
	int j;
	int k;
	int last;
	int pos;
	int run;
	int key;
	int key2;
	int base;
	int count;
	int idx;
	int value;

	memset(KIND_BUILDING, 0, 25 * sizeof(int));
	for (i = 0; i < ITEM_COUNT; i++) {
		ITEM_BEST[i] = BUILDING_COUNT;
	}
	p = *(unsigned char**) 0x7e3f30;
	pos = 0;
	run = 0;
	KIND_BUILDING[8] = 0x2f;
	KIND_BUILDING[7] = 0x32;
	KIND_BUILDING[6] = 0x29;
	KIND_BUILDING[10] = 0x21;
	KIND_BUILDING[14] = 0x1e;
	KIND_BUILDING[15] = 0x1f;
	KIND_BUILDING[16] = 0x20;
	KIND_BUILDING[11] = 0x17;
	KIND_BUILDING[12] = 0x35;
	KIND_BUILDING[9] = 0x14;
	last = BUILDING_COUNT;
	for (i = 0; i < BUILDING_COUNT; i++, p += BUILDING_STRIDE) {
		key = p[0];
		if (key != last) {
			last = key;
			pos = 0;
			run = 0;
			if (i < BUILDING_COUNT) {
				q = p;
				for (j = i; j < BUILDING_COUNT && q[0] == key; j++) {
					run++;
					q += BUILDING_STRIDE;
				}
			}
		} else {
			pos++;
		}
		ids = (unsigned short*) (p + 0x23);
		for (k = 0; k < p[0x22]; k++, ids++) {
			if (*ids == 0xffff) {
				continue;
			}
			idx = *ids & 0x7fff;
			base = KIND_BUILDING[*(unsigned char*) (*(char**) 0x91aaf0 + idx * ITEM_STRIDE + 0x21)];
			q = *(unsigned char**) 0x7e3f30 + base * BUILDING_STRIDE;
			key2 = q[0];
			count = 0;
			if (base < BUILDING_COUNT) {
				for (j = base; j < BUILDING_COUNT && q[0] == key2; j++) {
					count++;
					q += BUILDING_STRIDE;
				}
			}
			value = base + count * pos / run;
			if (value < ITEM_BEST[idx]) {
				ITEM_BEST[idx] = value;
			}
		}
	}
	r = (unsigned char*) (*(char**) 0x91aaf0 + 0x21);
	for (best = ITEM_BEST; (int) best < 0x91aaf0; best++, r += ITEM_STRIDE) {
		if (*best == BUILDING_COUNT) {
			*best = KIND_BUILDING[*r];
		}
	}
}
