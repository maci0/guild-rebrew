


#include <string.h>
#pragma intrinsic(memset)

#include "Develop/client_types.h"


// SIZE 0xe

#include "Develop/DieGildeAddOn/game/entity_record.h"








extern pos14_7f4c00 gm_GameTime;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern unsigned char gm_ActiveTownIndex;
extern char g_77531c;

char* __cdecl he_StartHandlungSearch(int, int, int, int, int);
char* __cdecl he_fn_Handlung(void);
int __cdecl d2_DispatchTutorialEvent(int, char*, int, int);
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);
void __cdecl cm_SendCopyEntityData(char*);
void __cdecl gm_CalcEntityInventoryStats(char*, char*);
int __cdecl gm_CalcEscortCost(int, int);
void __cdecl cm_RequestTransferCurrencyNoKill(int, int, unsigned char, int);
void __cdecl d2_DispatchTutorialInput(int, char*, int, int);

int __cdecl cm_DispatchCartTransfer(int playerIdx, char* cart, char* origin, char* dest)
{
	int res;
	char* e;
	char msg[0xf8];
	char info[0xb8];

	res = 0;
	for (e = he_StartHandlungSearch(2, 3, *(int*) (cart + 2), 0, 0x11); e != 0; e = he_fn_Handlung()) {
		*(pos14_7f4c00*) (e + 0x52) = (*(pos14_7f4c00*)&gm_GameTime);
		*(int*) (e + 0x70) = -1;
	}
	if (d2_DispatchTutorialEvent(0x24, dest, 0, 0) == 1) {
		memset(msg, 0, sizeof(msg));
		msg[4] = 0xf;
		*(int*) (msg + 8) = ((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[playerIdx].entity_id;
		*(int*) (msg + 0xc) = -1;
		msg[0x36] = 2;
		*(pos14_7f4c00*) (msg + 0x28) = (*(pos14_7f4c00*)&gm_GameTime);
		gm_AddTime((pos14_7f4c00*) (msg + 0x28), 0, 0, 1);
		*(int*) (msg + 0x58) = *(int*) (cart + 2);
		*(int*) (msg + 0x5c) = *(int*) (origin + 1);
		*(int*) (msg + 0x60) = *(int*) (dest + 1);
		*(int*) (msg + 0x78) = cart[0x28];
		g_77531c = (char) *(int*) (msg + 0x78);
		cm_SendCopyEntityData(msg);
		if (cart[0x28] != 0) {
			gm_CalcEntityInventoryStats(cart, info);
			res = gm_CalcEscortCost(*(int*) (info + 0xb0), cart[0x28]);
			cm_RequestTransferCurrencyNoKill(-1, ((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[playerIdx].entity_id, gm_ActiveTownIndex, res);
		}
		if (playerIdx == gm_LocalPlayerSlot) {
			d2_DispatchTutorialInput(0x24, dest, 0, 0);
		}
	}
	return res;
}
