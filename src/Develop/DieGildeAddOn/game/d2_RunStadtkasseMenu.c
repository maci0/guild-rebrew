#include "Develop/DieGildeAddOn/game/entity_record.h"


extern int sv_ClickedObjekt;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern char gm_EntitySlotTable[];
extern int g_14abb58;
extern char g_6aae28[];

void __cdecl d2_ClearStatusTextSlots(void);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl RegisterStatusText(char*, int, int);
void __cdecl d2_ShowGildenkasseDialog(int);

void __cdecl d2_RunStadtkasseMenu(int building)
{
	int x;

	d2_ClearStatusTextSlots();
	while (main_RunFrameLoop(d2_RunStadtkasseMenu, 0x67fff) != 0) {
		if (((char *)&((ENTITY_RECORD_VIEW *)gm_EntitySlotTable)[gm_LocalPlayerSlot])[0x166] != 0) {
			x = RegisterStatusText(g_6aae28, g_14abb58, 0x16);
		}
		else {
			x = 0;
		}
		if (sv_ClickedObjekt != 0 && sv_ClickedObjekt == x) {
			d2_ShowGildenkasseDialog(building);
		}
	}
}
