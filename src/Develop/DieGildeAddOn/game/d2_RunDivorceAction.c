#include "Develop/DieGildeAddOn/game/spiel.h"

#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern unsigned char g_773d75;
extern double g_6660d8;
extern double g_664ee8;
extern double g_6629a0;

char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl cm_AppendCommandSyncField(unsigned char, unsigned char, short, void*);
void __cdecl cm_BeginPacketFieldDelta(char*, int);
void __cdecl cm_RequestModifyHealth(int, int);
void __cdecl cm_RequestChangeAttribute(void);
int __cdecl cm_SendSetAttribute(void);
int __cdecl cm_RequestMoveCredits(int, int, char, int);
int __cdecl cm_GetCommandStatus(int);
void __cdecl cm_StepCommandQueue(void);
void __cdecl d2_DestroyForm(int);
int __cdecl d2_CenterDialogWindows(int);
int __cdecl d2_SetForm(int, int);
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_CheckActionBlocker(void*, int);
int __cdecl gm_CheckEntityStock(void*, int, char);
int __cdecl gm_AccumulateTyped2(char*);

typedef struct {
	int sel;
	int mode;
	int n;
} DivorceDlgSel;

/* ADDRESS: GOLDTL 0x005d52d0 */
int __cdecl d2_RunDivorceAction(char* p)
{
	float w;
	DivorceDlgSel s;
	char* obj;
	int dlg;
	int m;
	int x;
	int base;

	s.sel = -1;
	s.mode = 0;
	if (*(unsigned char*) (p + 2) != 6 && *(unsigned char*) (p + 2) != 7) {
		if (*(int*) (p + 0x194) < 8) {
			return 0x22;
		}
		w = (float) gm_WalkEntityChain(*(unsigned short*) p);
		s.n = gm_AccumulateTyped2(p);
		if ((float) s.n / w < g_6660d8) {
			return 0x22;
		}
		obj = gm_LookupEntityRecordById(*(int*) (p + 0x5c));
		cm_RequestModifyHealth(*(int*) (p + 4), -8);
		cm_BeginPacketFieldDelta(p, *(int*) (p + 4));
		cm_AppendCommandSyncField(4, 1, 0x5c, &s.sel);
		cm_RequestChangeAttribute();
		cm_BeginPacketFieldDelta(obj, *(int*) (obj + 4));
		cm_AppendCommandSyncField(4, 1, 0x5c, &s.sel);
		cm_AppendCommandSyncField(2, 1, 0x50, &s.sel);
		cm_RequestChangeAttribute();
		m = (int) (w * g_664ee8);
		x = cm_RequestMoveCredits(*(int*) (obj + 4), *(int*) (p + 4), g_773d75, m);
		while (cm_GetCommandStatus(x) == 0) {
			cm_StepCommandQueue();
		}
		return 0x11;
	}
	w = (float) gm_WalkEntityChain(*(unsigned short*) p);
	s.n = (int) (w * g_664ee8);
	obj = gm_LookupEntityRecordById(*(int*) (p + 0x5c));
	dlg = d2_LoadForm(0, 0, "privillegien\\scheidung");
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 1);
	base = 0x114 + (*(unsigned char*) (p + 9) ? 0xa : 0);
	x = io_AppendText(0x1d8f, base + *(unsigned char*) (p + 0xd), 8, s.n - (int) (w * g_6629a0), *(unsigned short*) obj, *(unsigned short*) obj);
	d2_GetWindowListItem(dlg, 1, x);
	d2_GetWindowListItem(dlg, 1, x + 1);
	g_100f1dc = -1;
	for (;;) {
		if (g_100f1dc != -1) {
			if (g_100f1dc == 2) {
				if (d2_CheckActionBlocker(p, 8) == 0 || gm_CheckEntityStock(p, s.n, g_773d75) == 0) {
					goto tail;
				}
				cm_RequestModifyHealth(*(int*) (p + 4), -8);
				cm_BeginPacketFieldDelta(p, *(int*) (p + 4));
				cm_AppendCommandSyncField(4, 1, 0x5c, &s.sel);
				x = cm_SendSetAttribute();
				while (cm_GetCommandStatus(x) == 0) {
					cm_StepCommandQueue();
				}
				cm_BeginPacketFieldDelta(obj, *(int*) (obj + 4));
				cm_AppendCommandSyncField(4, 1, 0x5c, &s.sel);
				cm_AppendCommandSyncField(2, 1, 0x50, &s.sel);
				x = cm_SendSetAttribute();
				while (cm_GetCommandStatus(x) == 0) {
					cm_StepCommandQueue();
				}
				x = cm_RequestMoveCredits(*(int*) (obj + 4), *(int*) (p + 4), g_773d75, s.n);
				while (cm_GetCommandStatus(x) == 0) {
					cm_StepCommandQueue();
				}
				io_AppendText((int) g_6811b0);
				io_AppendText(0x1d90);
				g_774654 = 1;
				s.mode = 0x81;
			} else if (g_100f1dc == 1) {
				g_774654 = 1;
				s.mode = 2;
			}
		}
tail:
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
			s.mode = 2;
		}
		if (main_RunFrameLoop(d2_RunDivorceAction, 0x657c7) == 0) {
			break;
		}
	}
	d2_DestroyForm(dlg);
	return s.mode;
}
