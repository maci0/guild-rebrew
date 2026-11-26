


extern char* g_7e2aa0;
extern char* g_7746c0;
extern int g_7746d4;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char* g_773d78;
extern char* g_7746cc;

void __cdecl fcn_0052f710(void);
void __cdecl sv_ClearObjectSelection(void);
void __cdecl fcn_00471af0(int, int);
int __cdecl fcn_00502cd0(int, int, int, int);
void __cdecl fcn_0057e880(int, int, int, int);
void __cdecl fcn_005ba910(int, int);

void __cdecl d2_OpenMarktstandPanel(int buildingArg, int queryTypeId)
{
	(*(int*)&g_7e2aa0) = 0;
	g_7746c0 = 0;
	fcn_0052f710();
	sv_ClearObjectSelection();
	g_7746d4 = 1;
	if (g_6a25b8 != -1) {
		fcn_00471af0(g_6a25b8, 0);
	}
	(*(int*)&g_7746cc) = fcn_00502cd0(*(int*) (g_773d78 + 0x5d), 1, 0, queryTypeId);
	if ((*(int*)&g_7746cc) != 0) {
		fcn_0057e880(0x17, (*(int*)&g_7746cc), 0, queryTypeId);
		while ((*(int*)&g_7746cc) != 0) {
			g_7746d4 = 1;
			fcn_005ba910(buildingArg, 9);
		}
	}
	fcn_0057e880(0x18, (*(int*)&g_7746cc), 0, queryTypeId);
	fcn_0057e880(0x17, (*(int*)&g_7746cc), 1, queryTypeId);
	(*(int*)&g_7746cc) = 0;
	if (g_6a25b8 != -1) {
		fcn_00471af0(g_6a25b8, 1);
	}
}
