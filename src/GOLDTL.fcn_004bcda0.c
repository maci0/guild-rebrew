#include "Develop/DieGildeAddOn/auxillary/plant.h"
#include "Develop/Units/d3/d3_object.h"

typedef struct PLANT_SLOT {
	int counter;
	char pad4[4];
	unsigned char a;
	unsigned char b;
	unsigned short id;
	unsigned char d;
	char state;
	char pad_e[2];
	int owner;
	void* object;
} PLANT_SLOT;

void __cdecl fcn_004bcf20(PLANT_SLOT* slot, void* info);

/* ADDRESS: GOLDTL 0x004bcda0 */
char* __cdecl fcn_004bcda0(void* tab, unsigned int a2, unsigned int a3, int id, unsigned int unused)
{
	PLANT_SLOT* table;
	PLANT_SLOT* slot;
	char* info;
	int i;

	info = plt_FindPlantInfo(id);
	table = (PLANT_SLOT*) tab;
	if (table == 0) {
		return 0;
	}
	for (i = 0, slot = table; i < 0x40; i++, slot++) {
		if ((unsigned int) slot->a != a2) {
			continue;
		}
		if ((unsigned int) slot->b != a3) {
			continue;
		}
		if (slot->state == (char) 0xff) {
			continue;
		}
		break;
	}
	if (i == 0x40) {
		for (i = 0, slot = table; i < 0x40; i++, slot++) {
			if (slot->state == (char) 0xff) {
				slot->counter = *(int*) 0x7728f8;
				*(int*) 0x7728f8 += 1;
				break;
			}
		}
		if (i == 0x40) {
			return 0;
		}
	}
	slot = &table[i];
	slot->id = (unsigned short) id;
	if (info == 0) {
		slot->owner = -1;
		if (id != 0) {
			slot->state = 1;
		} else {
			slot->state = (char) 0xff;
			if (slot->object != 0) {
				d3_DestroyObject((D3_OBJECT*) slot->object);
				slot->object = 0;
			}
		}
	} else {
		if (slot->object != 0) {
			d3_DestroyObject((D3_OBJECT*) slot->object);
			slot->object = 0;
		}
		fcn_004bcf20(slot, info);
	}
	slot->a = (unsigned char) a2;
	slot->b = (unsigned char) a3;
	if (info != 0) {
		slot->d = *(unsigned char*) (info + 0x42);
	} else {
		slot->d = 0;
	}
	return (char*) slot;
}
