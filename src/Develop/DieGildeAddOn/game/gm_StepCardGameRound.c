


typedef struct Seq {
	int state;
	char pad4[0xb0 - 4];
	int xb0;
} Seq;
// SIZE 0xb4

#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl gm_CollectCardGameAnte(void);
void __cdecl gm_DealInitialCards(void);
void __cdecl gm_EvaluateCardGameBoard(void);
void __cdecl gm_PickCardGameBet(void);
void __cdecl ai_EvaluateCardGameFold(void);
void __cdecl gm_DealFourthCard(void);
void __cdecl gm_CollectCardGameBets(void);
void __cdecl ai_PlayCardGameTurn(void);
void __cdecl gm_DealFifthCard(void);
void __cdecl gm_SettleCardGameRound(void);

/* ADDRESS: GOLDDE 0x00495950 */
short __cdecl gm_StepCardGameRound(void)
{
	switch (((Seq*)g_1007cd4)->state) {
	case 0:
		((Seq*)g_1007cd4)->state = 1;
		return ((Seq*)g_1007cd4)->xb0 ? 0x10 : 0x21;
	case 1:
		gm_CollectCardGameAnte();
		((Seq*)g_1007cd4)->state++;
		gm_DealInitialCards();
		gm_EvaluateCardGameBoard();
		gm_PickCardGameBet();
		return 0;
	case 2:
		((Seq*)g_1007cd4)->state = 3;
		return (((Seq*)g_1007cd4)->xb0 ? 0 : 0x20) | 9;
	case 3:
		gm_EvaluateCardGameBoard();
		ai_EvaluateCardGameFold();
		((Seq*)g_1007cd4)->state++;
		gm_DealFourthCard();
		gm_CollectCardGameBets();
		return 0;
	case 4:
		((Seq*)g_1007cd4)->state = 5;
		gm_EvaluateCardGameBoard();
		gm_PickCardGameBet();
		return (((Seq*)g_1007cd4)->xb0 ? 0 : 0x20) | 9;
	case 5:
		ai_EvaluateCardGameFold();
		gm_CollectCardGameBets();
		((Seq*)g_1007cd4)->state++;
		return 0x1c;
	case 6:
		ai_PlayCardGameTurn();
		((Seq*)g_1007cd4)->state++;
		return 0x10;
	case 7:
		gm_DealFifthCard();
		((Seq*)g_1007cd4)->state++;
		break;
	case 8:
		gm_EvaluateCardGameBoard();
		((Seq*)g_1007cd4)->state++;
		return (((Seq*)g_1007cd4)->xb0 ? 0 : 0x20) | 9;
	case 9:
		ai_EvaluateCardGameFold();
		gm_CollectCardGameBets();
		((Seq*)g_1007cd4)->state++;
		return 0;
	case 10:
		((Seq*)g_1007cd4)->state = 11;
		gm_SettleCardGameRound();
		return 0x10;
	}
	return 0;
}
