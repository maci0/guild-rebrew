

#include <string.h>

// SIZE 0xf8
struct msg {
	char pad0[4];
	unsigned char kind;
	char pad5[3];
	int owner;
	int target;
	char pad10[0x26];
	unsigned char code;
	char pad37[0x21];
	unsigned char who;
	char pad59[3];
	int other;
	char pad60[0x98];
};

// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"








#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern char* gm_CityEntity;
extern unsigned char gm_ActiveTownIndex;
#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl gm_CompareGameTime(pos14_7f4c00*, pos14_7f4c00*);
void __cdecl d2_CloseActionPopup(char*);
void __cdecl he_FreeAction(char*);
#include "Develop/DieGildeAddOn/game/spiel.h"
int __cdecl d2_CreateActionPopupSlot(char*, int, int, char*, int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
void __cdecl cm_RequestTransferCurrencyNoKill(int, int, unsigned char, int);
void __cdecl cm_SendCopyEntityData(struct msg*);

/* ADDRESS: GOLDDE 0x00536db0 */
void __cdecl he_RunMeisterpruefungExam(char* u)
{
	int t;
	struct msg m;
	int v;

	if (*(int*) (u + 0x70) == -1 || *(int*) (u + 0x70) == -2) {
		if (*(char**) (u + 0x74) != 0) {
			d2_CloseActionPopup(u);
		}
		he_FreeAction(u);
		return;
	}
	if (gm_CompareGameTime(&gm_GameTime, (pos14_7f4c00*) (u + 0x44)) == -1) {
		return;
	}
	switch (*(int*) (u + 0x70)) {
	case 0:
		t = gm_CalcPersonWealth(*(unsigned short*) (u + 8));
		v = (int) (t * 0.05f);
		*(int*) (u + 0xb0) = v;
		if (*(char**) (u + 0x74) == 0) {
			d2_CreateActionPopupSlot(u, 0, 0, "Berufe\\Messagebox_Meisterpruef", 0x5ec);
		}
		if (*(char**) (u + 0x74) == 0) {
			he_FreeAction(u);
			return;
		}
		d2_SetForm(*(int*) (*(char**) (u + 0x74) + 8), 0);
		io_AppendText((int) "$C");
		io_AppendText(0x10b4, *(unsigned short*) (u + 8), v);
		*(int*) (u + 0x70) = 1;
		break;
	case 1:
		if (gm_CompareGameTime(&gm_GameTime, (pos14_7f4c00*) (u + 0x52)) > 0) {
			d2_CloseActionPopup(u);
			he_FreeAction(u);
			return;
		}
		if (*(char**) (u + 0x74) == 0) {
			*(int*) (u + 0x70) = 0;
			return;
		}
		if (g_100f884 != *(int*) (*(char**) (u + 0x74) + 8) || d2_DialogButtonAction == -1) {
			return;
		}
		if (d2_DialogButtonAction == 2) {
			memset(&m, 0, sizeof(m));
			v = *(int*) (u + 0xb0);
			cm_RequestTransferCurrencyNoKill(((ENTITY_RECORD*)gm_CityEntity)->entity_id, ((ENTITY_RECORD*)gm_EntitySlotTable)[*(unsigned short*) (u + 8)].entity_id, gm_ActiveTownIndex, v);
			m.kind = 0x56;
			m.target = -1;
			m.code = 0x11;
			m.who = 4;
			m.other = v;
			m.owner = ((ENTITY_RECORD*)gm_EntitySlotTable)[*(unsigned short*) (u + 8)].entity_id;
			cm_SendCopyEntityData(&m);
			d2_CloseActionPopup(u);
			he_FreeAction(u);
			return;
		}
		if (d2_DialogButtonAction == 1) {
			d2_CloseActionPopup(u);
			he_FreeAction(u);
			return;
		}
		break;
	}
}
