


// SIZE 0x21c
typedef struct {
	unsigned short id;
	unsigned char type;
	char pad3[0x16c - 3];
	unsigned char* home;
	unsigned char* work;
	char pad174[0x21c - 0x174];
} Obj;

#include "Develop/DieGildeAddOn/game/entity_record.h"

void __cdecl hp_RemoveProdEntry(int h);
void __cdecl m_FreeTracked(void* p);
void __cdecl gv_FreeFieldAllocs(int* slot);
#include "Develop/DieGildeAddOn/game/spiel.h"

int __cdecl gm_FreeGebaeude(unsigned char* o)
{
	int i;

	if (o == 0) {
		return -1;
	}
	if (*o == 0) {
		return -2;
	}
	if (*(unsigned short*) (o + 0x27) != 0xffff && (*(unsigned char*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[*(unsigned short*) (o + 0x27)].entity_type) == 6) {
		hp_RemoveProdEntry(*(int*) (o + 1));
	}
	switch (*o) {
	case 0x1e:
		if (*(void**) (o + 0x71) != 0) {
			m_FreeTracked(*(void**) (o + 0x71));
			*(void**) (o + 0x71) = 0;
		}
		*(void**) (o + 0x71) = 0;
		break;
	case 0x48:
	case 0x49:
	case 0x4a:
		gv_FreeFieldAllocs(*(int**) (o + 0x65));
		*(void**) (o + 0x65) = 0;
		break;
	case 0x4b:
	case 0x4c:
	case 0x4d:
		m_FreeTracked(*(void**) (o + 0x65));
		*(void**) (o + 0x65) = 0;
		break;
	}
	for (i = 0; i < 768; i++) {
		if ((*(unsigned char**)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].ptr_170) == o) {
			(*(unsigned char**)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].ptr_170) = 0;
		}
		if ((*(unsigned char**)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].ptr_16c) == o) {
			(*(unsigned char**)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].ptr_16c) = 0;
		}
	}
	if (*(char**) (o + 0x5d) != 0) {
		gm_FreeObjectListRecursive((struct LinkedNode**) (o + 0x5d));
	}
	*o = 0;
	return 0;
}
