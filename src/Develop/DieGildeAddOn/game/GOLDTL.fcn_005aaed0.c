

extern int g_7746a0;
#include "Develop/DieGildeAddOn/game/game_player.h"
#include "Develop/DieGildeAddOn/game/entity_record.h"
extern int g_14aac24;
extern char g_6aafe4[];

void __cdecl fcn_005338a0(void);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl RegisterStatusText(char*, int, int);
int __cdecl gm_CheckZunftPreismanipulation(char*);
void __cdecl d2_RunZunftPreismanipulationDialog(int);

/* ADDRESS: GOLD 0x5a1bb0 */
void __cdecl d2_RunZunftPreismanipMenu(int a)
{
	int x;

	x = 0;
	fcn_005338a0();
	while (main_RunFrameLoop(d2_RunZunftPreismanipMenu, 0x67fff) != 0) {
		if (gm_CheckZunftPreismanipulation(((char*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[g_774970])) != 0) {
			x = RegisterStatusText(g_6aafe4, g_14aac24, 0x16);
		}
		if (g_7746a0 != 0 && g_7746a0 == x) {
			d2_RunZunftPreismanipulationDialog(a);
		}
	}
}
