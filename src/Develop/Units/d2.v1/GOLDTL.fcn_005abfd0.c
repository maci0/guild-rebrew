


#include "Develop/DieGildeAddOn/game/entity_record.h"








#include "Develop/DieGildeAddOn/game/game_player.h"
extern int d2_CurrentWindowId;
extern int g_14ab930;
extern int g_100f1dc;
extern int d2_CurrentElementId;
extern int g_14ce8e0;
#include "client_dialog_state.h"
extern char s_6ab060[];

int __cdecl fcn_004f39b0(int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
void __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
#include "Develop/Units/d2.v1/d2_gui.h"
int __cdecl d2_GetControlValue(int);
int __cdecl d2_CheckActionBlocker(ENTITY_RECORD*, int);
void __cdecl fcn_005100f0(int, int);
void __cdecl he_NotifyConfession(ENTITY_RECORD*, ENTITY_RECORD*, unsigned char*);
void __cdecl fcn_004f5e20(int, int);
int __cdecl fcn_00526120(int, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl fcn_00532ef0(void);
void __cdecl fcn_00471e30(int);

void __cdecl d2_OpenBeichteDialog(unsigned char* e)
{
	int flag;
	int btnA;
	int btnB;
	int btnC;
	int dlg;
	int amt;
	int v;
	ENTITY_RECORD* me;

	flag = 0;
	btnA = -1;
	btnC = -1;
	btnB = -1;
	if (*(unsigned short*) (e + 0x27) == 0xffff) {
		return;
	}
	amt = fcn_004f39b0(((ENTITY_RECORD_VIEW*)g_7f4ca0)[g_774970].entity_id);
	dlg = fcn_00470820(0, 0, s_6ab060);
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 0);
	fcn_005340f0(d2_CurrentWindowId);
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(dlg, 1);
	io_AppendText(0x197f);
	if (amt != 0) {
		btnB = d2_GetWindowListItem(dlg, 1, io_AppendText(0x1981, amt));
		d2_SetElementValue(btnB, 2, 6, 2);
		btnA = d2_GetWindowListItem(dlg, 1, io_AppendText(0x1982));
		btnC = d2_GetWindowListItem(dlg, 1, io_AppendText(0x1983));
		flag = 1;
	}
	else {
		io_AppendText(0x1980);
	}
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_100f1dc != -1 && flag != 0) {
			if (d2_CurrentElementId == btnA) {
				me = ((ENTITY_RECORD*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[g_774970]);
				v = d2_GetControlValue(btnB);
				if (d2_CheckActionBlocker(me, v) != 0) {
					fcn_005100f0(me->entity_id, -v);
					if (*(unsigned short*) (e + 0x27) != 0xffff && *(unsigned short*) (e + 0x27) != g_774970) {
						fcn_005100f0(((ENTITY_RECORD_VIEW*)g_7f4ca0)[*(unsigned short*) (e + 0x27)].entity_id, 1);
						he_NotifyConfession(((ENTITY_RECORD*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[g_774970]), ((ENTITY_RECORD*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[*(unsigned short*) (e + 0x27)]), e);
					}
					fcn_004f5e20(me->entity_id, v / 2);
					fcn_00526120(g_14ab930, 0);
					g_774654 = 1;
				}
			}
			else if (d2_CurrentElementId == btnC) {
				g_774654 = 1;
			}
		}
	} while (main_RunFrameLoop((void*) d2_OpenBeichteDialog, 0x677c7) != 0);
	fcn_00532ef0();
	fcn_00471e30(dlg);
}
