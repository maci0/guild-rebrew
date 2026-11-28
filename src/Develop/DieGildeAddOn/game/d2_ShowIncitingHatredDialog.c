extern char g_6a59fc[];

#include <string.h>

typedef struct
{
	int x0;
	int x4;
	__int64 mask;
	int x10;
	char pad14[0x3c];
} Query;
/* SIZE 0x50 */

typedef struct
{
	unsigned short id;
	unsigned char type;
	char pad3;
	int handle;
} HatredEntity;
/* SIZE 8 */

extern int d2_DialogButtonAction;
extern int io_RightButtonReleased;
extern __int64 gm_TargetPersonTypeMask;
extern int d2_CurrentElementId;
extern float g_6628ac;
extern unsigned char gm_ActiveTownIndex;
#include "Develop/Units/d2.v1/client_dialog_state.h"
#include "Develop/client_types.h"

char* __cdecl gm_LookupEntityRecordById(int a);
int __cdecl gm_CalcPersonWealth(unsigned short id);
int __cdecl gm_AccumulateTyped2(char* a);
unsigned short __cdecl gm_RandomMod(int a);
int __cdecl gm_GetEntityRelation(int a, int i);
void __cdecl cm_RequestCopyEntityData(int a, int b, int c, int d);
void __cdecl cm_RequestMoveCredits(int a, int b, char c, int n);
void __cdecl cm_RequestModifyHealth(int a, int b);
void __cdecl io_FormatTextBuffer(void* out, int id, ...);
void __cdecl he_PostEntityMessage(int a, int b, char* text, int c, int d, char* file);
int __cdecl d2_OpenTargetPicker(Query* q, char* text, int a, void* b);
int __cdecl d2_LoadForm(int a, int b, char* name);
void __cdecl d2_SetOverlayAnimation(int a, int b);
void __cdecl d2_CenterDialogWindows(int h);
void __cdecl d2_DestroyForm(int h);
void __cdecl d2_SetForm(int h, int a);
int __cdecl d2_GetWindowListItem(int h, int a, int b);
int __cdecl io_AppendText(int id, ...);
int __cdecl d2_CheckActionBlocker(char* e, int a);
int __cdecl gm_CheckEntityStock(void* e, int a, char b);
void __cdecl d2_ShowModalMessageBox(char* text, int a);
int __cdecl main_RunFrameLoop(void* fn, int a);

