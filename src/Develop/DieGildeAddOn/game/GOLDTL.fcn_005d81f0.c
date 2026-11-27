#include <string.h>
#include "client_dialog_state.h"
#include "client_actions.h"

typedef struct {
	int a;
	int size;
	int cd_lo;
	int cd_hi;
	int kind;
	int pad14[15];
} ExpelWorkerReq;

#include "Develop/DieGildeAddOn/game/entity_record.h"









extern const int g_666018;
extern int g_66601c;
extern int g_100f1dc;
extern int d2_CurrentElementId;
extern int g_14ce8e0;


extern char* __cdecl gm_LookupEntityRecordById(int);
extern char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
extern void __cdecl cm_RequestModifyHealth(int, int);
extern int __cdecl cm_RequestChangeBits(int, int, int, int, int);
extern void __cdecl io_FormatTextBuffer(char*, int, ...);
extern void __cdecl he_PostEntityMessage(int, int, char*, int, int, char*);
extern void __cdecl gm_TransferEntityBuildings(char*, int);
extern void __cdecl cm_RequestKillSpieler(int, int);
extern char* __cdecl fcn_005bdc30(int, int*, char*, int, int);
extern int __cdecl d2_LoadForm(int, int, char*);
extern void __cdecl d2_SetOverlayAnimation(int, int);
extern void __cdecl d2_CenterDialogWindows(int);
extern void __cdecl d2_SetForm(int, int);
extern int __cdecl io_AppendText(int, int, int, int);
extern int __cdecl d2_GetWindowListItem(int, int, int);
extern int __cdecl d2_CheckActionBlocker(char*, int);
extern int __cdecl cm_GetCommandStatus(int);
extern void __cdecl cm_StepCommandQueue(void);
extern void __cdecl fcn_00526120(char*, int);
extern int __cdecl gm_RandomMod(int);
extern int __cdecl main_RunFrameLoop(int, int);
extern void __cdecl d2_DestroyForm(int);

/* Validates the current entity action against its target and executes the
 * action's announce/notify path; returns one of the 0x10/0x20/0x60/0x81 codes. */
