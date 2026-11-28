

#include <stdio.h>
#include <string.h>

// SIZE 0x21c
typedef struct House {
	char pad0[2];
	char kind;
	char pad3;
	int f4;
	char pad8[0x4c];
	int f54;
	char pad58[0x1c4];
} House;

// SIZE 0x2f4
typedef struct Ctl {
	char pad0[0x58];
	int f58;
	char pad5c[0x294];
	House* house;
} Ctl;

// SIZE 0x80
typedef struct Chat {
	int names[8];
	char text[0x60];
} Chat;

extern char gm_EntitySlotTable[];
extern char* d2_Controls;
extern unsigned char g_6a2c14[8];
extern int d2_QuickChatLastTick;
extern int d2_CurrentWindowId;
extern int g_14ac628;
extern int io_RightButtonReleased;
extern char io_LastKeyScancode;
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern int d2_DialogButtonAction;
extern int d2_CurrentElementId;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern char str_empty[];
extern char g_7e3a60[];

int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterForm(int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl d2_AddElementToWindow(int, int, int, int);
#include "Develop/Units/d2.v1/d2_gui.h"
int __cdecl d2_AddWindowTextButton(int, int, int, int, int);
void __cdecl d2_SetElementFont(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
void __cdecl d2_SetBildArgument(int, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_SelectControl(int);
char* __cdecl d2_GetControlValue(int);
void __cdecl cm_RequestSendChat(Chat*);
void __cdecl d2_DestroyForm(int);

void __cdecl d2_RunChatConsole(void)
{
	int ids[8];
	Chat chat;
	int dlg;
	int win;
	int edit;
	int n;
	int i;

	ids[0] = -1;
	ids[1] = -1;
	ids[2] = -1;
	ids[3] = -1;
	ids[4] = -1;
	ids[5] = -1;
	ids[6] = -1;
	ids[7] = -1;
	d2_QuickChatLastTick = 0;
	dlg = d2_LoadForm(0, 0, "misc\\chatconsole");
	d2_CenterForm(dlg, 3);
	d2_SetForm(dlg, 3);
	n = 0;
	for (i = 0; i < 768; i++) {
		if (((House*) gm_EntitySlotTable)[i].kind == 7) {
			ids[n] = d2_AddElementToWindow(n * 0x30 + 0x64, 4, ((House*) gm_EntitySlotTable)[i].f54, d2_CurrentWindowId);
			((Ctl*) d2_Controls)[ids[n]].f58 = 1;
			((Ctl*) d2_Controls)[ids[n]].house = &((House*) gm_EntitySlotTable)[i];
			d2_SetElementValue(ids[n], g_6a2c14[n]);
			n++;
		}
	}
	win = d2_AddWindowTextButton(0, 0, 0xc5, g_14ac628, d2_CurrentWindowId);
	d2_SetElementFont(win, 0x54);
	d2_SetForm(dlg, 2);
	edit = d2_GetWindowListItem(dlg, 2, io_AppendText(0x1cc3, str_empty));
	d2_SetBildArgument(edit, 0x60);
	while (main_RunFrameLoop(d2_RunChatConsole, 0x657c7)) {
		d2_SetForm(dlg, 1);
		io_AppendText((int) "$C");
		io_AppendText((int) g_7e3a60);
		if (io_RightButtonReleased != 0 || io_LastKeyScancode == 1) {
			d2_DialogCloseRequested = 1;
		}
		d2_SelectControl(edit);
		if ((d2_DialogButtonAction != -1 || io_LastKeyScancode == 0x1c) && (d2_CurrentElementId == win || io_LastKeyScancode == 0x1c)) {
			for (i = 0; i < 8; i++) {
				if (ids[i] != -1 && d2_GetControlValue(ids[i]) != 0) {
					chat.names[i] = ((Ctl*) d2_Controls)[ids[i]].house->f4;
				}
			}
			sprintf(chat.text, "$%iFF ", ((House*) gm_EntitySlotTable)[gm_LocalPlayerSlot].f54 - 0x59a);
			strcat(chat.text, d2_GetControlValue(edit));
			strcat(chat.text, "$A");
			d2_SetElementValue(edit, str_empty);
			cm_RequestSendChat(&chat);
			d2_DialogCloseRequested = 1;
		}
	}
	for (i = 0; i < 8; i++) {
		if (ids[i] != -1) {
			g_6a2c14[i] = (unsigned char) d2_GetControlValue(ids[i]);
		}
	}
	d2_DestroyForm(dlg);
	io_LastKeyScancode = 0;
}
