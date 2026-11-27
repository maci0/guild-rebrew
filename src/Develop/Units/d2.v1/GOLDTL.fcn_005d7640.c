


#include "Develop/DieGildeAddOn/game/entity_record.h"










typedef struct Cmd {
	int type;
	char pad4[0x21c - 4];
	ENTITY_RECORD* target;
} Cmd;


extern char s_6a2f5c[];
extern char s_6acd38[];
extern int g_100f1dc;
extern int d2_CurrentElementId;
#include "client_dialog_state.h"
extern int g_14ce8e0;

int __cdecl amt_SendAndWaitOfficeCommand(ENTITY_RECORD*, ENTITY_RECORD*, ENTITY_RECORD*);
void __cdecl io_FormatTextBuffer(char*, ...);
int __cdecl fcn_00526120(char*, int);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl d2_CheckActionBlocker(ENTITY_RECORD*, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);
int __cdecl gm_HandleGegenspionage();

int __cdecl d2_RunGegenspionageDialog(ENTITY_RECORD* ent, Cmd* cmd)
{
	ENTITY_RECORD* pa;
	char text[0x200];
	ENTITY_RECORD* pb;
	int i;
	int left;
	int rank;
	int want_a;
	int want_b;
	int h;
	int s;
	int yes;
	int no;

	pb = 0;
	left = 2;
	pa = 0;
	if (cmd->type == 3) {
		rank = ent->unk_165[1];
	} else if (cmd->type == 4 && cmd->target != 0) {
		rank = cmd->target->unk_165[1];
	} else {
		return 0x60;
	}
	if (rank == 15) {
		want_b = 14;
		want_a = 13;
	} else if (rank == 21) {
		want_b = 20;
		want_a = 19;
	} else if (rank == 27) {
		want_b = 26;
		want_a = 25;
	} else {
		return 0x20;
	}
	for (i = 0; i < 768; i++) {
		if (left == 0) {
			break;
		}
		if (((ENTITY_RECORD*)g_7f4ca0)[i].unk_165[1] == want_a) {
			pa = &((ENTITY_RECORD*)g_7f4ca0)[i];
			left--;
		} else if (((ENTITY_RECORD*)g_7f4ca0)[i].unk_165[1] == want_b) {
			pb = &((ENTITY_RECORD*)g_7f4ca0)[i];
			left--;
		}
	}
	if (ent->entity_state != 6 && ent->entity_state != 7) {
		if (ent->unk_194 < 6 || left > 0) {
			return 0x20;
		}
		return amt_SendAndWaitOfficeCommand(ent, pb, pa) ? 0x10 : 0x20;
	}
	if (left > 0) {
		io_FormatTextBuffer(text, s_6a2f5c, 0x1dcb);
		fcn_00526120(text, 0);
		return 0;
	}
	h = d2_LoadForm(0, 0, s_6acd38);
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(h);
	d2_SetForm(h, 1);
	s = io_AppendText(0x1dc9, 6, pb->entity_index, pa->entity_index);
	yes = d2_GetWindowListItem(h, 1, s);
	no = d2_GetWindowListItem(h, 1, s + 1);
	g_100f1dc = -1;
	do {
		if (g_100f1dc != -1) {
			if (d2_CurrentElementId == yes) {
				if (d2_CheckActionBlocker(ent, 6)) {
					if (amt_SendAndWaitOfficeCommand(ent, pb, pa)) {
						io_FormatTextBuffer(text, 0x1dca);
					} else {
						io_FormatTextBuffer(text, s_6a2f5c, 0x1dcb);
					}
					fcn_00526120(text, 0);
					g_774654 = 1;
				}
			} else if (d2_CurrentElementId == no) {
				g_774654 = 1;
			}
		}
		if (g_14ce8e0) {
			g_774654 = 1;
		}
	} while (main_RunFrameLoop(gm_HandleGegenspionage, 0x657c7));
	d2_DestroyForm(h);
	return 1;
}
