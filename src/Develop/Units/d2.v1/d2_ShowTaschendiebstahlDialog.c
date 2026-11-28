#include "Develop/DieGildeAddOn/game/client_data.h"
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int d2_DialogButtonAction, g_14abaac, io_RightButtonReleased;
#include "Develop/Units/d2.v1/client_dialog_state.h"
#include "Develop/DieGildeAddOn/game/entity_record.h"
int __cdecl d2_CheckOwnerBlocked(char* obj);
void __cdecl d2_InitPlayerBar(char* obj, int a);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
int __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
void __cdecl d2_UpdateBuildingWorkerSlots(char* obj);
void __cdecl d2_ShowModalMessageBox(int a, int b);
void __cdecl cm_SendCopyEntityData(int a1);
void __cdecl d3snd_PlayWorkerOrderVoice(void);
void __cdecl sv_ClearObjectSelection(void);
int __cdecl main_RunFrameLoop(int, int);
void __cdecl d2_DestroyForm(int);
void __cdecl d2_RestoreHudAfterDialog(void);
int __cdecl d3_EndCameraAndUiMode(void);

/* ADDRESS: GOLDTL 0x005ae000 */
int __cdecl d2_ShowTaschendiebstahlDialog(char* obj)
{
	char packet[0xf8];
	int* ids;
	char* e;
	int dlg;
	int n;
	int i;
	int r;
	int idx;

	r = d2_CheckOwnerBlocked(obj);
	if (r != 0) {
		return r;
	}
	d2_InitPlayerBar(obj, 0);
	dlg = d2_LoadForm(0, 0, "locations\\diebesgilde\\taschendiebstahl");
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 1);
	io_AppendText(0x19f0);
	d2_DialogButtonAction = -1;
	ids = (int*) (packet + 0x38); for (i = 0; i < 6; i++) {
		ids[i] = -1;
	}
	n = 0;
	do {
		d2_UpdateBuildingWorkerSlots(obj);
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		}
		if (d2_DialogButtonAction != -1) {
			if (d2_DialogButtonAction == 2) {
				for (e = (char*) ch_ContextCharacters; (int) e < (int) (ch_ContextCharacters + 32) && n < 6; e += 4) {
					char* p;

					p = *(char**) e;
					if (p != 0 && *(char*) (p + 0x188) != 0) {
						ids[n] = *(int*) (p + 4);
						n++;
					}
				}
				if (n != 0) {
					idx = *(unsigned short*) (obj + 0x27);
					*(char*) (packet + 4) = 0x61;
					*(int*) (packet + 8) = *(int*) (((char *)&((ENTITY_RECORD_VIEW *)gm_EntitySlotTable)[idx]) + 4);
					*(int*) (packet + 0xc) = *(int*) (obj + 1);
					*(int*) (packet + 0x28) = gm_GameTime.a;
					*(int*) (packet + 0x2c) = gm_GameTime.b;
					*(int*) (packet + 0x30) = gm_GameTime.c;
					*(unsigned short*) (packet + 0x34) = gm_GameTime.d;
					*(char*) (packet + 0x36) = 1;
					*(int*) (packet + 0x80) = *(int*) (((char *)&((ENTITY_RECORD_VIEW *)gm_EntitySlotTable)[idx]) + 4);
					cm_SendCopyEntityData((int) packet);
					d3snd_PlayWorkerOrderVoice();
					sv_ClearObjectSelection();
					d2_DialogCloseRequested = 1;
				} else {
					d2_ShowModalMessageBox(g_14abaac, 0);
				}
			} else if (d2_DialogButtonAction == 1) {
				d2_DialogCloseRequested = 1;
			}
		}
	} while (main_RunFrameLoop(0x5ae000, 0x677c7) != 0);
	d2_DestroyForm(dlg);
	d2_RestoreHudAfterDialog();
	return d3_EndCameraAndUiMode();
}
