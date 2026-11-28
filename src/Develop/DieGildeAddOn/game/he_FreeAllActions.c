#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/client_types.h"
#include "Develop/DieGildeAddOn/game/he_action.h"



void __cdecl he_FreeAction(char*);

void __cdecl he_FreeAllActions(void)
{
	int i;

	for (i = 0; i <= he_LastEventSlot && i < 0x400; i++) {
		if (he_ActionSlots[i].kind != 0) {
			he_FreeAction((char*) &he_ActionSlots[i]);
		}
	}
}
