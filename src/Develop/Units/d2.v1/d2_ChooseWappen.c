

#include <string.h>
#pragma intrinsic(memset)

#include "Develop/client_types.h"
typedef D2_RADIO_GROUP Group;
// SIZE 0x8c

// SIZE 0x21c
typedef struct {
	unsigned short id;
	unsigned char type;
	char pad3;
	int handle;
	char pad8[0x4c];
	int district;
	char pad58[0x1c4];
} House5c80;

#define HOUSES 768
#define DISTRICT0 0x59a

extern D2_RADIO_GROUP g_102cbc4[8];
extern char g_7f4ca0[];
#include "Develop/DieGildeAddOn/game/game_player.h"
extern int d2_CurrentWindowId;
extern int g_100f1dc;
#include "Develop/Units/d2.v1/client_dialog_state.h"
#include "Develop/DieGildeAddOn/command/client_packet_builder.h"
extern char g_6ac80c[];

int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_InitWindowBounds(int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_CreateRadioGroup(int n, ...);
int __cdecl d2_AddElementToWindow(int x, int y, int a3, int win);
void __cdecl d2_AddToRadioGroup(int g, int id);
void __cdecl d2_SetElementEnabled(int i, int flag);
int __cdecl d2_GetWindowListItem(int, int, int);
void __cdecl d2_ResetUiInputAndBounds(void);

int __cdecl cm_AppendCommandSyncField(int type, int count, int off, char* data);
int __cdecl cm_SendSetAttribute(void);
int __cdecl cm_GetCommandStatus(int);
void __cdecl cm_StepCommandQueue(void);
int __cdecl cm_RequestSysMessage(int, void*);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_ClearRadioGroup(int i);
void __cdecl d2_DestroyForm(int);

void __cdecl d2_ChooseWappen(void)
{
	int back;
	int grp;
	int district;
	int d;
	int btn[8];
	int ev[0x1f];
	int j;
	House5c80* me_h;
	int i;
	int b;
	int found;
	int r;

	d = d2_LoadForm(0, 0, g_6ac80c);
	d2_CenterDialogWindows(d);
	d2_SetForm(d, 0);
	d2_InitWindowBounds(d2_CurrentWindowId);
	d2_SetForm(d, 1);
	io_AppendText(0x85);
	d2_SetForm(d, 2);
	grp = d2_CreateRadioGroup(0);
	for (i = 0; i < 8; i++) {
		btn[i] = d2_AddElementToWindow(i * 0x30 + 10, 0x78, i + DISTRICT0, d2_CurrentWindowId);
		d2_AddToRadioGroup(grp, btn[i]);
	}
	for (i = 0; i < 8; i++) {
		for (j = 0; j < HOUSES; j++) {
			if (((House5c80*)g_7f4ca0)[j].id != 0xffff && ((House5c80*)g_7f4ca0)[j].district == DISTRICT0 - i && ((House5c80*)g_7f4ca0)[j].id != g_774970
				&& (((House5c80*)g_7f4ca0)[j].type == 6 || ((House5c80*)g_7f4ca0)[j].type == 7 || ((House5c80*)g_7f4ca0)[j].type == 5)) {
				d2_SetElementEnabled(btn[i], 0);
			}
		}
	}
	d2_SetForm(d, 3);
	back = d2_GetWindowListItem(d, 3, io_AppendText(0x7f));
	g_102cbc4[grp].sel = -1;
	d2_ResetUiInputAndBounds();
	do {
		for (i = 0; i < 8; i++) {
			b = btn[i];
			d2_SetElementEnabled(b, 1);
			for (j = 0; j < HOUSES; j++) {
				if (((House5c80*)g_7f4ca0)[j].id != 0xffff && ((House5c80*)g_7f4ca0)[j].district == i + DISTRICT0 && ((House5c80*)g_7f4ca0)[j].id != g_774970
					&& (((House5c80*)g_7f4ca0)[j].type == 6 || ((House5c80*)g_7f4ca0)[j].type == 7 || ((House5c80*)g_7f4ca0)[j].type == 5)) {
					d2_SetElementEnabled(b, 0);
				}
			}
		}
		if (g_102cbc4[grp].sel != -1) {
			d2_SetElementEnabled(back, 1);
		}
		else {
			d2_SetElementEnabled(back, 0);
		}
		if (g_100f1dc == 2 && g_102cbc4[grp].sel != -1) {
			me_h = &((House5c80*)g_7f4ca0)[g_774970];
			district = g_102cbc4[grp].sel + DISTRICT0;
			found = 0;
			cm_BeginPacketFieldDelta((char*) me_h, me_h->handle);
			cm_AppendCommandSyncField(4, 1, (char*) me_h - g_aed32c + 0x54, (char*) &district);
			r = cm_SendSetAttribute();
			while (cm_GetCommandStatus(r) == 0) {
				cm_StepCommandQueue();
			}
			for (i = 8; i != 0; i--) {
				for (j = 0; j < HOUSES; j++) {
					if (((House5c80*)g_7f4ca0)[j].id != 0xffff && ((House5c80*)g_7f4ca0)[j].district == g_102cbc4[grp].sel + DISTRICT0 && ((House5c80*)g_7f4ca0)[j].id != g_774970
						&& (((House5c80*)g_7f4ca0)[j].type == 6 || ((House5c80*)g_7f4ca0)[j].type == 7 || ((House5c80*)g_7f4ca0)[j].type == 5)) {
						found = 1;
					}
				}
			}
			if (found == 0) {
				g_774654 = 1;
				memset(ev, 0, sizeof(ev));
				ev[0] = g_774970;
				cm_RequestSysMessage(0xd, ev);
			}
		}
	} while (main_RunFrameLoop(d2_ChooseWappen, 0x677c7) != 0);
	d2_ClearRadioGroup(grp);
	d2_DestroyForm(d);
}
