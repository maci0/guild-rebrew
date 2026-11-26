


#include <string.h>

// SIZE 0xf8
#include "client_types.h"
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
extern int g_100f1dc;
extern int g_14ce8e0;
extern int d2_CurrentElementId;
#include "client_dialog_state.h"

int __cdecl he_GetActionProgress(char*, int*, int*, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
void __cdecl fcn_00472640(int, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl fcn_00471e30(int);
unsigned short __cdecl gm_RandomMod(int);
void __cdecl cm_SendCopyEntityData(struct msg*);

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
	dlg = fcn_00470820(0, 0, "Locations\\Domizil\\skill");
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 0);
	fcn_005340f0(d2_CurrentWindowId);
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
	fcn_00472640(yes, ok);
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		} else if (g_100f1dc != -1) {
			if (d2_CurrentElementId == yes) {
				memset(&msg, 0, sizeof(msg));
				msg.kind = 0x97;
				msg.code = 1;
				msg.owner = ((ENTITY_RECORD_VIEW*)g_7f4ca0)[*(unsigned short*) (entity + 0x27)].entity_id;
				msg.target = *(int*) (entity + 1);
				msg.when = gm_GameTime;
				msg.who = *who;
				msg.delay = gm_RandomMod(0x5a0) + 1000;
				msg.other = kind;
				cm_SendCopyEntityData(&msg);
				g_774654 = 1;
			} else if (d2_CurrentElementId == no) {
				g_774654 = 1;
			}
		}
	} while (main_RunFrameLoop(d2_RunDomizilSkillConfirmDialog, 0x677c7) != 0);
	fcn_00471e30(dlg);
	return 1;
}
