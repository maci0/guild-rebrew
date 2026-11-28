


extern char s_6ad2f8[];
extern char s_6ad2e8[];
extern int main_LoopFlags;
extern int d2_CurrentWindowId;
extern unsigned char msx_AudioVolumeSettings[4];
extern unsigned char g_7766a4[4];
extern int g_14ac564;
extern int g_14ac568;
extern int g_14ac56c;
extern int g_14ac570;
extern int g_14ac574;
extern int g_14ac53c;
extern int g_14ac540;
extern int g_14ac544;
extern int g_14ac548;
extern int g_14ac54c;
extern int g_14ac5a8;
extern int g_14ac5ac;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char io_LastKeyScancode;
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern int d2_DialogButtonAction;
extern char* g_7747b8;

int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_UpdateViewportCenter(int);
void __cdecl d2_PositionFormWindows(int, int);
void __cdecl d2_CenterForm(int, int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_InitWindowBounds(int);
void __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
#include "Develop/Units/d2.v1/d2_gui.h"
void __cdecl d2_SetValueGaugeFlags(int, int);
void __cdecl d2_SetValueGaugeLabel(int, int);
void __cdecl d2_SetValueGaugeStepLabels(int, int, int, int, int, int, int);
void __cdecl d2_CreateButtonRow(int, int, int*, int, ...);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl d2_GetControlValue(int);
void __cdecl sb_SetMasterVolume(int);
void __cdecl SetMasterVolume(int);
int __cdecl sb_PlayVoice(char*, char*, int, int, int, int, int);
void __cdecl io_SaveIniSettings(void);
void __cdecl msx_ApplyAudioSettings(void);
void __cdecl d2_DestroyForm(int);

void __cdecl d2_ShowSoundOptions(void)
{
	int s2;
	int s0;
	int s3;
	float master;
	int playing;
	int changed;
	int ok;
	int cancel;
	float sfx;
	float music;
	int btn[2];
	int dlg;
	int wait;
	int s1;
	int s4;

	changed = 0;
	playing = 0;
	wait = main_LoopFlags & ~0x2000;
	dlg = d2_LoadForm(0, 0, s_6ad2f8);
	d2_UpdateViewportCenter(wait);
	d2_PositionFormWindows(dlg, 1);
	d2_CenterForm(dlg, 2);
	d2_SetForm(dlg, 0);
	d2_InitWindowBounds(d2_CurrentWindowId);
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(dlg, 2);
	io_AppendText(0x1c5b);
	d2_SetForm(dlg, 1);
	s0 = d2_GetWindowListItem(dlg, 1, 0);
	s1 = d2_GetWindowListItem(dlg, 1, 1);
	s2 = d2_GetWindowListItem(dlg, 1, 2);
	s3 = d2_GetWindowListItem(dlg, 1, 3);
	s4 = d2_GetWindowListItem(dlg, 1, 4);
	d2_SetElementValue(s0, 0, 0x7f, msx_AudioVolumeSettings[0]);
	d2_SetValueGaugeFlags(s0, 0x882);
	d2_SetValueGaugeLabel(s0, g_14ac564);
	d2_SetElementValue(s1, 0, 0x7f, msx_AudioVolumeSettings[1]);
	d2_SetValueGaugeFlags(s1, 0x882);
	d2_SetValueGaugeLabel(s1, g_14ac568);
	d2_SetElementValue(s2, 0, 0x7f, msx_AudioVolumeSettings[2]);
	d2_SetValueGaugeFlags(s2, 0x882);
	d2_SetValueGaugeLabel(s2, g_14ac56c);
	d2_SetElementValue(s3, 0, 0x7f, msx_AudioVolumeSettings[3]);
	d2_SetValueGaugeFlags(s3, 0x882);
	d2_SetValueGaugeLabel(s3, g_14ac570);
	d2_SetElementValue(s4, 0, 4, g_7766a4[0]);
	d2_SetValueGaugeFlags(s4, 0x82);
	d2_SetValueGaugeLabel(s4, g_14ac574);
	d2_SetValueGaugeStepLabels(s4, 5, g_14ac53c, g_14ac540, g_14ac544, g_14ac548, g_14ac54c);
	d2_SetForm(dlg, 3);
	d2_CreateButtonRow(d2_CurrentWindowId, 0, btn, 2, g_14ac5a8, g_14ac5ac);
	ok = btn[0];
	cancel = btn[1];
	while (main_RunFrameLoop((void*) d2_ShowSoundOptions, wait) != 0) {
		if (io_RightButtonReleased != 0 || io_LastKeyScancode == 1) {
			d2_DialogCloseRequested = 1;
		}
		if (d2_DialogButtonAction != -1) {
			if (d2_CurrentElementId == ok) {
				changed = 1;
				d2_DialogCloseRequested = 1;
			} else if (d2_CurrentElementId == cancel) {
				d2_DialogCloseRequested = 1;
			}
		}
		if (g_14ce8d0 != 0 && (d2_CurrentElementId == s0 || d2_CurrentElementId == s1 || d2_CurrentElementId == s2 || d2_CurrentElementId == s3)) {
			master = d2_GetControlValue(s0) * 0.01f;
			music = (float)(d2_GetControlValue(s1));
			sfx = (float)(d2_GetControlValue(s2));
			sb_SetMasterVolume((int) (music * master));
			SetMasterVolume((int) (sfx * master));
			if (d2_CurrentElementId == s1 && playing == 0) {
				playing = sb_PlayVoice(g_7747b8, s_6ad2e8, 1, 0x3f, 0x7f, 0, 0);
			}
		}
	}
	if (changed) {
		msx_AudioVolumeSettings[0] = (unsigned char) d2_GetControlValue(s0);
		msx_AudioVolumeSettings[1] = (unsigned char) d2_GetControlValue(s1);
		msx_AudioVolumeSettings[2] = (unsigned char) d2_GetControlValue(s2);
		msx_AudioVolumeSettings[3] = (unsigned char) d2_GetControlValue(s3);
		g_7766a4[0] = (unsigned char) d2_GetControlValue(s4);
		io_SaveIniSettings();
		msx_ApplyAudioSettings();
	}
	d2_DestroyForm(dlg);
}
