
#include "Develop/DieGildeAddOn/game/building_prototype.h"

extern unsigned char* lpGebaeudePROT;
#include "Develop/DieGildeAddOn/game/game_player.h"
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern char g_6ac690[];

int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl gm_CalculateGebaeudeValue(unsigned char*, int);
void __cdecl gm_CollectGebaeudeUpgrades(unsigned char* e);
char* __cdecl gm_SearchTable67(int id);
void __cdecl d2_SetForm(int, int);
int __cdecl gm_GetEntityMood(unsigned char* e);
int __cdecl io_AppendText();
int __cdecl d2_GetWindowListItem(int, int, int);
void __cdecl d2_SetElementEnabled(int i, int flag);
void __cdecl d2_SetFormVisibility(int k, int flag);
void __cdecl d2_RunTechTreeDialog(unsigned char*, int);
void __cdecl d2_ShowRenovationDialog(unsigned char*);
void __cdecl d2_RunRoomUpgradeDialog(unsigned char*);
void __cdecl d2_RunBuildingUpgradeDialog(unsigned char*);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);

/* ADDRESS: GOLDDE 0x005a6e20 */
void __cdecl d2_ShowGebaeudeOptions(unsigned char* p)
{
	int h1;
	int h2;
	int last;
	int r;
	int h3;
	int id;
	unsigned char* tbl;
	int h4;
	int redraw;
	int d;
	int k;
	int fl;
	char* t;

	last = -1;
	redraw = 1;
	h1 = -1;
	h2 = -1;
	h3 = -1;
	h4 = -1;
	tbl = (unsigned char*)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[p[0]];
	id = *(int*) (p + 1);
	d = d2_LoadForm(0, 0, g_6ac690);
	d2_CenterDialogWindows(d);
	d2_SetOverlayAnimation(0, 0);
	r = gm_CalculateGebaeudeValue(p, (char) p[0x5c]);
	gm_CollectGebaeudeUpgrades(p);
	do {
		t = gm_SearchTable67(id);
		if ((*(unsigned short*) (p + 0x5a) & 0x400) != 0 || t == 0) {
			d2_DialogCloseRequested = 1;
		}
		fl = *(unsigned short*) (p + 0x5a);
		if (fl != last) {
			redraw = 1;
		}
		last = fl;
		if (redraw != 0) {
			d2_SetForm(d, 1);
			k = (int) (9 - gm_GetEntityMood(p) / 10 + 0.5);
			if (*(unsigned short*) (p + 0x27) != gm_LocalPlayerSlot && *(unsigned short*) (p + 0x25) != gm_LocalPlayerSlot) {
				io_AppendText(0x17a0, *(unsigned short*) (p + 0x25), p, k + 0x17b1, k + 0x17bb, r);
				if (*tbl == 1) {
					io_AppendText(0x17a2, p[0x65]);
				}
			}
			io_AppendText(0x179e, p, k + 0x17b1, k + 0x17bb, r);
			if (*tbl == 1) {
				io_AppendText(0x17a2, p[0x65]);
			}
			h2 = d2_GetWindowListItem(d, 1, io_AppendText(0x17a5));
			if (*tbl != 3) {
				h1 = d2_GetWindowListItem(d, 1, io_AppendText(0x17ac));
			}
			if (tbl[0x21] > 1) {
				h3 = d2_GetWindowListItem(d, 1, io_AppendText(0x17a8));
			}
			h4 = d2_GetWindowListItem(d, 1, io_AppendText(0x17ab));
			redraw = 0;
		}
		if ((p[0x5a] & 4) != 0) {
			if (h1 != -1) {
				d2_SetElementEnabled(h1, 0);
			}
			if (h2 != -1) {
				d2_SetElementEnabled(h2, 0);
			}
		}
		if (h4 != -1) {
			if ((p[0x5a] & 0x40) != 0) {
				d2_SetElementEnabled(h4, 0);
			}
			else {
				d2_SetElementEnabled(h4, 1);
			}
		}
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		}
		if (d2_DialogButtonAction != -1) {
			if (d2_CurrentElementId == h1) {
				d2_SetFormVisibility(d, 0);
				d2_RunTechTreeDialog(p, 0xfd);
				d2_SetFormVisibility(d, 1);
			}
			else if (d2_CurrentElementId == h2) {
				d2_SetFormVisibility(d, 0);
				d2_ShowRenovationDialog(p);
				d2_SetFormVisibility(d, 1);
				redraw = 1;
			}
			else if (d2_CurrentElementId == h3) {
				d2_SetFormVisibility(d, 0);
				d2_RunRoomUpgradeDialog(p);
				d2_SetFormVisibility(d, 1);
				redraw = 1;
			}
			else if (d2_CurrentElementId == h4) {
				d2_SetFormVisibility(d, 0);
				d2_RunBuildingUpgradeDialog(p);
				d2_SetFormVisibility(d, 1);
				redraw = 1;
			}
		}
	} while (main_RunFrameLoop(d2_ShowGebaeudeOptions, 0x677c7) != 0);
	d2_DestroyForm(d);
	g_7746f8 = 0;
}
