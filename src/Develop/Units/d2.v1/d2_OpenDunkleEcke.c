


#include "Develop/DieGildeAddOn/game/game_player.h"

char* __cdecl gm_QueryEntities(int, int, int, int);
void __cdecl d2_RunDunkleEckeOwnerDialog(char*, char*, char*);
void __cdecl d2_ShowDunkleEcke(char*, char*);
void __cdecl d3_EndCameraAndUiMode(void);

/* ADDRESS: GOLDDE 0x00587be0 */
void __cdecl d2_OpenDunkleEcke(char* building, char* context)
{
	char* entry;

	entry = gm_QueryEntities(*(int*) (context + 0x14), 1, 0, 0x12c);
	if (entry != 0) {
		if (*(unsigned short*) (building + 0x27) == gm_LocalPlayerSlot) {
			d2_RunDunkleEckeOwnerDialog(building, context, entry);
		}
		else {
			d2_ShowDunkleEcke(building, entry);
		}
	}
	d3_EndCameraAndUiMode();
}
