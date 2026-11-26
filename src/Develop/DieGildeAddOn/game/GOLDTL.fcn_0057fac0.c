


extern char g_7f4ca4[];
#include "Develop/DieGildeAddOn/game/game_player.h"
extern unsigned char g_773d75;

char* __cdecl fcn_00503d10(int);
void __cdecl cm_RequestTransferCurrencyNoKill(int, int, int, int);
int __cdecl cm_SendSellObjekt(int, int, int, int, char, int);

void __cdecl d2_GrantTutorialLumber(int a)
{
	char* e;

	if (a == 0) {
		e = fcn_00503d10(0x155);
		cm_RequestTransferCurrencyNoKill(*(int*) (g_7f4ca4 + *(unsigned short*) ((char*)&g_774970) * 0x21c), -1, 0, 0x2bc0);
		cm_SendSellObjekt(*(int*) (e + 2), -1, 0x155, 3, g_773d75, 0);
	}
}
