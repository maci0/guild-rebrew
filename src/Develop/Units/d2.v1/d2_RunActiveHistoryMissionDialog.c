extern int gm_MissionJobs[9];
#include "Develop/DieGildeAddOn/game/game_player.h"
extern int d2_DialogButtonAction;
extern int d2_CurrentElementId;
extern char gm_SelectedMissionIndex;
extern int g_7728dc;
#include "Develop/Units/d2.v1/client_dialog_state.h"

int __cdecl gm_LookupMissionSpec(int a);
void __cdecl d2_RunMissionBriefingDialog(int a, int b);
int __cdecl d2_LoadForm(int a, int b, char* s);
void __cdecl d2_CenterDialogWindows(int a);
void __cdecl d2_SetForm(int a, int b);
int __cdecl io_AppendText(int a, ...);
int __cdecl d2_GetWindowListItem(int a, int b, int c);
int __cdecl gm_AllocRandomMissionJob(int a, int b, int c);
int __cdecl cm_RequestSysMessage(int a, void* b);
int __cdecl cm_GetCommandStatus(int a);
void __cdecl cm_StepCommandQueue(void);
int __cdecl main_RunFrameLoop(void* a, int b);
void __cdecl d2_DestroyForm(int a);
void __cdecl d2_ShowMissionSpecDialog(int a, int b);
void __cdecl main_ExitToGameLoop(int a);
void __cdecl sb_ReleaseSampleBank(int a);

/* The dialog message the three choice handlers send. Only three fields are
 * touched here; the native object is 0x7c bytes. */
typedef struct DLG_MSG {
	int id;
	char pad0[0xc];
	int vend;
	char pad1[0xc];
	int vunk;
	char pad2[0x58];
} DLG_MSG;

/* Mission announcement dialog for the special\mission sequence: opens the
 * dialog, resolves three choice strings, waits for the selection, then tears
 * the dialog and the arena down. Native body: 684 bytes, frame 0x190. */
/* ADDRESS: GOLDTL 0x004b5b40 */
void __cdecl d2_RunActiveHistoryMissionDialog(int mode)
{
	DLG_MSG m1;
	DLG_MSG m2;
	DLG_MSG m3;
	int* obj;
	int changed;
	int arena_done;
	int flags;
	int r1;
	int r2;
	int r3;
	int q;
	int i;
	int h;
	char* slot;
	int dlg;

	changed = 0;
	arena_done = 0;
	obj = 0;
	slot = (char*) (0x7f4ca0 + (int) gm_LocalPlayerSlot * 0x21c);
	h = gm_LookupMissionSpec(gm_MissionJobs[0]);
	for (i = 0; i < 9; i++) {
		gm_MissionJobs[i] = 0;
	}
	flags = (mode & ~9) | 0x100;
	d2_RunMissionBriefingDialog(h, flags);
	dlg = d2_LoadForm(0, 0, "special\\mission");
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 1);
	io_AppendText(0x1b95, *(unsigned short*) slot);
	r1 = d2_GetWindowListItem(dlg, 1, io_AppendText(0x1b96, 0x1b98));
	r2 = d2_GetWindowListItem(dlg, 1, io_AppendText(0x1b96, 0x1b99));
	r3 = d2_GetWindowListItem(dlg, 1, io_AppendText(0x1b96, 0x1b9a));

	d2_DialogButtonAction = -1;
	do {
		if (d2_DialogButtonAction != -1) {
			if (d2_CurrentElementId == r1) {
				obj = (int*) gm_AllocRandomMissionJob(*(int*) (slot + 4), (int) gm_SelectedMissionIndex, 1);
				m1.id = *(int*) (slot + 4);
				m1.vend = 0;
				changed = 1;
				m1.vunk = *obj;
				q = cm_RequestSysMessage(10, &m1);
				while (cm_GetCommandStatus(q) == 0) {
					cm_StepCommandQueue();
				}
				d2_DialogCloseRequested = 1;
			}
			else if (d2_CurrentElementId == r2) {
				m2.id = *(int*) (slot + 4);
				gm_SelectedMissionIndex = -1;
				m2.vend = 0;
				m2.vunk = 0;
				q = cm_RequestSysMessage(10, &m2);
				while (cm_GetCommandStatus(q) == 0) {
					cm_StepCommandQueue();
				}
				d2_DialogCloseRequested = 1;
			}
			else if (d2_CurrentElementId == r3) {
				m3.id = *(int*) (slot + 4);
				gm_SelectedMissionIndex = -1;
				arena_done = 1;
				m3.vend = 1;
				m3.vunk = 0;
				q = cm_RequestSysMessage(10, &m3);
				while (cm_GetCommandStatus(q) == 0) {
					cm_StepCommandQueue();
				}
				d2_DialogCloseRequested = 1;
			}
		}
	} while (main_RunFrameLoop((void*) d2_RunActiveHistoryMissionDialog, flags | 0x80) != 0);
	d2_DestroyForm(dlg);
	if (changed) {
		d2_ShowMissionSpecDialog(*obj, flags);
	}
	else if (arena_done) {
		main_ExitToGameLoop(flags);
	}
	if (g_7728dc != 0) {
		sb_ReleaseSampleBank(g_7728dc);
	}
	g_7728dc = 0;
}
