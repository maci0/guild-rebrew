#include "Develop/DieGildeAddOn/game/game_player.h"
extern int d2_CurrentWindowId;
extern int g_14ce8e0;
#include "client_dialog_state.h"
extern int g_100f1dc;
extern int d2_CurrentElementId;
extern char* g_1015ea0;
#include "Develop/DieGildeAddOn/game/entity_record.h"

typedef struct {
	int out0;
	int out1;
	int out2;
	int ids[32];
	char tail[0x180];
} Rec_5c9850;

int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText();
int __cdecl fcn_005340f0(int);
int __cdecl fcn_005c9450(char*, int, int*);
int __cdecl d2_GetFormWindow(int, int);
void __cdecl fcn_00533f40(int, int, int, int, int, int*, int*, int*);
int __cdecl d2_ShowBuildingTurnSummary(int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);
#include "Develop/Units/d2.v1/d2_gui.h"
/* ADDRESS: GOLDTL 0x005c9850 */
void __cdecl d2_ShowGebaeudeList(void)
{
	Rec_5c9850 rec;
	char* table;
	int obj;
	int n;
	int j;

	table = (char*)&((ENTITY_RECORD*)g_7f4ca0)[(unsigned short) g_774970];
	obj = fcn_00470820(0, 0, (char*) 0x6ac94c);
	d2_CenterDialogWindows(obj);
	d2_SetForm(obj, 0);
	fcn_005340f0(d2_CurrentWindowId);
	d2_SetForm(obj, 1);
	io_AppendText(0xb2);
	d2_SetForm(obj, 2);
	n = fcn_005c9450(table, 0x80, rec.ids);
	d2_SetForm(obj, 0);
	fcn_00533f40(0x206, 0x167, d2_CurrentWindowId, d2_GetFormWindow(obj, 2), 0x100,
	    &rec.out1, &rec.out0, &rec.out2);
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		} else if (g_100f1dc != -1) {
			for (j = 0; j < n; j++) {
				if (d2_CurrentElementId == rec.ids[j]) {
					d2_ShowBuildingTurnSummary(*(int*) (&((D2_CONTROL_TL*) g_1015ea0)[d2_CurrentElementId].associated_object));
				}
			}
		}
	} while (main_RunFrameLoop(d2_ShowGebaeudeList, 0x657c7) != 0);
	d2_DestroyForm(obj);
}
