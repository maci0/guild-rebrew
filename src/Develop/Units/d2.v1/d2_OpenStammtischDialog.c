


#include "Develop/DieGildeAddOn/game/entity_record.h"






#include "Develop/DieGildeAddOn/game/game_player.h"


char* __cdecl fcn_00502cd0(int, int, int, int);
char* __cdecl he_StartHandlungSearch(int, int, int, int, int);
void __cdecl d2_RunStammtischDialog(char*, char*);
void __cdecl d2_RunPlayerStammtischDialog(char*, char*);
void __cdecl d3_EndCameraAndUiMode(void);

void __cdecl d2_OpenStammtischDialog(char* building, char* room)
{
	char* table;

	table = fcn_00502cd0(*(int*) (room + 0x14), 1, 0, 0x12d);
	if (table != 0 && he_StartHandlungSearch(2, 0, 0x2a, 3, *(int*) (building + 1)) != 0) {
		if (((ENTITY_RECORD*)gm_EntitySlotTable)[gm_LocalPlayerSlot].entity_index == *(unsigned short*) (building + 0x27)) {
			d2_RunStammtischDialog(building, table);
		}
		else {
			d2_RunPlayerStammtischDialog(building, table);
		}
	}
	d3_EndCameraAndUiMode();
}
