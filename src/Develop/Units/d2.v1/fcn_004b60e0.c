extern int g_10069a0;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern char g_7f4ca0[];
extern int g_100f1dc;
extern int g_6a3760;
extern int g_774954;
extern char g_6a3440;
#include "client_dialog_state.h"

int __cdecl gm_LookupMissionSpec(int);
char* __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(char*);
void __cdecl d2_SetForm(char*, int);
void __cdecl d2_RunMissionBriefingDialog(int, int);
void __cdecl io_AppendText(int, int);
int __cdecl main_RunFrameLoop(int, int);
void __cdecl d2_DestroyForm(char*);
void __cdecl fcn_004b5530(int, int);
void __cdecl fcn_004b5a80(int);
void __cdecl main_ExitToGameLoop(int);
void __cdecl fcn_004b60e0(int);

/* ADDRESS: GOLDTL 0x004b60e0 */
void __cdecl fcn_004b60e0(int flags)
{
	unsigned short* tab;
	char* obj;
	int tag;
	int v;
	int r;

	r = 0;
	tab = (unsigned short*) (0x7f4ca0 + (unsigned int) g_774970 * 0x21c);
	tag = gm_LookupMissionSpec(g_10069a0);
	obj = d2_LoadForm(0, 0, (char*) 0x681130);
	d2_CenterDialogWindows(obj);
	d2_SetForm(obj, 0);
	v = (flags & 0xfffffff6) | 0x100;
	d2_RunMissionBriefingDialog(tag, v);
	d2_SetForm(obj, 1);
	io_AppendText(0x1b95, *tab);
	g_100f1dc = -1;
	for (;;) {
		if (g_6a3760 == -1) {
			if (g_774954 != 0) {
				r = 3;
			} else {
				r = (g_6a3440 != 5) + 1;
			}
			g_774654 = 1;
		}
		if (!main_RunFrameLoop((int) fcn_004b60e0, v | 0x80)) {
			break;
		}
	}
	d2_DestroyForm(obj);
	if (r == 1) {
		fcn_004b5530(g_10069a0, v);
		return;
	}
	if (r == 2) {
		fcn_004b5a80(v);
		return;
	}
	if (r == 3) {
		main_ExitToGameLoop(v);
		return;
	}
}
