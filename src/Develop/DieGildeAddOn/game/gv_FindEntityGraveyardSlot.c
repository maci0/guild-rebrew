#include "Develop/DieGildeAddOn/game/building_prototype.h"

extern unsigned char* lpGebaeudeINST;
extern unsigned char* lpGebaeudePROT;

void* __cdecl FindSlotEntryFiltered(int a, unsigned char* rec, void* prev, void* filter, int mask);
int __cdecl gv_MatchEntityGraveyardSlot(void);

/* ADDRESS: GOLDDE 0x004e0710 */
int __cdecl gv_FindEntityGraveyardSlot(int entity, unsigned char** out1, void** out2)
{
	unsigned char* rec;
	void* slot;
	int i;

	*out1 = 0;
	*out2 = 0;
	rec = lpGebaeudeINST;
	for (i = 0; i < 256; i++, rec += 0xa9) {
		if (rec[0] != 0 && ((BUILDING_PROTOTYPE*)lpGebaeudePROT)[rec[0]].category == 0x1d) {
			slot = FindSlotEntryFiltered(entity, rec, 0, (void*) gv_MatchEntityGraveyardSlot, 0xff);
			if (slot != 0) {
				*out1 = rec;
				*out2 = slot;
				return 1;
			}
		}
	}
	return 0;
}
