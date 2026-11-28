

extern int sv_ClickedObjekt;
#include "Develop/DieGildeAddOn/game/game_player.h"
#include "Develop/DieGildeAddOn/game/entity_record.h"
extern int g_14aac94;
extern char g_6aafac[];

void __cdecl d2_ClearStatusTextSlots(void);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl RegisterStatusText(char*, int, int);
int __cdecl amt_CanUpgradeBuildingTier2(char*);
void __cdecl d2_StartZunftLevel2Action(int);

/* ADDRESS: GOLD 0x5a1a20 */
void __cdecl d2_RunZunftLevel2Menu(int a)
{
	int x;

	x = 0;
	d2_ClearStatusTextSlots();
	while (main_RunFrameLoop(d2_RunZunftLevel2Menu, 0x67fff) != 0) {
		if (amt_CanUpgradeBuildingTier2(((char*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot])) != 0) {
			x = RegisterStatusText(g_6aafac, g_14aac94, 0x16);
		}
		if (sv_ClickedObjekt != 0 && sv_ClickedObjekt == x) {
			d2_StartZunftLevel2Action(a);
		}
	}
}
