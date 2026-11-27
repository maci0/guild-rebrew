
#include "Develop/DieGildeAddOn/game/building_prototype.h"

extern unsigned char* lpGebaeudePROT;
extern int d2_CurrentWindowId;
#include "Develop/DieGildeAddOn/game/game_player.h"
#include "Develop/DieGildeAddOn/game/entity_record.h"
extern char s_6a99f4[];

int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
void __cdecl d2_AddElementToWindow(int, int, int, int);
int __cdecl gm_CalcBuildingCost(void*, int);

int __cdecl d2_CreateGebaeudeTooltip(int i)
{
	char roman[7][4] = { "", "I", "II", "III", "IV", "V", "VI" };
	char* rec;
	int dlg;

	rec = ((char*)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[i]);
	dlg = fcn_00470820(0, 0, s_6a99f4);
	d2_CenterDialogWindows(dlg);
	d2_SetForm(0, 1);
	if (rec[0] != 10) {
		io_AppendText(0x27, i * 14 + 0x48e, roman[(unsigned char) rec[0x247]]);
	} else {
		io_AppendText(i * 14 + 0x48e);
	}
	d2_SetForm(0, 2);
	d2_AddElementToWindow(0, 0, i + 0x427, d2_CurrentWindowId);
	io_AppendText(i * 14 + 0x48f);
	if (rec[0] != 10) {
		d2_SetForm(0, 3);
		io_AppendText(0x2a, roman[(unsigned char) rec[0x247]]);
		io_AppendText(0x28, gm_CalcBuildingCost(((char*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[g_774970]), i));
		io_AppendText(0x29, *(int*) (rec + 0x243));
	}
	return dlg;
}
