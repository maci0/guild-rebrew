


extern char gm_EntityIdField[];
#include "Develop/DieGildeAddOn/game/game_player.h"
extern unsigned char gm_ActiveTownIndex;

char* __cdecl gm_FindCityItemHolder(int);
void __cdecl cm_RequestTransferCurrencyNoKill(int, int, int, int);
int __cdecl cm_SendSellObjekt(int, int, int, int, char, int);

void __cdecl d2_GrantTutorialLumber(int a)
{
	char* e;

	if (a == 0) {
		e = gm_FindCityItemHolder(0x155);
		cm_RequestTransferCurrencyNoKill(*(int*) (gm_EntityIdField + *(unsigned short*) ((char*)&gm_LocalPlayerSlot) * 0x21c), -1, 0, 0x2bc0);
		cm_SendSellObjekt(*(int*) (e + 2), -1, 0x155, 3, gm_ActiveTownIndex, 0);
	}
}
