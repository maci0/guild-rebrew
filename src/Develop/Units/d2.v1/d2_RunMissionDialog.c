#include <string.h>

#include "Develop/DieGildeAddOn/game/entity_record.h"







typedef struct Job {
	int op;
	int id;
	char pad8[0x1c];
} Job;
// SIZE 0x24

typedef struct Spec {
	int op;
	int level;
} Spec;

typedef struct Req {
	int id;
	int x4;
	int x8;
	int xc;
	int x10;
	char pad14[0x68];
} Req;
// SIZE 0x7c


#include "Develop/DieGildeAddOn/game/game_player.h"
extern char g_10069a0[];
extern int d2_CurrentElementId;
extern int g_100f1dc;
#include "client_dialog_state.h"
extern signed char g_6a3440;

Spec* __cdecl gm_LookupMissionSpec(int op);
void __cdecl d2_RunMissionBriefingDialog(Spec* s, int flags);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
int __cdecl d2_SetForm(int k, int i);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl cm_RequestSysMessage(int, Req*);
int __cdecl cm_GetCommandStatus(int);
void __cdecl cm_StepCommandQueue(void);
void __cdecl d2_DestroyForm(int);
int* __cdecl gm_AllocRandomMissionJob(int a, int b, int c);
void __cdecl d2_ShowMissionSpecDialog(int a1, int flags);
void __cdecl main_ExitToGameLoop(int flags);

/* ADDRESS: GOLDTL 0x004b5df0 */
void __cdecl d2_RunMissionDialog(int flags)
{
	int level;
	int b_ok;
	int done;
	int cancel;
	int b_back;
	int mode;
	int b_quit;
	Req m2;
	Req m1;
	ENTITY_RECORD* ent;
	Spec* s;
	int dlg;
	int h;
	int* p;
	int i;

	b_ok = -1;
	level = -1;
	s = 0;
	done = 0;
	cancel = 0;
	ent = ((ENTITY_RECORD*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[g_774970]);
	for (i = 0; i < 128; i++) {
		if (((Job*)g_10069a0)[i].op != 0 && ((Job*)g_10069a0)[i].id == ent->entity_id) {
			s = gm_LookupMissionSpec(((Job*)g_10069a0)[i].op);
			level = s->level + 1;
			memset(&((Job*)g_10069a0)[i], 0, sizeof(Job));
			break;
		}
	}
	flags = (flags & ~9) | 0x100;
	d2_RunMissionBriefingDialog(s, flags);
	dlg = d2_LoadForm(0, 0, "special\\mission");
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 1);
	io_AppendText(0x1b94, ent->entity_index);
	if (level > -1 && level < 4) {
		b_ok = d2_GetWindowListItem(dlg, 1, io_AppendText(0x1b96, 0x1b98));
	}
	b_back = d2_GetWindowListItem(dlg, 1, io_AppendText(0x1b96, 0x1b99));
	b_quit = d2_GetWindowListItem(dlg, 1, io_AppendText(0x1b96, 0x1b9a));
	g_100f1dc = -1;
	mode = flags | 0x80;
	do {
		if (g_100f1dc != -1) {
			if (d2_CurrentElementId == b_ok) {
				done = 1;
				g_774654 = 1;
			} else if (d2_CurrentElementId == b_back) {
				g_6a3440 = -1;
				m1.id = ent->entity_id;
				m1.x10 = 0;
				h = cm_RequestSysMessage(10, &m1);
				while (cm_GetCommandStatus(h) == 0) {
					cm_StepCommandQueue();
				}
				g_774654 = 1;
			} else if (d2_CurrentElementId == b_quit) {
				g_6a3440 = -1;
				m2.id = ent->entity_id;
				cancel = 1;
				m2.x10 = 1;
				h = cm_RequestSysMessage(10, &m2);
				while (cm_GetCommandStatus(h) == 0) {
					cm_StepCommandQueue();
				}
				g_774654 = 1;
			}
		}
	} while (main_RunFrameLoop(d2_RunMissionDialog, mode) != 0);
	d2_DestroyForm(dlg);
	if (done) {
		p = gm_AllocRandomMissionJob(ent->entity_id, level, 1);
		m2.id = ent->entity_id;
		m2.x10 = 0;
		h = cm_RequestSysMessage(10, &m2);
		while (cm_GetCommandStatus(h) == 0) {
			cm_StepCommandQueue();
		}
		d2_ShowMissionSpecDialog(*p, flags);
		return;
	}
	if (cancel) {
		main_ExitToGameLoop(flags);
	}
}
