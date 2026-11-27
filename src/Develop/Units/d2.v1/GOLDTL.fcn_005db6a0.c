


#include <string.h>

typedef struct
{
	int x0;
	int x4;
	__int64 mask;
	int x10;
	char pad14[0x3c];
} Query;
// SIZE 0x50

extern __int64 g_666018;
extern int g_14ac6a0;
extern int g_14acb94;
extern int g_100f1dc;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_dialog_state.h"

char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl amt_SendAction0x45(char*, char*, int);
void __cdecl fcn_00526120(int, int);
unsigned short* __cdecl fcn_005cadc0(int, Query*, int, char*, int);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl d2_CheckActionBlocker(char*, int);
int __cdecl cm_GetCommandStatus(int);
void __cdecl cm_StepCommandQueue(void);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);

int __cdecl gm_HandleVerhoerMode2(char* e, char* o)
{
	Query q;
	int cancel;
	char* p;
	unsigned short* g;
	int dlg;
	int id;
	int ok;
	int h;
	int r;

	if (e[2] != 6) {
		if (*(int*) (e + 0x1c8) & 0x100) {
			return 0x20;
		}
		if (*(int*) (e + 0x194) < 4) {
			return 0x20;
		}
		p = gm_LookupEntityRecordById(*(int*) (o + 0x214));
		if (p == 0) {
			return 0x60;
		}
		if (p[0x166] == 0) {
			return 0x60;
		}
		amt_SendAction0x45(e, p, 2);
		return 0x10;
	}
	r = 2;
	memset(&q, 0, sizeof(q));
	if (*(int*) (e + 0x1c8) & 0x100) {
		fcn_00526120(g_14ac6a0, 0);
		return 0x81;
	}
	q.x10 = 6;
	q.x4 = 0xc00;
	q.mask = g_666018;
	g = fcn_005cadc0(5, &q, g_14acb94, "", 0);
	if (g == 0) {
		return 2;
	}
	dlg = d2_LoadForm(0, 0, "privillegien\\verhoer");
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 1);
	id = io_AppendText(0x1e1e, *g, 4);
	ok = d2_GetWindowListItem(dlg, 1, id);
	cancel = d2_GetWindowListItem(dlg, 1, id + 1);
	g_100f1dc = -1;
	do {
		if (g_100f1dc != -1) {
			if (d2_CurrentElementId == ok && d2_CheckActionBlocker(e, 4) != 0) {
				h = amt_SendAction0x45(e, (char*) g, 2);
				while (h != -1 && cm_GetCommandStatus(h) == 0) {
					cm_StepCommandQueue();
				}
				g_774654 = 1;
				r = 0x91;
			} else if (d2_CurrentElementId == cancel) {
				g_774654 = 1;
			}
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
	} while (main_RunFrameLoop((void*) gm_HandleVerhoerMode2, 0x657c7) != 0);
	d2_DestroyForm(dlg);
	return r;
}
