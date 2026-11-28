#include <string.h>
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/DieGildeAddOn/game/client_data.h"
#include "Develop/Units/d2.v1/client_dialog_state.h"
struct D2_DEATH_PACT_MSG {
	char pad0[4];
	unsigned char b4;
	char pad5[3];
	int f8;
	int fc;
	char pad10[0x18];
	pos14_7f4c00 stamp;
	unsigned char b36;
	char pad37;
	int f38;
	char pad3c[0x1c];
	int f58;
	char pad5c[0x9c];
};
extern int io_RightButtonReleased, d2_CurrentElementId;
void __cdecl d2_InitPlayerBar(void* a1, int a2);
int __cdecl d2_LoadForm(int a1, int a2, char* path);
void __cdecl d2_SetOverlayAnimation(int a1, int a2);
void __cdecl d2_CenterDialogWindows(int a1);
void __cdecl d2_SetForm(int a1, int a2);
void __cdecl d2_InitWindowBounds(int a1);
int __cdecl io_AppendText(int a1, ...);
int __cdecl d2_GetWindowListItem(int a1, int a2, int a3);
int __cdecl main_RunFrameLoop(void* a1, int a2);
void __cdecl cm_SendCopyEntityData(struct D2_DEATH_PACT_MSG* m);
void __cdecl d2_DestroyForm(int a1);
void __cdecl d2_RestoreHudAfterDialog(void);
void __cdecl fcn_005305a0(void);
int __cdecl d3_EndCameraAndUiMode(void);
void __cdecl d2_ShowModalMessageBox(int a1, int a2);
/* ADDRESS: GOLDTL 0x0058fbd0 */
int __cdecl d2_RunDeathPactDialog(char* gebaeude)
{
	int id1;
	struct D2_DEATH_PACT_MSG m;
	int id2;
	int dlg;
	int i;
	int one;
	int sel;

	d2_InitPlayerBar(gebaeude, 0);
	dlg = d2_LoadForm(0, 0, (char*) 0x6a96d8);
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 0);
	d2_InitWindowBounds(d2_CurrentWindowId);
	one = 1;
	d2_SetForm(dlg, one);
	io_AppendText(0x40f6, 0x40f5, 0x228);
	d2_SetForm(dlg, 2);
	i = io_AppendText(0x40f7);
	id1 = d2_GetWindowListItem(dlg, 2, i);
	id2 = d2_GetWindowListItem(dlg, 2, i + 1);
	d2_DialogButtonAction = -1;
	do {
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = one;
		} else if (d2_DialogButtonAction != -1) {
			sel = d2_CurrentElementId;
			if (sel == id1) {
				char* p;
				char* h;

				i = 0;
				p = (char*) 0x7f4e28;
				do {
					if (*(char*) p != 0) {
						goto found;
					}
					p += 0x21c;
					i++;
				} while ((int) p < 0x85a228);
				goto nofree;
found:
				h = (char*) (0x7f4ca0 + i * 0x21c);
				if (h != 0) {
					memset(&m, 0, sizeof(m));
					m.b4 = 0x8a;
					m.b36 = 1;
					m.f8 = *(int*) (*(unsigned short*) (gebaeude + 0x27) * 0x21c + 0x7f4ca4);
					m.fc = *(int*) (gebaeude + 1);
					m.stamp = gm_GameTime;
					m.f58 = *(int*) (h + 4);
					m.f38 = *(int*) (h + 4);
					cm_SendCopyEntityData(&m);
					d2_DialogCloseRequested = 1;
				} else {
nofree:
					d2_ShowModalMessageBox(*(int*) 0x14b556c, 0);
				}
			} else if (sel == id2) {
				d2_DialogCloseRequested = one;
			}
		}
	} while (main_RunFrameLoop((void*) d2_RunDeathPactDialog, 0x677c7) != 0);
	d2_DestroyForm(dlg);
	d2_RestoreHudAfterDialog();
	fcn_005305a0();
	return d3_EndCameraAndUiMode();
}
