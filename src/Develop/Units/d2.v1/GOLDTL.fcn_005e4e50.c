


#include "Develop/DieGildeAddOn/game/entity_record.h"









#include "Develop/DieGildeAddOn/game/game_player.h"
extern char s_6ad3c4[];
extern char s_681140[];
extern char s_6ad3bc[];
extern char s_6ad3a8[];
extern char* g_7746c4;
extern int g_14ce8e0;
extern int g_100f1dc;
extern int d2_CurrentElementId;
#include "client_dialog_state.h"

int __cdecl fcn_00470820(int, int, char*);
int __cdecl fcn_004f65a0(ENTITY_RECORD*, int, int*, int*);
int __cdecl gm_GetBuildingTechEffect(int, int, int);
int __cdecl fcn_00472830(int, int);
void __cdecl fcn_005340f0(int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl fcn_005338a0(void);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
void __cdecl fcn_00472640(int, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl cm_RequestLinkEvidence(int, int);
void __cdecl fcn_004c6ae0(int, int);
void __cdecl cm_RequestChangeBits(int, int, int, int, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, char*);
void __cdecl fcn_00471e30(int);

void __cdecl d2_ShowSchneidereiPlauschDialog(ENTITY_RECORD* other)
{
	int count;
	int yes;
	int found;
	int list[4];
	char text[0x400];
	ENTITY_RECORD* me;
	int dlg;
	int max;
	int i;

	me = &((ENTITY_RECORD*)g_7f4ca0)[g_774970];
	dlg = fcn_00470820(0, 0, s_6ad3c4);
	found = fcn_004f65a0(&((ENTITY_RECORD*)g_7f4ca0)[g_774970], 4, list, &count);
	if ((*(int*)&g_7746c4)) {
		max = gm_GetBuildingTechEffect((*(int*)&g_7746c4), 0x24, 1);
	} else {
		max = 1;
	}
	if (count >= max + 1) {
		count = max + 1;
	}
	fcn_005340f0(fcn_00472830(dlg, 0));
	d2_CenterDialogWindows(dlg);
	fcn_005338a0();
	d2_SetForm(dlg, 1);
	io_AppendText(0x4227);
	io_AppendText(0x422b, other->entity_index, count, 0x422c, other->entity_index, 1);
	d2_SetForm(dlg, 2);
	yes = d2_GetWindowListItem(dlg, 2, io_AppendText((int) s_681140, 0x422d));
	io_AppendText((int) s_6ad3bc, 0x422e);
	if (found == 0 || count == 0) {
		fcn_00472640(yes, 0);
	}
	while (main_RunFrameLoop(d2_ShowSchneidereiPlauschDialog, 0x67fff)) {
		if (g_14ce8e0 || g_100f1dc == 1) {
			g_774654 = 1;
		}
		if (g_100f1dc != -1 && d2_CurrentElementId == yes) {
			if (found) {
				for (i = 0; i < count; i++) {
					cm_RequestLinkEvidence(list[i], ((ENTITY_RECORD*)g_7f4ca0)[g_774970].entity_id);
				}
				fcn_004c6ae0(((ENTITY_RECORD*)g_7f4ca0)[g_774970].entity_id, -1);
				fcn_004c6ae0(other->entity_id, -1);
				cm_RequestChangeBits(me->entity_id, 0x1cc, 4, 0x20000, 0);
				io_FormatTextBuffer(text, 0x422f, other->entity_index);
				fcn_00545d40(((ENTITY_RECORD*)g_7f4ca0)[g_774970].entity_id, -1, text, 0, 0x5ec, 0);
				if (other->entity_state == 6 || other->entity_state == 7) {
					io_FormatTextBuffer(text, 0x4230, g_774970, 1);
					fcn_00545d40(other->entity_id, -1, text, 0, 0x5ec, s_6ad3a8);
				}
				g_774654 = 3;
			} else {
				fcn_004c6ae0(other->entity_id, -1);
				g_774654 = 3;
			}
		}
	}
	fcn_00471e30(dlg);
}
