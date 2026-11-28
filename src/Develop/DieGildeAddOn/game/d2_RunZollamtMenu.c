


extern int d2_SelectedEntityUiFlags;
extern int sv_ClickedObjekt;
extern int g_14abcbc;
extern int g_14abcd8;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_14abce4;
extern char s_6ab3a0[];
extern char s_6ab394[];
extern char s_6aa34c[];
extern char s_6a9924[];
extern char s_6ab384[];
extern char s_6ab368[];

void __cdecl d2_ClearStatusTextSlots(void);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl RegisterStatusText(char*, int, int);
char* __cdecl gm_QueryEntities(int, int, int, int, int);
void __cdecl d2_ShowPersonalbuch(char*, char*);
void __cdecl d2_ShowProductionSelection(char*);
void __cdecl d2_SelectPatrolTarget(char*);
void __cdecl d2_StartZollkasseTargetSelect(char*);
void __cdecl d2_OpenMeisterbriefDialog(char*);

/* ADDRESS: GOLDDE 0x00594720 */
void __cdecl d2_RunZollamtMenu(char* building)
{
	int a;
	int b;
	int c;
	int d;
	int e;

	a = 0;
	b = 0;
	e = 0;
	c = 0;
	d = 0;
	d2_ClearStatusTextSlots();
	if (main_RunFrameLoop((void*) d2_RunZollamtMenu, 0x67fff) != 0) {
		do {
			if (d2_SelectedEntityUiFlags & 0x200) {
				a = RegisterStatusText(s_6ab3a0, g_14abcbc, 0x16);
				b = RegisterStatusText(s_6ab394, g_14abcd8, 0x16);
				c = RegisterStatusText(s_6aa34c, g_14a7b50, 0xc);
				d = RegisterStatusText(s_6a9924, g_14a7d28, 0x16);
				if (gm_QueryEntities(*(int*) (building + 0x5d), 2, 6, 0, 0x147) != 0) {
					e = RegisterStatusText(s_6ab384, g_14abce4, 0x16);
				}
				else if (gm_QueryEntities(*(int*) (building + 0x5d), 2, 6, 0, 0x148) != 0) {
					e = RegisterStatusText(s_6ab368, g_14abce4, 0x16);
				}
			}
			if ((d2_SelectedEntityUiFlags & 0x200) && sv_ClickedObjekt != 0) {
				if (sv_ClickedObjekt == c) {
					d2_ShowPersonalbuch(building, s_6aa34c);
				}
				else if (sv_ClickedObjekt == a) {
					d2_ShowProductionSelection(building);
				}
				else if (sv_ClickedObjekt == b) {
					d2_SelectPatrolTarget(building);
				}
				else if (sv_ClickedObjekt == e) {
					d2_StartZollkasseTargetSelect(building);
				}
				else if (sv_ClickedObjekt == d) {
					d2_OpenMeisterbriefDialog(building);
				}
			}
		} while (main_RunFrameLoop((void*) d2_RunZollamtMenu, 0x67fff) != 0);
	}
}
