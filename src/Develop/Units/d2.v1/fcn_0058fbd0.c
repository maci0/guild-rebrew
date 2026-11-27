#include <string.h>
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_data.h"
#include "client_dialog_state.h"
struct msg58 {
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
extern int g_14ce8e0, d2_CurrentElementId;
void __cdecl fcn_0052a0c0(void* a1, int a2);
int __cdecl d2_LoadForm(int a1, int a2, char* path);
void __cdecl d2_SetOverlayAnimation(int a1, int a2);
void __cdecl d2_CenterDialogWindows(int a1);
void __cdecl d2_SetForm(int a1, int a2);
void __cdecl d2_InitWindowBounds(int a1);
int __cdecl io_AppendText(int a1, ...);
int __cdecl d2_GetWindowListItem(int a1, int a2, int a3);
int __cdecl main_RunFrameLoop(void* a1, int a2);
void __cdecl cm_SendCopyEntityData(struct msg58* m);
void __cdecl d2_DestroyForm(int a1);
void __cdecl d2_RestoreHudAfterDialog(void);
void __cdecl fcn_005305a0(void);
int __cdecl d3_EndCameraAndUiMode(void);
void __cdecl fcn_00526120(int a1, int a2);
/* ADDRESS: GOLDTL 0x0058fbd0 */
int __cdecl fcn_0058fbd0(char* gebaeude)
{
	int id1;
	struct msg58 m;
	int id2;
	int dlg;
	int i;
	int one;
	int sel;

	fcn_0052a0c0(gebaeude, 0);
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
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = one;
		} else if (g_100f1dc != -1) {
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
					g_774654 = 1;
				} else {
nofree:
					fcn_00526120(*(int*) 0x14b556c, 0);
				}
			} else if (sel == id2) {
				g_774654 = one;
			}
		}
	} while (main_RunFrameLoop((void*) fcn_0058fbd0, 0x677c7) != 0);
	d2_DestroyForm(dlg);
	d2_RestoreHudAfterDialog();
	fcn_005305a0();
	return d3_EndCameraAndUiMode();
}
