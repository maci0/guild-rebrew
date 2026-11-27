

extern int d2_CurrentWindowId;
#include "Develop/DieGildeAddOn/game/game_player.h"
#include "Develop/DieGildeAddOn/game/entity_record.h"
extern char g_6a9694[];

int __cdecl gm_GetLawEntry(int, int*);
void __cdecl d2_SetForm(int, int);
int __cdecl d2_AddElementToWindow(int, int, int, int);
int __cdecl io_AppendText(char*, ...);
void __cdecl fcn_00534210(int, int, char*, int, int);

void __cdecl fcn_005c9220(int* o)
{
	int info[9];
	int i;

	if (o[0] != -1) {
		if (gm_GetLawEntry(o[5], info) != 0 && info[6] != 0 && info[3] != 0) {
			d2_SetForm(o[0], o[1]);
			for (i = 0; i < info[3]; i++) {
				d2_AddElementToWindow(5 + i * 16, 5, 0x526, d2_CurrentWindowId);
			}
		}
		if (o[4] <= 4) {
			d2_SetForm(o[0], o[2]);
			io_AppendText(g_6a9694, o[4] + 0x16b7);
			d2_SetForm(o[0], o[3]);
			fcn_00534210(0, 6, (char*)&((ENTITY_RECORD*)g_7f4ca0)[g_774970], o[4], 0x4df);
		}
	}
}
