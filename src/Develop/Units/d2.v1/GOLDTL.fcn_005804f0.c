


extern int* g_665f08;
#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(char*, ...);
void __cdecl fcn_00471af0(int, int);
int __cdecl sb_CheckVoicePlaying(int);
void __cdecl sb_StopVoice(int, int);

void __cdecl d2_HideTutorialPrompt(void)
{
	d2_SetForm(g_665f08[13], 0);
	io_AppendText(g_6811b0);
	fcn_00471af0(g_665f08[13], 0);
	if (g_665f08[5] != 0) {
		if (sb_CheckVoicePlaying(g_665f08[5]) != 0) {
			sb_StopVoice(g_665f08[5], 0);
		}
		g_665f08[5] = 0;
	}
}
