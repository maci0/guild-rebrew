extern char g_681130[];
extern int gm_MissionJobs;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern char gm_EntitySlotTable[];
extern int d2_DialogButtonAction;
extern int g_6a3760;
extern int g_774954;
extern char gm_SelectedMissionIndex;
#include "Develop/Units/d2.v1/client_dialog_state.h"

int __cdecl gm_LookupMissionSpec(int);
char* __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(char*);
void __cdecl d2_SetForm(char*, int);
void __cdecl d2_RunMissionBriefingDialog(int, int);
void __cdecl io_AppendText(int, int);
int __cdecl main_RunFrameLoop(int, int);
void __cdecl d2_DestroyForm(char*);
void __cdecl d2_ShowMissionSpecDialog(int, int);
void __cdecl d2_RunSpecialMissionDialog(int);
void __cdecl main_ExitToGameLoop(int);
void __cdecl d2_WaitHistoryMissionDialog(int);

/* ADDRESS: GOLDTL 0x004b60e0 */
/* ADDRESS: GOLDDE 0x004a4370 */
void __cdecl d2_WaitHistoryMissionDialog(int flags)
{
	unsigned short* tab;
	char* obj;
	int tag;
	int v;
	int r;

	r = 0;
	tab = (unsigned short*) ((int) &gm_EntitySlotTable + (unsigned int) gm_LocalPlayerSlot * 0x21c);
	tag = gm_LookupMissionSpec(gm_MissionJobs);
	obj = d2_LoadForm(0, 0, (char*) &g_681130);
	d2_CenterDialogWindows(obj);
	d2_SetForm(obj, 0);
	v = (flags & 0xfffffff6) | 0x100;
	d2_RunMissionBriefingDialog(tag, v);
	d2_SetForm(obj, 1);
	io_AppendText(0x1b95, *tab);
	d2_DialogButtonAction = -1;
	for (;;) {
		if (g_6a3760 == -1) {
			if (g_774954 != 0) {
				r = 3;
			} else {
				r = (gm_SelectedMissionIndex != 5) + 1;
			}
			d2_DialogCloseRequested = 1;
		}
		if (!main_RunFrameLoop((int) d2_WaitHistoryMissionDialog, v | 0x80)) {
			break;
		}
	}
	d2_DestroyForm(obj);
	if (r == 1) {
		d2_ShowMissionSpecDialog(gm_MissionJobs, v);
		return;
	}
	if (r == 2) {
		d2_RunSpecialMissionDialog(v);
		return;
	}
	if (r == 3) {
		main_ExitToGameLoop(v);
		return;
	}
}
