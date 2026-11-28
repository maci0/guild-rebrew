

#include <stdio.h>
#include <string.h>

// SIZE 0x210
typedef struct {
	char pad0[9];
	char name[0x80];
	char text[0x187];
} Rec;

// SIZE 0x220
typedef struct {
	char id;
	char pad1[3];
	int h;
	int f8;
	int padc;
	Rec rec;
} Slot;

// SIZE 0x7c
typedef struct {
	int f0;
	char name[0x78];
} Msg;

// SIZE 0x3cc
#include "Develop/Units/d2.v1/d2_win.h"








// SIZE 0x2f4
typedef struct {
	char pad0[0x10];
	int f10;
	int f14;
	char pad18[0x28];
	D2_WIN* f40;
	char pad44[0x2b0];
} Ctl;

#include "Develop/client_types.h"
extern Win_1015f40 d2_Windows[0x60];
extern char* d2_Controls;
extern char s_6acfdc[];
extern char s_6acff0[];
extern char s_6a3a54[];
extern int d2_CurrentWindowId;
extern int main_LoopFlags;
extern int vfs_RootDir;
extern int d2_HoveredWindow;
extern char* g_14ac64c;
extern char* g_14ac604;
extern int io_RightButtonReleased;
extern int g_14ce8d8;
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern int d2_CurrentElementId;

int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_PositionFormWindows(int, int);
void __cdecl d2_CenterForm(int, int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_InitWindowBounds(int);
void __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetFormWindow(int, int);
void __cdecl d2_CreateWindowScrollbar(int, int, int, int, int, int*, int*, int*);
void __cdecl d2_PopulateSaveSlotList(int, int, void*, void*, char*, int);
void __cdecl d2_SetElementEnabled(int, int);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl vfs_LookupPath(char*, int, int*);
void __cdecl d2_SetSlotVisibility(int, int);
int __cdecl d2_EditSlotTextInput(int, int, char*);
int __cdecl d2_ConfirmTextIdMessageBox(char*, int);
int __cdecl ls_CanSaveGame(void);
void __cdecl d2_ShowStatusBanner(char*);
int __cdecl cm_RequestSysMessage(int, Msg*);
void __cdecl d2_DestroyForm(int);
#include "Develop/Units/d2.v1/d2_gui.h"
int __cdecl d2_ShowNetworkLoadGame(void)
{
	int i;
	int dlg;
	int sel;
	int wait;
	int b;
	int a;
	int c;
	int st;
	Msg m;
	char tmp[0x104];
	Slot slots[16];
	Rec recs[32];
	int flag;

	wait = main_LoopFlags;
	dlg = d2_LoadForm(0, 0, s_6acfdc);
	d2_PositionFormWindows(dlg, 1);
	d2_CenterForm(dlg, 2);
	d2_SetForm(dlg, 0);
	d2_InitWindowBounds(d2_CurrentWindowId);
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(0, 2);
	io_AppendText(0x1c58);
	d2_SetForm(0, 0);
	d2_CreateWindowScrollbar(0x214, 0x168, d2_CurrentWindowId, d2_GetFormWindow(dlg, 1), 0x82, &a, &b, &c);
	d2_PopulateSaveSlotList(dlg, 1, slots, recs, s_6acff0, 1);
	d2_SetElementEnabled(slots[0].h, 0);
	sel = d2_GetFormWindow(dlg, 1);
	while (main_RunFrameLoop((void*) d2_ShowNetworkLoadGame, wait) != 0) {
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		}
		if (g_14ce8d8 != 0 && *(int*) &((D2_WIN*)d2_Windows)[sel].pad3c[0x224] == 0) {
			for (i = 2; i < 16; i++) {
				if (d2_CurrentElementId != slots[i].h && d2_HoveredWindow != slots[i].f8) {
					if (d2_HoveredWindow == -1) {
						continue;
					}
					if ((D2_WIN*) ((D2_CONTROL_TL*)d2_Controls)[((D2_WIN*)d2_Windows)[d2_HoveredWindow].slot].parent != &((D2_WIN*)d2_Windows)[slots[i].f8]) {
						continue;
					}
				}
				flag = 0;
				sprintf(tmp, s_6a3a54, slots[i].rec.name);
				if (vfs_LookupPath(tmp, vfs_RootDir, &st)) {
					flag = 1;
				}
				d2_SetSlotVisibility(slots[i].h, 0);
				if (!d2_EditSlotTextInput(((D2_CONTROL_TL*) d2_Controls)[slots[i].h].x, ((D2_CONTROL_TL*) d2_Controls)[slots[i].h].y, slots[i].rec.text)) {
					d2_SetSlotVisibility(slots[i].h, 1);
					break;
				}
				if (!flag || d2_ConfirmTextIdMessageBox(g_14ac64c, 0x101)) {
					if (!ls_CanSaveGame()) {
						d2_ShowStatusBanner(g_14ac604);
					} else {
						memset(&m, 0, sizeof(m));
						m.f0 = i;
						strcpy(m.name, slots[i].rec.text);
						cm_RequestSysMessage(0xf, &m);
					}
					d2_DialogCloseRequested = 1;
				}
				d2_SetSlotVisibility(slots[i].h, 1);
			}
		}
	}
	d2_DestroyForm(dlg);
	return 0;
}
