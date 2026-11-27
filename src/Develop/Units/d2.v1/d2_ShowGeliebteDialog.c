#include <string.h>
#include "Develop/DieGildeAddOn/game/game_player.h"
#include "client_dialog_state.h"

/* SIZE 0x21c */
typedef struct {
	char p0[4];
	int f4;
	char p8;
	unsigned char b9;
	char pa[0x21c - 0xa];
} D2_RESIDENCE_ENTITY;

extern D2_RESIDENCE_ENTITY g_7f4ca0[];
extern int d2_CurrentWindowId;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int d2_CurrentElementId;
extern int g_666018;
extern int g_66601c;

void __cdecl d2_ClearStatusTextSlots(void);
int __cdecl d2_LoadForm(int, int, char *);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_InitWindowBounds(int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl io_AppendText();
int __cdecl d2_GetWindowListItem(int, int, int);
char *__cdecl he_StartHandlungSearch(int, int, int);
char *__cdecl he_fn_Handlung(void);
char *__cdecl gm_LookupEntityRecordById(int);
void __cdecl d2_SetElementEnabled(int, int);
void __cdecl io_FormatTextBuffer(char *, int, ...);
unsigned short *__cdecl d2_OpenTargetPicker(int *, char *, char *, int);
int __cdecl d2_ShowModalMessageBox(char *, int);
void __cdecl cm_SendCopyEntityData(char *);
void __cdecl d2_SetFormVisibility(int, int);
void __cdecl d2_RunGeliebteDetailDialog(D2_RESIDENCE_ENTITY *, char *, char *);
int __cdecl main_RunFrameLoop(void *, int);
void __cdecl d2_DestroyForm(int);
void __cdecl d3_EndCameraAndUiMode(void);

/* Residence ("Wohnsitz") dialog: lists the player's lovers' residences as
 * buttons and runs the dialog loop until it closes. */
/* ADDRESS: GOLDTL 0x0059fe60 */
void __cdecl d2_ShowGeliebteDialog(char *building)
{
	int item;
	int ids[4];
	int buttons[4];
	int acts[4];
	int avail[4];
	int box[0x14];
	char msg[0xf8];
	char text_b[0x40];
	char text_a[0x40];
	char text_c[0x200];
	int dlg;
	int n;
	int i;
	char *ent;
	char *act;
	unsigned short *sel;

	buttons[0] = -1;
	buttons[1] = -1;
	buttons[2] = -1;
	buttons[3] = -1;
	d2_ClearStatusTextSlots();
	dlg = d2_LoadForm(0, 0, "locations\\wohnsitz\\geliebte");
	d2_SetForm(dlg, 0);
	d2_InitWindowBounds(d2_CurrentWindowId);
	d2_CenterDialogWindows(dlg);
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(dlg, 2);
	if (g_7f4ca0[g_774970].b9 == 0) {
		item = d2_GetWindowListItem(dlg, 2, io_AppendText(0x1a50));
	} else {
		item = d2_GetWindowListItem(dlg, 2, io_AppendText(0x1a51));
	}
	g_100f1dc = -1;
	do {
		memset(ids, 0xff, sizeof(ids));
		acts[0] = -1;
		acts[1] = -1;
		acts[2] = -1;
		acts[3] = -1;
		n = 0;
		for (ent = he_StartHandlungSearch(1, 0, 0x6f); ent != 0 && n < 4; ent = he_fn_Handlung()) {
			if (*(int *) (ent + 0xac) == g_7f4ca0[g_774970].f4) {
				acts[n] = *(int *) (ent + 4);
				if (*(int *) (ent + 0x70) == 0) {
					avail[n] = 1;
				} else {
					avail[n] = 0;
				}
				ids[n] = *(int *) (ent + 0xb0);
				n++;
			}
		}
		d2_SetForm(dlg, 1);
		io_AppendText("$C");
		io_AppendText("$Z$[%s$]$N", 0x1a4e);
		io_AppendText(0x1a4f);
		for (i = 0; i < 4; i++) {
			ent = gm_LookupEntityRecordById(ids[i]);
			if (ent == 0) {
				break;
			}
			buttons[i] = d2_GetWindowListItem(dlg, 1, io_AppendText(0x1a52, *(unsigned short *) ent));
			d2_SetElementEnabled(buttons[i], avail[i]);
		}
		if (n >= 4) {
			d2_SetElementEnabled(item, 0);
		} else {
			d2_SetElementEnabled(item, 1);
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		} else if (g_100f1dc != -1) {
			if (d2_CurrentElementId == item) {
				memset(box, 0, sizeof(box));
				box[4] = 6;
				box[1] = (g_7f4ca0[g_774970].b9 != 0) ? 0x20409 : 0x2040a;
				box[2] = g_666018;
				box[3] = g_66601c;
				io_FormatTextBuffer(text_a, 0x1a53);
				io_FormatTextBuffer(text_b, 0x1a54);
				sel = d2_OpenTargetPicker(box, text_a, text_b, 0);
				if (sel != 0) {
					if (g_7f4ca0[g_774970].b9 == 0) {
						io_FormatTextBuffer(text_c, 0x1a55, *sel);
					} else {
						io_FormatTextBuffer(text_c, 0x1a56, *sel);
					}
					if (d2_ShowModalMessageBox(text_c, 1) != 0) {
						memset(msg, 0, sizeof(msg));
						msg[4] = 0x6f;
						msg[0x36] = 2;
						*(int *) (msg + 8) = g_7f4ca0[g_774970].f4;
						*(int *) (msg + 0xc) = *(int *) (building + 1);
						*(int *) (msg + 0x5c) = *(int *) (sel + 2);
						*(int *) (msg + 0x58) = g_7f4ca0[g_774970].f4;
						cm_SendCopyEntityData(msg);
					}
				}
			} else {
				for (i = 0; i < 4; i++) {
					if (d2_CurrentElementId == buttons[i]) {
						ent = gm_LookupEntityRecordById(ids[i]);
						act = he_StartHandlungSearch(1, 1, acts[i]);
						d2_SetFormVisibility(dlg, 0);
						d2_RunGeliebteDetailDialog(&g_7f4ca0[g_774970], ent, act);
						d2_SetFormVisibility(dlg, 1);
						break;
					}
				}
			}
		}
	} while (main_RunFrameLoop((void *) d2_ShowGeliebteDialog, 0x67fff) != 0);
	d2_DestroyForm(dlg);
	d3_EndCameraAndUiMode();
}
