


extern int* d2_TutorialState;
extern char str_empty[];
#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl d2_ShowStatusBanner(char*);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(char*, ...);
void __cdecl d2_SetFormVisibility(int, int);
int __cdecl sb_CheckVoicePlaying(int);
void __cdecl sb_StopVoice(int, int);
int __cdecl d3snd_PlaySoundEffect(int, int, int, int);

void __cdecl d2_ShowTutorialInlineForm(void)
{
	if (d2_TutorialState[6] != 0 && *(int*) (d2_TutorialState[6] + 0x14) != 0) {
		d2_ShowStatusBanner(str_empty);
		d2_SetForm(d2_TutorialState[9], 0);
		io_AppendText(str_dollar_C);
		io_AppendText(*(char**) (d2_TutorialState[6] + 0x14));
		d2_SetFormVisibility(d2_TutorialState[9], 1);
		if (*(int*) (d2_TutorialState[6] + 0x18) != 0) {
			if (d2_TutorialState[5] != 0) {
				if (sb_CheckVoicePlaying(d2_TutorialState[5]) != 0) {
					sb_StopVoice(d2_TutorialState[5], 0);
				}
				d2_TutorialState[5] = 0;
			}
			d2_TutorialState[5] = d3snd_PlaySoundEffect(-7, 0, *(int*) (d2_TutorialState[6] + 0x18), -1);
		}
	}
}
