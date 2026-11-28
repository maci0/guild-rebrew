


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

extern __int64 gm_TargetPersonTypeMask;
extern int g_14ac6a0;
extern int g_14acb40;
extern int d2_DialogButtonAction;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d2.v1/client_dialog_state.h"

char* __cdecl gm_LookupEntityRecordById(int);
void __cdecl amt_ApplyOfficeSupportEffect(char*, char*);
void __cdecl d2_ShowModalMessageBox(int, int);
unsigned short* __cdecl d2_OpenTargetPicker(Query*, int, int, int);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);

/* ADDRESS: GOLDDE 0x005bc230 */
int __cdecl amt_HandleOfficeSupport(char* e, char* o)
{
	Query q;
	int cancel;
	char* p;
	unsigned short* h;
	int dlg;
	int id;
	int ok;
	int r;

	if (e[2] != 6) {
		if (*(int*) (e + 0x1cc) & 0x80000) {
			return 0x20;
		}
		p = gm_LookupEntityRecordById(*(int*) (o + 0x214));
		if (p == 0) {
			return 0x60;
		}
		if (p[0x166] == 0) {
			return 0x60;
		}
		amt_ApplyOfficeSupportEffect(e, p);
		return 0x10;
	}
	r = 2;
	memset(&q, 0, sizeof(q));
	if (*(int*) (e + 0x1cc) & 0x80000) {
		d2_ShowModalMessageBox(g_14ac6a0, 0);
		return 0x81;
	}
	q.x10 = 6;
	q.x4 = 0xc00;
	q.mask = gm_TargetPersonTypeMask;
	h = d2_OpenTargetPicker(&q, g_14acb40, 0, 0);
	if (h == 0) {
		return 2;
	}
	dlg = d2_LoadForm(0, 0, "privillegien\\verhoer");
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 1);
	id = io_AppendText(0x1e09, *h);
	ok = d2_GetWindowListItem(dlg, 1, id);
	cancel = d2_GetWindowListItem(dlg, 1, id + 1);
	d2_DialogButtonAction = -1;
	do {
		if (d2_DialogButtonAction != -1) {
			if (d2_CurrentElementId == ok) {
				amt_ApplyOfficeSupportEffect(e, (char*) h);
				r = 0x91;
				d2_DialogCloseRequested = 1;
			} else if (d2_CurrentElementId == cancel) {
				d2_DialogCloseRequested = 1;
			}
		}
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		}
	} while (main_RunFrameLoop((void*) amt_HandleOfficeSupport, 0x657c7) != 0);
	d2_DestroyForm(dlg);
	return r;
}
