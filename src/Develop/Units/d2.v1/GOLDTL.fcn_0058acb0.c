


// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"








#include "Develop/DieGildeAddOn/game/game_player.h"
extern int d2_CurrentWindowId;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int d2_CurrentElementId;
#include "client_dialog_state.h"

int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl io_AppendText();
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl d2_CheckActionBlocker(ENTITY_RECORD*, int);
void __cdecl fcn_005100f0(int, int);
#include "client_packet_builder.h"
void __cdecl cm_AppendPacketFieldDelta(int, int, int, int*);
int __cdecl cm_RequestChangeAttribute(void);
int __cdecl cm_GetCommandStatus(int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);
void __cdecl d3_EndCameraAndUiMode(void);

void __cdecl d2_RunDomizilKabinettDialog(int unused, char* p)
{
	int ok;
	int cancel;
	int b;
	int h;
	int s;
	int v;
	int id;

	b = *(int*) (p + 0x20);
	h = fcn_00470820(0, 0, "Locations\\Domizil\\kabinett");
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(h);
	d2_SetForm(h, 0);
	fcn_005340f0(d2_CurrentWindowId);
	d2_SetForm(h, 1);
	io_AppendText("$C");
	io_AppendText(0x407d, 0x4171, b);
	d2_SetForm(h, 2);
	s = io_AppendText(0x407e);
	ok = d2_GetWindowListItem(h, 2, s);
	cancel = d2_GetWindowListItem(h, 2, s + 1);
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		} else if (g_100f1dc != -1) {
			if (d2_CurrentElementId == ok) {
				if (d2_CheckActionBlocker(((ENTITY_RECORD*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[g_774970]), b) == 1) {
					v = 0;
					fcn_005100f0(((ENTITY_RECORD_VIEW*)g_7f4ca0)[g_774970].entity_id, -b);
					cm_BeginPacketFieldDelta(p, *(int*) (p + 2));
					cm_AppendPacketFieldDelta(4, 1, 0x1c, &v);
					cm_AppendPacketFieldDelta(4, 1, 0x20, &v);
					id = cm_RequestChangeAttribute();
					while (id != -1 && cm_GetCommandStatus(id) == 0) {
						main_RunFrameLoop(0, 0x20007);
					}
					g_774654 = 1;
				}
			} else if (d2_CurrentElementId == cancel) {
				g_774654 = 1;
			}
		}
	} while (main_RunFrameLoop(d2_RunDomizilKabinettDialog, 0x677c7) != 0);
	d2_DestroyForm(h);
	d3_EndCameraAndUiMode();
}
