#include <string.h>
/* SIZE 0x21c */
typedef struct {
	char f0[4];
	int f4;
	char pad[0x214];
} Slot5c06;

extern Slot5c06 g_7f4ca0[];
#include "Develop/DieGildeAddOn/game/game_player.h"
extern int g_100f1dc;
extern int g_14ce8e0;
#include "client_dialog_state.h"
extern int d2_CurrentElementId;
extern char g_6ac494[];

float __cdecl gm_RandomFloat01(void);
int __cdecl d2_CheckActionBlocker(void*, int);
int __cdecl he_HasNoActiveAction0x88(void*, void*);
int __cdecl CountMatchingStraftatEntries(int, unsigned short);
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl fcn_00526120(char*, int);
int __cdecl fcn_00470820(int, int, void*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl fcn_005c9220(int*);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl cm_SendCopyEntityData(char* msg);
void __cdecl cm_RequestModifyHealth(int id, int k);
float __cdecl gm_CalcSkillDuelScore(void*, unsigned short*, int);
void __cdecl d2_DestroyForm(int);

/* ADDRESS: GOLDTL 0x005c06e0 */
int __cdecl d2_RunStraftatAccuseDialog(unsigned short* entityRecord)
{
	int result;
	int h1;
	int h2;
	int dlg;
	int r;
	int t;
	int ids[6];
	char text[0x400];
	char ev[0xf8];
	float f;
	Slot5c06* me;

	result = 0;
	if (!entityRecord)
		goto none;
	if (*entityRecord == 0xffff)
		goto none;
	if (*entityRecord == g_774970)
		goto none;
	if (!d2_CheckActionBlocker(&g_7f4ca0[g_774970], 2))
		return 0;
	if (!he_HasNoActiveAction0x88(entityRecord, &g_7f4ca0[g_774970])) {
		io_FormatTextBuffer(text, 0x409f, *entityRecord);
		fcn_00526120(text, 0);
		return 0;
	}
	me = &g_7f4ca0[g_774970];
	r = CountMatchingStraftatEntries(*(int*) (entityRecord + 2), g_774970);
	if (r <= 0) {
		io_FormatTextBuffer(text, 0x1756, *entityRecord);
		fcn_00526120(text, 0);
		return 0;
	}
	if (!d2_CheckActionBlocker(&g_7f4ca0[g_774970], 2))
		return 0;
	dlg = fcn_00470820(0, 0, g_6ac494);
	d2_CenterDialogWindows(dlg);
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(dlg, 1);
	t = io_AppendText(0x1759, r, (r != 1) + 0x1752, *entityRecord, *entityRecord);
	h1 = d2_GetWindowListItem(dlg, 1, t);
	h2 = d2_GetWindowListItem(dlg, 1, t + 1);
	memset(ids, 0xff, sizeof(ids));
	ids[0] = dlg;
	ids[1] = 2;
	ids[2] = 3;
	ids[3] = 4;
	ids[4] = 4;
	ids[5] = 0x13;
	fcn_005c9220(ids);
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		} else if (g_100f1dc != -1) {
			if (d2_CurrentElementId == h1) {
				cm_RequestModifyHealth(me->f4, -2);
				f = gm_CalcSkillDuelScore(me, entityRecord, 4);
				if (gm_RandomFloat01() + f >= 1.0f) {
					ev[4] = 0x2e;
					*(int*) (ev + 8) = *(int*) (entityRecord + 2);
					*(int*) (ev + 0xc) = -1;
					ev[0x36] = 2;
					*(int*) (ev + 0x5c) = me->f4;
					*(int*) (ev + 0x58) = *(int*) (entityRecord + 2);
					cm_SendCopyEntityData(ev);
					io_FormatTextBuffer(text, 0x175b, *entityRecord);
				} else {
					io_FormatTextBuffer(text, 0x175c, *entityRecord, *entityRecord);
				}
				fcn_00526120(text, 0);
				g_774654 = 1;
				result = 1;
			} else if (d2_CurrentElementId == h2) {
				g_774654 = 1;
			}
		}
	} while (main_RunFrameLoop((void*) d2_RunStraftatAccuseDialog, 0x677c7) != 0);
	d2_DestroyForm(dlg);
	return result;
none:
	return 0;
}
