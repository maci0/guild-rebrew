typedef struct {
	char pad0[0x4];
	int* f4;
	char pad8[0x98];
	int fa0;
	char pada4[0x8];
	int fac;
} CARD_GAME_ANTE_CTX;

#include "Develop/DieGildeAddOn/game/game_data.h"
extern unsigned char g_773d75;

void __cdecl cm_RequestTransferCurrencyNoKill(int, int, char, int);
typedef struct {
	int state;
	int flag;
	int c;
	int d;
} CARD_GAME_SLOT_STATE;

typedef struct {
	char pad0[0x4];
	int* f4;
	char pad8[0x98];
	int fa0;
	char pada4[0x14];
	short fb8;
} CARD_GAME_SETTLE_CTX;

#include "Develop/client_types.h"
extern slot_1007ce8 g_1007ce8[];

short __cdecl gm_ResolveCardGameWinner(void);
void __cdecl cm_RequestTransferCurrencyNoKill(int, int, char, int);

/* ADDRESS: GOLDTL 0x004a8770 */
void __cdecl gm_CollectCardGameAnte(void)
{
	((CARD_GAME_ANTE_CTX*)g_1007cd4)->fa0 = ((CARD_GAME_ANTE_CTX*)g_1007cd4)->fac * 3;
	cm_RequestTransferCurrencyNoKill(-1, ((CARD_GAME_ANTE_CTX*)g_1007cd4)->f4[1], (*(char*)&g_773d75), ((CARD_GAME_ANTE_CTX*)g_1007cd4)->fac);
}

/* ADDRESS: GOLDTL 0x004a87b0 */
void __cdecl gm_SettleCardGameRound(void)
{
	int i;

	((CARD_GAME_SETTLE_CTX*)g_1007cd4)->fb8 = gm_ResolveCardGameWinner();
	if (((CARD_GAME_SETTLE_CTX*)g_1007cd4)->fb8 == 0)
		cm_RequestTransferCurrencyNoKill(((CARD_GAME_SETTLE_CTX*)g_1007cd4)->f4[1], -1, (*(char*)&g_773d75), ((CARD_GAME_SETTLE_CTX*)g_1007cd4)->fa0);
	for (i = 0; i < 24; i++) {
		((CARD_GAME_SLOT_STATE*)g_1007ce8)[i].state = 3;
		((CARD_GAME_SLOT_STATE*)g_1007ce8)[i].flag = 0;
	}
}