/* ADDRESS: GOLDTL 0x005d78e0 */
/* ADDRESS: GOLDDE 0x005b9140 */
int __cdecl d2_ShowIncitingHatredDialog(char* actor, char* request)
{
	Query req;
	char buf[0x100];
	HatredEntity* firstEntity;
	HatredEntity* secondEntity;
	int rc;
	int v;
	int w1;
	int w2;
	int d1;
	int d2;
	int dialog;
	int ret;
	int r1;
	int r2;
	int sum;

	if (*(unsigned char*) (actor + 2) != 6) {
		int bv;
		int bw1;
		int bw2;
		int bd1;
		int bd2;
		int bsum;

		if (*(int*) (actor + 0x194) < 4) {
			return 0x20;
		}
		firstEntity = (HatredEntity*) gm_LookupEntityRecordById(*(int*) (request + 0x214));
		if (firstEntity == 0) {
			return 0x20;
		}
		secondEntity = (HatredEntity*) gm_LookupEntityRecordById(*(int*) (request + 0x218));
		if (secondEntity == 0) {
			return 0x20;
		}
		bsum = gm_CalcPersonWealth(secondEntity->id);
		bsum = bsum + gm_CalcPersonWealth(firstEntity->id);
		bv = (int) (bsum * g_6628ac);
		if (gm_AccumulateTyped2(actor) < bv) {
			return 0x20;
		}
		bw1 = gm_RandomMod(0x1e) + 3;
		bw2 = gm_RandomMod(0x1e) + 3;
		bd1 = gm_GetEntityRelation(firstEntity->id, secondEntity->id);
		bd2 = gm_GetEntityRelation(secondEntity->id, firstEntity->id);
		cm_RequestCopyEntityData(firstEntity->handle, secondEntity->handle, bw1 - bd1 - 0x7f, 1);
		cm_RequestCopyEntityData(secondEntity->handle, firstEntity->handle, bw2 - bd2 - 0x7f, 1);
		cm_RequestMoveCredits(-1, *(int*) (actor + 4), *(char*) &gm_ActiveTownIndex, bv);
		cm_RequestModifyHealth(*(int*) (actor + 4), -4);
		if (firstEntity->type == 6 || firstEntity->type == 7) {
			io_FormatTextBuffer(buf, 0x1dd3, secondEntity->id, secondEntity->id);
			he_PostEntityMessage(firstEntity->handle, firstEntity->handle, buf, 0, 0x5fb, (char*) &g_6a59fc);
		}
		if (secondEntity->type == 6 || secondEntity->type == 7) {
			io_FormatTextBuffer(buf, 0x1dd3, firstEntity->id, firstEntity->id);
			he_PostEntityMessage(secondEntity->handle, secondEntity->handle, buf, 0, 0x5fb, (char*) &g_6a59fc);
		}
		return 0x10;
	}
	rc = 0;
	memset(&req, 0, sizeof(req));
	req.x4 = 0x400;
	req.x10 = 6;
	req.mask = gm_TargetPersonTypeMask;
	io_FormatTextBuffer(buf, 0x1dcf);
	firstEntity = (HatredEntity*) d2_OpenTargetPicker(&req, buf, 0, 0);
	if (firstEntity == 0) {
		return 0;
	}
	io_FormatTextBuffer(buf, 0x1dd0, firstEntity->id);
	secondEntity = (HatredEntity*) d2_OpenTargetPicker(&req, buf, 0, 0);
	if (secondEntity == 0) {
		return 0;
	}
	sum = gm_CalcPersonWealth(secondEntity->id);
	sum = sum + gm_CalcPersonWealth(firstEntity->id);
	v = (int) (sum * g_6628ac);
	dialog = d2_LoadForm(0, 0, "privillegien\\hass_erzeugen");
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(dialog);
	d2_SetForm(dialog, 1);
	ret = io_AppendText(0x1dd1, 4, v, firstEntity->id, secondEntity->id);
	r1 = d2_GetWindowListItem(dialog, 1, ret);
	r2 = d2_GetWindowListItem(dialog, 1, ret + 1);
	d2_DialogButtonAction = -1;
	do {
		if (d2_DialogButtonAction != -1) {
			if (d2_CurrentElementId == r1) {
				if (d2_CheckActionBlocker(actor, 4) != 0 &&
				    gm_CheckEntityStock(actor, v, *(char*) &gm_ActiveTownIndex) != 0) {
					w1 = gm_RandomMod(0x1e) + 3;
					w2 = gm_RandomMod(0x1e) + 3;
					d1 = gm_GetEntityRelation(firstEntity->id, secondEntity->id);
					d2 = gm_GetEntityRelation(secondEntity->id, firstEntity->id);
					cm_RequestCopyEntityData(firstEntity->handle, secondEntity->handle,
						     w1 - d1 - 0x7f, 1);
					cm_RequestCopyEntityData(secondEntity->handle, firstEntity->handle,
						     w2 - d2 - 0x7f, 1);
					cm_RequestMoveCredits(-1, *(int*) (actor + 4),
						     *(char*) &gm_ActiveTownIndex, v);
					cm_RequestModifyHealth(*(int*) (actor + 4), -4);
					io_FormatTextBuffer(buf, 0x1dd2, firstEntity->id, secondEntity->id);
					d2_ShowModalMessageBox(buf, 0);
					if (firstEntity->type == 6 || firstEntity->type == 7) {
						io_FormatTextBuffer(buf, 0x1dd3, secondEntity->id, secondEntity->id);
						he_PostEntityMessage(firstEntity->handle, firstEntity->handle, buf,
							     0, 0x5fb, (char*) &g_6a59fc);
					}
					if (secondEntity->type == 6 || secondEntity->type == 7) {
						io_FormatTextBuffer(buf, 0x1dd3, firstEntity->id, firstEntity->id);
						he_PostEntityMessage(secondEntity->handle, secondEntity->handle, buf,
							     0, 0x5fb, (char*) &g_6a59fc);
					}
					d2_DialogCloseRequested = 1;
					rc = 1;
				}
			} else if (d2_CurrentElementId == r2) {
				d2_DialogCloseRequested = 1;
			}
		}
		if (io_RightButtonReleased) {
			d2_DialogCloseRequested = 1;
		}
	} while (main_RunFrameLoop((void*) d2_ShowIncitingHatredDialog, 0x657c7) != 0);
	d2_DestroyForm(dialog);
	return rc;
}
