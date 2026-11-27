extern int d2_CurrentWindowId;
extern int g_772500;
extern int g_77255c;
extern int g_14ce8e0;
#include "client_dialog_state.h"

void* __cdecl d2_LoadForm(int a, int b, char* name);
void __cdecl d2_CenterDialogWindows(void* dlg);
void __cdecl d2_SetForm(void* dlg, int panel);
int __cdecl d2_InitWindowBounds(int a);
void __cdecl d2_SetOverlayAnimation(int a, int b);
int __cdecl gm_LookupEntityRecordById(int id);
void __cdecl d2_ClearWindowChildren(int a, int b);
int __cdecl io_AppendText();
void __cdecl d2_BuildPersonStatusDesc(void* slot);
void __cdecl fcn_005ca740(int x, int y, int a, int b, void* slot, int c);
int __cdecl main_RunFrameLoop(void (*fn)(void), int code);
void __cdecl d2_DestroyForm(void* dlg);

/* ADDRESS: GOLDTL 0x005a1e40 */
void __cdecl d2_RunStammtischDialog(int gebaeude, int* objekt)
{
	int changed;
	void* dlg;
	int* src;
	int sel[4][14];
	int* p;
	int* q;
	int n;
	int ent;
	int i;

	memset(sel, 0, sizeof(sel));
	dlg = d2_LoadForm(0, 0, "locations\\Wirtshaus\\Stammtisch");
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 0);
	d2_InitWindowBounds(d2_CurrentWindowId);
	d2_SetOverlayAnimation(0, 0);
	src = (int*) ((char*) objekt + 0x1c);
	for (;;) {
		changed = 0;
		n = 0;
		q = src;
		p = sel[0];
		for (i = 0; i < 4; i++) {
			ent = gm_LookupEntityRecordById(*q);
			if (ent != p[0]) {
				changed = 1;
			}
			if (ent != 0) {
				p[0] = ent;
				n++;
				p += 0xe;
			}
			q++;
		}
		for (i = n; i < 4; i++) {
			sel[i][0] = 0;
		}
		if (changed) {
			d2_SetForm(dlg, 1);
			d2_ClearWindowChildren(d2_CurrentWindowId, 1);
			io_AppendText((char*) 0x188c, gebaeude);
			if (n == 0) {
				io_AppendText((char*) 0x188e);
			} else {
				int x0 = *(int*) (g_77255c + 0xc) + *(short*) (g_772500 + 0x1ebd8) * -2;
				int third = x0 / 3;
				int remainder_half = (x0 % 3) / 2;
				p = sel[0];
				for (i = 0; i < n; i++) {
					p[0xc] = 1;
					p[4] = (i % 2 + 1) * third + remainder_half + (*(short*) (g_772500 + 0x1ebd8) + 10) * (i % 2) - 10;
					p[5] = (i / 2) * 0x82 + 100;
					d2_BuildPersonStatusDesc(p);
					fcn_005ca740(p[4], p[5], d2_CurrentWindowId, 0x54, p, 1);
					p += 0xe;
				}
			}
			d2_SetForm(dlg, 2);
			d2_ClearWindowChildren(d2_CurrentWindowId, 1);
			if (n == 4) {
				io_AppendText((char*) 0x1892);
			}
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (main_RunFrameLoop((void (*)(void)) d2_RunStammtischDialog, 0x677c7) == 0) {
			break;
		}
	}
	d2_DestroyForm(dlg);
}
