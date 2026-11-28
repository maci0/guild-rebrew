


#include <string.h>

// SIZE 0x10
struct offer {
	int good;
	int b;
	int c;
	char* seller;
};

// SIZE 0xc
struct level {
	int value;
	int b;
	int c;
};

extern unsigned char gm_ActiveTownIndex;

unsigned short __cdecl gm_PickRandomOfferId(int, int);
void __cdecl gm_CheckEntityObjectSlots(char*, int, struct offer*, struct level*);
float __cdecl gm_GetSeasonPrice(int, unsigned char);
void __cdecl cm_RequestTransferCurrencyNoKill(int, int, unsigned char, int);
int __cdecl cm_SendSellObjekt(int, int, int, int, unsigned char, int);

void __cdecl he_RewardRandomItemOrGold0a4(char* h)
{
	struct level lv;
	struct offer o;

	memset(&o, 0, sizeof(o));
	o.good = gm_PickRandomOfferId(3, 6);
	gm_CheckEntityObjectSlots(h, 1, &o, &lv);
	if (o.seller != 0) {
		if (*(int*) (o.seller + 0xe) >= 3) {
			cm_RequestTransferCurrencyNoKill(*(int*) (h + 4), -1, gm_ActiveTownIndex, (int) gm_GetSeasonPrice((unsigned short) o.good, gm_ActiveTownIndex));
		} else {
			cm_SendSellObjekt(*(int*) (h + 4), -1, o.good, 1, gm_ActiveTownIndex, 0);
		}
	} else if (lv.value >= 6) {
		cm_RequestTransferCurrencyNoKill(*(int*) (h + 4), -1, gm_ActiveTownIndex, (int) gm_GetSeasonPrice(o.good, gm_ActiveTownIndex));
	} else {
		cm_SendSellObjekt(*(int*) (h + 4), -1, o.good, 1, gm_ActiveTownIndex, 0);
	}
}
