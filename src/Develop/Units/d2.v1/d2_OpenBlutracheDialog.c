


#include <string.h>

// SIZE 0xf8
#include "client_types.h"
struct msg {
	int f0;
	char b4;
	char pad5[3];
	int f8;
	int fc;
	char pad10[0x18];
	pos14_7f4c00 pos;
	char b36;
	char pad37;
	int ids[4];
	char pad48[0xb0];
};

// SIZE 0x21c
typedef struct {
	int f0;
	int f4;
	char pad8[0x180];
	char b188;
	char pad189[0x93];
} House;

extern pos14_7f4c00 gm_GameTime;
extern char g_7f4ca0[];
#include "Develop/DieGildeAddOn/game/game_player.h"
extern char s_6ad434[];
extern char s_6811b0[];
extern int d2_CurrentWindowId;
extern int g_14b5ac0;
extern int g_14b5ac4;
extern int g_14b5ac8;
extern int g_14ce8e0;
extern int g_100f1dc;
extern int d2_CurrentElementId;
#include "Develop/Units/d2.v1/client_dialog_state.h"

void __cdecl d2_InitPlayerBar(char*, int);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_InitWindowBounds(int);
int __cdecl io_AppendText(int, ...);
void __cdecl d2_CreateButtonRow(int, int, int*, int, ...);
void __cdecl d2_ShowModalMessageBox(int, int);
void __cdecl cm_SendCopyEntityData(struct msg*);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);
void __cdecl d2_RestoreHudAfterDialog(void);
void __cdecl sv_ClearObjectSelection(void);
void __cdecl d3_EndCameraAndUiMode(void);

void __cdecl d2_OpenBlutracheDialog(char* e)
{
	int ids[2];
	int list[4];
	struct msg m;
	int dlg;
	int n;
	int i;

	d2_InitPlayerBar(e, 0);
	dlg = d2_LoadForm(0, 0, s_6ad434);
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 0);
	d2_InitWindowBounds(d2_CurrentWindowId);
	d2_SetForm(dlg, 1);
	io_AppendText((int) s_6811b0);
	io_AppendText(0x41e7, 0x41e6, 0xed6);
	d2_SetForm(dlg, 3);
	d2_CreateButtonRow(d2_CurrentWindowId, 0, ids, 2, g_14b5ac0, g_14b5ac4);
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		} else if (g_100f1dc != -1) {
			if (d2_CurrentElementId == ids[0]) {
				n = 0;
				for (i = 0; i < 768; i++) {
					if (n >= 4) {
						break;
					}
					if (((House*)g_7f4ca0)[i].b188 != 0) {
						list[n] = i;
						n++;
					}
				}
				if (n != 0) {
					memset(&m, 0, sizeof(m));
					m.b4 = (char) 0xa1;
					m.b36 = 1;
					m.f8 = ((House*)g_7f4ca0)[g_774970].f4;
					m.fc = *(int*) (e + 1);
					m.pos = gm_GameTime;
					for (i = 0; i < n; i++) {
						m.ids[i] = ((House*)g_7f4ca0)[list[i]].f4;
					}
					cm_SendCopyEntityData(&m);
					g_774654 = 1;
				} else {
					d2_ShowModalMessageBox(g_14b5ac8, 0);
				}
			} else if (d2_CurrentElementId == ids[1]) {
				g_774654 = 1;
			}
		}
	} while (main_RunFrameLoop((void*) d2_OpenBlutracheDialog, 0x677c7) != 0);
	d2_DestroyForm(dlg);
	d2_RestoreHudAfterDialog();
	sv_ClearObjectSelection();
	d3_EndCameraAndUiMode();
}
