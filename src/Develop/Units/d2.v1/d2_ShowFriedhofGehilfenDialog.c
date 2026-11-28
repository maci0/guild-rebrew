


typedef struct
{
	int* x0;
	int x4;
	unsigned char x8;
	int* xc;
	int x10;
} Req;
// SIZE 0x14

extern int d2_CurrentWindowId;
extern int d2_DialogButtonAction;
extern int io_RightButtonReleased;
extern int d2_CurrentElementId;
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern char s_6a9748[];
extern char s_6a9714[];
extern char s_6a96d8[];

int __cdecl gv_CanHireGraveyardWorker(int, int*);
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl d2_ShowModalMessageBox(char*, int);
int __cdecl d2_LoadForm(int, int, int);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_InitWindowBounds(int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl gv_SendAllocGraveyardWorker(int, int, int, int, int);
int __cdecl cm_GetCommandStatus(int);
char* __cdecl cm_GetCommandResult(int);
int __cdecl sprintf(char*, const char*, ...);
int __cdecl evt_LoadGfxScript(char*);
void __cdecl evt_CallScriptFunction(int, int, char*);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);

/* ADDRESS: GOLDDE 0x005730b0 */
int __cdecl d2_ShowFriedhofGehilfenDialog(int a1, Req* request)
{
	int cancel;
	int info;
	int ok;
	char line[0x40];
	char buf[0x200];
	int result;
	int status;
	int dlg;
	int id;
	int h;
	char* p;

	result = 0;
	status = gv_CanHireGraveyardWorker(a1, &info);
	if (status != 1) {
		if (status == 0) {
			io_FormatTextBuffer(buf, 0x4135, info, 0x229, a1);
			d2_ShowModalMessageBox(buf, 0);
		}
		return 0;
	}
	dlg = d2_LoadForm(0, 0, (int) s_6a96d8);
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 0);
	d2_InitWindowBounds(d2_CurrentWindowId);
	d2_SetForm(dlg, 1);
	io_AppendText(0x4132, 0x4131, 0x229);
	d2_SetForm(dlg, 2);
	id = io_AppendText(0x4133);
	ok = d2_GetWindowListItem(dlg, 2, id);
	cancel = d2_GetWindowListItem(dlg, 2, id + 1);
	d2_DialogButtonAction = -1;
	do {
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		} else if (d2_DialogButtonAction != -1) {
			if (d2_CurrentElementId == ok) {
				if (*request->xc == -1) {
					d2_DialogCloseRequested = 1;
				} else {
					h = gv_SendAllocGraveyardWorker(a1, *request->x0, request->x8, request->x10, 0x1c);
					while (h != -1 && (status = cm_GetCommandStatus(h)) == 0) {
						main_RunFrameLoop((void*) status, 0x20007);
					}
					p = cm_GetCommandResult(h);
					if (p != 0) {
						sprintf(line, s_6a9748, *(int*) (p + 4));
						id = evt_LoadGfxScript(s_6a9714);
						evt_CallScriptFunction(id, 1, line);
					}
					result = 1;
					d2_DialogCloseRequested = 1;
				}
			} else if (d2_CurrentElementId == cancel) {
				d2_DialogCloseRequested = 1;
			}
		}
	} while (main_RunFrameLoop((void*) d2_ShowFriedhofGehilfenDialog, 0x677c7) != 0);
	d2_DestroyForm(dlg);
	return result;
}
