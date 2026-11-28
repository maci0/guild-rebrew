


// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"









#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;

extern int gm_AllEntitiesControllable;
extern int d2_CurrentWindowId;
extern int d2_DialogButtonAction;
extern int io_RightButtonReleased;
extern int d2_CurrentElementId;
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern int g_14b556c;

int __cdecl gm_GetSeason(pos14_7f4c00*);
int __cdecl d2_CheckOwnerBlocked(char*);
char* __cdecl he_StartHandlungSearch(int, int, int, int, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl d2_ShowModalMessageBox(int, int);
void __cdecl d3_EndCameraAndUiMode(void);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_InitWindowBounds(int);
int __cdecl io_AppendText();
int __cdecl d2_GetWindowListItem(int, int, int);
void __cdecl d2_InitPlayerBar(char*, int);
int __cdecl main_RunFrameLoop(void*, int);
#include "Develop/DieGildeAddOn/game/spiel.h"
void __cdecl d2_SetElementEnabled(int, int);
int __cdecl d2_SendFriedhofUpgradeWorkerCmd(char*, ENTITY_RECORD*, int);
void __cdecl d2_DestroyForm(int);
void __cdecl d2_RestoreHudAfterDialog(void);
void __cdecl sv_ClearObjectSelection(void);

void __cdecl d2_RunFriedhofUpgradeWorkerDialog(char* who)
{
	int b2;
	char buf[0x400];
	ENTITY_RECORD* hh;
	int st;
	int h;
	int s;
	int b1;
	int b4;
	int i;
	int k;

	hh = 0;
	st = gm_GetSeason(&gm_GameTime);
	if (d2_CheckOwnerBlocked(who) != 0) {
		return;
	}
	if (gm_AllEntitiesControllable == 0 && st != 2) {
		io_FormatTextBuffer(buf, 0x413b);
		d2_ShowModalMessageBox((int) buf, 4);
		d3_EndCameraAndUiMode();
		return;
	}
	if (he_StartHandlungSearch(2, 0, 0x8f, 3, *(int*) (who + 1)) != 0) {
		io_FormatTextBuffer(buf, 0x413c);
		d2_ShowModalMessageBox((int) buf, 4);
		d3_EndCameraAndUiMode();
		return;
	}
	h = d2_LoadForm(0, 0, "Locations\\Friedhof\\UpgradeWorker");
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(h);
	d2_SetForm(h, 0);
	d2_InitWindowBounds(d2_CurrentWindowId);
	d2_SetForm(h, 1);
	io_AppendText(0x4138);
	d2_SetForm(h, 3);
	s = io_AppendText(0x4139, 0x228);
	b1 = d2_GetWindowListItem(h, 3, s);
	b2 = d2_GetWindowListItem(h, 3, s + 1);
	b4 = d2_GetWindowListItem(h, 3, s + 2);
	d2_InitPlayerBar(who, 0);
	while (main_RunFrameLoop(d2_RunFriedhofUpgradeWorkerDialog, 0x677c7) != 0) {
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		}
		for (i = 0; i < 768; i++) {
			if (((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].selected != 0) {
				hh = ((ENTITY_RECORD*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i]);
				break;
			}
		}
		if (hh != 0) {
			if (gm_GetEntitySkill((char*) hh, 1) >= 1.0) {
				d2_SetElementEnabled(b1, 0);
			} else {
				d2_SetElementEnabled(b1, 1);
			}
			if (gm_GetEntitySkill((char*) hh, 2) >= 1.0) {
				d2_SetElementEnabled(b2, 0);
			} else {
				d2_SetElementEnabled(b2, 1);
			}
			if (gm_GetEntitySkill((char*) hh, 4) >= 1.0) {
				d2_SetElementEnabled(b4, 0);
			} else {
				d2_SetElementEnabled(b4, 1);
			}
		}
		if (d2_DialogButtonAction != -1) {
			if (d2_CurrentElementId == b1) {
				k = 1;
			} else if (d2_CurrentElementId == b2) {
				k = 2;
			} else if (d2_CurrentElementId == b4) {
				k = 4;
			} else {
				continue;
			}
			if (hh == 0) {
				d2_ShowModalMessageBox(g_14b556c, 0);
			} else if (d2_SendFriedhofUpgradeWorkerCmd(who, hh, k) != 0) {
				d2_DialogCloseRequested = 1;
			}
		}
	}
	d2_DestroyForm(h);
	d2_RestoreHudAfterDialog();
	sv_ClearObjectSelection();
	d3_EndCameraAndUiMode();
}
