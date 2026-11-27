/* "Locations\zigeuner\blutrache" blood-revenge dialog.
 *
 * Opens the dialog through fcn_00470820, installs the two range timers
 * (fcn_004677e0), fills the two choice ids with fcn_00533a60, then runs the
 * modal frame loop: each pass refreshes the local 0xe-byte UI time stamp from
 * the selected house entity at +0x52 (or from g_7f4c00 when no entity is
 * selected), drives the entity's progress ratio through the 0x500d20
 * stamps and fcn_00472380, updates the markup text through io_AppendText,
 * and on focus id 0 pays out through fcn_00525f60/fcn_005100f0 before filling
 * the 0xf8-byte panel record for fcn_004c5530.
 *
 * The stored row extent (1961 bytes) is wrong: this body ends at 0x5e635f
 * (add esp,0x128; jmp 0x532ef0, 1215 bytes). Bytes 0x5e6360-0x5e664f are a
 * separate dialog callback (frame 0x458, own ret) that the inventory has not
 * split out, so the row cannot be byte-exact until the extent is repaired. */
#include <string.h>

#include "client_types.h"
#include "Develop/DieGildeAddOn/game/game_player.h"
#include "client_dialog_state.h"

#include "Develop/DieGildeAddOn/game/game_timestamp.h"










/* 0xf8-byte dialog panel record handed to fcn_004c5530. */
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
	int sel;                    /* 0x58 */
	char pad5c[0x9c];           /* 0x5c */
} Panel;                        /* SIZE 0xf8 */

/* 0x21c-byte house record indexed by g_774970. */
typedef struct {
	int f0;                     /* 0x00 */
	int f4;                     /* 0x04 */
	char pad8[0x180];
	unsigned char b188;         /* 0x188 */
	char pad189[0x93];
} House;                        /* SIZE 0x21c */

extern char s_6ad434[];
extern char s_6811b0[];
extern int d2_CurrentWindowId;
extern char* g_77255c;
extern volatile int g_6b7fac;
extern int g_14b5af8;
extern int g_14b5afc;
extern pos14_7f4c00 gm_GameTime;
extern char g_7f4ca0[];
extern int g_14ce8e0;
extern int g_100f1dc;
extern int d2_CurrentElementId;
extern float g_6628a0;
extern float g_662cf8;

void __cdecl gm_AddTime(void*, int, int, int);
int __cdecl fcn_0042e410(int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl d2_AddWindowValueGauge(int, int, int, int, int, int, int, int);
#include "d2_gui.h"
int __cdecl gm_GetBuildingOptionCount(char*);
void __cdecl d2_CreateButtonRow(int, int, int*, int, int, int);
int __cdecl he_HasActiveAction0xa0(char*);
int __cdecl gm_GetElapsedMinutes(void*, void*);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetControlValue(int);
void __cdecl d2_SetElementEnabled(int, int);
void __cdecl d2_SetSlotVisibility(int, int);
int __cdecl d2_CheckActionBlocker(void*, int);
void __cdecl gm_ModifyHealth(int, int);
void __cdecl cm_SendCopyEntityData(void*);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);
void __cdecl d3_EndCameraAndUiMode(void);

