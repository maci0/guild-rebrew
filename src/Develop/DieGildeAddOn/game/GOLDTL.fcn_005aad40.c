

extern int g_7746a0;
#include "Develop/DieGildeAddOn/game/game_player.h"
#include "Develop/DieGildeAddOn/game/entity_record.h"
extern int g_14aac94;
extern char g_6aafac[];

void __cdecl fcn_005338a0(void);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl RegisterStatusText(char*, int, int);
int __cdecl amt_CanUpgradeBuildingTier2(char*);
void __cdecl d2_StartZunftLevel2Action(int);

/* ADDRESS: GOLD 0x5a1a20 */
void __cdecl fcn_005aad40(int a)
{
	int x;

	x = 0;
	fcn_005338a0();
	while (main_RunFrameLoop(fcn_005aad40, 0x67fff) != 0) {
		if (amt_CanUpgradeBuildingTier2(((char*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[g_774970])) != 0) {
			x = RegisterStatusText(g_6aafac, g_14aac94, 0x16);
		}
		if (g_7746a0 != 0 && g_7746a0 == x) {
			d2_StartZunftLevel2Action(a);
		}
	}
}
