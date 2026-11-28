#include "Develop/DieGildeAddOn/game/building_prototype.h"

extern unsigned char* lpGebaeudeINST;
extern unsigned char* lpGebaeudePROT;

void* __cdecl FindSlotEntryFiltered(int a, unsigned char* rec, void* prev, void* filter, int mask);
int __cdecl gm_SameEntityId(void);

/* ADDRESS: GOLDDE 0x004e07a0 */
int __cdecl gv_FindEntityGraveSlot(int entity, unsigned char** out_building, void** out_slot)
{
	unsigned char* rec;
	void* r;
	int i;

	*out_building = 0;
	*out_slot = 0;
	rec = lpGebaeudeINST;
	for (i = 0; i < 256; i++, rec += 0xa9) {
		if (rec[0] != 0 && ((BUILDING_PROTOTYPE *)lpGebaeudePROT)[rec[0]].category == 0x1d) {
			r = FindSlotEntryFiltered(entity, rec, 0, (void*) gm_SameEntityId, 0xff);
			if (r != 0) {
				*out_building = rec;
				*out_slot = r;
				return 1;
			}
		}
	}
	return 0;
}