/* ADDRESS: GOLDTL 0x005e5ea0 */
void __cdecl d2_ShowBlutracheDialog(char* participant)
{
	GAME_TIMESTAMP st;
	int timer2;
	int stage = 2;
	int idx = 0;
	int timer1;
	int ids[2];
	int n;
	unsigned int last = 0;
	int value;
	Panel msg;
	char* entity;
	int dlg;

	st = *(GAME_TIMESTAMP*) &gm_GameTime;
	gm_AddTime(&st, 0x18, 0, 0);
	st.hour = (unsigned short) (fcn_0042e410(stage) + 0x15);
	*(int*) ((char*) &st + 6) = 0;

	dlg = fcn_00470820(0, 0, s_6ad434);
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 0);
	fcn_005340f0(d2_CurrentWindowId);
	d2_SetForm(dlg, stage);
	timer1 = d2_AddWindowValueGauge((*(int*) (g_77255c + 0xc) - 300) / 2, 10, 300, 0, 100, 0x75, 0x42, d2_CurrentWindowId);
	d2_SetElementValue(timer1, 0, 100, 0);
	d2_SetForm(dlg, 2);
	timer2 = d2_AddWindowValueGauge(0x57, 7, 200, 0, 100, 0x7b, 2, d2_CurrentWindowId);
	gm_GetBuildingOptionCount(participant);
	d2_SetElementValue(timer2, 0, gm_GetBuildingOptionCount(participant) - 1, 0, 1);
	d2_SetForm(dlg, 3);
	d2_CreateButtonRow(d2_CurrentWindowId, 0, ids, stage, g_14b5af8, g_14b5afc);

	for (;;) {
		if ((unsigned int) g_6b7fac > last + 0x8c || d2_GetControlValue(timer2) != idx) {
			last = g_6b7fac;
			entity = (char*) he_HasActiveAction0xa0(participant);
			if (entity != 0) {
				st = *(GAME_TIMESTAMP*) (entity + 0x52);
				st.hour += *(int*) (entity + 0x70) ? 0 : 2;
				value = gm_GetElapsedMinutes(entity + 0x44, (void*) 0x7f4c00);
				n = gm_GetElapsedMinutes(entity + 0x44, &st);
				d2_SetElementValue(timer1, 0, 100,
					(int) ((((float) value / n < 1.0f) ? ((float) value / n) : 1.0f) * 100.0f));
			}
			else {
				st = *(GAME_TIMESTAMP*) &gm_GameTime;
				gm_AddTime(&st, 0x18, 0, 0);
				st.hour = (unsigned short) (fcn_0042e410(2) + 0x15);
				*(int*) ((char*) &st + 6) = 0;
				d2_SetElementValue(timer1, 0, 100, 0);
			}
			d2_SetForm(dlg, 1);
			io_AppendText((int) s_6811b0);
			if (entity != 0) {
				if (*(int*) (entity + 0x70) == 0) {
					io_AppendText(0x41f8, 0x41f4, *(int*) (entity + 0xac) + 0x41fb, &st);
				}
				else {
					io_AppendText(0x41f9, 0x41f4);
				}
			}
			else {
				idx = d2_GetControlValue(timer2);
				if (idx < 4) {
					stage = 2;
				}
				else {
					stage = (idx >= 7) + 3;
				}
				io_AppendText(0x41f5, 0x41f4, stage, idx + 0x41fb, &st);
			}
			d2_SetElementEnabled(ids[0], entity == 0);
			d2_SetElementEnabled(ids[1], entity == 0);
			d2_SetForm(dlg, 2);
			d2_SetSlotVisibility(timer1, entity != 0);
			d2_SetSlotVisibility(timer2, entity == 0);
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		else if (g_100f1dc != -1) {
			if (d2_CurrentElementId == ids[0]) {
				if (d2_CheckActionBlocker(((House*) g_7f4ca0) + g_774970, stage) == 1) {
					gm_ModifyHealth(((House*) g_7f4ca0)[g_774970].f4, -stage);
					memset(&msg, 0, sizeof(msg));
					msg.b4 = 0xa0;
					msg.b36 = 2;
					msg.f8 = ((House*) g_7f4ca0)[g_774970].f4;
					msg.fc = *(int*) (participant + 1);
					msg.pos = gm_GameTime;
					msg.sel = idx;
					cm_SendCopyEntityData(&msg);
					g_774654 = 1;
				}
			}
			else if (d2_CurrentElementId == ids[1]) {
				g_774654 = 1;
			}
		}
		if (main_RunFrameLoop((void*) d2_ShowBlutracheDialog, 0x677c7) == 0) {
			break;
		}
	}
	d2_DestroyForm(dlg);
	d3_EndCameraAndUiMode();
}
