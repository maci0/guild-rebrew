


#include <string.h>

// SIZE 0xf8
#include "Develop/client_types.h"
struct msg {
	char pad0[4];
	unsigned char kind;
	char pad5[3];
	int owner;
	int target;
	char pad10[0x18];
	pos14_7f4c00 when;
	unsigned char code;
	char pad37[0x21];
	int who;
	int other;
	char pad60[8];
	int delay;
	char pad6c[0x8c];
};

// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"








extern pos14_7f4c00 gm_GameTime;
extern int d2_CurrentWindowId;
extern int d2_DialogButtonAction;
extern int io_RightButtonReleased;
extern int d2_CurrentElementId;
#include "Develop/Units/d2.v1/client_dialog_state.h"

int __cdecl he_GetActionProgress(char*, int*, int*, int);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_InitWindowBounds(int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
void __cdecl d2_SetElementEnabled(int, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);
unsigned short __cdecl gm_RandomMod(int);
void __cdecl cm_SendCopyEntityData(struct msg*);

/* ADDRESS: GOLDDE 0x0056c2b0 */
int __cdecl d2_RunDomizilSkillConfirmDialog(char* entity, int* who, int kind)
{
	int item_idx;
	int yes;
	int no;
	int unused_b;
	struct msg msg;
	int dlg;
	int ok;

	ok = 1;
	if (he_GetActionProgress(entity, &item_idx, &unused_b, 0) != 0) {
		ok = 0;
	}
	if (kind == 3) {
		ok = 0;
	}
	dlg = d2_LoadForm(0, 0, "Locations\\Domizil\\skill");
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 0);
	d2_InitWindowBounds(d2_CurrentWindowId);
	d2_SetForm(dlg, 1);
	io_AppendText(0x4045, kind + 0x4172);
	io_AppendText(kind + 0x4176);
	if (ok) {
		io_AppendText(0x4046, 0x182);
	}
	d2_SetForm(dlg, 2);
	item_idx = io_AppendText(0x4047);
	yes = d2_GetWindowListItem(dlg, 2, item_idx);
	no = d2_GetWindowListItem(dlg, 2, item_idx + 1);
	d2_SetElementEnabled(yes, ok);
	d2_DialogButtonAction = -1;
	do {
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		} else if (d2_DialogButtonAction != -1) {
			if (d2_CurrentElementId == yes) {
				memset(&msg, 0, sizeof(msg));
				msg.kind = 0x97;
				msg.code = 1;
				msg.owner = ((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[*(unsigned short*) (entity + 0x27)].entity_id;
				msg.target = *(int*) (entity + 1);
				msg.when = gm_GameTime;
				msg.who = *who;
				msg.delay = gm_RandomMod(0x5a0) + 1000;
				msg.other = kind;
				cm_SendCopyEntityData(&msg);
				d2_DialogCloseRequested = 1;
			} else if (d2_CurrentElementId == no) {
				d2_DialogCloseRequested = 1;
			}
		}
	} while (main_RunFrameLoop(d2_RunDomizilSkillConfirmDialog, 0x677c7) != 0);
	d2_DestroyForm(dlg);
	return 1;
}
