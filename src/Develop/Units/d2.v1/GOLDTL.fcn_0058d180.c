


#include <string.h>

// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"









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
	char pad37;
	int field;
	char pad3c[0x20];
	int who;
	unsigned char slot;
	char pad61[0x97];
};

extern pos14_7f4c00 gm_GameTime;

extern int d2_CurrentWindowId;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int d2_CurrentElementId;
#include "client_dialog_state.h"
extern int g_14b5798;
extern int g_14b579c;
extern int g_14b556c;

int __cdecl he_HasActiveGrabpflege(char*, int, int);
void __cdecl d2_ShowGreenMessageBox(int, int, int);
void __cdecl d2_InitPlayerBar(char*, int);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_InitWindowBounds(int);
int __cdecl io_AppendText();
int __cdecl d2_GetWindowListItem(int, int, int);
void __cdecl d2_ShowModalMessageBox(int, int);
int __cdecl cm_SendCopyEntityData(struct msg*);
int __cdecl cm_GetCommandStatus(int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);
void __cdecl d2_RestoreHudAfterDialog(void);
void __cdecl sv_ClearObjectSelection(void);

int __cdecl d2_ConfirmGrabpflege(char* who, char* request)
{
	int r;
	int ok;
	int cancel;
	struct msg m;
	int h;
	int s;
	int i;
	int id;
	ENTITY_RECORD* hh;

	r = 0;
	if (he_HasActiveGrabpflege(who, *(int*) (request + 4), *(unsigned char*) (request + 8)) != 0) {
		d2_ShowGreenMessageBox(g_14b5798, g_14b579c, 0);
		return 0;
	}
	d2_InitPlayerBar(who, 0);
	h = d2_LoadForm(0, 0, "Locations\\Friedhof\\Friedhof");
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(h);
	d2_SetForm(h, 0);
	d2_InitWindowBounds(d2_CurrentWindowId);
	d2_SetForm(h, 1);
	io_AppendText(0x4120, 0x411e, 0x228);
	d2_SetForm(h, 2);
	s = io_AppendText(0x4121);
	ok = d2_GetWindowListItem(h, 2, s);
	cancel = d2_GetWindowListItem(h, 2, s + 1);
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		} else if (g_100f1dc != -1) {
			if (d2_CurrentElementId == ok) {
				hh = 0;
				for (i = 0; i < 768; i++) {
					if (((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].selected != 0) {
						hh = ((ENTITY_RECORD*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[i]);
						break;
					}
				}
				if (hh == 0) {
					d2_ShowModalMessageBox(g_14b556c, 0);
				} else {
					memset(&m, 0, sizeof(m));
					m.kind = 0x8d;
					m.code = 1;
					m.owner = ((ENTITY_RECORD_VIEW*)g_7f4ca0)[*(unsigned short*) (who + 0x27)].entity_id;
					m.target = *(int*) (who + 1);
					m.when = gm_GameTime;
					m.who = *(int*) (request + 4);
					m.slot = request[8];
					m.field = hh->entity_id;
					id = cm_SendCopyEntityData(&m);
					while (id != -1 && cm_GetCommandStatus(id) == 0) {
						main_RunFrameLoop(0, 0x20007);
					}
					r = 1;
					g_774654 = 1;
				}
			} else if (d2_CurrentElementId == cancel) {
				g_774654 = 1;
			}
		}
	} while (main_RunFrameLoop(d2_ConfirmGrabpflege, 0x677c7) != 0);
	d2_DestroyForm(h);
	d2_RestoreHudAfterDialog();
	sv_ClearObjectSelection();
	return r;
}
