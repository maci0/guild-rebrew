/*
 * Draw the tooltip of record broadcast slot a2 (0..4) at the house of
 * g_774970.
 */
#include "Develop/DieGildeAddOn/game/entity_record.h"
#include <string.h>
#include "Develop/Units/d2.v1/d2_gui.h"
#include "client_types.h"
typedef pos14_7f4c00 Tbebe;


/* Message packet handed to fcn_004c5530. Field names unknown, so the layout
 * keeps raw offsets. */
typedef struct
{
	int f0;
	unsigned char b4;
	char pad5[3];
	int f8;
	int fc;
	char pad10[0x26];
	unsigned char b36;
	char pad37[0x23];
	unsigned char b5a;
	char pad5b[0x9d];
} MsgBebe;
/* SIZE 0xf8 */

struct s_1015f4c
{
	int x;
	int y;
	char pad[0x384];
	int idx;
	char pad2[0xc];
	int w;
	int h;
	int c;
	int d;
	char pad3[0x20];
};

extern char g_7f4ca0[];
#include "Develop/DieGildeAddOn/game/game_player.h"
extern int d2_CurrentWindowId;
extern int tp_d2_SelectedControl;
extern int g_100f1dc;
extern int g_14ce8e0;
#include "client_dialog_state.h"
extern char* g_1015ea0;
extern float g_662a98;
extern float g_664168;
#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern s_1015f4c g_1015f4c[];

char* __cdecl he_StartHandlungSearch(int a, int b, int c, int d, int e);
int __cdecl gm_CheckPrivilege(int a1, char* a2, int a3);
int __cdecl fcn_00470820(int a, int b, char* name);
void __cdecl d2_CenterDialogWindows(int h);
void __cdecl d2_DestroyForm(int h);
void __cdecl d2_SetForm(int h, int a);
void __cdecl d2_SetOverlayAnimation(int a, int b);
int __cdecl io_AppendText(int id, ...);
int __cdecl d2_AddElementToWindow(int x, int y, int id, int layer);
void __cdecl fcn_005340f0(int i);
void __cdecl fcn_00534160(int x0, int y, int len, int t);
int __cdecl fcn_0051e070(void);
void __cdecl d3_EndCameraAndUiMode(void);
int __cdecl main_RunFrameLoop(void* fn, int a);
void __cdecl fcn_0057e880(int a, int b, int c, int d);
void __cdecl gm_AddTime(Tbebe*, int, int, int);
int __cdecl gm_GetElapsedMinutes(void*, void*);
void __cdecl cm_RequestModifyHealth(int a, int b);
void __cdecl cm_SendCopyEntityData(MsgBebe* msg);

