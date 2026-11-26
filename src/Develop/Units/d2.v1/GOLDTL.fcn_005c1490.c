#include <stdio.h>

extern char g_7f4ca0[];
#include "Develop/DieGildeAddOn/game/game_player.h"
extern int d2_CurrentWindowId;
extern int g_100f1dc;
extern int g_14ce8e0;
#include "client_dialog_state.h"
extern char g_6811b0[];
extern char g_10161b4[];
extern char g_1016198[];
#include "Develop/DieGildeAddOn/game/entity_record.h"
void __cdecl msx_SetFadeDuration(int);
void __cdecl fcn_0046e830(int, int, int, int, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl fcn_00471e30(int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl fcn_004ac1e0(unsigned short);
unsigned short __cdecl fcn_004ac2c0(unsigned short, unsigned short);
int __cdecl fcn_004ac320(unsigned short*);
void __cdecl fcn_004ac410(unsigned char*, int, unsigned short);
int __cdecl io_AppendText();
void __cdecl fcn_00532ef0(void);
void __cdecl fcn_005340f0(int);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl he_StartHandlungSearch();

/* ADDRESS: GOLDTL 0x005c1490 */
void __cdecl d2_ShowBardPoemDialog(void)
{
	int h;
	char buf[0x100];
	char* elem;
	char* e2;
	char* rec;
	int r;
	int idx;

	elem = (char*) he_StartHandlungSearch(1, 0, 0x6b);
	h = fcn_00470820(0, 0, "special\\barde");
	d2_SetForm(h, 0);
	fcn_005340f0(d2_CurrentWindowId);
	d2_CenterDialogWindows(h);
	d2_SetOverlayAnimation(0, 0);
	g_100f1dc = -1;
	d2_SetForm(h, 1);
	if (elem != 0 && *(int*) (elem + 0x70) == 2) {
		rec = (char*) fcn_004ac1e0(*(unsigned short*) (elem + 0xac));
		fcn_004ac2c0(*(unsigned short*) (elem + 0xac),
		    *(unsigned short*) (elem + 0xae));
		e2 = (char*) he_StartHandlungSearch(3, 0, 0x11, 3, *(int*) (elem + 4), 2,
		    (int) g_774970);
		if (e2 != 0) {
			*(int*) (e2 + 0x70) = -1;
		}
		if (*(int*) &((ENTITY_RECORD_VIEW*) g_7f4ca0)[(int) g_774970].flags_1c8 & 0x20000) {
			io_AppendText(0x1e27);
			do {
				if (g_14ce8e0 != 0) {
					g_774654 = 1;
				}
			} while (main_RunFrameLoop((void*) d2_ShowBardPoemDialog, 0x677c7) != 0);
			fcn_00471e30(h);
			fcn_00532ef0();
			return;
		}
		e2 = (char*) fcn_004ac320((unsigned short*)
		    ((char*) &((ENTITY_RECORD*) g_7f4ca0)[(int) g_774970]));
		if (e2 == 0) {
			io_AppendText(0x1e28);
			do {
				if (g_14ce8e0 != 0) {
					g_774654 = 1;
				}
			} while (main_RunFrameLoop((void*) d2_ShowBardPoemDialog, 0x677c7) != 0);
			fcn_00471e30(h);
			fcn_00532ef0();
			return;
		}
		msx_SetFadeDuration(0x3e8);
		io_AppendText(0x1e2a, (int) *(unsigned short*) (rec + 0xc) + 1, e2);
		sprintf(buf, "Gedichte_Announcement\\%s.mp3", rec + 0xe);
		r = 0;
		do {
			if (g_14ce8e0 != 0) {
				g_774654 = 1;
			} else if (g_100f1dc != -1) {
				if (g_100f1dc == 2) {
					fcn_004ac410((unsigned char*)
					    ((char*) &((ENTITY_RECORD*) g_7f4ca0)[(int) g_774970]), (int) e2,
					    *(unsigned short*) (elem + 0xac));
					r = 1;
					g_774654 = 1;
				} else if (g_100f1dc == 1) {
					g_774654 = 1;
				}
			}
		} while (main_RunFrameLoop((void*) d2_ShowBardPoemDialog, 0x677c7) != 0);
		if (r == 0) {
			fcn_00471e30(h);
			fcn_00532ef0();
			return;
		}
		fcn_00471e30(h);
		h = fcn_00470820(0, 0, "special\\barde2");
		d2_SetForm(h, 0);
		fcn_005340f0(d2_CurrentWindowId);
		d2_CenterDialogWindows(h);
		d2_SetOverlayAnimation(0, 0);
		g_100f1dc = -1;
		d2_SetForm(h, 1);
		io_AppendText((int) *(unsigned short*) (rec + 0xc));
		d2_SetForm(h, 2);
		idx = d2_CurrentWindowId;
		d2_SetForm(h, 3);
		fcn_0046e830(-1, -1, d2_CurrentWindowId, idx, 0x767);
		*(int*) (g_10161b4 + idx * 0x3cc) = 0x30;
		d2_SetForm(h, 2);
		io_AppendText((int) *(unsigned short*) (rec + 0xc) + 2);
		g_100f1dc = -1;
		sprintf(buf, "gedichte\\%s.mp3", rec + 0xe);
		do {
			if (g_14ce8e0 != 0) {
				g_774654 = 1;
			}
		} while (main_RunFrameLoop((void*) d2_ShowBardPoemDialog, 0x677c7) != 0);
		d2_SetForm(h, 3);
		io_AppendText(g_6811b0);
		d2_SetForm(h, 1);
		io_AppendText(g_6811b0);
		io_AppendText(0x1e5c);
		d2_SetForm(h, 2);
		io_AppendText(g_6811b0);
		*(int*) (g_1016198 + d2_CurrentWindowId * 0x3cc) = 0;
		if (*(int*) rec == 0) {
			io_AppendText(0x1e5e, (int) *(unsigned short*) (rec + 4) + 0x16b7);
		} else if (*(int*) rec == 1) {
			io_AppendText(0x1e5d, (int) *(unsigned short*) (rec + 4) + 0x1ee);
		} else {
			io_AppendText(0x1e5f);
		}
		do {
			if (g_14ce8e0 != 0) {
				g_774654 = 1;
			}
		} while (main_RunFrameLoop((void*) d2_ShowBardPoemDialog, 0x677c7) != 0);
		fcn_00471e30(h);
		fcn_00532ef0();
		return;
	}
	io_AppendText(0x1e26);
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
	} while (main_RunFrameLoop((void*) d2_ShowBardPoemDialog, 0x677c7) != 0);
	fcn_00471e30(h);
	fcn_00532ef0();
}
