

extern int sv_ClickedObjekt;
#include "Develop/DieGildeAddOn/game/game_player.h"
#include "Develop/DieGildeAddOn/game/entity_record.h"
extern int g_14aac24;
extern char g_6aafe4[];

void __cdecl d2_ClearStatusTextSlots(void);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl RegisterStatusText(char*, int, int);
int __cdecl gm_CheckZunftPreismanipulation(char*);
void __cdecl d2_RunZunftPreismanipulationDialog(int);

/* ADDRESS: GOLD 0x5a1bb0 */
void __cdecl d2_RunZunftPreismanipMenu(int a)
{
	int x;

	x = 0;
	d2_ClearStatusTextSlots();
	while (main_RunFrameLoop(d2_RunZunftPreismanipMenu, 0x67fff) != 0) {
		if (gm_CheckZunftPreismanipulation(((char*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot])) != 0) {
			x = RegisterStatusText(g_6aafe4, g_14aac24, 0x16);
		}
		if (sv_ClickedObjekt != 0 && sv_ClickedObjekt == x) {
			d2_RunZunftPreismanipulationDialog(a);
		}
	}
}
