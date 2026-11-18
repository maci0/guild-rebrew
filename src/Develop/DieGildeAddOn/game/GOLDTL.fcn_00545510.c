#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_types.h"
#include "Develop/DieGildeAddOn/game/he_action.h"



void __cdecl fcn_00546190(char*);

void __cdecl fcn_00545510(void)
{
	int i;

	for (i = 0; i <= he_LastEventSlot && i < 0x400; i++) {
		if (g_77e980[i].kind != 0) {
			fcn_00546190((char*) &g_77e980[i]);
		}
	}
}
