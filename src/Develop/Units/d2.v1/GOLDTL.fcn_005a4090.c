

#include <string.h>
#pragma intrinsic(memset)

// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"







// SIZE 0xc
struct want {
	int n;
	int x;
	int y;
};

// SIZE 0x14
struct line {
	int n;
	int x;
	int y;
	int handle;
	int slot;
};


#include "Develop/DieGildeAddOn/game/game_player.h"
extern unsigned char g_773d75;
extern int g_100f1dc;
extern int g_14ce8e0;
#include "client_dialog_state.h"
extern int d2_CurrentElementId;
extern int g_14ab670;
#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern unsigned short g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern char g_6aaba0[];

void __cdecl gm_GenerateLoanOffers(char*, ENTITY_RECORD*, int, struct want*);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText();
int __cdecl d2_GetWindowListItem(int, int, int);
void __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl cm_RequestTransferCurrencyNoKill(int, int, char, int);
int __cdecl cm_SendCopyEntityData(char* msg);
int __cdecl cm_GetCommandStatus(int);
void __cdecl d2_SetGroupVisibility(int k, int flag);
void __cdecl fcn_00526120(int, int);
void __cdecl d2_DestroyForm(int);

void __cdecl d2_ChooseNewLoan(char* p)
{
	struct line list[3];
	char ev[0xf8];
	struct want src[3];
	int i;
	int h;
	int r;
	int j;

	memset(list, 0, sizeof(list));
	gm_GenerateLoanOffers(p, &((ENTITY_RECORD*)g_7f4ca0)[g_774970], 3, src);
	j = 0;
	for (i = 0; i < 3; i++) {
		if (src[i].n > 0) {
			list[j].n = src[i].n;
			list[j].x = src[i].x;
			list[j].y = src[i].y;
			list[j].slot = i;
			j++;
		}
	}
	h = fcn_00470820(0, 0, g_6aaba0);
	d2_CenterDialogWindows(h);
	d2_SetForm(h, 1);
	io_AppendText(0x18d0);
	d2_SetForm(h, 2);
	io_AppendText(0x18d1, *(unsigned short*) (p + 0x25), p);
	for (i = 0; i < 3; i++) {
		if (list[i].n > 0) {
			list[i].handle = d2_GetWindowListItem(h, 2, io_AppendText(0x18d2, list[i].n, list[i].y, list[i].x, 0x5d));
		}
	}
	io_AppendText(0x18d3);
	d2_SetOverlayAnimation(0, 0);
	while (main_RunFrameLoop(d2_ChooseNewLoan, 0x677c7) != 0) {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_100f1dc == 2) {
			for (i = 0; i < 3; i++) {
				if (list[i].n != 0 && d2_CurrentElementId == list[i].handle) {
					goto found;
				}
			}
			continue;
found:
			memset(ev, 0, sizeof(ev));
			ev[4] = 0x23;
			*(int*) (ev + 8) = ((ENTITY_RECORD*)g_7f4ca0)[*(unsigned short*) (p + 0x27)].entity_id;
			*(int*) (ev + 0xc) = *(int*) (p + 1);
			*(int*) (ev + 0x28) = (*(int*)&gm_GameTime);
			*(int*) (ev + 0x2c) = (*(int*)&g_7f4c04);
			*(int*) (ev + 0x30) = g_7f4c08;
			*(short*) (ev + 0x34) = g_7f4c0c;
			ev[0x36] = 0x12;
			*(int*) (ev + 0x58) = *(int*) (p + 1);
			*(int*) (ev + 0x5c) = ((ENTITY_RECORD*)g_7f4ca0)[g_774970].entity_id;
			*(int*) (ev + 0x60) = list[i].n;
			*(int*) (ev + 0x64) = list[i].x;
			*(int*) (ev + 0x6c) = list[i].y;
			cm_RequestTransferCurrencyNoKill(((ENTITY_RECORD*)g_7f4ca0)[g_774970].entity_id, *(int*) (p + 1), g_773d75, list[i].n);
			r = cm_SendCopyEntityData(ev);
			while (cm_GetCommandStatus(r) == 0) {
				main_RunFrameLoop(0, 0x677c7);
			}
			d2_SetGroupVisibility(h, 0);
			fcn_00526120(g_14ab670, 4);
			d2_SetGroupVisibility(h, 1);
			*(int*) (p + list[i].slot * 0xc + 0x71) = -1;
			g_774654 = 1;
		}
		else if (g_100f1dc == 1) {
			g_774654 = 1;
		}
	}
	d2_DestroyForm(h);
}
