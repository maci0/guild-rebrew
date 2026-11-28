


#include <string.h>

// SIZE 0x50
typedef struct {
	int a;
	int size;
	__int64 cd;
	int kind;
	int pad14[15];
} Req;

extern __int64 gm_TargetPersonTypeMask;
extern char s_6acd74[];
extern char s_6a59fc[];
extern int d2_DialogButtonAction;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d2.v1/client_dialog_state.h"

unsigned char* __cdecl gm_LookupEntityRecordById(int);
void __cdecl cm_RequestModifyHealth(int, int);
int __cdecl cm_RequestChangeBits(int, int, int, int, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_PostEntityMessage(int, int, char*, int, int, char*);
void __cdecl d2_ShowModalMessageBox(char*, int);
unsigned char* __cdecl d2_OpenTargetPicker(Req*, char*, int, int);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl d2_CheckActionBlocker(unsigned char*, int);
int __cdecl cm_GetCommandStatus(int);
void __cdecl cm_StepCommandQueue(void);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);

/* ADDRESS: GOLDDE 0x005b96e0 */
int __cdecl gm_HandleDrainTargetAP(unsigned char* actor, unsigned char* action)
{
	int result;
	int cancel;
	int ok;
	Req req;
	char text[0x200];
	unsigned char* o;
	int dlg;
	int id;
	int h;

	if (actor[2] != 6) {
		if (*(int*) (actor + 0x194) < 2) {
			return 0x20;
		}
		if (*(int*) (actor + 0x1c8) & 0x8000) {
			return 0x20;
		}
		o = gm_LookupEntityRecordById(*(int*) (action + 0x214));
		if (o == 0) {
			return 0x60;
		}
		cm_RequestModifyHealth(*(int*) (actor + 4), -2);
		cm_RequestModifyHealth(*(int*) (o + 4), -3);
		cm_RequestChangeBits(*(int*) (actor + 4), 0x1c8, 4, 0x8000, 0);
		if (o[2] == 6 || o[2] == 7) {
			io_FormatTextBuffer(text, 0x1dda, *(unsigned short*) actor, 3);
			he_PostEntityMessage(*(int*) (o + 4), *(int*) (o + 4), text, 0, 0x5fb, s_6a59fc);
		}
		return 0x10;
	}
	result = 2;
	memset(&req, 0, sizeof(req));
	if (*(int*) (actor + 0x1c8) & 0x8000) {
		io_FormatTextBuffer(text, 0x1ce0);
		d2_ShowModalMessageBox(text, 0);
		return 0x81;
	}
	req.size = 0x400;
	req.kind = 6;
	req.cd = gm_TargetPersonTypeMask;
	io_FormatTextBuffer(text, 0x1dd7);
	o = d2_OpenTargetPicker(&req, text, 0, 0);
	if (o == 0) {
		return 2;
	}
	dlg = d2_LoadForm(0, 0, s_6acd74);
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 1);
	id = io_AppendText(0x1dd8, 2, *(unsigned short*) o, *(unsigned short*) o, 3, 2);
	ok = d2_GetWindowListItem(dlg, 1, id);
	cancel = d2_GetWindowListItem(dlg, 1, id + 1);
	d2_DialogButtonAction = -1;
	do {
		if (d2_DialogButtonAction != -1) {
			if (d2_CurrentElementId == ok) {
				if (d2_CheckActionBlocker(actor, 2)) {
					cm_RequestModifyHealth(*(int*) (actor + 4), -2);
					cm_RequestModifyHealth(*(int*) (o + 4), -3);
					h = cm_RequestChangeBits(*(int*) (actor + 4), 0x1c8, 4, 0x8000, 0);
					while (cm_GetCommandStatus(h) == 0) {
						cm_StepCommandQueue();
					}
					io_FormatTextBuffer(text, 0x1dd9, *(unsigned short*) o, *(unsigned short*) o, 3,
						*(unsigned short*) o, 3);
					d2_ShowModalMessageBox(text, 0);
					if (o[2] == 6 || o[2] == 7) {
						io_FormatTextBuffer(text, 0x1dda, *(unsigned short*) actor, 3);
						he_PostEntityMessage(*(int*) (o + 4), *(int*) (o + 4), text, 0, 0x5fb, s_6a59fc);
					}
					d2_DialogCloseRequested = 1;
					result = 0x81;
				}
			} else if (d2_CurrentElementId == cancel) {
				d2_DialogCloseRequested = 1;
			}
		}
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		}
	} while (main_RunFrameLoop((void*) gm_HandleDrainTargetAP, 0x657c7) != 0);
	d2_DestroyForm(dlg);
	return result;
}
