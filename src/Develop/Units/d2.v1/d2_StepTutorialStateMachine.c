extern int d2_TutorialActive;
extern int *d2_TutorialState;
extern int tp_d2_ActiveHudSlot;
extern int d3_CameraAnimating;
extern int d3_ActiveCameraAnimation;
extern int d2_InsideBuildingActive;
extern int g_774a18;
extern volatile int gm_GameTicks;
extern volatile int tb_TimerPaused;
extern int g_774650;
extern int g_774658;
#include "Develop/Units/d2.v1/client_dialog_state.h"

int __cdecl sb_CheckVoicePlaying(int);
int __cdecl sb_StopVoice(int, int);
void __cdecl d2_BringFormToFront(int);
void __cdecl d2_SetElementEnabled(int, int);
void __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl d3snd_PlaySoundEffect(int, int, int, int);
void __cdecl d3_EndCameraAndUiMode(void);
void __cdecl d2_ShowStatusBanner(int);
void __cdecl d2_HighlightSelectedControl(int);
int __cdecl d2_DispatchTutorialInput(int, int, int, int);
int __cdecl d2_ShowTutorialPage(void);
int __cdecl d2_PollTutorialVoiceDone(void);
void __cdecl d2_ShowTutorialInlineForm(void);
void __cdecl d2_HideTutorialHint(void);
void __cdecl d2_ShowTutorialStepMessage(void);
void __cdecl d2_HideTutorialPrompt(void);
void __cdecl d2_UpdateTutorialProgress(void);
void __cdecl d2_ShowTutorialStep(void);
int __cdecl d2_CheckTutorialCueClicked(void);
void __cdecl d2_UpdateTutorialArrow(int);

