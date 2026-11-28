


extern int* d2_TutorialState;
extern unsigned char** tp_d2_ActiveHudSlot;
extern int d2_DialogButtonAction;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char io_LastKeyScancode;

int __cdecl sb_CheckVoicePlaying(int);
void __cdecl sb_StopVoice(int, int);

int __cdecl d2_PollTutorialVoiceDone(void)
{
	int o;
	unsigned char* p;

	o = d2_TutorialState[7];
	if (o == 0) {
		return -4;
	}
	if (*(int*) (o + 0x74) == 0) {
		return -4;
	}
	p = *tp_d2_ActiveHudSlot;
	if (p != 0 && *p == 0x87) {
		if (d2_DialogButtonAction != -1) {
			if (d2_CurrentElementId == d2_TutorialState[8]) {
				if (d2_TutorialState[5] != 0) {
					if (sb_CheckVoicePlaying(d2_TutorialState[5]) != 0) {
						sb_StopVoice(d2_TutorialState[5], 0);
					}
					d2_TutorialState[5] = 0;
				}
				return 1;
			}
		}
		else if (io_LastKeyScancode == 0x1c) {
			if (d2_TutorialState[5] != 0) {
				if (sb_CheckVoicePlaying(d2_TutorialState[5]) != 0) {
					sb_StopVoice(d2_TutorialState[5], 0);
				}
				d2_TutorialState[5] = 0;
			}
			return 1;
		}
	}
	return 0;
}
