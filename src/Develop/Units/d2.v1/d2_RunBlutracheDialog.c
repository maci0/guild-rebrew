#include <string.h>
#include "Develop/client_types.h"
#include "Develop/DieGildeAddOn/game/game_player.h"
#include "Develop/Units/d2.v1/d2_gui.h"

/* 0xf8-byte message panel record handed to fcn_004c5530. */
typedef struct {
	int f0;                     /* 0x00 */
	unsigned char b4;           /* 0x04 */
	char pad5[3];
	int f8;                     /* 0x08 */
	int fc;                     /* 0x0c */
	char pad10[0x18];           /* 0x10 */
	pos14_7f4c00 pos;           /* 0x28 */
	unsigned char b36;          /* 0x36 */
	char pad37[0x21];           /* 0x37 */
	int val;                    /* 0x58 */
	int target_id;              /* 0x5c */
	char pad60[0x98];           /* 0x60 */
} BLUTRACHE_PACKET_F8;                 /* SIZE 0xf8 */

extern char str_dollar_C[];
extern int d2_CurrentWindowId;
extern unsigned short gm_LocalPlayerSlot;
extern unsigned char gm_ActiveTownIndex;
extern pos14_7f4c00 gm_GameTime;
extern char gm_EntitySlotTable[];
extern char gm_EntityIdField[];
extern int d2_DialogButtonAction;
extern int io_RightButtonReleased;
extern int d2_DialogCloseRequested;
extern int gm_TargetPersonTypeMask, g_66601c;
#include "Develop/DieGildeAddOn/game/entity_record.h"
int __cdecl d3snd_PlaySoundEffect(int, int, char*, int);
void __cdecl d2_ShowGreenMessageBox(int, int, int);
char* __cdecl d2_OpenTargetPicker(int*, int, int, void*);
void __cdecl d3_EndCameraAndUiMode(void);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_InitWindowBounds(int);
int __cdecl d2_AddWindowValueGauge(int, int, int, int, int, int, int, int);
void __cdecl d2_SetValueGaugeStepLabels(int, int, ...);
void __cdecl d2_CreateButtonRow(int, int, int*, int, ...);
int __cdecl gm_GetBuildingSlotCapacity(char*);
int __cdecl d2_GetControlValue(int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
int __cdecl io_AppendText(int, ...);
int __cdecl gm_CheckEntityStock(char*, int, unsigned char);
void __cdecl cm_RequestChangeBits(int, int, int, int, int);
void __cdecl cm_RequestTransferCurrencyNoKill(int, int, unsigned char, int);
void __cdecl cm_SendCopyEntityData(void*);
int __cdecl fcn_0064d41a(char*, char*, ...);
void __cdecl d2_ShowModalMessageBox(char*, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);

/* ADDRESS: GOLDTL 0x005e5a50 */
/* ADDRESS: GOLDDE 0x005c6d10 */
void __cdecl d2_RunBlutracheDialog(char* entity)
{
	char text[512];
	char buf[100];
	BLUTRACHE_PACKET_F8 pkt;
	int query[20];
	int ids[2];
	int control;
	int dialog;
	char* target;
	int max_val;
	int val;

	if (*(unsigned char*) &((ENTITY_RECORD*) gm_EntitySlotTable)[gm_LocalPlayerSlot].entity_flags & 0x10) {
		d3snd_PlaySoundEffect(-7, 0, (char*) 0x6ad46c, -1);
		d2_ShowGreenMessageBox(*(int*) 0x14b5a24, *(int*) 0x14b5a28, 0);
		return;
	}
	memset(query, 0, sizeof(query));
	memset(query + 7, -1, 8 * sizeof(int));
	query[2] = gm_TargetPersonTypeMask;
	query[3] = g_66601c;
	query[0] = 1;
	query[1] = 0x400;
	query[4] = 6;
	target = d2_OpenTargetPicker(query, *(int*) 0x14b5a2c, 0, 0);
	if (target == 0) {
		d3_EndCameraAndUiMode();
		return;
	}
	dialog = d2_LoadForm(0, 0, (char*) 0x6ad434);
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(dialog);
	d2_SetForm(dialog, 0);
	d2_InitWindowBounds(d2_CurrentWindowId);
	d2_SetForm(dialog, 2);
	control = d2_AddWindowValueGauge(0x57, 7, 200, 0, 100, 0x7b, 2, d2_CurrentWindowId);
	d2_SetElementValue(control, 0, 5, 0, 1);
	d2_SetValueGaugeStepLabels(control, 6, *(int*) 0x14b5a48, *(int*) 0x14b5a4c,
	             *(int*) 0x14b5a50, *(int*) 0x14b5a54,
	             *(int*) 0x14b5a58, *(int*) 0x14b5a5c);
	d2_SetForm(dialog, 3);
	d2_CreateButtonRow(d2_CurrentWindowId, 0, ids, 2, *(int*) 0x14b5a80, *(int*) 0x14b5a84);
	do {
		max_val = gm_GetBuildingSlotCapacity(entity) - 1;
		val = d2_GetControlValue(control);
		if (val >= max_val) {
			val = max_val;
		}
		d2_SetElementValue(control, 0, max_val, val, 1);
		io_FormatTextBuffer(text, val + 0x41d0, *(unsigned short*) target);
		d2_SetForm(dialog, 1);
		io_AppendText((int) str_dollar_C);
		io_AppendText(0x41d6, 0x41c1, val + 0x41c4, text);
		if (gm_LocalPlayerSlot != *(unsigned short*) (entity + 0x27)) {
			io_AppendText(0x41d7, (val > 1 ? val : 1) * 32000);
		}
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		} else if (d2_DialogButtonAction != -1) {
			int clicked = *(int*) 0x67d370;
			if (clicked == ids[0]) {
				if (gm_CheckEntityStock((char*) &((ENTITY_RECORD*) gm_EntitySlotTable)[gm_LocalPlayerSlot], val, gm_ActiveTownIndex) != 0) {
					cm_RequestChangeBits(((ENTITY_RECORD*) gm_EntitySlotTable)[gm_LocalPlayerSlot].entity_id, 0x1cc, 4, 0x10, 0);
					if (gm_LocalPlayerSlot != *(unsigned short*) (entity + 0x27)) {
						cm_RequestTransferCurrencyNoKill(-1, ((ENTITY_RECORD*) gm_EntitySlotTable)[gm_LocalPlayerSlot].entity_id,
						             gm_ActiveTownIndex, (val > 1 ? val : 1) * 32000);
					}
					memset(&pkt, 0, sizeof(pkt));
					pkt.b4 = 0x9d;
					pkt.fc = -1;
					pkt.b36 = 2;
					pkt.val = val;
					pkt.f8 = ((ENTITY_RECORD*) gm_EntitySlotTable)[gm_LocalPlayerSlot].entity_id;
					pkt.pos = gm_GameTime;
					pkt.target_id = *(int*) (target + 4);
					cm_SendCopyEntityData(&pkt);
					io_FormatTextBuffer(text, 0x41da, 0x41c1);
					fcn_0064d41a(buf, (char*) 0x6ad454, val);
					d3snd_PlaySoundEffect(-7, 0, buf, -1);
					d2_ShowModalMessageBox(text, 0);
					d2_DialogCloseRequested = 1;
				}
			} else if (clicked == ids[1]) {
				d2_DialogCloseRequested = 1;
			}
		}
	} while (main_RunFrameLoop((void*) d2_RunBlutracheDialog, 0x677c7) != 0);
	d2_DestroyForm(dialog);
	d3_EndCameraAndUiMode();
}
