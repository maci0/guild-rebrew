


// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"









#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;

extern int g_774800;
extern int d2_CurrentWindowId;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int d2_CurrentElementId;
#include "client_dialog_state.h"
extern int g_14b556c;

int __cdecl fcn_00500e20(pos14_7f4c00*);
int __cdecl fcn_00525fb0(char*);
char* __cdecl he_StartHandlungSearch(int, int, int, int, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl fcn_00526120(int, int);
void __cdecl fcn_00532ef0(void);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl io_AppendText();
int __cdecl d2_GetWindowListItem(int, int, int);
void __cdecl fcn_0052a0c0(char*, int);
int __cdecl main_RunFrameLoop(void*, int);
#include "Develop/DieGildeAddOn/game/spiel.h"
void __cdecl fcn_00472640(int, int);
int __cdecl fcn_0058ff60(char*, ENTITY_RECORD*, int);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_0052a2d0(void);
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
	st = fcn_00500e20(&gm_GameTime);
	if (fcn_00525fb0(who) != 0) {
		return;
	}
	if (g_774800 == 0 && st != 2) {
		io_FormatTextBuffer(buf, 0x413b);
		fcn_00526120((int) buf, 4);
		fcn_00532ef0();
		return;
	}
	if (he_StartHandlungSearch(2, 0, 0x8f, 3, *(int*) (who + 1)) != 0) {
		io_FormatTextBuffer(buf, 0x413c);
		fcn_00526120((int) buf, 4);
		fcn_00532ef0();
		return;
	}
	h = fcn_00470820(0, 0, "Locations\\Friedhof\\UpgradeWorker");
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(h);
	d2_SetForm(h, 0);
	fcn_005340f0(d2_CurrentWindowId);
	d2_SetForm(h, 1);
	io_AppendText(0x4138);
	d2_SetForm(h, 3);
	s = io_AppendText(0x4139, 0x228);
	b1 = d2_GetWindowListItem(h, 3, s);
	b2 = d2_GetWindowListItem(h, 3, s + 1);
	b4 = d2_GetWindowListItem(h, 3, s + 2);
	fcn_0052a0c0(who, 0);
	while (main_RunFrameLoop(d2_RunFriedhofUpgradeWorkerDialog, 0x677c7) != 0) {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		for (i = 0; i < 768; i++) {
			if (((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].selected != 0) {
				hh = ((ENTITY_RECORD*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[i]);
				break;
			}
		}
		if (hh != 0) {
			if (gm_GetEntitySkill((char*) hh, 1) >= 1.0) {
				fcn_00472640(b1, 0);
			} else {
				fcn_00472640(b1, 1);
			}
			if (gm_GetEntitySkill((char*) hh, 2) >= 1.0) {
				fcn_00472640(b2, 0);
			} else {
				fcn_00472640(b2, 1);
			}
			if (gm_GetEntitySkill((char*) hh, 4) >= 1.0) {
				fcn_00472640(b4, 0);
			} else {
				fcn_00472640(b4, 1);
			}
		}
		if (g_100f1dc != -1) {
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
				fcn_00526120(g_14b556c, 0);
			} else if (fcn_0058ff60(who, hh, k) != 0) {
				g_774654 = 1;
			}
		}
	}
	fcn_00471e30(h);
	fcn_0052a2d0();
	sv_ClearObjectSelection();
	fcn_00532ef0();
}