/* ADDRESS: GOLDTL 0x005d81f0 */
unsigned int __cdecl d2_ShowExpelWorkerDialog(char* entity, int* action)
{
	ExpelWorkerReq found;
	char text[512];
	char name[256];
	char* ent;
	char* other;
	char* rec;
	char* state_ptr;
	int i;
	int j;
	int count;
	int kid;
	int ret;
	int thr;
	int r;

	if (*(unsigned char*) (entity + 2) != 6) {
		if (*(int*) (entity + 0x194) < 5)
			return 0x20;
		if (*action == 3 && (*(int*) (entity + 0x1c8) & 0x80) == 0) {
			other = entity;
		} else {
			if (*action != 4)
				goto fail60;
			other = (char*) action[0x87];
			if (other == 0)
				goto fail60;
			if ((*(int*) (other + 0x1c8) & 0x80) != 0)
				goto fail60;
		}
		ent = gm_LookupEntityRecordById(action[0x85]);
		if (ent == 0)
			goto fail60;
		rec = gm_StartFilteredEntitySearch(1, 1, action[0x86]);
		if (rec == 0)
			goto fail60;
		cm_RequestModifyHealth(*(int*) (entity + 4), -5);
		cm_RequestChangeBits(*(int*) (other + 4), 0x1c8, 4, 0x80, 0);
		if (((ENTITY_RECORD_VIEW*)g_7f4ca0)[*(unsigned short*) (rec + 0x27)].entity_type == 6 ||
		    ((ENTITY_RECORD_VIEW*)g_7f4ca0)[*(unsigned short*) (rec + 0x27)].entity_type == 7) {
			io_FormatTextBuffer(text, 0x1ddf, *(unsigned short*) entity, rec, *(unsigned short*) ent);
			he_PostEntityMessage(*(unsigned short*) (rec + 0x27), *(unsigned short*) (rec + 0x27),
				text, 0, 0x5fb, (char*) 0x6a59fc);
		}
		gm_TransferEntityBuildings(ent, (int) gm_CityEntity);
		cm_RequestKillSpieler(*(int*) (ent + 4), 1);
		return 0x10;
	}
	memset(&found, 0, sizeof(found));
	if (*action == 3) {
		other = entity;
	} else {
		if (*action != 4 || action[0x87] == 0)
			goto fail60;
		other = (char*) action[0x87];
	}
	if ((*(unsigned char*) (other + 0x1c8) & 0x80) != 0) {
		io_FormatTextBuffer(name, 0x1ce0);
		fcn_00526120(name, 0);
		return 0x81;
	}
	ret = 0;
	found.size = 0x410;
	found.kind = 6;
	found.cd_lo = g_666018;
	found.cd_hi = g_66601c;
	found.a = 0;
	io_FormatTextBuffer(name, 0x9b);
	rec = fcn_005bdc30(1, (int*) &found, name, 0, 0);
	if (rec == 0)
		return 0;
	if (*(unsigned short*) (rec + 0x27) == 0xffff)
		return 0;
	state_ptr = (char*) ((ENTITY_RECORD*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[*(unsigned short*) (rec + 0x27)]);
	j = d2_LoadForm(0, 0, (char*) 0x6acd8c);
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(j);
	d2_SetForm(j, 1);
	i = io_AppendText(0x1ddd, 5, *(unsigned short*) state_ptr, rec);
	kid = d2_GetWindowListItem(j, 1, i);
	i = d2_GetWindowListItem(j, 1, i + 1);
	g_100f1dc = -1;
	do {
		if (g_100f1dc != -1) {
			if (d2_CurrentElementId == kid) {
				if (d2_CheckActionBlocker(entity, 5) != 0) {
					cm_RequestModifyHealth(*(int*) (entity + 4), -5);
					thr = cm_RequestChangeBits(*(int*) (other + 4), 0x1c8, 4, 0x80, 0);
					while (cm_GetCommandStatus(thr) == 0) {
						cm_StepCommandQueue();
					}
					io_FormatTextBuffer(text, 0x1dde);
					fcn_00526120(text, 0);
					r = gm_RandomMod(0x300) & 0xffff;
					ent = 0;
					count = 0x300;
					do {
						if (((ENTITY_RECORD_VIEW*)g_7f4ca0)[r].entity_index != 0xffff &&
						    (*(char**)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[r].ptr_16c) == rec &&
						    ((ENTITY_RECORD_VIEW*)g_7f4ca0)[r].entity_type == 0) {
							ent = (char*) ((ENTITY_RECORD*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[r]);
							break;
						}
						count -= 1;
						r = (r + 1) % 0x300;
					} while (count != 0);
					if (ent != 0) {
						if (*(unsigned char*) (state_ptr + 2) == 6 ||
						    *(unsigned char*) (state_ptr + 2) == 7) {
							io_FormatTextBuffer(text, 0x1ddf, *(unsigned short*) entity, rec,
								*(unsigned short*) ent);
							he_PostEntityMessage(*(int*) (state_ptr + 4), *(int*) (state_ptr + 4),
								text, 0, 0x5fb, (char*) 0x6a59fc);
						}
						gm_TransferEntityBuildings(ent, (int) gm_CityEntity);
						cm_RequestKillSpieler(*(int*) (ent + 4), 1);
					}
					ret = 0x81;
					g_774654 = 1;
				}
			} else if (d2_CurrentElementId == i) {
				g_774654 = 1;
			}
		}
		if (g_14ce8e0 != 0)
			g_774654 = 1;
	} while (main_RunFrameLoop((int) d2_ShowExpelWorkerDialog, 0x657c7) != 0);
	d2_DestroyForm(j);
	return ret;
fail60:
	return 0x60;
}
