#include "Develop/DieGildeAddOn/game/building_prototype.h"


// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"










extern unsigned char* lpGebaeudePROT;
extern char g_868060[];
#include "Develop/DieGildeAddOn/game/game_player.h"
extern unsigned char g_773d75;
extern int g_100f1dc;
extern int g_14ce8e0;
#include "client_dialog_state.h"
extern int d2_CurrentElementId;
extern char g_6aae08[];

unsigned char* __cdecl fcn_00502cd0(int, int, int, int, int);
int __cdecl gm_SumQueryEntryValues(int a, char b);
int __cdecl gm_AccumulateTyped2(ENTITY_RECORD* entity);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText();
void __cdecl d2_ClampAmountToRange(int, int, int, int*);
int __cdecl gm_AmountToUnits(int a, unsigned char b);
int __cdecl d2_GetWindowListItem(int, int, int);
#include "Develop/Units/d2.v1/d2_gui.h"
int __cdecl d2_GetControlValue(int slot);
int __cdecl fcn_0050b750(int a, unsigned char k);
int __cdecl gm_CheckEntityStock(ENTITY_RECORD*, int, unsigned char);
void __cdecl cm_RequestMoveCredits(int, int, unsigned char, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d3_EndCameraAndUiMode(void);
void __cdecl d2_DestroyForm(int);

void __cdecl d2_RunGildenkasseDialog(unsigned char* p)
{
	int h2;
	int n;
	int h1;
	unsigned char* obj;
	unsigned char* tbl;
	int acc;
	int ok;
	int d;
	int b;
	int v;

	h2 = -1;
	h1 = -1;
	b = 0;
	tbl = (unsigned char*)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[p[0]];
	obj = fcn_00502cd0(*(int*) (p + 0x5d), 2, 6, 0, 0x142);
	n = gm_SumQueryEntryValues(*(int*) (obj + 0x14), g_773d75);
	acc = gm_AccumulateTyped2(((ENTITY_RECORD*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[g_774970]));
	if ((((BUILDING_PROTOTYPE*)tbl)->category) == 0x17 && ((ENTITY_RECORD_VIEW*)g_7f4ca0)[g_774970].grade == 0x1e) {
		ok = 1;
	}
	else if ((((BUILDING_PROTOTYPE*)tbl)->category) == 0x18 && ((ENTITY_RECORD_VIEW*)g_7f4ca0)[g_774970].grade == 0x1f) {
		ok = 1;
	}
	else if ((((BUILDING_PROTOTYPE*)tbl)->category) == 0x19 && ((ENTITY_RECORD_VIEW*)g_7f4ca0)[g_774970].grade == 0x20) {
		ok = 1;
	}
	else if ((((BUILDING_PROTOTYPE*)tbl)->category) == 0x1a && ((ENTITY_RECORD_VIEW*)g_7f4ca0)[g_774970].grade == 0x21) {
		ok = 1;
	}
	else {
		ok = 0;
	}
	d = fcn_00470820(0, 0, g_6aae08);
	d2_CenterDialogWindows(d);
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(d, 1);
	io_AppendText(0x1a1a, n);
	if (ok != 0) {
		int col;

		b = io_AppendText(0x1a1b, *(unsigned short*) (((char(*)[0x2f4])g_868060)[g_773d75] + 0x54) * 2 + 0x9a8);
		d2_ClampAmountToRange(0x640, acc, 0x20, &col);
		d2_SetElementValue(d2_GetWindowListItem(d, 1, b), gm_AmountToUnits(0x640, g_773d75), gm_AmountToUnits(col, g_773d75), gm_AmountToUnits(0x640, g_773d75));
		h1 = d2_GetWindowListItem(d, 1, b + 1);
		h2 = d2_GetWindowListItem(d, 1, b + 2);
	}
	g_100f1dc = -1;
	while (main_RunFrameLoop(d2_RunGildenkasseDialog, 0x677c7) != 0) {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (ok != 0 && g_100f1dc != -1) {
			if (d2_CurrentElementId == h1) {
				v = d2_GetControlValue(d2_GetWindowListItem(d, 1, b));
				v = fcn_0050b750(v, g_773d75);
				if (gm_CheckEntityStock(((ENTITY_RECORD*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[g_774970]), v, g_773d75) != 0) {
					cm_RequestMoveCredits(*(int*) (obj + 2), ((ENTITY_RECORD_VIEW*)g_7f4ca0)[g_774970].entity_id, g_773d75, v);
					g_774654 = 1;
				}
			}
			else if (d2_CurrentElementId == h2) {
				g_774654 = 1;
			}
		}
	}
	d3_EndCameraAndUiMode();
	d2_DestroyForm(d);
}
