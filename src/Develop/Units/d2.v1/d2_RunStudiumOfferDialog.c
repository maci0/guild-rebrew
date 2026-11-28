

typedef struct Player {
	char name[0x2f4];
} Player;
// SIZE 0x2f4

typedef struct Share {
	int amount;
	int kind;
	int goal;
} Share;

// SIZE 0x2f4
typedef struct {
	char pad0[0x5c];
	int shown;
	char pad60[0x1d0 - 0x60];
	int style;
	char pad1d4[0x2f4 - 0x1d4];
} Slot;

// SIZE 0xf8
struct msg {
	int f0;
	char b4;
	char pad5[3];
	int f8;
	int fc;
	char pad10[0x26];
	char b36;
	char pad37[0x21];
	int f58;
	char pad5c[4];
	int f60;
	char b64;
	char b65;
	char pad66[0x92];
};

// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"





extern char gm_TownTable[];

#include "Develop/DieGildeAddOn/game/game_player.h"
extern char* d2_Controls;
extern char s_6ace6c[];
extern char s_679060[];
extern char s_68be7c[];
extern int d2_CurrentWindowId;
extern int main_LoopFlags;
extern int d2_DialogButtonAction;
extern int io_RightButtonReleased;
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern int d2_CurrentElementId;

void __cdecl gm_CalcStudiumOffers(ENTITY_RECORD*, Share*);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_AddElementToWindow(int, int, int, int);
void __cdecl io_FormatTextBuffer(char*, char*, ...);
#include "Develop/Units/d2.v1/d2_gui.h"
int __cdecl d2_GetWindowListItem(int, int, int);
void __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl cm_SendCopyEntityData(struct msg*);
void __cdecl cm_RequestChangeBits(int, int, int, int, int);
void __cdecl d2_DestroyForm(int);

int __cdecl d2_RunStudiumOfferDialog(int unused, unsigned short* p)
{
	int dlg;
	int ids[4];
	Share shares[3];
	struct msg m;
	char text[0x100];
	int result;
	int i;

	gm_CalcStudiumOffers(&((ENTITY_RECORD*)gm_EntitySlotTable)[gm_LocalPlayerSlot], shares);
	dlg = d2_LoadForm(0, 0, s_6ace6c);
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 1);
	io_AppendText(0x1a9d, (((unsigned char*) p)[9] != 0) + 0x1aa0, *p, 5);
	d2_SetForm(dlg, 2);
	for (i = 0; i < 3; i++) {
		ids[i] = d2_AddElementToWindow(0x14, i * 0x5a + 10, 0x4c6, d2_CurrentWindowId);
		(*(int*)&((D2_CONTROL_TL*)d2_Controls)[ids[i]].value_05c) = 1;
		(*(int*)&((D2_CONTROL_TL*)d2_Controls)[ids[i]].flags_1d0) = 3;
		io_FormatTextBuffer(text, s_679060, ((Player*)gm_TownTable)[i + 1].name);
		d2_ShowTxt(0xbe, i * 0x5a + 10, text, d2_CurrentWindowId);
		io_FormatTextBuffer(text, s_679060, shares[i].kind + 0x16b7);
		d2_ShowTxt(0xbe, i * 0x5a + 10 + 0x14, text, d2_CurrentWindowId);
		io_FormatTextBuffer(text, s_679060, shares[i].goal + 0x16b7);
		d2_ShowTxt(0xbe, i * 0x5a + 10 + 0x28, text, d2_CurrentWindowId);
		io_FormatTextBuffer(text, s_68be7c, shares[i].amount);
		d2_ShowTxt(0xbe, i * 0x5a + 10 + 0x3c, text, d2_CurrentWindowId);
	}
	d2_SetForm(dlg, 3);
	ids[3] = d2_GetWindowListItem(dlg, 3, io_AppendText(0x1ba8));
	d2_SetOverlayAnimation(0, 0);
	d2_DialogButtonAction = -1;
	result = 0;
	while (main_RunFrameLoop((void*) d2_RunStudiumOfferDialog, main_LoopFlags) != 0) {
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		}
		if (d2_DialogButtonAction != -1) {
			if (d2_CurrentElementId == ids[3]) {
				d2_DialogCloseRequested = 1;
			} else {
				for (i = 0; i < 3; i++) {
					if (d2_CurrentElementId == ids[i]) {
						m.b36 = 0x12;
						m.b4 = 0x5f;
						m.f8 = *(int*) (p + 2);
						m.fc = -1;
						m.f58 = ((ENTITY_RECORD*)gm_EntitySlotTable)[gm_LocalPlayerSlot].entity_id;
						m.b64 = (char) shares[i].kind;
						m.b65 = (char) shares[i].goal;
						m.f60 = shares[i].amount;
						cm_SendCopyEntityData(&m);
						cm_RequestChangeBits(*(int*) (p + 2), 0x1c8, 4, 0x10000, 0);
						result = 1;
						d2_DialogCloseRequested = 1;
						break;
					}
				}
			}
		}
	}
	d2_DestroyForm(dlg);
	return result;
}
