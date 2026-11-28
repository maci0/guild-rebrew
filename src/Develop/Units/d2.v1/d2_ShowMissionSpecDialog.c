

extern char g_681130[];
extern char g_68112c[];
extern char g_681110[];
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int d2_DialogButtonAction;
#include "Develop/Units/d2.v1/client_dialog_state.h"

char* __cdecl gm_LookupMissionSpec(int);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl io_AppendText(int);
int __cdecl fcn_0064d41a(char*, char*, ...);
int __cdecl d3snd_PlaySoundEffect(int, int, char*, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);
int __cdecl sb_CheckVoicePlaying(int);
void __cdecl sb_StopVoice(int, int);

/* ADDRESS: GOLDDE 0x004a37c0 */
void __cdecl d2_ShowMissionSpecDialog(int a1, int flags)
{
	char buf[0x100];
	char* r;
	int h;
	int x;

	r = gm_LookupMissionSpec(a1);
	h = d2_LoadForm(0, 0, g_681130);
	d2_CenterDialogWindows(h);
	d2_SetForm(h, 1);
	io_AppendText(*(int*) (r + 8) + 1);
	io_AppendText((int) g_68112c);
	io_AppendText(0x7d);
	fcn_0064d41a(buf, g_681110, *(int*) (r + 0xc));
	x = d3snd_PlaySoundEffect(-7, 0, buf, -1);
	while (main_RunFrameLoop(d2_ShowMissionSpecDialog, flags) != 0) {
		if (io_RightButtonReleased != 0)
			d2_DialogCloseRequested = 1;
		if (d2_DialogButtonAction == 2)
			d2_DialogCloseRequested = 1;
	}
	if (h != -1)
		d2_DestroyForm(h);
	if (sb_CheckVoicePlaying(x) != 0)
		sb_StopVoice(x, 0x19);
}
