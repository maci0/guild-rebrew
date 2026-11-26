#include "client_types.h"
extern int g_6a25b4;
#include "Develop/DieGildeAddOn/game/game_data.h"




void __cdecl d2_DestroyForm(int);

void __cdecl fcn_00471af0(int, int);
void __cdecl fcn_0052f7b0(void);

void __cdecl d2_RestoreHudAfterDialog(void)
{
	d2_DestroyForm(g_6a25b4);
	g_6a25b4 = -1;
	ResetDisplayCounters();
	if (g_6a25b8 != -1) {
		fcn_00471af0(g_6a25b8, 1);
	}
	fcn_0052f7b0();
}
