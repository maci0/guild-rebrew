

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// SIZE 0x210
typedef struct {
	int id;
	char pad4[5];
	char name[0x207];
} Rec;

// SIZE 0x2f4
typedef struct {
	char pad0[0x18];
	int f18;
	char pad1c[0x40];
	int f5c;
	char pad60[0xc];
	int f6c;
	char pad70[0x160];
	int f1d0;
	char pad1d4[0x120];
} Slot;

// SIZE 0x10
typedef struct {
	char pad0[0xc];
	int fc;
} Win;

extern char s_6acf98[];
extern char s_6acf90[];
extern int d2_CurrentWindowId;
extern char* g_14ac654;
extern char* d2_Controls;
extern char* d2_CurrentWindow;
extern int d2_DialogButtonAction;
extern int io_RightButtonReleased;
extern int g_14ce8d8;
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern int d2_CurrentElementId;

int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetFormWindow(int, int);
void __cdecl d2_CreateWindowScrollbar(int, int, int, int, int, int*, int*, int*);
int __cdecl vfs_ListFilesByExtension(int, int, Rec*);
int __cdecl d2_GetWindowListItem(int, int, int);
#include "Develop/Units/d2.v1/d2_gui.h"
#include "Develop/Units/d2.v1/d2_gui.h"
void __cdecl d2_SetLabelText(int, char*);
void __cdecl d2_SetElementFont(int, int);
int __cdecl d2_GetControlValue(int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);

int __cdecl d2_OpenFileSelector(int wait, int mode, int title, int a4, int a5, char* out)
{
	int list;
	int field;
	int result;
	int flag;
	int ok;
	int w;
	int h;
	char buf[0x20];
	Rec recs[32];
	int dlg;
	int count;
	int i;

	list = -1;
	field = -1;
	ok = -1;
	result = 0;
	dlg = d2_LoadForm(0, 0, s_6acf98);
	d2_CenterDialogWindows(dlg);
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(dlg, 2);
	io_AppendText(title);
	d2_SetForm(dlg, 0);
	d2_CreateWindowScrollbar(0x140, 0x100, d2_CurrentWindowId, d2_GetFormWindow(dlg, 1), 0x18, &w, &h, &field);
	memset(recs, 0, sizeof(recs));
	count = vfs_ListFilesByExtension(a4, a5, recs);
	flag = mode & 1;
	if (!flag) {
		d2_SetForm(dlg, 3);
		ok = d2_GetWindowListItem(dlg, 3, io_AppendText(0x1ccc));
		d2_SetForm(dlg, 0);
		list = d2_GetWindowListItem(dlg, 0, 0);
		d2_SetElementValue(list, g_14ac654);
	}
	d2_SetForm(dlg, 1);
	for (i = 0; i < count; i++) {
		recs[i].id = d2_ShowTxt(0, (short) (i * 24), recs[i].name, d2_CurrentWindowId);
		((D2_CONTROL_TL*) d2_Controls)[recs[i].id].value_05c = 1;
		((D2_CONTROL_TL*) d2_Controls)[recs[i].id].value_06c = 1;
		((D2_CONTROL_TL*) d2_Controls)[recs[i].id].width = ((Win*)d2_CurrentWindow)->fc;
		((D2_CONTROL_TL*) d2_Controls)[recs[i].id].flags_1d0 = 3;
	}
	_itoa(count, buf, 10);
	d2_SetLabelText(field, buf);
	d2_SetElementFont(field, 0x54);
	while (main_RunFrameLoop((void*) d2_OpenFileSelector, wait) != 0) {
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		}
		if (g_14ce8d8 != 0) {
			for (i = 0; i < count; i++) {
				if (d2_CurrentElementId == recs[i].id) {
					if (flag) {
						sprintf(out, s_6acf90, a4, recs[i].name, a5);
						d2_DialogCloseRequested = 1;
						result = 1;
					} else {
						d2_SetElementValue(list, recs[i].name);
					}
					break;
				}
			}
		}
		if (d2_DialogButtonAction != -1 && d2_CurrentElementId == ok) {
			if (!flag) {
				sprintf(out, s_6acf90, a4, d2_GetControlValue(list), a5);
			}
			d2_DialogCloseRequested = 1;
			result = 1;
		}
	}
	d2_DestroyForm(dlg);
	return result;
}
