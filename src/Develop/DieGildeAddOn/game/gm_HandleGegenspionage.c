


#include <stdio.h>
#include <string.h>

// SIZE 0xf8
#include "Develop/client_types.h"
struct msg {
	int f0;
	char b4;
	char pad5[3];
	int f8;
	int fc;
	char pad10[0x18];
	pos14_7f4c00 pos;
	char b36;
	char pad37[0x39];
	int f70;
	char pad74[0x84];
};

#pragma pack(2)
// SIZE 0xd6
typedef struct {
	char pad0[8];
	unsigned short w8;
	char pada[0x48];
	pos14_7f4c00 pos52;
	char pad60[0x10];
	int f70;
	char pad74[0x50];
	int fc4;
	pos14_7f4c00 posc8;
} Obj;
#pragma pack()

// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"





extern pos14_7f4c00 gm_GameTime;

extern char s_6acd1c[];
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d2.v1/client_dialog_state.h"

void __cdecl cm_RequestModifyHealth(int, int);
Obj* __cdecl he_StartHandlungSearch(int, int, int);
Obj* __cdecl he_fn_Handlung(void);
void __cdecl cm_SendSetHE(int, Obj*);
void __cdecl cm_SendCopyEntityData(struct msg*);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl d2_CheckActionBlocker(unsigned char*, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl d2_ShowModalMessageBox(char*, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);

int __cdecl gm_HandleGegenspionage(unsigned char* e)
{
	int cancel;
	int ok;
	int dlg;
	struct msg m;
	char text[0x200];
	int result;
	int found;
	int id;
	Obj* p;
	char* t;

	result = 2;
	if (e[2] != 6 && e[2] != 7) {
		if (*(int*) (e + 0x194) < 4) {
			return 0x20;
		}
		memset(&m, 0, sizeof(m));
		m.b4 = 0x18;
		m.f8 = *(int*) (e + 4);
		m.fc = *(int*) (e + 4);
		m.b36 = 2;
		m.pos = gm_GameTime;
		cm_RequestModifyHealth(*(int*) (e + 4), -4);
		for (p = he_StartHandlungSearch(1, 0, 0x18); p != 0; p = he_fn_Handlung()) {
			if (p->fc4 == *(int*) (e + 4)) {
				result |= 0x10;
				p->pos52 = gm_GameTime;
				p->posc8 = gm_GameTime;
				cm_SendSetHE(p->f70, p);
				m.f70 = ((ENTITY_RECORD*)gm_EntitySlotTable)[p->w8].entity_id;
				cm_SendCopyEntityData(&m);
			}
		}
		return result;
	}
	dlg = d2_LoadForm(0, 0, s_6acd1c);
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 1);
	id = io_AppendText(0x1db7, 4);
	ok = d2_GetWindowListItem(dlg, 1, id);
	cancel = d2_GetWindowListItem(dlg, 1, id + 1);
	d2_DialogButtonAction = -1;
	do {
		if (d2_DialogButtonAction != -1) {
			if (d2_CurrentElementId == ok) {
				if (d2_CheckActionBlocker(e, 4)) {
					found = 0;
					io_FormatTextBuffer(text, 0x1db8);
					t = text + strlen(text);
					memset(&m, 0, sizeof(m));
					m.b4 = 0x18;
					m.f8 = *(int*) (e + 4);
					m.fc = *(int*) (e + 4);
					m.b36 = 2;
					m.pos = gm_GameTime;
					cm_RequestModifyHealth(*(int*) (e + 4), -4);
					for (p = he_StartHandlungSearch(1, 0, 0x18); p != 0; p = he_fn_Handlung()) {
						if (p->fc4 == *(int*) (e + 4)) {
							p->pos52 = gm_GameTime;
							found |= 1;
							cm_SendSetHE(0, p);
							m.f70 = ((ENTITY_RECORD*)gm_EntitySlotTable)[p->w8].entity_id;
							cm_SendCopyEntityData(&m);
							io_FormatTextBuffer(t, 0x1db9, p->w8);
							t = text + strlen(text);
						}
					}
					if (!found) {
						io_FormatTextBuffer(text, 0x1dba);
					}
					d2_ShowModalMessageBox(text, 0);
					d2_DialogCloseRequested = 1;
				}
			} else if (d2_CurrentElementId == cancel) {
				d2_DialogCloseRequested = 1;
			}
		}
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		}
	} while (main_RunFrameLoop((void*) gm_HandleGegenspionage, 0x657c7) != 0);
	d2_DestroyForm(dlg);
	return 2;
}
