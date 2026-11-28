#include "Develop/DieGildeAddOn/game/entity_record.h"


#include "Develop/DieGildeAddOn/game/game_player.h"
extern char gm_EntitySlotTable[];
extern int g_14abb84;
extern char* txt_TextEntries[];
extern int sv_ClickedObjekt;

void __cdecl d2_ClearStatusTextSlots(void);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_RunZunftLevel2Menu(void);
int __cdecl RegisterStatusText(char*, int, int);
int __cdecl amt_CheckHighOfficeEligibility(char*);
void __cdecl d2_RunGildenkasseDialog(char*);
void __cdecl d2_RunHighOfficePrivilegeDialog(void);

void __cdecl d2_RunZunftMenu(char* e)
{
	int a;
	int b;
	int id;
	char lvl;

	b = 0;
	id = 0;
	lvl = ((char *)&((ENTITY_RECORD_VIEW *)gm_EntitySlotTable)[gm_LocalPlayerSlot])[0x169];
	if (lvl == 0x1e) {
		id = 0x167c;
	} else if (lvl == 0x1f || lvl == 0x21) {
		id = 0x166a;
	} else if (lvl == 0x20) {
		id = 0x1674;
	}
	d2_ClearStatusTextSlots();
	while (main_RunFrameLoop((void*) d2_RunZunftLevel2Menu, 0x67fff) != 0) {
		a = RegisterStatusText("ob_ZUNFTKASSE", g_14abb84, 0x16);
		if (amt_CheckHighOfficeEligibility(((char *)&((ENTITY_RECORD_VIEW *)gm_EntitySlotTable)[gm_LocalPlayerSlot])) != 0 && id != 0) {
			b = RegisterStatusText("contact_ZUNFTLEVEL3", ((int*)txt_TextEntries)[id], 0x16);
		}
		if (sv_ClickedObjekt != 0) {
			if (sv_ClickedObjekt == a) {
				d2_RunGildenkasseDialog(e);
			} else if (sv_ClickedObjekt == b) {
				d2_RunHighOfficePrivilegeDialog();
			}
		}
	}
}
