

#include "Develop/DieGildeAddOn/game/game_data.h"
extern int d2_DialogButtonAction;

void __cdecl d2_CreateActionPopupSlot(char*, int, int, char*, int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText();
void __cdecl d2_CloseActionPopup(char*);
void __cdecl he_FreeAction(char*);

void __cdecl he_RunNeueVorkommenSuchen(char* e)
{
	int id;

	switch (*(int*) (e + 0x70)) {
	case 0:
		id = *(int*) (e + 0xac);
		d2_CreateActionPopupSlot(e, 0, 0, "Misc\\EventMessagebox", 0x5f2);
		d2_SetForm(*(int*) (*(char**) (e + 0x74) + 8), 0);
		io_AppendText("HE_NEUE_VORKOMMEN_SUCHEN_MSG: Ich bin ein Bug !!! %s gefunden!!", id * 2 + 0x9a8);
		*(int*) (e + 0x70) = *(int*) (e + 0x70) + 1;
		return;
	case 1:
		if (g_100f884 != *(int*) (*(char**) (e + 0x74) + 8) || d2_DialogButtonAction == -1 || d2_DialogButtonAction != 2) {
			return;
		}
		/* fall through */
	case -2:
	case -1:
		d2_CloseActionPopup(e);
		he_FreeAction(e);
	}
}
