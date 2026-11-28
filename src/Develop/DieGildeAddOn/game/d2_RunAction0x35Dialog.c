

#include <string.h>
#pragma intrinsic(memset)

// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"






#include "Develop/DieGildeAddOn/game/game_player.h"
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d2.v1/client_dialog_state.h"
#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern unsigned short gm_GameTimeHour;
extern int gm_GameTimeSliceDword;
extern short gm_GameTimeTailWord;
extern char g_6ac494[];

int __cdecl he_CountEntityActions(void*, unsigned short*, int*);
int __cdecl he_HasNoActiveAction0x88(unsigned short*, void*);
int __cdecl d2_CheckActionBlocker(void*, int);
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl d2_ShowModalMessageBox(char*, int);
int __cdecl d2_LoadForm(int, int, void*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
void __cdecl d2_DrawLawCandidateStatus(int*);
int __cdecl main_RunFrameLoop(void*, int);
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
unsigned short __cdecl gm_RandomMod(int n);
void __cdecl cm_SendCopyEntityData(char* msg);
void __cdecl d2_DestroyForm(int);

/* ADDRESS: GOLDDE 0x005a31d0 */
int __cdecl d2_RunAction0x35Dialog(unsigned short* obj)
{
	int res;
	int cnt;
	int arr[6];
	char text[0x400];
	int d;

	res = 0;
	if (obj == 0) {
		return 0;
	}
	if (*obj == 0xffff) {
		return 0;
	}
	if (*obj == gm_LocalPlayerSlot) {
		return 0;
	}
	if (he_CountEntityActions(((ENTITY_RECORD*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot]), obj, &cnt) == 0) {
		io_FormatTextBuffer(text, 0x190f, *obj);
		d2_ShowModalMessageBox(text, 0);
		return 0;
	}
	if (he_HasNoActiveAction0x88(obj, ((ENTITY_RECORD*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot])) == 0) {
		io_FormatTextBuffer(text, 0x409f, *obj);
		d2_ShowModalMessageBox(text, 0);
		return 0;
	}
	if (cnt > 3) {
		io_FormatTextBuffer(text, 0x190e);
		d2_ShowModalMessageBox(text, 0);
		return 0;
	}
	if (d2_CheckActionBlocker(((ENTITY_RECORD*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot]), 1) == 0) {
		return 0;
	}
	d = d2_LoadForm(0, 0, g_6ac494);
	d2_CenterDialogWindows(d);
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(d, 1);
	io_AppendText(0x1910, *obj, *obj, 1, *obj);
	memset(arr, 0xff, sizeof(arr));
	arr[0] = d;
	arr[3] = 4;
	arr[4] = 4;
	arr[1] = 2;
	arr[2] = 3;
	arr[5] = 3;
	d2_DrawLawCandidateStatus(arr);
	d2_DialogButtonAction = -1;
	do {
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		}
		if (d2_DialogButtonAction != -1) {
			if (d2_DialogButtonAction == 2) {
				char ev[0xf8];

				gm_StartFilteredEntitySearch(1, 5, 0xa);
				ev[4] = 0x35;
				ev[0x36] = 2;
				*(int*) (ev + 8) = ((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot].entity_id;
				*(int*) (ev + 0xc) = ((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot].entity_id;
				*(int*) (ev + 0x58) = (*(int*)&gm_GameTime);
				*(int*) (ev + 0x5c) = (*(int*)&gm_GameTimeHour);
				*(int*) (ev + 0x60) = gm_GameTimeSliceDword;
				*(short*) (ev + 0x64) = gm_GameTimeTailWord;
				ev[0x6d] = (char) gm_RandomMod(0x1d);
				*(int*) (ev + 0x68) = *(int*) (obj + 2);
				cm_SendCopyEntityData(ev);
				res = 1;
				d2_DialogCloseRequested = 1;
			}
			else if (d2_DialogButtonAction == 1) {
				d2_DialogCloseRequested = 1;
			}
		}
	} while (main_RunFrameLoop((void*) d2_RunAction0x35Dialog, 0x677c7) != 0);
	d2_DestroyForm(d);
	return res;
}