/* ADDRESS: GOLDTL 0x0057e0a0 */
/* ADDRESS: GOLDDE 0x00563e90 */
int __cdecl d2_StepTutorialStateMachine(void)
{
	void (__cdecl *cb)(int); int* cues; unsigned int deadline; int cue_ready;
	unsigned int cue_time;
	unsigned int start_time;
	unsigned int current_time;

	if (d2_TutorialActive == 0) {
		return -4;
	}
	if (d2_TutorialState[6] == 0) {
		return -4;
	}
	if (*(int *)((int)d2_TutorialState[7] + 0x74) == 0) {
		return -4;
	}
	if (tp_d2_ActiveHudSlot == *(int *)((int)d2_TutorialState[7] + 0x74) && d2_TutorialState[0] != 2) {
		if (d3_CameraAnimating != 0 || d2_InsideBuildingActive != 0) {
			goto ret0;
		}
		d2_SetOverlayAnimation(0, 0);
		d2_TutorialState[0] = 3;
	}
	if (tp_d2_ActiveHudSlot != *(int *)((int)d2_TutorialState[7] + 0x74)) {
		d2_TutorialState[0] = d2_TutorialState[1];
	}
	if (d2_TutorialState[0xc] == 1 && d2_TutorialState[0] != 9) {
		d2_TutorialState[0xc] = 0;
		d2_HideTutorialPrompt();
		d2_UpdateTutorialArrow(2);
	}
	if (g_774a18 == 0) {
		return 0;
	}
	d2_UpdateTutorialProgress();
	if (d3_CameraAnimating != 0) {
		return 0;
	}
	if (d2_InsideBuildingActive != 0) {
		return 0;
	}
	switch (d2_TutorialState[0]) {
	case 1:
		if (d3_ActiveCameraAnimation != 0) {
			break;
		}
		if (d2_ShowTutorialPage() != 0) {
			return -4;
		}
		d2_TutorialState[0xe] = 0;
		d2_TutorialState[0xf] = 0;
		d2_TutorialState[0] = 2;
		if (*(int *)((int)d2_TutorialState[6] + 8) == 1 || *(int *)((int)d2_TutorialState[6] + 8) == 2) {
			d2_TutorialState[1] = 4;
			d2_TutorialState[0xb] = 0;
		} else {
			d2_TutorialState[1] = 0xb;
			d2_TutorialState[0xb] = 1;
		}
		if (*(int *)((int)d2_TutorialState[6] + 8) == 2) {
			d2_TutorialState[0xf] = 1;
		}
		if (*(int *)((int)d2_TutorialState[6] + 0x38) != 0) {
			d2_DispatchTutorialInput(2, 0, 0, 0);
		}
		d2_TutorialState[0x14] = 0;
		if (*(int *)((int)d2_TutorialState[6] + 0x64) == 0) {
			d2_TutorialState[0x16] = 0;
		} else {
			d2_TutorialState[0x16] = 1;
		}
		d2_TutorialState[0x15] = 0;
		d2_TutorialState[0x17] = 0;
		d2_TutorialState[0x18] = -1;
		cb = *(void (__cdecl **)(int))((int)d2_TutorialState[6] + 0x34);
		if (cb != 0) {
			cb(0);
		}
		d2_HighlightSelectedControl(*(int *)((int)d2_TutorialState[7] + 0x74));
		d2_SetOverlayAnimation(0, 0);
		return 0;
	case 2:
		if (d2_PollTutorialVoiceDone() != 1) {
			break;
		}
		d2_TutorialState[0] = d2_TutorialState[1];
		d2_TutorialState[2] = ((unsigned int) gm_GameTicks);
		d2_TutorialState[3] = ((unsigned int) gm_GameTicks);
		d2_TutorialState[4] = 0;
		d2_HighlightSelectedControl(0);
		return 0;
	case 3:
		if (d2_PollTutorialVoiceDone() != 1) {
			break;
		}
		d2_TutorialState[0] = d2_TutorialState[1];
		goto ret0;
ret0:
		d2_HighlightSelectedControl(0);
		return 0;
	case 4:
		if (*(int *)((int)d2_TutorialState[6] + 0x40) == 3) {
			d2_DispatchTutorialInput(0, 0, 0, 0);
			return 0;
		}
		if (((unsigned int) gm_GameTicks) > *(int *)((int)d2_TutorialState[6] + 0x2c) + d2_TutorialState[2]) {
			d2_TutorialState[2] = ((unsigned int) gm_GameTicks);
			if (d2_TutorialState[10] == 0 && *(int *)((int)d2_TutorialState[6] + 0x14) != 0) {
				d2_TutorialState[10] = 1;
				d2_ShowTutorialInlineForm();
			}
		} else {
			if (((unsigned int) gm_GameTicks) > d2_TutorialState[2] + 0x238) {
				if (d2_TutorialState[10] != 1) {
					return 0;
				}
				d2_TutorialState[2] = ((unsigned int) gm_GameTicks);
				d2_TutorialState[10] = 0;
				d2_HideTutorialHint();
			}
		}
		if (d2_TutorialState[10] == 1) {
			d2_BringFormToFront(d2_TutorialState[9]);
			return 0;
		}
		break;
	case 5:
		d2_TutorialState[2] = ((unsigned int) gm_GameTicks);
		d2_TutorialState[10] = 0;
		d2_HideTutorialHint();
		d2_TutorialState[0xf] = 2;
		if (*(unsigned int *)((int)d2_TutorialState[6] + 0x50) <= 0) {
			goto label7;
		}
		d2_TutorialState[0x10] = 0;
		d2_TutorialState[0] = 6;
		d2_TutorialState[1] = 6;
		d2_ShowTutorialStep();
		return 0;
label7:
		d2_TutorialState[0] = 7;
		d2_TutorialState[1] = 7;
		return 0;
	case 6:
		start_time = (unsigned int) d2_TutorialState[3];
		cues = *(int**)((int)d2_TutorialState[6] + 0x58);
		cue_time = (unsigned int) cues[d2_TutorialState[0x10] * 4];
		current_time = (unsigned int) gm_GameTicks;
		deadline = cue_time + start_time;
		cue_ready = current_time >= deadline;
		tb_TimerPaused = cue_ready;
		d2_SetElementEnabled(d2_TutorialState[0x13], cue_ready);
		if (d2_CheckTutorialCueClicked() != 1) {
			break;
		}
		d2_TutorialState[0x10] = d2_TutorialState[0x10] + 1;
		d2_TutorialState[2] = ((unsigned int) gm_GameTicks);
		if ((unsigned int)d2_TutorialState[0x10] < *(unsigned int *)((int)d2_TutorialState[6] + 0x50)) {
			d2_TutorialState[3] = ((unsigned int) gm_GameTicks);
			d2_ShowTutorialStep();
			return 0;
		}
		goto label7;
	case 7:
		d2_TutorialState[0xf] = 3;
		d2_TutorialState[3] = ((unsigned int) gm_GameTicks);
		d2_TutorialState[0x14] = 0;
		d2_ShowTutorialStep();
		tb_TimerPaused = 0;
		if (*(int *)((int)d2_TutorialState[6] + 0x4c) != 0) {
			d2_TutorialState[0] = 9;
			d2_TutorialState[1] = 9;
		} else {
			d2_TutorialState[0] = 0xa;
			d2_TutorialState[1] = 0xa;
			d2_TutorialState[0xb] = (*(int *)((int)d2_TutorialState[6] + 0x24) == 0);
		}
		return 0;
	case 9:
		if (d2_TutorialState[10] == 1) {
			d2_TutorialState[2] = ((unsigned int) gm_GameTicks);
			d2_TutorialState[10] = 0;
			d2_HideTutorialHint();
		}
		if (d2_TutorialState[0xc] == 0 && *(int *)((int)d2_TutorialState[6] + 0x1c) != 0) {
			d2_TutorialState[0xc] = 1;
			d2_ShowTutorialStepMessage();
			d2_UpdateTutorialArrow(0);
		}
		if (d2_TutorialState[0xc] == 1) {
			d2_BringFormToFront(d2_TutorialState[0xd]);
		}
		d2_UpdateTutorialArrow(1);
		return 0;
	case 10:
		if (d2_TutorialState[10] == 1) {
			d2_TutorialState[2] = ((unsigned int) gm_GameTicks);
			d2_TutorialState[10] = 0;
			d2_HideTutorialHint();
		}
		if (((unsigned int) gm_GameTicks) > *(int *)((int)d2_TutorialState[6] + 0x44) + d2_TutorialState[3]) {
			d3_EndCameraAndUiMode();
			d2_DialogCloseRequested = g_774650 - g_774658;
			d2_TutorialState[0] = 0xb;
			d2_TutorialState[1] = 0xb;
			d2_TutorialState[3] = ((unsigned int) gm_GameTicks);
		}
		if (d2_TutorialState[0xb] != 0) {
			break;
		}
		if (*(int *)((int)d2_TutorialState[6] + 0x24) == 0) {
			break;
		}
		d2_ShowStatusBanner(*(int *)(*(int *)((int)d2_TutorialState[6] + 0x24) * 4 + 0x14a5320));
		if (*(int *)((int)d2_TutorialState[6] + 0x28) != 0) {
			if (d2_TutorialState[5] != 0) {
				if (sb_CheckVoicePlaying(d2_TutorialState[5]) != 0) {
					sb_StopVoice(d2_TutorialState[5], 0);
				}
				d2_TutorialState[5] = 0;
			}
			d2_TutorialState[5] = d3snd_PlaySoundEffect(-7, 0, *(int *)((int)d2_TutorialState[6] + 0x28), -1);
		}
		d2_TutorialState[0xb] = 1;
		d2_ShowTutorialPage();
		return 0;
	case 11:
		if (d2_TutorialState[10] == 1) {
			d2_TutorialState[2] = ((unsigned int) gm_GameTicks);
			d2_TutorialState[10] = 0;
			d2_HideTutorialHint();
		}
		if (((unsigned int) gm_GameTicks) > *(int *)((int)d2_TutorialState[6] + 0x30) + d2_TutorialState[3]) {
			d3_EndCameraAndUiMode();
			d2_DialogCloseRequested = g_774650 - g_774658;
			d2_TutorialState[0] = 0xc;
			d2_TutorialState[1] = 0xc;
			d2_TutorialState[3] = ((unsigned int) gm_GameTicks);
		}
		if (d2_TutorialState[0xb] != 0) {
			break;
		}
		if (*(int *)((int)d2_TutorialState[6] + 0x24) == 0) {
			break;
		}
		d2_ShowStatusBanner(*(int *)(*(int *)((int)d2_TutorialState[6] + 0x24) * 4 + 0x14a5320));
		if (*(int *)((int)d2_TutorialState[6] + 0x28) != 0) {
			if (d2_TutorialState[5] != 0) {
				if (sb_CheckVoicePlaying(d2_TutorialState[5]) != 0) {
					sb_StopVoice(d2_TutorialState[5], 0);
				}
				d2_TutorialState[5] = 0;
			}
			d2_TutorialState[5] = d3snd_PlaySoundEffect(-7, 0, *(int *)((int)d2_TutorialState[6] + 0x28), -1);
		}
		d2_TutorialState[0xb] = 1;
		d2_ShowTutorialPage();
		return 0;
	case 12:
		if (d2_TutorialState[10] == 1) {
			d2_TutorialState[2] = ((unsigned int) gm_GameTicks);
			d2_TutorialState[10] = 0;
			d2_HideTutorialHint();
		}
		cb = *(void (__cdecl **)(int))((int)d2_TutorialState[6] + 0x34);
		if (cb != 0) {
			cb(1);
		}
		d2_TutorialState[6] = *(int *)((int)d2_TutorialState[6] + 0x70);
		d2_TutorialState[0] = 1;
		d2_TutorialState[1] = 1;
		d2_ShowStatusBanner((int)(void *)0x6b5c60);
		break;
	default:
		break;
	}
	return 0;
}