/* ADDRESS: GOLDTL 0x005bebe0 */
void __cdecl d2_RunTalenteDialog(int a0, int a1, int broadcastSlot)
{
	int big[0x88];
	MsgBebe msg;
	int yoff[5] = {0x25e, 0x264, 0x26a, 0x270, 0x276};
	int found;
	int ids[5];
	int flag;
	unsigned char color;
	char* slot;
	int miss;
	float f;
	int h;
	int x;

	slot = he_StartHandlungSearch(2, 2, g_774970, 0, 0x60);
	memset(big, 0, sizeof(big));
	flag = 0;
	ids[0] = 0x3a;
	ids[1] = 0x1a;
	ids[2] = 0x17;
	ids[3] = 0x18;
	ids[4] = 0x19;
	big[0] = 1;
	if (broadcastSlot >= 5) {
		return;
	}
	miss = (gm_CheckPrivilege(ids[broadcastSlot], (char*) ((char*)&((ENTITY_RECORD*)g_7f4ca0)[g_774970]), (int) big) & 2) != 0 ? -1 : 0;
	color = *(unsigned char*) (((char*)&((ENTITY_RECORD*)g_7f4ca0)[g_774970]) + 0x80 + broadcastSlot);
	if (color < 0x2a) {
		color = 1;
	} else if (color < 0x54) {
		color = 2;
	} else if (color < 0x7e) {
		color = 4;
	} else if (color < 0xa8) {
		color = 6;
	} else if (color < 0xd2) {
		color = 9;
	} else {
		color = 12;
	}
	color = color + miss;
	h = fcn_00470820(0, 0, (char*) 0x6ac484);
	d2_SetForm(h, 0);
	fcn_005340f0(d2_CurrentWindowId);
	d2_CenterDialogWindows(h);
	d2_SetForm(h, 1);
	d2_SetOverlayAnimation(0, 0);
	io_AppendText(0x16af, broadcastSlot + 0x16b7);
	io_AppendText(broadcastSlot + 0x16c3);
	d2_SetForm(h, 2);
	x = ((struct s_1015f4c*) g_1015f4c)[d2_CurrentWindowId].x;
	f = (float) *(unsigned char*) (((char*)&((ENTITY_RECORD*)g_7f4ca0)[g_774970]) + 0x80 + broadcastSlot) * 0.023809524f;
	if (!(f < 5.0f)) {
		f = 5.0f;
	}
	found = d2_AddElementToWindow(x / 2 - 0x18, 4, (int) ((float) yoff[broadcastSlot] + f), d2_CurrentWindowId);
	fcn_00534160(x / 2 - 0x23, 0x3c, *(unsigned char*) (((char*)&((ENTITY_RECORD*)g_7f4ca0)[g_774970]) + 0x80 + broadcastSlot), 0x4df);
	d2_SetForm(h, 3);
	if (slot != 0) {
		io_AppendText(0x16b3, *(unsigned char*) (slot + 0xae) + 0x16b7, broadcastSlot + 0x16b7);
	} else if (*(unsigned char*) (((char*)&((ENTITY_RECORD*)g_7f4ca0)[g_774970]) + 0x80 + broadcastSlot) >= 0xfc) {
		io_AppendText(0x16b2);
	} else if (*(int*) (((char*)&((ENTITY_RECORD*)g_7f4ca0)[g_774970]) + 0x194) >= (int) color) {
		if (miss == 0) {
			switch (fcn_0051e070()) {
			case 0:
				io_AppendText(0x16b1, color, broadcastSlot + 0x16b7);
				break;
			case 1:
				io_AppendText(0x16b1, color, broadcastSlot + 0x16b7);
				break;
			}
			flag = 1;
		} else {
			switch (fcn_0051e070()) {
			case 0:
				io_AppendText(0x16b0,
					     (*(unsigned char*) (((char*)&((ENTITY_RECORD*)g_7f4ca0)[g_774970]) + 9) != 0 ? 0x28 : 0) + 0x253 +
						     *(unsigned char*) (((char*)&((ENTITY_RECORD*)g_7f4ca0)[g_774970]) + 0x169),
					     color, broadcastSlot + 0x16b7);
				break;
			case 1:
				io_AppendText(0x16b0,
					     (*(unsigned char*) (((char*)&((ENTITY_RECORD*)g_7f4ca0)[g_774970]) + 9) != 0 ? 0x28 : 0) + 0x253 +
						     *(unsigned char*) (((char*)&((ENTITY_RECORD*)g_7f4ca0)[g_774970]) + 0x169),
					     broadcastSlot + 0x16b7, color);
				break;
			}
			flag = 1;
		}
	} else {
		io_AppendText(0x16b4, color, broadcastSlot + 0x16b7);
	}
	do {
		if (slot != 0 && found != -1) {
			Tbebe t;
			float dur;

			t = *(Tbebe*) (slot + 0x44);
			gm_AddTime(&t, 5, 0, 0);
			dur = (float) gm_GetElapsedMinutes(slot + 0x44, slot + 0x52);
			*(float*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[found].value_1f4)) =
				(float) gm_GetElapsedMinutes(slot + 0x44, (void*) &gm_GameTime) / dur;
		}
		if (g_14ce8e0 != 0 && tp_d2_SelectedControl == 0) {
			g_774654 = 1;
		}
		if (g_100f1dc == 2) {
			if (flag) {
				cm_RequestModifyHealth(*(int*) (((char*)&((ENTITY_RECORD*)g_7f4ca0)[g_774970]) + 4), -color);
				msg.b36 = 1;
				msg.b4 = 0x60;
				msg.b5a = (unsigned char) broadcastSlot;
				msg.f8 = *(int*) (((char*)&((ENTITY_RECORD*)g_7f4ca0)[g_774970]) + 4);
				msg.fc = *(int*) (((char*)&((ENTITY_RECORD*)g_7f4ca0)[g_774970]) + 4);
				cm_SendCopyEntityData(&msg);
				fcn_0057e880(0x2c, 0, 0, broadcastSlot);
				g_774654 = 1;
			}
		} else if (g_100f1dc == 1) {
			g_774654 = 1;
		}
	} while (main_RunFrameLoop((void*) d2_RunTalenteDialog, 0x677c7) != 0);
	d3_EndCameraAndUiMode();
	d2_DestroyForm(h);
}
