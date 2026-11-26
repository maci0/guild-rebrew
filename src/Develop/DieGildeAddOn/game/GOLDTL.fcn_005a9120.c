#include "Develop/DieGildeAddOn/game/entity_record.h"


extern int g_7746a0;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern char g_7f4ca0[];
extern int g_14abb58;
extern char g_6aae28[];

void __cdecl fcn_005338a0(void);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl RegisterStatusText(char*, int, int);
void __cdecl d2_ShowGildenkasseDialog(int);

void __cdecl d2_RunStadtkasseMenu(int building)
{
	int x;

	fcn_005338a0();
	while (main_RunFrameLoop(d2_RunStadtkasseMenu, 0x67fff) != 0) {
		if (((char *)&((ENTITY_RECORD_VIEW *)g_7f4ca0)[g_774970])[0x166] != 0) {
			x = RegisterStatusText(g_6aae28, g_14abb58, 0x16);
		}
		else {
			x = 0;
		}
		if (g_7746a0 != 0 && g_7746a0 == x) {
			d2_ShowGildenkasseDialog(building);
		}
	}
}
