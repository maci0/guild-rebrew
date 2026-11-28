#include "Develop/DieGildeAddOn/game/game_data.h"



typedef struct {
	int a;
	int b;
	int c;
} ACTION_POPUP_SLOT_545930;
// SIZE 0xc

#include "Develop/client_types.h"
extern D2_ACTION_POPUP_SLOT g_77e8c0[16];

void __cdecl d2_CloseActionPopup(int);
void __cdecl d2_DestroyForm(int);

void __cdecl d2_ClearActionPopupSlots(void)
{
	int i;

	for (i = 0; i < 0x10; i++) {
		if (((ACTION_POPUP_SLOT_545930*)g_77e8c0)[i].b != -1) {
			d2_CloseActionPopup(((ACTION_POPUP_SLOT_545930*)g_77e8c0)[i].a);
		}
	}
	d2_DestroyForm(g_77e8a0);
}
