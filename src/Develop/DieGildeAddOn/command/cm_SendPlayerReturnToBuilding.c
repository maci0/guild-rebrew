#include "Develop/DieGildeAddOn/game/game_player.h"

#include "Develop/DieGildeAddOn/game/entity_record.h"
extern char g_675908[];
extern char str_empty[];

int __cdecl he_GetEntityReturnTarget(char* slot, int* out1, int* out2);
void __cdecl cm_RequestChrMoveToUniverse(int h, int a, int b, char* tag);
void __cdecl cm_RequestChrWalkToDummy(int h, int a, int b, char* tag);

/* ADDRESS: GOLDTL 0x0057f9a0 */
void __cdecl cm_SendPlayerReturnToBuilding(int unused)
{
	char* cursor;
	int idx;
	char* slot;
	int posX;
	int posY;

	if (unused != 0) {
		return;
	}
	idx = 0;
	cursor = gm_EntitySlotTable + 0x16c;
	for (;;) {
		char* rec = *(char**) cursor;
		if (rec != 0 && *(unsigned short*) (rec + 0x27) == gm_LocalPlayerSlot) {
			break;
		}
		cursor += sizeof(ENTITY_RECORD);
		idx++;
		if ((int) cursor >= (int)(gm_EntitySlotTable + 0x6556c)) {
			return;
		}
	}
	slot = (char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[idx];
	if (slot == 0) {
		return;
	}
	if (he_GetEntityReturnTarget(slot, &posX, &posY)) {
		cm_RequestChrMoveToUniverse(*(int*) (slot + 4), posX, posY, g_675908);
		cm_RequestChrWalkToDummy(*(int*) (slot + 4), posX, posY, str_empty);
	}
}
