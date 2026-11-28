


extern int* d2_TutorialState;
#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(char*, ...);
void __cdecl d2_SetFormVisibility(int, int);
int __cdecl sb_CheckVoicePlaying(int);
void __cdecl sb_StopVoice(int, int);

/* ADDRESS: GOLDDE 0x00566290 */
void __cdecl d2_HideTutorialPrompt(void)
{
	d2_SetForm(d2_TutorialState[13], 0);
	io_AppendText(str_dollar_C);
	d2_SetFormVisibility(d2_TutorialState[13], 0);
	if (d2_TutorialState[5] != 0) {
		if (sb_CheckVoicePlaying(d2_TutorialState[5]) != 0) {
			sb_StopVoice(d2_TutorialState[5], 0);
		}
		d2_TutorialState[5] = 0;
	}
}
