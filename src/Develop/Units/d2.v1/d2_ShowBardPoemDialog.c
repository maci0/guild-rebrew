#include <stdio.h>

extern char gm_EntitySlotTable[];
#include "Develop/DieGildeAddOn/game/game_player.h"
extern int d2_CurrentWindowId;
extern int d2_DialogButtonAction;
extern int io_RightButtonReleased;
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern char str_dollar_C[];
extern char g_10161b4[];
extern char g_1016198[];
#include "Develop/DieGildeAddOn/game/entity_record.h"
void __cdecl msx_SetFadeDuration(int);
void __cdecl d2_AddWindowScrollButtons(int, int, int, int, int);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_DestroyForm(int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl gm_GetBardEventEntry(unsigned short);
unsigned short __cdecl d2_GetBardPoemTextId(unsigned short, unsigned short);
int __cdecl gm_CalcBardPoemCost(unsigned short*);
void __cdecl gm_ApplyBardPoemEffect(unsigned char*, int, unsigned short);
int __cdecl io_AppendText();
void __cdecl d3_EndCameraAndUiMode(void);
void __cdecl d2_InitWindowBounds(int);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl he_StartHandlungSearch();

/* ADDRESS: GOLDTL 0x005c1490 */
/* ADDRESS: GOLDDE 0x005a38d0 */
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
	h = d2_LoadForm(0, 0, "special\\barde");
	d2_SetForm(h, 0);
	d2_InitWindowBounds(d2_CurrentWindowId);
	d2_CenterDialogWindows(h);
	d2_SetOverlayAnimation(0, 0);
	d2_DialogButtonAction = -1;
	d2_SetForm(h, 1);
	if (elem != 0 && *(int*) (elem + 0x70) == 2) {
		rec = (char*) gm_GetBardEventEntry(*(unsigned short*) (elem + 0xac));
		d2_GetBardPoemTextId(*(unsigned short*) (elem + 0xac),
		    *(unsigned short*) (elem + 0xae));
		e2 = (char*) he_StartHandlungSearch(3, 0, 0x11, 3, *(int*) (elem + 4), 2,
		    (int) gm_LocalPlayerSlot);
		if (e2 != 0) {
			*(int*) (e2 + 0x70) = -1;
		}
		if (*(int*) &((ENTITY_RECORD_VIEW*) gm_EntitySlotTable)[(int) gm_LocalPlayerSlot].flags_1c8 & 0x20000) {
			io_AppendText(0x1e27);
			do {
				if (io_RightButtonReleased != 0) {
					d2_DialogCloseRequested = 1;
				}
			} while (main_RunFrameLoop((void*) d2_ShowBardPoemDialog, 0x677c7) != 0);
			d2_DestroyForm(h);
			d3_EndCameraAndUiMode();
			return;
		}
		e2 = (char*) gm_CalcBardPoemCost((unsigned short*)
		    ((char*) &((ENTITY_RECORD*) gm_EntitySlotTable)[(int) gm_LocalPlayerSlot]));
		if (e2 == 0) {
			io_AppendText(0x1e28);
			do {
				if (io_RightButtonReleased != 0) {
					d2_DialogCloseRequested = 1;
				}
			} while (main_RunFrameLoop((void*) d2_ShowBardPoemDialog, 0x677c7) != 0);
			d2_DestroyForm(h);
			d3_EndCameraAndUiMode();
			return;
		}
		msx_SetFadeDuration(0x3e8);
		io_AppendText(0x1e2a, (int) *(unsigned short*) (rec + 0xc) + 1, e2);
		sprintf(buf, "Gedichte_Announcement\\%s.mp3", rec + 0xe);
		r = 0;
		do {
			if (io_RightButtonReleased != 0) {
				d2_DialogCloseRequested = 1;
			} else if (d2_DialogButtonAction != -1) {
				if (d2_DialogButtonAction == 2) {
					gm_ApplyBardPoemEffect((unsigned char*)
					    ((char*) &((ENTITY_RECORD*) gm_EntitySlotTable)[(int) gm_LocalPlayerSlot]), (int) e2,
					    *(unsigned short*) (elem + 0xac));
					r = 1;
					d2_DialogCloseRequested = 1;
				} else if (d2_DialogButtonAction == 1) {
					d2_DialogCloseRequested = 1;
				}
			}
		} while (main_RunFrameLoop((void*) d2_ShowBardPoemDialog, 0x677c7) != 0);
		if (r == 0) {
			d2_DestroyForm(h);
			d3_EndCameraAndUiMode();
			return;
		}
		d2_DestroyForm(h);
		h = d2_LoadForm(0, 0, "special\\barde2");
		d2_SetForm(h, 0);
		d2_InitWindowBounds(d2_CurrentWindowId);
		d2_CenterDialogWindows(h);
		d2_SetOverlayAnimation(0, 0);
		d2_DialogButtonAction = -1;
		d2_SetForm(h, 1);
		io_AppendText((int) *(unsigned short*) (rec + 0xc));
		d2_SetForm(h, 2);
		idx = d2_CurrentWindowId;
		d2_SetForm(h, 3);
		d2_AddWindowScrollButtons(-1, -1, d2_CurrentWindowId, idx, 0x767);
		*(int*) (g_10161b4 + idx * 0x3cc) = 0x30;
		d2_SetForm(h, 2);
		io_AppendText((int) *(unsigned short*) (rec + 0xc) + 2);
		d2_DialogButtonAction = -1;
		sprintf(buf, "gedichte\\%s.mp3", rec + 0xe);
		do {
			if (io_RightButtonReleased != 0) {
				d2_DialogCloseRequested = 1;
			}
		} while (main_RunFrameLoop((void*) d2_ShowBardPoemDialog, 0x677c7) != 0);
		d2_SetForm(h, 3);
		io_AppendText(str_dollar_C);
		d2_SetForm(h, 1);
		io_AppendText(str_dollar_C);
		io_AppendText(0x1e5c);
		d2_SetForm(h, 2);
		io_AppendText(str_dollar_C);
		*(int*) (g_1016198 + d2_CurrentWindowId * 0x3cc) = 0;
		if (*(int*) rec == 0) {
			io_AppendText(0x1e5e, (int) *(unsigned short*) (rec + 4) + 0x16b7);
		} else if (*(int*) rec == 1) {
			io_AppendText(0x1e5d, (int) *(unsigned short*) (rec + 4) + 0x1ee);
		} else {
			io_AppendText(0x1e5f);
		}
		do {
			if (io_RightButtonReleased != 0) {
				d2_DialogCloseRequested = 1;
			}
		} while (main_RunFrameLoop((void*) d2_ShowBardPoemDialog, 0x677c7) != 0);
		d2_DestroyForm(h);
		d3_EndCameraAndUiMode();
		return;
	}
	io_AppendText(0x1e26);
	do {
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		}
	} while (main_RunFrameLoop((void*) d2_ShowBardPoemDialog, 0x677c7) != 0);
	d2_DestroyForm(h);
	d3_EndCameraAndUiMode();
}
